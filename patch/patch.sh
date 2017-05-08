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
  sed -i -- '/iperf-2.0.4:/i onvif:\n	if [ -d $(PRJ_DIR)\/app\/onvif\/rootfs ]; then \\n		cp -av $(PRJ_DIR)\/app\/onvif\/rootfs\/* $(FS_DIR); \\n	fi\n onvif-clean:\n' ../snx_sdk/buildscript/Makefile.mod
fi

if grep -q 'config VIDEO_SENSOR_SC2135' ../snx_sdk/buildscript/driver_Kconfig
then
   echo sc2035 and sc2135 is already present in driver_Kconfig
else
   echo adding sc2035 and sc2135 
   sed -i -- '/config VIDEO_SENSOR_OV2740/i config VIDEO_SENSOR_SC2035\n bool "SC2035"\n default n\n\n config VIDEO_SENSOR_SC2135\n bool "SC2135"\n default y\n\n' ../snx_sdk/buildscript/driver_Kconfig
fi

if grep -q '#modprobe 8188eu' ../snx_sdk/filesystem/rootfs/src/target/root/etc_default/init.d/rcS
then
   echo enable 8188eu driver
   sed -i -- 's/#modprobe 8188eu/modprobe 8188eu/g' ../snx_sdk/filesystem/rootfs/src/target/root/etc_default/init.d/rcS
else 
   echo 8188eu driver is already enabled 
fi


if grep -q '#insmod isp driver' ../snx_sdk/filesystem/rootfs/src/target/root/etc_default/init.d/rcS
then
   echo enable sc2135 sensor driver
   sed -i -- 's/#insmod isp driver/modprobe sc2135/g' ../snx_sdk/filesystem/rootfs/src/target/root/etc_default/init.d/rcS
else 
   echo sc2135 sensor driver is already enabled 
fi

if grep -q '#modprobe snx_vb2' ../snx_sdk/filesystem/rootfs/src/target/root/etc_default/init.d/rcS
then
   echo enable snx_vb2 module
   sed -i -- 's/#modprobe snx_vb2/modprobe snx_vb2/g' ../snx_sdk/filesystem/rootfs/src/target/root/etc_default/init.d/rcS
else 
   echo snx_vb2 module is already enabled 
fi

if grep -q '#modprobe snx_vc snx_vb2=1 snx_percent=0' ../snx_sdk/filesystem/rootfs/src/target/root/etc_default/init.d/rcS
then
   echo enable snx_vc module
   sed -i -- 's/#modprobe snx_vc snx_vb2=1 snx_percent=0/modprobe snx_vc snx_vb2=1 snx_percent=0/g' ../snx_sdk/filesystem/rootfs/src/target/root/etc_default/init.d/rcS
else 
   echo snx_vc module is already enabled 
fi

if grep -q '#modprobe snx_vo' ../snx_sdk/filesystem/rootfs/src/target/root/etc_default/init.d/rcS
then
   echo enable snx_vo module
   sed -i -- 's/#modprobe snx_vo/modprobe snx_vo/g' ../snx_sdk/filesystem/rootfs/src/target/root/etc_default/init.d/rcS
else 
   echo snx_vo module is already enabled 
fi

if grep -q 'eth0' ../snx_sdk/filesystem/rootfs/src/target/root/etc_default/init.d/rc.local
then
   echo replace eth0 with wlan0
   sed -i -- 's/eth0/wlan0/g' ../snx_sdk/filesystem/rootfs/src/target/root/etc_default/init.d/rc.local
else 
   echo eth0 is already replaced with wlan0 
fi

if grep -q '#telnetd' ../snx_sdk/filesystem/rootfs/src/target/root/etc_default/init.d/rc.local
then
   echo enable telnetd
   sed -i -- 's/#telnetd/telnetd/g' ../snx_sdk/filesystem/rootfs/src/target/root/etc_default/init.d/rc.local
else 
   echo telnetd is already enabled
fi

if grep -q '#boa -f /etc/boa/boa.conf' ../snx_sdk/filesystem/rootfs/src/target/root/etc_default/init.d/rc.local
then
   echo enable boa
   sed -i -- 's/#boa -f \/etc\/boa\/boa.conf/boa -f \/etc\/boa\/boa.conf/g' ../snx_sdk/filesystem/rootfs/src/target/root/etc_default/init.d/rc.local
else 
   echo boa is already enabled
fi

