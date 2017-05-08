# XiaomiXiaofangFirmware
Custom firmware for the Xiaomi Xiaofang IP Camera

# Introduction
This repository will host files to build a custom firmware for the Xiaomi Xiaofang IP Camera. This repository will extend the generic Sonix SDK.

# HowTo use

# HowTo flash

# FAQ

# TODO
* Add the SC2035 and SC2135 driver and build options.
* snx_isp.ko replace for SC2135 support
* Enable the rtl8188eu wifi driver
* Fix the Galaxy Server configuration files
* Activate Galaxy Server during boot
* Activate Boa during boot
* Live preview uses VLC web plugin. This has to be replaced.
* Media>Imagesettings gives error
* /etc/tsocks.conf is missing which gives error in using webui.
* WebUI>Network>UPNP gives "Segmentation fault"
* WebUI>Event>Motion Detection takes a very long time.
* WebUI>System>Information gives error: ERROR : snx_conf.c 573:Can't find the key : ./sys_information.cgi user ./sys_information.cgi ,power :
* WebUI> System> Date & Time  same sort error as above
* WebUI certificate is only valid for: 172.21.2.134
* WebUI/Galaxy Server> Increase resolution to FullHD support. Now 1280x720 is the highest.
* Modify Galaxy Server Log.xml to log to a file and not to the console.
* Add app SnOnvif, error: Create Key Error for /var/mq/cgi.mq : No such file or directoryMsg To Server Init Fail~
* SnOnvif requires ./web-admin/rootfs/var/mq
./web-admin/rootfs/var/mq/ffserver.mq
./web-admin/rootfs/var/mq/cgi.mq
./web-admin/rootfs/var/mq/mntrd.mq
./web-admin/rootfs/var/mq/motiond.mq
