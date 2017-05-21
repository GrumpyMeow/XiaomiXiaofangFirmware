#README.txt
##Mobile Device (Androd)
1. Install SimpleConfigApp.apk
2. Refer to Android_Simple_Config_User_Guide_v0.3 setup the router SSID/password you desired to connect.

##Device (SN98600 + 8188 wifi dongle)
1. insmod 8188eu.ko
2. ifconfig wlan0 up
3. ./rtw_simple_config -iwlan0 -c /etc/wpa_supplicant.conf 
4. When the mobile APP starts to broadcast signals, the device would receive the SSID/ password and save them to /etc/wpa_supplicant.conf
5. rtw_simple_config would call wpa_supplicant / udhcpc automatically and check if the connection is successful.

