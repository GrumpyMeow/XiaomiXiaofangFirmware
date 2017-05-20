#!/bin/bash

echo -e "Setting defconfig"
cd ../../snx_sdk/buildscript/

make clean

make sn98660_402mhz_sf_defconfig

echo -e "Applying patch"
cd ../../XiaomiXiaofangFirmware/sdk160/
/bin/cp -v -f -R snx_sdk/* ../../snx_sdk/

echo -e "execute: make menuconfig kernelmenuconfig make make install"

#in kernelmenuconfig: System Type not correctly visible in 
#mapping drivers for chip access
#support non lineair , mtd_physmap_len uitzoeken
