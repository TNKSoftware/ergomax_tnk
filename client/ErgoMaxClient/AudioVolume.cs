using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using Windows.Foundation.Collections;
using static ErgoMaxClient.AudioVolume;

namespace ErgoMaxClient;

internal class AudioVolume : IAudioEndpointVolumeCallback
{
    [ComImport]
    [Guid("BCDE0395-E52F-467C-8E3D-C4579291692E")]
    internal class MMDeviceEnumerator
    {
    }

    private enum DataFlow
    {
        Render,
        Capture,
        All
    }

    private enum Role
    {
        Console,
        Multimedia,
        Communications,
        All
    }


    [Guid("A95664D2-9614-4F35-A746-DE8DB63617E6"), InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    private interface IMMDeviceEnumerator
    {
        int NotImpl();

        [PreserveSig]
        int GetDefaultAudioEndpoint(DataFlow dataFlow, Role role, out IMMDevice ppDevice);
    }

    [Guid("D666063F-1587-4E43-81F1-B948E807363F"), InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    private interface IMMDevice
    {
        [PreserveSig]
        int Activate(ref Guid iid, int dwClsCtx, IntPtr pActivationParams, [MarshalAs(UnmanagedType.IUnknown)] out object ppInterface);
    }

    [ComImport]
    [Guid("D666063F-1587-4E43-81F1-B948E807363F")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAudioEndpointVolumeCallback
    {
        void OnNotify([In]AUDIO_VOLUME_NOTIFICATION_DATA pNotifyData);
    }

    [Guid("5CDF2C82-841E-4546-9722-0CF74078229A"), InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    public interface IAudioEndpointVolume
    {
        [PreserveSig]
        int RegisterControlChangeNotify([In]IAudioEndpointVolumeCallback pNotify);

        [PreserveSig]
        int UnregisterControlChangeNotify([In] IAudioEndpointVolumeCallback pNotify);

        [PreserveSig]
        int GetChannelCount(
            [Out][MarshalAs(UnmanagedType.U4)] out UInt32 channelCount);

        [PreserveSig]
        int SetMasterVolumeLevel(
            [In][MarshalAs(UnmanagedType.R4)] float level,
            [In][MarshalAs(UnmanagedType.LPStruct)] Guid eventContext);

        [PreserveSig]
        int SetMasterVolumeLevelScalar(
            [In][MarshalAs(UnmanagedType.R4)] float level,
            [In][MarshalAs(UnmanagedType.LPStruct)] Guid eventContext);

        [PreserveSig]
        int GetMasterVolumeLevel(
            [Out][MarshalAs(UnmanagedType.R4)] out float level);

        [PreserveSig]
        int GetMasterVolumeLevelScalar(
            [Out][MarshalAs(UnmanagedType.R4)] out float level);

        [PreserveSig]
        int SetChannelVolumeLevel(
            [In][MarshalAs(UnmanagedType.U4)] UInt32 channelNumber,
            [In][MarshalAs(UnmanagedType.R4)] float level,
            [In][MarshalAs(UnmanagedType.LPStruct)] Guid eventContext);

        [PreserveSig]
        int SetChannelVolumeLevelScalar(
            [In][MarshalAs(UnmanagedType.U4)] UInt32 channelNumber,
            [In][MarshalAs(UnmanagedType.R4)] float level,
            [In][MarshalAs(UnmanagedType.LPStruct)] Guid eventContext);

        [PreserveSig]
        int GetChannelVolumeLevel(
            [In][MarshalAs(UnmanagedType.U4)] UInt32 channelNumber,
            [Out][MarshalAs(UnmanagedType.R4)] out float level);

        [PreserveSig]
        int GetChannelVolumeLevelScalar(
            [In][MarshalAs(UnmanagedType.U4)] UInt32 channelNumber,
            [Out][MarshalAs(UnmanagedType.R4)] out float level);

        [PreserveSig]
        int SetMute(
            [In][MarshalAs(UnmanagedType.Bool)] Boolean isMuted,
            [In][MarshalAs(UnmanagedType.LPStruct)] Guid eventContext);

        [PreserveSig]
        int GetMute(
            [Out][MarshalAs(UnmanagedType.Bool)] out Boolean isMuted);

        [PreserveSig]
        int GetVolumeStepInfo(
            [Out][MarshalAs(UnmanagedType.U4)] out UInt32 step,
            [Out][MarshalAs(UnmanagedType.U4)] out UInt32 stepCount);

        [PreserveSig]
        int VolumeStepUp(
            [In][MarshalAs(UnmanagedType.LPStruct)] Guid eventContext);

        [PreserveSig]
        int VolumeStepDown(
            [In][MarshalAs(UnmanagedType.LPStruct)] Guid eventContext);

        [PreserveSig]
        int QueryHardwareSupport(
            [Out][MarshalAs(UnmanagedType.U4)] out UInt32 hardwareSupportMask);

        [PreserveSig]
        int GetVolumeRange(
            [Out][MarshalAs(UnmanagedType.R4)] out float volumeMin,
            [Out][MarshalAs(UnmanagedType.R4)] out float volumeMax,
            [Out][MarshalAs(UnmanagedType.R4)] out float volumeStep);
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct AUDIO_VOLUME_NOTIFICATION_DATA
    {
        public Guid guidEventContext;
        public bool bMuted;
        public float fMasterVolume;
        public uint nChannels;
        public float afChannelVolumes;
    }

    private IMMDeviceEnumerator enumerator;
    private IMMDevice device;
    private IAudioEndpointVolume volume;

    public void Begin()
    {
        // MMDeviceEnumeratorオブジェクトを作成する
        enumerator = (IMMDeviceEnumerator)(new MMDeviceEnumerator());
        enumerator.GetDefaultAudioEndpoint(DataFlow.Render, Role.Multimedia, out device);

        Guid IID_IAudioEndpointVolume = typeof(IAudioEndpointVolume).GUID;
        device.Activate(ref IID_IAudioEndpointVolume, 0, IntPtr.Zero, out object vo);
        
        volume = vo as IAudioEndpointVolume;
        volume.RegisterControlChangeNotify(this);
    }

    public void End()
    {
        if (volume != null) {
            Marshal.ReleaseComObject(volume);
        }


        if (device != null) Marshal.ReleaseComObject(device);
        if (enumerator != null) Marshal.ReleaseComObject(enumerator);
    }

    public delegate void VolumeChangedHandler(int vol, bool mute);
    public event VolumeChangedHandler VolumeChanged;

    public void OnNotify(AUDIO_VOLUME_NOTIFICATION_DATA pNotifyData)
    {
        VolumeChanged?.Invoke((int)(pNotifyData.fMasterVolume * 100.0f + 0.5f), pNotifyData.bMuted);
    }

    public void Dispose()
    {
        GC.SuppressFinalize(this);
    }
}
