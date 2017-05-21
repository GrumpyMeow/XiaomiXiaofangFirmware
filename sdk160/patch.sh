#!/bin/bash

echo -e "Setting defconfig"
cd ../../snx_sdk/buildscript/

make clean

#make sn98660_402mhz_sf_defconfig
make sn98660_QR_Scan_402mhz_sf_defconfig

echo -e "Applying patch"
cd ../../XiaomiXiaofangFirmware/sdk160/
/bin/cp -v -f -R snx_sdk/* ../../snx_sdk/

echo -e "execute: make menuconfig, make kernelmenuconfig, make, make install, make firmware"
