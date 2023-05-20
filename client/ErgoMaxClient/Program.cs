
using System.Diagnostics;
using System.Text;
using ErgoMaxRawHID;
using System.Management;
using System.Threading;

namespace ErgoMaxClient;

internal static class Program
{
    class TaskTray : Form
    {
        private HidClient hid;
        private ToolStripMenuItem mi_connect, mi_exit;

        private AudioVolume volume;

        public TaskTray()
        {
            ShowInTaskbar = false;

            NotifyIcon icon = new NotifyIcon();
            icon.Icon = Properties.Resources.mainicon;
            icon.Visible = true;
            icon.Text = "ErgoMax TNK Remix";
            ContextMenuStrip menu = new ContextMenuStrip();

            mi_connect = new ToolStripMenuItem();
            mi_connect.Text = "Connect";
            mi_connect.Click += new EventHandler(OnClickConnect);
            menu.Items.Add(mi_connect);

            mi_exit = new ToolStripMenuItem();
            mi_exit.Text = "Exit";
            mi_exit.Click += new EventHandler(OnClickExit);
            menu.Items.Add(mi_exit);

            volume = new AudioVolume();
            volume.VolumeChanged += OnVolumeChanged;
            volume.Begin();


            icon.ContextMenuStrip = menu;

            hid = new HidClient();
            hid.Request += OnRequest;
            hid.vendorId = 0x746E;
            hid.productId = 0x0002;

            Connect();
        }

        private void OnVolumeChanged(int vol, bool mute)
        {
            string msg;
            if(mute == true) {
                msg = "Volume : Muted";
            } else {
                msg = "Volume : " + string.Format("{0,3}%", vol);
            }
            hid.SendMessage(msg);
        }


        private string GetDateText()
        {
            var now = DateTime.Now;
            return now.ToShortDateString() + " " + now.ToShortTimeString();
        }

        private void SendTemporaryMessage(string msg, bool unicode = false)
        {
            if(unicode == false) {
                hid.SendMessage(msg);
            } else {
                hid.SendUnicode(msg);
            }
            hid.SendClear(5000);
        }

        private void SendCurrentDate()
        {
            var now = DateTime.Now;
            string datestr = now.ToShortDateString() + " " + now.ToShortTimeString();
            SendTemporaryMessage(datestr);
        }

        private async void SendCPUState()
        {
            await Task.Run(() => {
                string msg = "CPU usage  ";
                try {
                    float cpuUsage = 0.0f;
                    var searcher = new ManagementObjectSearcher("select LoadPercentage from CIM_Processor");
                    foreach (var obj in searcher.Get()) {
                        var val = obj["LoadPercentage"];
                        if(val != null) {
                            cpuUsage = Convert.ToSingle(val.ToString());
                        }
                    }

                    msg += string.Format("{0,3}%", cpuUsage);
                } catch {
                    msg += "  ---%";
                }
                SendTemporaryMessage(msg);
            });

        }

        private async void SendGPUState()
        {
            await Task.Run(() => {
                string msg = "GPU usage  ";
                try {
                    var category = new PerformanceCounterCategory("GPU Engine");
                    var counterNames = category.GetInstanceNames();
                    var gpuCounters = new List<PerformanceCounter>();
                    var result = 0f;

                    foreach (string counterName in counterNames) {
                        if (counterName.EndsWith("engtype_3D")) {
                            foreach (PerformanceCounter counter in category.GetCounters(counterName)) {
                                if (counter.CounterName == "Utilization Percentage") {
                                    gpuCounters.Add(counter);
                                }
                            }
                        }
                    }

                    gpuCounters.ForEach(x =>
                    {
                        _ = x.NextValue();
                    });

                    Thread.Sleep(500);

                    gpuCounters.ForEach(x =>
                    {
                        result += x.NextValue();
                    });
                    msg += string.Format("{0,3}%", Math.Floor(result + 0.5f));
                } catch {
                    msg += "  ---%";
                }
                SendTemporaryMessage(msg);
            });

        }

        private void OnRequest(byte command, byte[] data)
        {
            switch (command) {
            case 0: SendCurrentDate(); break;
            case 1: SendCPUState(); break;
            case 2: SendGPUState(); break;
            }
        }

        private void Connect()
        {
            if(hid.IsConnected == true) {
                hid.Disconnect();
                mi_connect.Text = "Connect";
            } else {
                hid.Connect();
                mi_connect.Text = "Disconnect";
            }
        }

        private void OnClickExit(object sender, EventArgs e)
        {
            volume.End();
            Application.Exit();
        }

        private void OnClickConnect(object sender, EventArgs e)
        {

        }
    }


    static void Main()
    {
        AudioVolume av = new AudioVolume();
        av.Begin();

        ApplicationConfiguration.Initialize();
        var tt = new TaskTray();
        Application.Run();
    }
}
