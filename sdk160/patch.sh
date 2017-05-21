#!/bin/bash

echo -e "Applying patch"
/bin/cp -v -f -R snx_sdk/* ../../snx_sdk/

echo -e "Setting defconfig"
cd ../../snx_sdk/buildscript/

make clean

make sn98660_QR_Scan_402mhz_sf_defconfig


echo -e "execute: make menuconfig"
echo -e "\tselect: 'Flash Layout and firmware/_f setting' > Configure file partition > Erase etc when update FIRMWARE.bin'"
echo -e "\tselect: 'User / Vendor Setting > [select what you want, memory size is limited ]'"
echo -e "\tselect: 'Sonix Driver > USB WiFi Support'"
echo -e "\tselect: 'Sonix Driver > USB WiFi Support > RTL8188EUS/ETV driver v4.3.0.3'"
echo -e "\tdeselect: 'Sonix Driver > Sensor driver > Deselect all'"
echo -e "\tselect: 'Sonix Driver > Sensor driver > SC2135'"
echo -e "\tselect: 'Sonix Driver > NVRAM support'"

echo -e "execute: make kernelmenuconfig"
echo -e "\tselect: 'General setup > Kernel compression mode > LZMA'"
echo -e "\tselect: 'General setup > Optimize for size'"
echo -e "\tselect: 'System Type > SONiX SN986XX Implementations >  Select target board > Support SONiX SN98660 Platform'"

#echo -e "\tselect: Device Drivers > Memory Technology Device (MTD) support > Direct char device access to MTD devices"

#echo -e "\tdeselect: 'Device Drivers > SCSI device support > SCSI CDROM support'"

echo -e "\tdeselect: 'Device Drivers > Network device support > Ethernet (10 or 100Mbit) '"
echo -e "\tselect: 'Device Drivers > Network device support > Wireless LAN > Realtek 8187 and 8187B USB support'"

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
