# XiaomiXiaofangFirmware
Files for building your own custom firmware for the Xiaomi Xiaofang IP Camera.

!! Many issues, bugs, troubles, errors, warnings and disasters will happen when using this firmware at this moment. !!
!! I cannot guarantee that you can reflash your device back to the original Xiaomi firmware. !!

# Introduction
This repository will host files to build a custom firmware for the Xiaomi Xiaofang IP Camera. This repository will extend the generic Sonix SDK version 1.60.

# HowTo use
!! At the moment not all files are present in this repository !!
1. Download the Sonix VirtualBox Appliance file
1. Download the Sonix SN986 SDK 1.60
1. Download the files from this repository. Place them in the folder next to (!not in!) snx_sdk. 
1. Navigate to the "patch" directory
1. Execute "patch.sh"

# HowTo flash and use a prebuilt firmware
1. After booting the device it will host an AP with the name "SNIP39_xxxxxxx" (xxx=mac). The passphrase is 8x8, thus: "88888888".
1. After connecting to the SNIP AP. You can access the WebAdmin interface by browsing to: https://10.42.0.1
You can login using "root", pw: ismart12


First test release. 

You can flash this version with placing the firmware (FIRMWARE660R.bin) in the root of your SDCard and powering-on the device holding the setup button for a few seconds.



