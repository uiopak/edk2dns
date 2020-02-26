# edk2dns

Simple app performing DNS lookup in [UEFI](https://uefi.org/) using [EDK II](https://github.com/tianocore/edk2).

---

For more information about building edk2, you may check [this](https://github.com/tianocore-training/Tianocore_Training_Contents/wiki) training or [this](https://github.com/tianocore/tianocore.github.io/wiki/Getting-Started-with-EDK-II) starting tutorial.

---

You can build this app similar to [this](https://github.com/tianocore/tianocore.github.io/wiki/Getting-Started-Writing-Simple-Application) Hello World.

To run this app in QEMU build OVMF with network support.

First add required drivers (description from [OvmfPkg](https://github.com/tianocore/edk2/tree/master/OvmfPkg)):

```
* Also independently of the iPXE NIC drivers, Intel's proprietary E1000 NIC
  driver (from the BootUtil distribution) can be embedded in the OVMF image at
  build time:

  - Download BootUtil:
    - Navigate to
      https://downloadcenter.intel.com/download/19186/Ethernet-Intel-Ethernet-Connections-Boot-Utility-Preboot-Images-and-EFI-Drivers
    - Click the download link for "PREBOOT.EXE".
    - Accept the Intel Software License Agreement that appears.
    - Unzip "PREBOOT.EXE" into a separate directory (this works with the
      "unzip" utility on platforms different from Windows as well).
    - Copy the "APPS/EFI/EFIx64/E3522X2.EFI" driver binary to
      "Intel3.5/EFIX64/E3522X2.EFI" in your WORKSPACE.
    - Intel have stopped distributing an IA32 driver binary (which used to
      match the filename pattern "E35??E2.EFI"), thus this method will only
      work for the IA32X64 and X64 builds of OVMF.
```

Last version containing this driver is [24.3](https://downloadcenter.intel.com/download/29334/Ethernet-Intel-Ethernet-Connections-Boot-Utility-Preboot-Images-and-EFI-Drivers)

Than build OFMF using this command:

```
build p OvmfPkg\OvmfPkgX64.dsc -a X64 -D NETWORK_HTTP_BOOT_ENABLE -D NETWORK_TLS_ENABLE -D E1000_ENABLE
```

On Windows to add network to QEMU you can use TAP adapter created using OpenVPN or create [2nd TAP](https://stackoverflow.com/questions/21210071/how-to-create-a-2nd-tap-adapter-for-openvpn-client-on-win7).

Last thing is to share internet connection with [TAP](https://answers.microsoft.com/en-us/windows/forum/windows_10-networking/internet-connection-sharing-in-windows-10/f6dcac4b-5203-4c98-8cf2-dcac86d98fb9)
and from `From the Home networking connection drop-down menu` select your TAP.
Due to a Windows bug, you may need to disable and re-enable Internet Connection Sharing to restore internet connection.

To use TAP with QEMU after renaming adapter name to e.g. "TAP" you can use this command to start QEMU:

```
qemu-system-x86_64.exe -s -pflash OVMF.fd -hda fat:rw:hda  -netdev tap,id=mynet0,ifname=TAP -device e1000,netdev=mynet0
```

In this example app is placed inside `hda` directory.
