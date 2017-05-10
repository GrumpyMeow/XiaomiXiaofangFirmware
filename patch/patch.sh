 #!/bin/bash 

echo Setting defconfig 
cd ../snx_sdk/buildscript/
make sn98660_QR_Scan_402mhz_sf_defconfig

echo Applying patch
cd ../../patch/

/bin/cp -v -f -R snx_sdk/* ../snx_sdk/

echo Executing make
cd ../snx_sdk/buildscript/
make

echo Executing make install
make install

cd ../../patch/
tar -cvzf xiaofang_0.002.tgz ../snx_sdk/image/