if grep -q '#/usr/sbin/inetd' ../snx_sdk/filesystem/rootfs/src/target/root/etc_default/init.d/rc.local
then
   echo enable inetd
   sed -i -- 's/#\/usr\/sbin\/inetd/\/usr\/sbin\/inetd/g' ../snx_sdk/filesystem/rootfs/src/target/root/etc_default/init.d/rc.local
else 
   echo inetd is already enabled
fi


if grep -q '#/bin/wsdd &' ../snx_sdk/filesystem/rootfs/src/target/root/etc_default/init.d/rc.local
then
   echo enable wsdd
   sed -i -- 's/#\/bin\/wsdd &/\/bin\/wsdd &/g' ../snx_sdk/filesystem/rootfs/src/target/root/etc_default/init.d/rc.local
else 
   echo wsdd is already enabled
fi

if grep -q '#/bin/http-tunneling-serv &' ../snx_sdk/filesystem/rootfs/src/target/root/etc_default/init.d/rc.local
then
   echo enable http-tunneling-serv
   sed -i -- 's/#\/bin\/http-tunneling-serv &/\/bin\/http-tunneling-serv &/g' ../snx_sdk/filesystem/rootfs/src/target/root/etc_default/init.d/rc.local
else 
   echo http-tunneling-serv is already enabled
fi

if grep -q '#/bin/sonix-proj &' ../snx_sdk/filesystem/rootfs/src/target/root/etc_default/init.d/rc.local
then
   echo enable sonix-proj
   sed -i -- 's/#/bin/sonix-proj &/\/bin\/sonix-proj &/g' ../snx_sdk/filesystem/rootfs/src/target/root/etc_default/init.d/rc.local
else 
   echo sonix-proj is already enabled
fi

if grep -q '#/bin/twowayaudio &' ../snx_sdk/filesystem/rootfs/src/target/root/etc_default/init.d/rc.local
then
   echo enable twowayaudio
   sed -i -- 's/#\/bin\/twowayaudio &/\/bin\/twowayaudio &/g' ../snx_sdk/filesystem/rootfs/src/target/root/etc_default/init.d/rc.local
else 
   echo twowayaudio is already enabled
fi

if grep -q '#if [ -f /usr/bin/SnOnvif ]; then' ../snx_sdk/filesystem/rootfs/src/target/root/etc_default/init.d/rc.local
then
   echo enable SnOnvif
   sed -i -- 's/#if [ -f \/usr\/bin\/SnOnvif ]; then\n#    echo "Start Onvif ..."\n#    \/usr\/bin\/SnOnvif &\n#    echo \n#fi/if [ -f \/usr\/bin\/SnOnvif ]; then\n    echo "Start Onvif ..."\n    \/usr\/bin\/SnOnvif &\n    echo \nfi/g' ../snx_sdk/filesystem/rootfs/src/target/root/etc_default/init.d/rc.local
else 
   echo SnOnvif is already enabled
fi

if grep -q '#echo "Start cron sevice..."' ../snx_sdk/filesystem/rootfs/src/target/root/etc_default/init.d/rc.local
then
   echo enable Cron
   sed -i -- 's/#echo "Start cron sevice..."\n#mkdir -p \/var\/spool\/cron\/crontabs \n#cp \/etc\/web\/cron.hourly \/var\/spool\/cron\/crontabs\/root > \/dev\/null 2>&1\n#crond/echo "Start cron sevice..."\nmkdir -p \/var\/spool\/cron\/crontabs \ncp \/etc\/web\/cron.hourly \/var\/spool\/cron\/crontabs\/root > \/dev\/null 2>&1\ncrond/g' ../snx_sdk/filesystem/rootfs/src/target/root/etc_default/init.d/rc.local
else 
   echo Cron is already enabled
fi

if grep -q '#if [ -f /usr/bin/IspService ]; then' ../snx_sdk/filesystem/rootfs/src/target/root/etc_default/init.d/rc.local
then
   echo enable IspService isp tuning tool
   sed -i -- 's/#if [ -f \/usr\/bin\/IspService ]; then\n#	echo "Start isp tuning tool ..."\n#	\/usr\/bin\/IspService &\n#	echo\n#fi/if [ -f \/usr\/bin\/IspService ]; then\n	echo "Start isp tuning tool ..."\n	\/usr\/bin\/IspService &\n	echo\nfi/g' ../snx_sdk/filesystem/rootfs/src/target/root/etc_default/init.d/rc.local
else 
   echo IspService is already enabled (isp tuning tool)
fi

