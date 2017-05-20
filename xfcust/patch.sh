#!/bin/bash 

echo -e "** Xiaomi Xiaofang Custom firmware builder script **\n"

echo -e "Extracting firmware rootfs files"
mkdir /mnt/rootfs
mount  -o loop -t cramfs ./3.0.3.56/rootfs.cramfs /mnt/rootfs/ 
(cd /mnt/rootfs/ ; tar cfp - .)|(cd ../snx_sdk/filesystem/rootfs/src/target/ ; tar xfp  - --warning=no-timestamp)
(cd /mnt/rootfs/ ; tar cfp - .)|(cd ../snx_sdk/filesystem/rootfs-rescue/src/target/ ; tar xfp - --warning=no-timestamp)
umount /mnt/rootfs
rmdir /mnt/rootfs
/bin/rm -f ../snx_sdk/filesystem/rootfs/src/target/lib/modules/2.6.35.12/kernel/drivers/ar0130.ko
/bin/rm -f ../snx_sdk/filesystem/rootfs/src/target/lib/modules/2.6.35.12/kernel/drivers/imx322.ko
/bin/rm -f ../snx_sdk/filesystem/rootfs/src/target/lib/modules/2.6.35.12/kernel/drivers/ov9715.ko
/bin/rm -f ../snx_sdk/filesystem/rootfs/src/target/lib/modules/2.6.35.12/kernel/drivers/sc2035.ko
echo -e " Done\n"

echo "Patching rootfs files"
/bin/cp  -f -r  rootfs/* ../../snx_sdk/rootfs/
/bin/cp  -f -r  rootfs/* ../../snx_sdk/rootfs-rescue/
echo -e " Done\n"

echo "Providing nvram.bin"
/bin/cp -f ./needed/nvram.bin ../snx_sdk/image/
echo -e " Done\n"

echo "Copying KERNEL.bin from source firmware"
/bin/cp -f ./3.0.3.56/KERNEL.bin ../snx_sdk/image/
echo -e "\tDone"

echo "Creating uImage file from KERNEL.bin"
dd if=../snx_sdk/image/KERNEL.bin of=../snx_sdk/image/uImage bs=1 skip=4 count=$(( $(stat -c %s ../snx_sdk/image/KERNEL.bin) - 116 )) iflag=skip_bytes,count_bytes
echo -e "\tDone\n"

echo "Duplicating uImage to rescue_uImage (for now)"
/bin/cp -f ../snx_sdk/image/uImage ../snx_sdk/image/rescue_uImage
echo -e "\tDone\n"


cd ../snx_sdk/buildscript/
make firmware
