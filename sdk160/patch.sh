#!/bin/bash

echo -e "Setting defconfig"
cd ../../snx_sdk/buildscript/

make sn98660_QR_Scan_402mhz_sf_defconfig

echo -e "Applying patch"
cd ../../sdk160/patch/
/bin/cp -v -f -R snx_sdk/* ../../snx_sdk/

echo -e "Executing make"
cd ../../snx_sdk/buildscript/

make

echo -e "Executing make install"
make install

