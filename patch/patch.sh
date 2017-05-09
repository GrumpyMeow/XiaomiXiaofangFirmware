 #!/bin/bash 

echo Setting defconfig 
cd ../snx_sdk/buildscript/
make sn98660_QR_Scan_402mhz_sf_defconfig

echo Applying patch
cd ../../patch/

/bin/cp -f -R snx_sdk/* ../snx_sdk/

echo Executing make
cd ../snx_sdk/buildscript/
#make
#make install
