#!/bin/sh

TOTAL_RESULT="Pass"

function file_compare()
{
	if [ "$2" != "" ]; then
		CMP_RESULT=`diff $1 $2 2>&1`
		if [ "$CMP_RESULT" != "" ]; then
			echo "OSABL Check, Compare Result : $1 vs $2, ERROR!!!!!!!!!!"
			TOTAL_RESULT="Failed!"
#		else
#			echo "Compare Result : $1 vs $2, PASS"
		fi
	fi
	
	if [ "$3" != "" ]; then
		CMP_RESULT=`diff $1 $3 2>&1`
		if [ "$CMP_RESULT" != "" ]; then
			echo "OSABL Check, Compare Result : $1 vs $3, ERROR!!!!!!!!!!"
			TOTAL_RESULT="Failed!"
#		else
#			echo "Compare Result : $1 vs $3, PASS"
		fi		
	fi
	
	if [ "$4" != "" ]; then
		CMP_RESULT=`diff $1 $4 2>&1`
		if [ "$CMP_RESULT" != "" ]; then
			echo "OSABL Check, Compare Result : $1 vs $4, ERROR!!!!!!!!!!"
			TOTAL_RESULT="Failed!"
#		else
#			echo "Compare Result : $1 vs $4, PASS"
		fi		
	fi	
}

FILENAME=config.mk
FOLDER1=./
FOLDER2=./UTIL/os/linux/
FOLDER3=./NETIF/os/linux/
FOLDER4=./MODULE/os/linux/
file_compare $FOLDER1$FILENAME $FOLDER2$FILENAME $FOLDER3$FILENAME $FOLDER4$FILENAME

FILENAME=Makefile.clean
FOLDER1=./
FOLDER2=./UTIL/os/linux/
FOLDER3=./NETIF/os/linux/
FOLDER4=./MODULE/os/linux/
file_compare $FOLDER1$FILENAME $FOLDER2$FILENAME $FOLDER3$FILENAME $FOLDER4$FILENAME

FILENAME1=Makefile.inc
FILENAME2=Makefile
FOLDER1=./
FOLDER2=./UTIL/
FOLDER3=./NETIF/
FOLDER4=./MODULE/
file_compare $FOLDER1$FILENAME1 $FOLDER2$FILENAME2 $FOLDER3$FILENAME2 $FOLDER4$FILENAME2

FILENAME=rtmp_os.h
FOLDER1=./MODULE/include/
FOLDER2=./UTIL/include/
FOLDER3=./NETIF/include/
file_compare $FOLDER1$FILENAME $FOLDER2$FILENAME $FOLDER3$FILENAME

FILENAME=link_list.h
FOLDER2=./UTIL/include/
FOLDER3=./NETIF/include/
FOLDER1=./MODULE/include/
file_compare $FOLDER1$FILENAME $FOLDER2$FILENAME $FOLDER3$FILENAME 

FILENAME=rtmp_cmd.h
FOLDER2=./UTIL/include/
FOLDER3=./NETIF/include/
FOLDER1=./MODULE/include/
file_compare $FOLDER1$FILENAME $FOLDER2$FILENAME $FOLDER3$FILENAME 

FILENAME=rt_os_util.h
FOLDER2=./UTIL/include/
FOLDER3=./NETIF/include/
FOLDER1=./MODULE/include/
file_compare $FOLDER1$FILENAME $FOLDER2$FILENAME $FOLDER3$FILENAME 

FILENAME=rt_os_net.h
FOLDER1=./MODULE/include/
FOLDER2=./NETIF/include/
file_compare $FOLDER1$FILENAME $FOLDER2$FILENAME

FILENAME=chip_id.h
FOLDER1=./MODULE/include/chip/
FOLDER2=./NETIF/include/chip/
file_compare $FOLDER1$FILENAME $FOLDER2$FILENAME

FILENAME=rtmp_type.h
FOLDER2=./UTIL/include/
FOLDER3=./NETIF/include/
FOLDER1=./MODULE/include/
file_compare $FOLDER1$FILENAME $FOLDER2$FILENAME $FOLDER3$FILENAME 

FILENAME=rtmp_osabl.h
FOLDER2=./UTIL/include/
FOLDER3=./NETIF/include/
FOLDER1=./MODULE/include/
file_compare $FOLDER1$FILENAME $FOLDER2$FILENAME $FOLDER3$FILENAME 

FILENAME=rtmp_comm.h
FOLDER2=./UTIL/include/
FOLDER3=./NETIF/include/
FOLDER1=./MODULE/include/
file_compare $FOLDER1$FILENAME $FOLDER2$FILENAME $FOLDER3$FILENAME 

FILENAME=iface_util.h
FOLDER2=./UTIL/include/iface/
FOLDER3=./NETIF/include/iface/
FOLDER1=./MODULE/include/iface/
file_compare $FOLDER1$FILENAME $FOLDER2$FILENAME $FOLDER3$FILENAME 

FILENAME=rt_linux_cmm.h
FOLDER2=./UTIL/include/os/
FOLDER3=./NETIF/include/os/
FOLDER1=./MODULE/include/os/
file_compare $FOLDER1$FILENAME $FOLDER2$FILENAME $FOLDER3$FILENAME 

FILENAME=rt_os.h
FOLDER2=./UTIL/include/os/
FOLDER3=./NETIF/include/os/
FOLDER1=./MODULE/include/os/
file_compare $FOLDER1$FILENAME $FOLDER2$FILENAME $FOLDER3$FILENAME 

FILENAME=rt_linux.h
FOLDER2=./UTIL/include/os/
FOLDER3=./NETIF/include/os/
FOLDER1=./MODULE/include/os/
file_compare $FOLDER1$FILENAME $FOLDER2$FILENAME $FOLDER3$FILENAME 


echo "OSABL Check, Overall Result : " $TOTAL_RESULT
