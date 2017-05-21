	 Realtek Simple Config Tool	
	----------------------------


1. Package contain
------------------

	SimpleConfig.apk source code	
	Document
	rtw_simple_config.tar.gz
	Realtek wifi driver source code


2. Introduction
---------------
	
	"rtw_simple_config" is a tool for configuring the wireless setting of an device(ex: IPCAM), user can install an app to an IOS/Android device, then the app will send some packets to the air, DUT will learn the wireless setting by sniffing those packets.

	Usage	-- 
        rtw_simple_config       -i<ifname> -c<wpa_cfgfile> -n<dev_name> -p <pincode> -m <phone_mac>
                                 [-dD] [-v]

	OPTIONS:
        -i = interface name
        -c = the path of wpa_supplicant config file
        -p = pincode
        -d = enable debug message, -D = more debug message.
        -n = device name
        -m = filtering MAC, only accept the configuration frame which's from this MAC address
        -v = version

	Example:
        rtw_simple_config -i wlan0 -c ./wpa_conf -n RTKSC_SAMPLE -D
        rtw_simple_config -i wlan0 -c ./wpa_conf -p 14825561 -n RTKSC_SAMPLE -d

3. Preparation
--------------	

	Before starting porting procedure, please make sure the environment 
	1. Verifying the driver's monitor mode function. 
		"Simple_Config" need to sniffer the broadcast packets in the air, please reference the document "Realtek_Monitor_Mode_Guide.txt" to verify wireless interface monitor mode.
		
	2. Important!! 
	   "Simple_Config" contain a Realtek private decode/encode library -- libsc.a, this part is platform dependent, please prepare the tool-chain of your platform then check with Realtek contact window, they would help you to made libsc.a for your platform.

	3. Make sure rtw_simple_config is only process to control WiFi HW, do NOT perform softap or wpa_supplicant during rtw_simple_config running.
	
4. Porting
-----------

	1. Edit the Makefile, give a correct setting of following variable
		1. $(CC)
		2. $(AR)
		3. $(TARGET)	-- Optional, if you want to change the program name.	

	2. "rtw_simple_config" is consist of by main.c and a static library(libsc.a), you can use the API which's provided by static libsc.a to decoded/get/set wireless profile. 
	"main.c" shows an example to sniff & decoded the wireless configuration, then establishes the link and gets IP address with AP.

	3. you can customize following part in main.c
		1. def_chPlan			/* default channel plan  */
		2. connect_ap() 		/* the way of associating with AP in your platform ? */ 
		3. request_ip()			/* the way of getting IP address in your platform ? */
		4. control_handler()		/* Optional!! if you need to customize the control request of phone's app.	*/

	   you NEED to customize following part in sc_common.h
		1. WIFI_MODULE_NAME		/* the path Realtek wireless driver module			*/
		2. PROC_MODULE_PATH		/* the path of Realtek wireless driver in /proc	folder		*/

	4. Append "-d" or "-D" option to print debug message.
	
	5. Append "-v" option to print version information.
	
	Note
	1. "rtw_simple_config" will generate some temporary files, that means the device MUST provide a directory with read/write permission.
	2. If your system leak of "iwconfig" or "iw" command. you can port those tools by attaching wireless_tools.30.rtl.zip.
	3. The property of generating configuration file may not meet your request, you can modify the value of "commset" in store_cfgfile() funcion.


Linux porting example:
	1. copy & uncompress rtw_simple_config.tar.gz to your host system.
	2. modify $(CC) + $(AR) in Makefile, type "make", please MAKE SURE you have a right libsc.a!!
	3. mkdir /home/rtw_simple_config.
	4. push iw, iwconfig, rtw_simple_config to /home/rtw_simple_config.
	5. chmod -R 777 /home/rtw_simple_config.
	6. type "rtw_simple_config -i wlan0 -c ./wpa_conf -n RTKSC_SAMPLE -d" for testing.
	7. Done !!

	
Android porting example :
	1. copy rtw_simple_config.tar.gz to <android_sdk>/external/, souce build/envsetup.sh , lunch proper profile.
	2. tar -zxvf rtw_simple_config.tar.gz, enter release folder and put libsc.a in here then type "mm -B".
	3. copy rtw_simple_config from out/target/product/<platform>/system/bin/
	4. do the same thing to get <iw, iwconfig> executable file.	(Optinal task)
	5. adb shell mkdir /data/rtw_simple_config.
	6. adb push <iw, iwconfig, rtw_simple_config> to /data/rtw_simple_config.
	7. adb shell chmod -R 777 /data/rtw_simple_config.
	8. type "rtw_simple_config -i wlan0 -c ./wpa_conf -n RTKSC_SAMPLE -d" for testing.
	9. Done !!
	

	
	
	
	
5. Trouble shouting
-----------
	Please check following item.
	1. Does iwconfig/ifconfig/rmmod/insmod command get ready?
	2. Can system run monitor mode function?
	3. Rtw_simple_config, apk, libsc.a, wifi driver MUST come from same release package.
	3. Can you perform wpa_supplicant manually?
	4. Is the format of generating wpa_config file correct?
	5. Does system got IP address? Important!! request_ip() function MUST to be customize.
	
	Please provide following information.
	1. /proc/net/rtlxxxx/wlanx/survey_info. 
	2. Debug message log during rtw_simple_config running.
	3. kernel log + sniffer log. (optional)
