#!/bin/bash 

echo -e "** Xiaomi Xiaofang Custom firmware builder script **\n"

echo "Clean SDK filesystem and rootfs"
/bin/rm -f -r ../snx_sdk/filesystem/rootfs/src/target/*
/bin/rm -f -r ../snx_sdk/filesystem/rootfs-rescue/src/target/*
/bin/rm -f -r ../snx_sdk/rootfs/*
/bin/rm -f -r ../snx_sdk/rootfs-rescue/*
#/bin/rm -f -r ../snx_sdk/image/*
echo -e " Done\n"

echo -e "Extracting firmware rootfs files"
mkdir /mnt/rootfs
mount  -o loop -t cramfs ./3.0.3.56/rootfs.cramfs /mnt/rootfs/ 
(cd /mnt/rootfs/ ; tar cfp - .)|(cd ../snx_sdk/filesystem/rootfs/src/target/ ; tar xfp  - --warning=no-timestamp)
(cd /mnt/rootfs/ ; tar cfp - .)|(cd ../snx_sdk/filesystem/rootfs-rescue/src/target/ ; tar xfp - --warning=no-timestamp)
umount /mnt/rootfs
rmdir /mnt/rootfs

echo -e " Done\n"

echo "Patching SDK files"
cd snx_sdk
/bin/cp  -f -r . ../../snx_sdk/


cd ../snx_sdk/buildscript/
#make clean
make


/bin/rm -f ../snx_sdk/filesystem/rootfs/src/target/lib/modules/2.6.35.12/kernel/drivers/ar0130.ko
/bin/rm -f ../snx_sdk/filesystem/rootfs/src/target/lib/modules/2.6.35.12/kernel/drivers/imx322.ko
/bin/rm -f ../snx_sdk/filesystem/rootfs/src/target/lib/modules/2.6.35.12/kernel/drivers/ov9715.ko
/bin/rm -f ../snx_sdk/filesystem/rootfs/src/target/lib/modules/2.6.35.12/kernel/drivers/sc2035.ko


make firmware

exit



cd ..
echo -e " Done\n"

echo "Providing nvram.bin"
/bin/cp -f ./needed/nvram.bin ../snx_sdk/image/
echo -e " Done\n"

echo "Next step is to 'make the SDK'. This will result in:"
echo "* ../snx_sdk/rootfs/ (combination of filesystem and modules)"
echo "* ../snx_sdk/rescue-rootfs (combination of filesystem and modules)"
echo "* ../snx_sdk/image/rescue_uImage (rescue kernel)" 
echo "* ../snx_sdk/image/uImage (kernel)"
echo "* ../snx_sdk/image/u-boot.bin (bootloader)"

read -p "Press any key to 'make the SDK'... " -n1 -s
echo -e "\n"

cd ../snx_sdk/buildscript/
#make clean
make
find ../rootfs/ -type f | xargs ../toolchain/crosstool-4.5.2/arm-linux/bin/strip -s
find ../rootfs-rescue/ -type f | xargs ../toolchain/crosstool-4.5.2/arm-linux/bin/strip -s

#make rootfs
make install

cd  ../../patch/

read -p "Press any key to 'make the firmware'... " -n1 -s
echo -e "\n"

echo "Copying KERNEL.bin from source firmware"

/bin/cp -f ./3.0.3.56/KERNEL.bin ../snx_sdk/image/
echo -e "\tDone"

echo "Creating uImage file from KERNEL.bin"
dd if=../snx_sdk/image/KERNEL.bin of=../snx_sdk/image/uImage bs=1 skip=4 count=$(( $(stat -c %s ../snx_sdk/image/KERNEL.bin) - 116 )) iflag=skip_bytes,count_bytes
echo -e "\tDone\n"

echo "Duplicating uImage to rescue_uImage (for now)"
/bin/cp -f ../snx_sdk/image/uImage ../snx_sdk/image/rescue_uImage
echo -e "\tDone\n"

echo "Making firmware" 
cd ../snx_sdk/buildscript/
make kernelimage
make firmware

echo "Copying firmware file (FIRMWARE_660R.bin) to PATCH directory"
/bin/cp -f ../image/FIRMWARE_660R.bin ../../patch/
echo -e "\tDone\n"
echo "Place the FIRMWARE_660R.bin file in the root of a SDCard"
echo "Hold the setup button during boot"
