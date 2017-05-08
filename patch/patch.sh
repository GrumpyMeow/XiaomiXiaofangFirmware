 #!/bin/bash 

echo replacing snx_isp.ko
# The module snx_isp.ko has a hardcoded list of sensors it supports. Replace the SDK version with the version from firmware v3.0.3.56
# the snx_isp.ko in the SDK has support for the sc2035, but not the sc2135.
# SDK version supports: snx111, ov9715, ov2659, ov2715, imx132, ar0130, imx188, ov9772, ov9750, ov2643, imx238, ar0330, h22, h42, mt9v139, tw9912, cs4101k, cs1211k, ov7675, imx225, imx322, ov9732, ov7725, gc1024, ov2740, sc2035
# TODO: 
# * Maybe it's better to use the SDK version by replacing sc2035 with sc2135 in the binary file.
# * Maybe rename the sc2135.ko file to sc2035.ko to have snx_isp.ko pick it up
# * The list of copy destinations may be pruned
/bin/cp -f snx_isp.ko ../snx_sdk/driver/video/rootfs-rescue/lib/modules/2.6.35.12/kernel/drivers/snx_isp.ko
/bin/cp -f snx_isp.ko ../snx_sdk/driver/video/ko/isp3/snx_isp.ko
/bin/cp -f snx_isp.ko ../snx_sdk/driver/video/ko_rescue/isp3/snx_isp.ko
/bin/cp -f snx_isp.ko ../snx_sdk/driver/video/rootfs/lib/modules/2.6.35.12/kernel/drivers/snx_isp.ko
/bin/cp -f snx_isp.ko ../snx_sdk/rootfs-rescue/lib/modules/2.6.35.12/kernel/drivers/snx_isp.ko
/bin/cp -f snx_isp.ko ../snx_sdk/rootfs/lib/modules/2.6.35.12/kernel/drivers/snx_isp.ko

echo replacing unknown password
# The SDK root user has a unknown password. I didn't make an effort to decrypt the password. I chose to replace the password with the one from the firmware v3.0.3.56.
# Thus you can login with: root ismart12
sed -i -- 's/$1$2368HyEJ$kwdhYsA4j0BOLLvdohThM1:10933/rJ0FHsG0ZbyZo:17092/g' ../snx_sdk/filesystem/rootfs/src/target/root/etc_default/shadow
sed -i -- 's/$1$2368HyEJ$kwdhYsA4j0BOLLvdohThM1:10933/rJ0FHsG0ZbyZo:17092/g' ../snx_sdk/filesystem/rootfs-rescue/src/target/root/etc_default/shadow

echo replacing Galaxy Server configuration files
# Copy translated, FPS fixed and EOL fixed configuration files.
/bin/cp -f sonix/* ../snx_sdk/app/galaxy-server/rootfs/root/etc_default/sonix/
/bin/cp -f sonix/* ../snx_sdk/rootfs/root/etc_default/sonix/

if grep -q 'config APP_ONVIF' ../snx_sdk/buildscript/app_Kconfig
then
    echo onvif app is already present in app_Kconfig
else 
  echo adding onvif app to app_Kconfig
  sed -i -- '/config APP_IPERF/i config APP_ONVIF\n bool "onvif"\n default y\n\n' ../snx_sdk/buildscript/app_Kconfig
fi

if grep -q 'onvif:' ../snx_sdk/buildscript/Makefile.mod
then
    echo onvif app is already present in Makefile.mod
else 
  echo adding onvif app to Makefile.mod
  sed -i -- '/iperf-2.0.4:/i onvif:\n	if [ -d $(PRJ_DIR)/app/onvif/rootfs ]; then \\n		cp -av $(PRJ_DIR)/app/onvif/rootfs/* $(FS_DIR); \\n	fi\n onvif-clean:\n' ../snx_sdk/buildscript/Makefile.mod
fi

if grep -q 'config VIDEO_SENSOR_SC2135' ../snx_sdk/buildscript/driver_Kconfig
then
   echo sc2035 and sc2135 is already present in driver_Kconfig
else
   echo adding sc2035 and sc2135 
   sed -i -- '/config VIDEO_SENSOR_OV2740/i config VIDEO_SENSOR_SC2035\n bool "SC2035"\n default n\n\n config VIDEO_SENSOR_SC2135\n bool "SC2135"\n default y\n\n' ../snx_sdk/buildscript/driver_Kconfig
fi
