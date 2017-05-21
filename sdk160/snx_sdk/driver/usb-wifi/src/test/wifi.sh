#!/bin/bash

#The script get the information of wireless interface.
#usage: sh wifi.sh hotpoint

total=0
failed=0


echo -e -n "Configure wireless interface $1 ...\t"
wpa_supplicant -B  -Dwext -i$1 -c/etc/wpa_supplicant.conf

if [ $? != 0 ];
then
	echo -e "Configure $1 FAILED"
	exit
else
	echo PASS
fi

echo -e -n "Get IP ...\t"
udhcpc -i $1

if [ $? != 0 ];
then
	echo -e "Get IP FAILED"
	exit
else
	echo PASS
fi

echo -e "Interface information ..."
ifconfig $1

echo -e "Ping g.cn ...\t"
ping -c 5 g.cn

if [ $? != 0 ];
then
	echo -e "ping g.cn FAILED"
	exit
else
	echo PASS
fi
