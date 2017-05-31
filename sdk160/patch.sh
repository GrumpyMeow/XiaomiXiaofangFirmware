#!/bin/bash

SNXSDK=$PWD/../../snx_sdk
SDK160=$PWD

echo "Todo: remove .o and .ko files from driver/usb-wifi folder"

echo -e "Fetching sourcecode of rtl8188eu driver"
#if [ ! -d $SNXSDK/driver/usb-wifi/src/driver/rtl8188eu ]; then
#	git clone https://github.com/lwfinger/rtl8188eu.git $SNXSDK/driver/usb-wifi/src/driver/rtl8188eu
#fi

if [ ! -d $SNXSDK/kernel/linux-2.6.35.12/src/drivers/staging/rtl8188eu ]; then	
	git clone https://github.com/lwfinger/rtl8188eu.git $SNXSDK/kernel/linux-2.6.35.12/src/drivers/staging/rtl8188eu
fi


echo -e "Fetching sourcecode of NETLINK and IW" 
if [ ! -d $SNXSDK/app/libnl/src ]; then
	git clone https://github.com/tgraf/libnl.git $SNXSDK/app/libnl/src
	cd $SNXSDK/app/libnl/src
	autoconf
	./autogen.sh
	#./configure --host=arm-linux-gnueabi --prefix=$SNXSDK/app/libnl/output
fi

if [ ! -d $SNXSDK/app/iw/src ]; then
	git clone https://github.com/Distrotech/iw.git $SNXSDK/app/iw/src
fi


cd $SNXSDK/buildscript
echo -e "Make clean"
make clean

echo -e "Applying patch"
cd $SDK160
echo -e "Applying patch"
/bin/cp -v -f -R snx_sdk/* $SNXSDK/

echo -e "Setting defconfig"
cd $SNXSDK/buildscript
make sn98660_QR_Scan_402mhz_sf_defconfig

echo -e "execute: cd ../../snx_sdk/buildscript/"
echo -e "execute: make menuconfig"

echo -e "execute: make kernelmenuconfig"
#echo -e "\tselect: 'General setup > Kernel compression mode > LZMA'"
#echo -e "\tselect: 'General setup > Optimize for size'"
#echo -e "\tselect: 'System Type > SONiX SN986XX Implementations >  Select target board > Support SONiX SN98660 Platform'"

#echo -e "\tselect: Device Drivers > Memory Technology Device (MTD) support > Direct char device access to MTD devices"
#echo -e "\tdeselect: 'Device Drivers > SCSI device support > SCSI CDROM support'"

#echo -e "\tdeselect: 'Device Drivers > Network device support > Ethernet (10 or 100Mbit) '"
#echo -e "\tselect: 'Device Drivers > Network device support > Wireless LAN > Realtek 8187 and 8187B USB support'"

#echo -e "\tdeselect: 'Device Drivers > Input device support > Support for memoryless force-feedback devices'"
#echo -e "\tdeselect: 'Device Drivers > Input device support > Event interface'"
#echo -e "\tdeselect: 'Device Drivers > Input device support > Keyboards'"
#echo -e "\tdeselect: 'Device Drivers > Input device support > Mice'"
#echo -e "\tdeselect: 'Device Drivers > Input device support > Joysticks/Gamepads'"
#echo -e "\tdeselect: 'Device Drivers > Input device support > Touchscreens'"
#echo -e "\tdeselect: 'Device Drivers > Input device support > Miscellaneous devices'"
#echo -e "\tdeselect: 'Device Drivers > Input device support > Hardware I/O ports > Gameport support'"
#echo -e "\tdeselect: 'Device Drivers > Input device support > Hardware I/O ports > Serial I/O support'"
#echo -e "\tdeselect: 'Device Drivers > Character devices > Legacy (BSD) PTY support'"

#echo -e "\tdeselect: 'Device Drivers > Video capture adapters > Enable advance debug functionality'"

#echo -e "\tdeselect: 'Device Drivers > Graphics support > Support for frame buffer devices'"

#echo -e "\tdeselect: 'Device Drivers > HID Devices'"

#echo -e "\tdeselect: 'Device Drivers > USB support > USB Serial Converter support'"

#echo -e "\tdeselect: 'File systems > CD-ROM/DVD Filesystems > ISO 9660 CDROM file system support'"

#echo -e "\tdeselect: 'Kernel hacking > Kernel debugging'"

echo -e "execute: make"

echo -e "execute: make install"
