# Enter door #1

This effort is to build a complete custom firmware based upon the Sonix SDK v1.60.


1. Download the Sonix VirtualBox Appliance file
1. Download the Sonix SN986 SDK 1.60
1. In the virtual machine: yum install git
1. In the virtual machine: yum install ncurses
1. In the virtual machine: yum install ncurses-devel
1. In the virtual machine: yum install git
1. Put the Sonix SN986 SDK 1.60 tgz file in /home/dev
1. cd /home/dev
1. tar xvf SN986_1.60_QR_Scan_019a_20160606_0951.tgz
1. cd SN986_1.60_QR_Scan_019a_20160606_0951/
1. git clone https://github.com/SanderSchutten/XiaomiXiaofangFirmware.git
1. ./sdk_unpack
1. cd XiaomiXiaofangFirmware/sdk160
1. ./patch.sh
1. cd ../../snx_sdk/buildscript
1. make menuconfig
1. make kernelmenuconfig
1. make
1. make install
1. cd ../image/
1. copy "FIRMWARE_660R.bin" to the root of your SD-card
1. power off the camera
1. put sdcard in the camera
1. push and hold the setup button
1. power on the camera, keep holding the setup button, count to 10, release the setup button
1. wait 2 minutes
1. connect to the SSID of the camera to appear

In case you get errors during build, it's best to start clean:
1. cd SN986_1.60_QR_SScan_019a_20160606_0951
1. ./sdk.cleanup
1. answer: "y"
1. /bin/rm -f -r XiaomiXiaofangFirmware
1. git clone https://github.com/SanderSchutten/XiaomiXiaofangFirmware.git
1. ./sdk.unpack
