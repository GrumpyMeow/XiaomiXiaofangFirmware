# XiaomiXiaofangFirmware
Files for building your own custom firmware for the Xiaomi Xiaofang IP Camera.

# Introduction
This repository will host files to build a custom firmware for the Xiaomi Xiaofang IP Camera. This repository will extend the generic Sonix SDK version 1.60.

# HowTo use
1. Download the Sonix VirtualBox Appliance file
1. Download the Sonix SN986 SDK 1.60
1. Download the files from this repository. Place them in the folder next to (!not in!) snx_sdk. 
1. Navigate to the "patch" directory
1. Execute "patch.sh"

# HowTo flash and use a prebuilt firmware
1. After connecting to the SNIP AP. You can access the WebAdmin interface by browsing to: https://10.42.0.1
You can login using "root", pw: ismart12




# FAQ

# TODO
* Live preview uses VLC web plugin. This has to be replaced.
* Media>Imagesettings gives error
* /etc/tsocks.conf is missing which gives error in using webui.
* WebUI>Network>UPNP gives "Segmentation fault"
* WebUI>Event>Motion Detection takes a very long time.
* WebUI>System>Information gives error: ERROR : snx_conf.c 573:Can't find the key : ./sys_information.cgi user ./sys_information.cgi ,power :
* WebUI> System> Date & Time  same sort error as above
* WebUI certificate is only valid for: 172.21.2.134
* WebUI/Galaxy Server> Increase resolution to FullHD support. Now 1280x720 is the highest.
? Modify Galaxy Server Log.xml to log to a file and not to the console.
? Add app SnOnvif, error: Create Key Error for /var/mq/cgi.mq : No such file or directoryMsg To Server Init Fail~
* SnOnvif requires ./web-admin/rootfs/var/mq files. They don't get copied, why?
