#!/bin/bash

echo Setting defconfig
cd ../../snx_sdk/buildscript/

make sn98660_QR_Scan_402mhz_sf_defconfig

echo Applying patch
cd ../../sdk160/patch/
/bin/cp -v -f -R snx_sdk/* ../../snx_sdk/

echo Executing make
cd ../snx_sdk/buildscript/

make

echo Executing make install
make install

