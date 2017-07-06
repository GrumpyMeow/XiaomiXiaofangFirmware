# XiaomiXiaofangFirmware
Files for building your own custom firmware for the Xiaomi Xiaofang IP Camera.
[06test](tel://*#06#)
<tel://*#06#>

!! Many issues, bugs, troubles, errors, warnings and disasters will happen when using this firmware at this moment. !!
!! I cannot guarantee that you can reflash your device back to the original Xiaomi firmware. !!

# Introduction
This repository will host files to build a custom firmware for the Xiaomi Xiaofang IP Camera. This repository will extend the generic Sonix SDK version 1.60.

It also will host a script to modify the original Xiaomi firmware and rebuild a customized firmware.

# HowTo flash and use a prebuilt firmware
1. After booting the device it will host an AP with the name "SNIP39_xxxxxxx" (xxx=mac). The passphrase is 8x8, thus: "88888888".
1. After connecting to the SNIP AP. You can access the WebAdmin interface by browsing to: https://10.42.0.1
You can login using "root", pw: ismart12


First test release. 

You can flash this version with placing the firmware (FIRMWARE660R.bin) in the root of your SDCard and powering-on the device holding the setup button for a few seconds.


Notes:
* make kernelmenuconfig: deselect: "Device Drivers" > "Network device support" > "Ethernet (10/100 mbit)". The SNX MAC Ethernet device hangs during boot.
* Version number of Realtek RTL8188 drivers can be found in include/rtw_version.h
