# Enter door1

This effort is to achieve to build a complete custom firmware based upon the Sonix SDK v1.60.

# Issues:
* [Resolved] The password in the SDK is unknown. This is resolved by utilizing the /etc/passwd and /etc/shadow file from the firmware. Login with: root ismart12.
* [Unresolved] DUring the load of the module SNX_NVRAM.KO the kernel gives a BUG error message related DMA mapping. Possible causes: wrong mtd/memory mapping, memory issue, dma issue.
* [Resolved] Galaxy Server gave "Segfault errors". These are resolved with modifying the configuration files in /root/etc_default/sonix/. 
* [Unresolved] A few pages of Web-Admin do not work.
* [Resolved] During boot the system hangs on "SNX MAC Ethernet" device. This is probably due to some missing hardware components.  make kernelmenuconfig: deselect: "Device Drivers" > "Network device support" > "Ethernet (10/100 mbit)".
