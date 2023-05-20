
using HidLibrary;
using System;
using System.IO;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading;
using System.Windows;
using System.Threading.Tasks;
using System.Collections.Generic;
using System.Windows.Markup;
using System.Security.Cryptography;

namespace ErgoMaxRawHID;

public enum HidCommand : byte
{
    SetKeyboardValue = 0x03,
    SetMessage = 0x05,
    SetBitmap = 0x06,
    UpdateMessageArea = 0x07,
    ClearMessage = 0x08,

    RequestCommand = 0x09
}

public class HidClient
{
    private HidDevice usb;
    private CancellationTokenSource cancel_token;

    public int vendorId { get; set; }
    public int productId { get; set; }

    public string BitmapFontPath
    {
        get;
        set;
    } = @"unscii-16-full.dat";

    public bool IsConnected
    {
        get { return (usb != null && usb.IsConnected); }
    }

    public void Connect()
    {
        // VID/PIDで複数取得出来るのでさらにUsagePageとUsageでフィルタリングして最初の一つを使う
        usb = HidDevices.Enumerate(vendorId, productId)
            .Where(x => (UInt16)x.Capabilities.UsagePage == 0xFF60 && x.Capabilities.Usage == 0x61)
            .FirstOrDefault();

        if (usb == null) return;

        usb.OpenDevice();

        if (!usb.IsConnected) return;

        cancel_token = new CancellationTokenSource();

        SendMessage("Client Ver 0.1");

        ReadReportTask();
    }


    public delegate void RequestCommand(byte command, byte[] data);
    public event RequestCommand Request;

    private SemaphoreSlim clearwait = null;

    private async void ReadReportTask()
    {
        await Task.Run(() => {
            while (cancel_token.IsCancellationRequested == false) {
                if (IsConnected == false) break;

                var data = usb.ReadReport();

                HidCommand cmd = (HidCommand)data.Data[0];
                if(cmd == HidCommand.RequestCommand) {
                    Request(data.Data[1], data.Data[2..]);
                }else if(cmd == HidCommand.SetKeyboardValue) {
                    cmd = (HidCommand)data.Data[1];
                    if(cmd == HidCommand.ClearMessage) {
                        if (clearwait != null) {
                            clearwait.Release();
                            clearwait.Dispose();
                            clearwait = null;
                        }
                    }

                }
            }
        });
    }


    public void SendBitmap(int pos, byte[] bmp)
    {
        // 8x8ピクセル四方 x 上下2ブロック
        // 通常、2値ビットマップは横方向8bit単位だが、OLEDでは縦方向8bit単位で処理するため、あらかじめ変換しておく
        byte[] nbmp = new byte[16];
        for (int b = 0; b < 2; b++) {
            for (int x = 0; x < 8; x++) {
                byte v = 0x00;
                for (int y = 0; y < 8; y++) {
                    int dy = b * 8 + y;
                    byte c = (byte)((bmp[dy] >> (7 - x)) & 0x01);
                    v |= (byte)(c << y);
                }
                nbmp[b * 8 + x] = v;
            }
        }

        var send_report = new HidReport(32);
        send_report.ReportId = 0;
        send_report.Data[0] = (byte)HidCommand.SetKeyboardValue;
        send_report.Data[1] = (byte)HidCommand.SetBitmap;

        send_report.Data[2] = (byte)pos; // 表示する位置

        Array.Copy(nbmp, 0, send_report.Data, 3, nbmp.Length);
        usb.WriteReport(send_report);
    }

    Dictionary<int, byte[]> chardata = null;

    public void SendMessage(string text)
    {
        if (IsConnected == false) return;

        var send_report = new HidReport(32);
        send_report.ReportId = 0;
        send_report.Data[0] = (byte)HidCommand.SetKeyboardValue;
        send_report.Data[1] = (byte)HidCommand.SetMessage;

        byte[] abin = Encoding.ASCII.GetBytes(text);
        Array.Copy(abin, 0, send_report.Data, 2, Math.Min(16, abin.Length));
        usb.WriteReport(send_report);

    }

    public async void SendUnicode(string text)
    {
        if (IsConnected == false) return;

        if (chardata == null) {
            chardata = new Dictionary<int, byte[]>();
            var file = File.OpenRead(BitmapFontPath);
            var br = new BinaryReader(file);
            while (file.Position < file.Length) {
                int code = br.ReadInt32();
                int len = br.ReadByte();
                byte[] cdata = br.ReadBytes(len);
                chardata.Add(code, cdata);
            }
        }

        SendClear(0);

        clearwait = new SemaphoreSlim(0, 1);
        await clearwait.WaitAsync();

        byte[] data;
        int pos = 0;
        foreach (var c in text) {
            if (chardata.TryGetValue(c, out data) == false) {
                pos++;
                continue;
            }

            int charsz = data.Length / 16;
            if (pos + charsz > 16) break;

            if (charsz == 1) {
                SendBitmap(pos, data);
                pos++;
            } else {
                // 32byte送信制限のため、ワイド文字は8x16ピクセル単位で個別に送信
                byte[] hdata = new byte[16];

                for (int i = 0; i < charsz; i++) {
                    for (int y = 0; y < 16; y++) {
                        hdata[y] = data[y * charsz + i];
                    }

                    SendBitmap(pos, hdata);
                    pos++;
                }
            }
        }


        // 残りは空白で埋める
        data = new byte[16];
        for(int i = text.Length; i < 16; i++) {
            SendBitmap(i, data);
        }

        SendUpdate();
    }

    public void SendUpdate()
    {
        var send_report = new HidReport(32);
        send_report.ReportId = 0;
        send_report.Data[0] = (byte)HidCommand.SetKeyboardValue;
        send_report.Data[1] = (byte)HidCommand.UpdateMessageArea;
        usb.WriteReport(send_report);
    }

    public async void SendClear(int delay)
    {
        if (delay > 0) {
            await Task.Delay(delay);
        }

        var send_report = new HidReport(32);
        send_report.ReportId = 0;
        send_report.Data[0] = (byte)HidCommand.SetKeyboardValue;
        send_report.Data[1] = (byte)HidCommand.ClearMessage;
        send_report.Data[2] = 0;
        usb.WriteReport(send_report);
    }


    public void Disconnect()
    {
        if (IsConnected) {
            if (cancel_token != null) cancel_token.Cancel();
            usb.CloseDevice();
        }
    }
}
