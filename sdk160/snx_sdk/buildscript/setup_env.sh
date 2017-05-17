#!/bin/sh

#find .git file
function find_project_dir()
{
	find_dir=$1
	while :
	do
		temp_dir=`find $find_dir -maxdepth 1 -name ".git" -type d`
		if [ -n "$temp_dir" ]
		then
			echo "$temp_dir"
			break
		elif [ -z "$find_dir" ]
		then
			break
		else
			find_dir=${find_dir%/*}
		fi
	done
}

#read key in normal module
function read_norkey()  
{
	file_name=$1  
	section=$2  
	key=$3   
	read_key=`awk -F '=' '/\['$section'\]/{a=1}a==1&&$1~/'$key'/{print $2;exit}' $file_name`  
	echo $read_key  
}

#read key in special module
function read_sokey()  
{
	file_name=$1  
	section=$2  
	key=$3  
	read_key=`awk -F '=' '/\{'$section'\}/{a=1}a==1&&$1~/'$key'/{print $2;exit}' $file_name`  
	echo $read_key  
}

#$1: file name
#$2: section begin name
#$3: section end name
show_section()
{
	sed -n "/\[$2\]/,/\[$3\]/{
		/^\[.*\]/d
		/^[ ]*$/d
		s/#.*$//
		p
	}" $1
}

#$1 scan module name
#$2: file name
#$3: section begin name
#$4: section end name
find_module_from_section()
{
	find_flag=""
	module_list=`show_section $2 $3 $4`
	for module in $module_list
	do
		if [ "$module" != "$1" ]
		then
			continue;
		fi
		find_flag="yes"
		break;
	done
	echo $find_flag
}

#generate Makefile.mod(3):for [common]###
function find_common()
{
	time_enter=0
	flag_common=""
	include_next=""
	for line in `cat $1`
	do
		if [ "$flag_common" = "common" ]
		then
			include_next=`echo $line | sed -n "s/\[\(.*\)\]/\1/p"`
			if [ "$include_next" != "" ]
			then
				flag_common=""
				continue;
			fi
			let time_enter++
			this_line=$line
			if [ $time_enter -le 2 ]
			then
				this_line=`echo $this_line | sed 's/$/)/g'`
				this_line=`echo $this_line | sed 's/=/:=$(/g'`
			else
				this_line=`echo $this_line | sed 's/=/:=/g'`
			fi
			echo "$this_line" >> $2
		fi
	  
		include=`echo $line | sed -n "s/\[\(common\)\]/\1/p"`
    
		if [ "$include" != "" ]
		then
			flag_common=common
		fi
	done
}

###for 11 type###
function generate_bootloader_type()
{
	par_mai=${para_arr[0]}
        par_sub=${para_arr[1]}
        par_fil=${para_arr[2]}
        par_whe=${para_arr[3]}
        par_num=${para_arr[4]}
        par_dir=${para_arr[5]}
        par_tye=${para_arr[6]}
        par_how=${para_arr[7]}
    
	if [ "$par_how" = "1" ]
	then
		depend_mak=`echo $par_sub | sed 's/,/ /g'`
		depend_cle=`echo $par_sub | sed 's/,/-clean /g'`
		depend_cle=`echo $depend_cle | sed 's/$/-clean /g'`
	fi
   
	if [ "$cur_src_flag" = "source" ]
	then
		par_dir=".git"
	fi
 
	if [ "$par_num" = "5" ]
	then
		if [ "$par_how" = "1" ]
		then
			echo "$par_mai: $depend_mak" >> $par_fil
		elif [ "$par_how" = "0" ]
		then
			echo "$par_mai: $par_sub" >> $par_fil
		fi
	elif [ "$par_num" = "4" ]
	then
		echo "$par_mai:" >> $par_fil
	fi
 
	if [ "$par_dir" = ".git" ]
	then
		echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe all" >> $par_fil
		echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe install INSTALL_DIR=\$(PRJ_DIR)/$par_whe/image" >> $par_fil
		echo "	if [ -d \$(PRJ_DIR)/$par_whe/image ]; then \\" >> $par_fil
		echo "		cp -av \$(PRJ_DIR)/$par_whe/image/* \$(DIST_DIR); \\" >> $par_fil
		echo "	fi" >> $par_fil
	else
		echo "	if [ -d \$(PRJ_DIR)/$par_whe/image ]; then \\" >> $par_fil
		echo "		cp -av \$(PRJ_DIR)/$par_whe/image/* \$(DIST_DIR); \\" >> $par_fil
		echo "	fi" >> $par_fil
	fi

	if [ "$par_num" = "5" ]
	then
		if [ "$par_how" = "1" ]
		then
			echo "$par_mai-clean: $depend_cle" >> $par_fil
		elif [ "$par_how" = "0" ]
		then
			echo "$par_mai-clean: $par_sub-clean" >> $par_fil
		fi
	elif [ "$par_num" = "4" ]
	then
		echo "$par_mai-clean:" >> $par_fil
	fi
    
	if [ "$par_dir" = ".git" ]
	then
		echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe clean" >> $par_fil
		echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe distclean" >> $par_fil
		echo "	rm -rf \$(PRJ_DIR)/$par_whe/image" >> $par_fil
		echo "" >> $par_fil
	else
		echo "" >> $par_fil
	fi
}

###for 11 type###
function generate_kernel_type()
{
	par_mai=${para_arr[0]}
        par_sub=${para_arr[1]}
        par_fil=${para_arr[2]}
        par_whe=${para_arr[3]}
        par_num=${para_arr[4]}
        par_dir=${para_arr[5]}
        par_tye=${para_arr[6]}
        par_how=${para_arr[7]}
    
	if [ "$par_how" = "1" ]
	then
		depend_mak=`echo $par_sub | sed 's/,/ /g'`
		depend_cle=`echo $par_sub | sed 's/,/-clean /g'`
		depend_cle=`echo $depend_cle | sed 's/$/-clean /g'`
	fi
	if [ "$cur_src_flag" = "source" ]
	then
		par_dir=".git"
	fi
    
	if [ "$par_num" = "5" ]
	then
		if [ "$par_how" = "1" ]
		then
			echo "$par_mai: $depend_mak" >> $par_fil
		elif [ "$par_how" = "0" ]
		then
			echo "$par_mai: $par_sub" >> $par_fil
		fi
	elif [ "$par_num" = "4" ]
	then
		echo "$par_mai:" >> $par_fil
	fi
 
	if [ "$par_dir" = ".git" ]
	then
		echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe all OBJ_DIR=\$(NORMAL_KERNEL_DIR)/src COMPILE_RESCUE=no" >> $par_fil
		echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe install INSTALL_DIR=\$(PRJ_DIR)/$par_whe/image OBJ_DIR=\$(NORMAL_KERNEL_DIR)/src COMPILE_RESCUE=no" >> $par_fil
		echo "	if [ -d \$(PRJ_DIR)/$par_whe/image ]; then \\" >> $par_fil
		echo "		cp -av \$(PRJ_DIR)/$par_whe/image/* \$(DIST_DIR); \\" >> $par_fil
		echo "	fi" >> $par_fil
		echo "ifeq (\$(CONFIG_RESCUE_SYSTEM), y)" >> $par_fil	
		echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe all OBJ_DIR=\$(RESCUE_KERNEL_DIR)/src COMPILE_RESCUE=yes" >> $par_fil
		echo "endif" >> $par_fil
	else
		echo "	if [ -d \$(PRJ_DIR)/$par_whe/image ]; then \\" >> $par_fil
		echo "		cp -av \$(PRJ_DIR)/$par_whe/image/* \$(DIST_DIR); \\" >> $par_fil
		echo "	fi" >> $par_fil
		echo "ifeq (\$(CONFIG_RESCUE_SYSTEM), y)" >> $par_fil	
		echo "	if [ -d \$(PRJ_DIR)/$par_whe/rescue_image ]; then \\" >> $par_fil
		echo "		cp -av \$(PRJ_DIR)/$par_whe/rescue_image/* \$(DIST_DIR); \\" >> $par_fil
		echo "	fi" >> $par_fil
		echo "endif" >> $par_fil
	fi

	if [ "$par_num" = "5" ]
	then
		if [ "$par_how" = "1" ]
		then
			echo "$par_mai-clean: $depend_cle" >> $par_fil
		elif [ "$par_how" = "0" ]
		then
			echo "$par_mai-clean: $par_sub-clean" >> $par_fil
		fi
	elif [ "$par_num" = "4" ]
	then
		echo "$par_mai-clean:" >> $par_fil
	fi
    
	if [ "$par_dir" = ".git" ]
	then
		echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe clean OBJ_DIR=\$(NORMAL_KERNEL_DIR)/src COMPILE_RESCUE=no" >> $par_fil
		echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe distclean OBJ_DIR=\$(NORMAL_KERNEL_DIR)/src COMPILE_RESCUE=no" >> $par_fil
		echo "	rm -rf \$(PRJ_DIR)/$par_whe/image" >> $par_fil
		echo "ifeq (\$(CONFIG_RESCUE_SYSTEM), y)" >> $par_fil	
		echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe clean OBJ_DIR=\$(RESCUE_KERNEL_DIR)/src COMPILE_RESCUE=yes" >> $par_fil
		echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe distclean OBJ_DIR=\$(RESCUE_KERNEL_DIR)/src COMPILE_RESCUE=yes" >> $par_fil
		echo "	rm -rf \$(PRJ_DIR)/$par_whe/rescue_image" >> $par_fil
		echo "endif" >> $par_fil
		echo "" >> $par_fil
	else
		echo "" >> $par_fil
	fi
}

###for 12 type###
function generate_rootfs_type()
{
	par_mai=${para_arr[0]}
	par_sub=${para_arr[1]}
	par_fil=${para_arr[2]}
	par_whe=${para_arr[3]}
	par_num=${para_arr[4]}
	par_how=${para_arr[5]}
    
	if [ "$par_how" = "1" ]
	then
		depend_mak=`echo $par_sub | sed 's/,/ /g'`
		depend_cle=`echo $par_sub | sed 's/,/-clean /g'`
		depend_cle=`echo $depend_cle | sed 's/$/-clean /g'`
	fi
    
	if [ "$par_num" = "5" ]
	then
		if [ "$par_how" = "1" ]
		then
			echo "$par_mai: $depend_mak" >> $par_fil
		elif [ "$par_how" = "0" ]
		then
			echo "$par_mai: $par_sub" >> $par_fil
		fi
	elif [ "$par_num" = "4" ]
	then
		echo "$par_mai:" >> $par_fil
	fi
 
	echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe all" >> $par_fil
	if [ "$par_mai" = "rootfs" ]
	then
		echo "	\$(MAKE) -C \$(HW_DIR)/flash-layout serial_flashlayout.conf ADDTO_MOUNT_PARTITION=yes" >> $par_fil
	else
		echo "	\$(MAKE) -C \$(HW_DIR)/flash-layout serial_flashlayout.conf" >> $par_fil
	fi
	echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe install" >> $par_fil

	if [ "$par_num" = "5" ]
	then
		if [ "$par_how" = "1" ]
		then
			echo "$par_mai-clean: $depend_cle" >> $par_fil
		elif [ "$par_how" = "0" ]
		then
			echo "$par_mai-clean: $par_sub-clean" >> $par_fil
		fi
	elif [ "$par_num" = "4" ]
	then
		echo "$par_mai-clean:" >> $par_fil
	fi
    
	echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe clean" >> $par_fil
	echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe distclean" >> $par_fil
	echo "" >> $par_fil
}

###for 20 24 type###
function generate_app_driver_bs_type()
{	

	par_mai=${para_arr[0]}
	par_sub=${para_arr[1]}
	par_fil=${para_arr[2]}
	par_whe=${para_arr[3]}
	par_num=${para_arr[4]}
	par_dir=${para_arr[5]}
	par_tye=${para_arr[6]}
	par_how=${para_arr[7]}
    
	if [ "$par_how" = "1" ]
	then
		depend_mak=`echo $par_sub | sed 's/,/ /g'`
		depend_cle=`echo $par_sub | sed 's/,/-clean /g'`
		depend_cle=`echo $depend_cle | sed 's/$/-clean /g'`
	fi

	if [ "$cur_src_flag" = "source" ]
	then
		par_dir=".git"
	fi

	if [ "$par_num" = "5" ]
	then
		if [ "$cur_type_flag" != "rootfs-bs" ]
		then
			echo "ifeq (\$(MODULE_ONLY), yes)" >> $par_fil	
			echo "$par_mai:" >> $par_fil
			echo "else" >> $par_fil
		fi
		if [ "$par_how" = "1" ]
		then
			echo "$par_mai: $depend_mak" >> $par_fil
		elif [ "$par_how" = "0" ]
		then
			echo "$par_mai: $par_sub" >> $par_fil
		fi
		if [ "$cur_type_flag" != "rootfs-bs" ]
		then
			echo "endif" >> $par_fil
		fi
	elif [ "$par_num" = "4" ]
	then
		echo "$par_mai:" >> $par_fil
	fi
			  
	if [ "$cur_rescue_flag" = "compile_rescue" ]
	then
		if [ "$par_dir" = ".git" ]
		then
			if [ "$cur_type_flag" = "driver" ]
			then
				echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe all KERNEL_DIR=\$(NORMAL_KERNEL_DIR) COMPILE_RESCUE=no" >> $par_fil
				echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe install INSTALL_DIR=\$(PRJ_DIR)/$par_whe/rootfs KERNEL_DIR=\$(NORMAL_KERNEL_DIR) COMPILE_RESCUE=no" >> $par_fil
			elif [ "$cur_type_flag" = "app" ]
			then
				echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe all COMPILE_RESCUE=no" >> $par_fil
				echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe install INSTALL_DIR=\$(PRJ_DIR)/$par_whe/rootfs COMPILE_RESCUE=no" >> $par_fil
			else
				echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe all INSTALL_DIR=\$(PRJ_DIR)/$par_whe/rootfs OBJ_DIR=\$(NORMAL_BUSYBOX_DIR)/src COMPILE_RESCUE=no" >> $par_fil
				echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe install INSTALL_DIR=\$(PRJ_DIR)/$par_whe/rootfs OBJ_DIR=\$(NORMAL_BUSYBOX_DIR)/src COMPILE_RESCUE=no" >> $par_fil
			fi
		fi
		if [ "$cur_type_flag" = "driver" ]
		then
			echo "	if [ -f \$(PRJ_DIR)/$par_whe/custom_install ]; then \\" >> $par_fil
			echo "		\$(PRJ_DIR)/$par_whe/custom_install install \$(PRJ_DIR)/$par_whe/rootfs \$(AUTOCONF_DIR) normal; \\" >> $par_fil
			echo "	fi" >> $par_fil
		fi
			echo "	if [ -d \$(PRJ_DIR)/$par_whe/rootfs ]; then \\" >> $par_fil
			echo "		cp -av \$(PRJ_DIR)/$par_whe/rootfs/* \$(FS_DIR); \\" >> $par_fil
			echo "	fi" >> $par_fil
		echo "ifeq (\$(CONFIG_RESCUE_SYSTEM), y)" >> $par_fil	
		if [ "$par_dir" = ".git" ]
		then
			if [ "$cur_type_flag" != "rootfs-bs" ]
			then
				echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe clean" >> $par_fil
				echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe distclean" >> $par_fil
			fi
			if [ "$cur_type_flag" = "driver" ]
			then
				echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe all KERNEL_DIR=\$(RESCUE_KERNEL_DIR) COMPILE_RESCUE=yes" >> $par_fil
				echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe install INSTALL_DIR=\$(PRJ_DIR)/$par_whe/rootfs-rescue KERNEL_DIR=\$(RESCUE_KERNEL_DIR) COMPILE_RESCUE=yes" >> $par_fil
			elif [ "$cur_type_flag" = "app" ]
			then		
				echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe all COMPILE_RESCUE=yes" >> $par_fil
				echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe install INSTALL_DIR=\$(PRJ_DIR)/$par_whe/rootfs-rescue COMPILE_RESCUE=yes" >> $par_fil
			else
				echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe all COMPILE_RESCUE=yes INSTALL_DIR=\$(PRJ_DIR)/$par_whe/rootfs-rescue OBJ_DIR=\$(RESCUE_BUSYBOX_DIR)/src" >> $par_fil
				echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe install INSTALL_DIR=\$(PRJ_DIR)/$par_whe/rootfs-rescue OBJ_DIR=\$(RESCUE_BUSYBOX_DIR)/src COMPILE_RESCUE=yes" >> $par_fil
			fi
		fi
		if [ "$cur_type_flag" = "driver" ]
		then
			echo "	if [ -f \$(PRJ_DIR)/$par_whe/custom_install ]; then \\" >> $par_fil
			echo "		\$(PRJ_DIR)/$par_whe/custom_install install \$(PRJ_DIR)/$par_whe/rootfs-rescue \$(AUTOCONF_DIR) rescue; \\" >> $par_fil
			echo "	fi" >> $par_fil
		fi
			echo "	if [ -d \$(PRJ_DIR)/$par_whe/rootfs-rescue ]; then \\" >> $par_fil
			echo "		cp -av \$(PRJ_DIR)/$par_whe/rootfs-rescue/* \$(RESCUE_FS_DIR); \\" >> $par_fil
			echo "	fi" >> $par_fil	
		echo "endif" >> $par_fil	
	elif [ "$cur_rescue_flag" = "only_rescue" ]
	then 
		echo "ifeq (\$(CONFIG_RESCUE_SYSTEM), y)" >> $par_fil	
		if [ "$par_dir" = ".git" ]
		then
			if [ "$cur_type_flag" = "driver" ]
			then
				echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe all KERNEL_DIR=\$(RESCUE_KERNEL_DIR) COMPILE_RESCUE=yes" >> $par_fil
				echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe install INSTALL_DIR=\$(PRJ_DIR)/$par_whe/rootfs-rescue KERNEL_DIR=\$(RESCUE_KERNEL_DIR) COMPILE_RESCUE=yes" >> $par_fil
			elif [ "$cur_type_flag" = "app" ]
			then		
				echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe all COMPILE_RESCUE=yes" >> $par_fil
				echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe install INSTALL_DIR=\$(PRJ_DIR)/$par_whe/rootfs-rescue COMPILE_RESCUE=yes" >> $par_fil
			else
				echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe all COMPILE_RESCUE=yes INSTALL_DIR=\$(PRJ_DIR)/$par_whe/rootfs-rescue OBJ_DIR=\$(RESCUE_BUSYBOX_DIR)/src" >> $par_fil
				echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe install INSTALL_DIR=\$(PRJ_DIR)/$par_whe/rootfs-rescue OBJ_DIR=\$(RESCUE_BUSYBOX_DIR)/src COMPILE_RESCUE=yes" >> $par_fil
			fi
		fi
		if [ "$cur_type_flag" = "driver" ]
		then
			echo "	if [ -f \$(PRJ_DIR)/$par_whe/custom_install ]; then \\" >> $par_fil
			echo "		\$(PRJ_DIR)/$par_whe/custom_install install \$(PRJ_DIR)/$par_whe/rootfs-rescue \$(AUTOCONF_DIR) rescue; \\" >> $par_fil
			echo "	fi" >> $par_fil
		fi
			echo "	if [ -d \$(PRJ_DIR)/$par_whe/rootfs-rescue ]; then \\" >> $par_fil
			echo "	cp -av \$(PRJ_DIR)/$par_whe/rootfs-rescue/* \$(RESCUE_FS_DIR); \\" >> $par_fil
			echo "	fi" >> $par_fil	
		echo "endif" >> $par_fil	
	elif [ "$cur_rescue_flag" = "rescue" ]
	then
		if [ "$par_dir" = ".git" ]
		then
			if [ "$cur_type_flag" = "driver" ]
			then
				echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe all KERNEL_DIR=\$(NORMAL_KERNEL_DIR) COMPILE_RESCUE=no" >> $par_fil
				echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe install INSTALL_DIR=\$(PRJ_DIR)/$par_whe/rootfs KERNEL_DIR=\$(NORMAL_KERNEL_DIR) COMPILE_RESCUE=no" >> $par_fil
			elif [ "$cur_type_flag" = "app" ]
			then
				echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe all COMPILE_RESCUE=no" >> $par_fil
				echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe install INSTALL_DIR=\$(PRJ_DIR)/$par_whe/rootfs COMPILE_RESCUE=no" >> $par_fil
			else
				echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe all INSTALL_DIR=\$(PRJ_DIR)/$par_whe/rootfs OBJ_DIR=\$(NORMAL_BUSYBOX_DIR)/src COMPILE_RESCUE=no" >> $par_fil
				echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe install INSTALL_DIR=\$(PRJ_DIR)/$par_whe/rootfs OBJ_DIR=\$(NORMAL_BUSYBOX_DIR)/src COMPILE_RESCUE=no" >> $par_fil
			fi
		fi
		if [ "$cur_type_flag" = "driver" ]
		then
			echo "	if [ -f \$(PRJ_DIR)/$par_whe/custom_install ]; then \\" >> $par_fil
			echo "		\$(PRJ_DIR)/$par_whe/custom_install install \$(PRJ_DIR)/$par_whe/rootfs \$(AUTOCONF_DIR) normal; \\" >> $par_fil
			echo "	fi" >> $par_fil
		fi
			echo "	if [ -d \$(PRJ_DIR)/$par_whe/rootfs ]; then \\" >> $par_fil
			echo "		cp -av \$(PRJ_DIR)/$par_whe/rootfs/* \$(FS_DIR); \\" >> $par_fil
			echo "	fi" >> $par_fil
		echo "ifeq (\$(CONFIG_RESCUE_SYSTEM), y)" >> $par_fil	
		if [ "$par_dir" = ".git" ]
		then
			if [ "$cur_type_flag" = "driver" ]
			then
				echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe install INSTALL_DIR=\$(PRJ_DIR)/$par_whe/rootfs-rescue KERNEL_DIR=\$(RESCUE_KERNEL_DIR) COMPILE_RESCUE=yes" >> $par_fil
			elif [ "$cur_type_flag" = "app" ]
			then		
				echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe install INSTALL_DIR=\$(PRJ_DIR)/$par_whe/rootfs-rescue COMPILE_RESCUE=yes" >> $par_fil
			else
				echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe install INSTALL_DIR=\$(PRJ_DIR)/$par_whe/rootfs-rescue OBJ_DIR=\$(RESCUE_BUSYBOX_DIR)/src COMPILE_RESCUE=yes" >> $par_fil
			fi
		fi
		if [ "$cur_type_flag" = "driver" ]
		then
			echo "	if [ -f \$(PRJ_DIR)/$par_whe/custom_install ]; then \\" >> $par_fil
			echo "		\$(PRJ_DIR)/$par_whe/custom_install install \$(PRJ_DIR)/$par_whe/rootfs-rescue \$(AUTOCONF_DIR) rescue; \\" >> $par_fil
			echo "	fi" >> $par_fil
		fi
			echo "	if [ -d \$(PRJ_DIR)/$par_whe/rootfs-rescue ]; then \\" >> $par_fil
			echo "		cp -av \$(PRJ_DIR)/$par_whe/rootfs-rescue/* \$(RESCUE_FS_DIR); \\" >> $par_fil
			echo "	fi" >> $par_fil	
		echo "endif" >> $par_fil	
	elif [ "$cur_type_flag" = "example" ]
	then
		if [ "$par_dir" = ".git" ]
		then
			echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe all KERNEL_DIR=\$(NORMAL_KERNEL_DIR) COMPILE_RESCUE=no" >> $par_fil
			echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe install INSTALL_DIR=\$(PRJ_DIR)/$par_whe/example KERNEL_DIR=\$(NORMAL_KERNEL_DIR) COMPILE_RESCUE=no" >> $par_fil
		fi
		echo "	if [ -d \$(PRJ_DIR)/$par_whe/example ]; then \\" >> $par_fil
		echo "		cp -av \$(PRJ_DIR)/$par_whe/example/* \$(EXAMPLE_DIR); \\" >> $par_fil
		echo "	fi" >> $par_fil
	else
		if [ "$par_dir" = ".git" ]
		then
			if [ "$cur_type_flag" = "driver" ]
			then
				echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe all KERNEL_DIR=\$(NORMAL_KERNEL_DIR) COMPILE_RESCUE=no" >> $par_fil
				echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe install INSTALL_DIR=\$(PRJ_DIR)/$par_whe/rootfs KERNEL_DIR=\$(NORMAL_KERNEL_DIR) COMPILE_RESCUE=no" >> $par_fil
			elif [ "$cur_type_flag" = "app" ]
			then
				echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe all COMPILE_RESCUE=no" >> $par_fil
				echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe install INSTALL_DIR=\$(PRJ_DIR)/$par_whe/rootfs COMPILE_RESCUE=no" >> $par_fil
			else
				echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe all INSTALL_DIR=\$(PRJ_DIR)/$par_whe/rootfs OBJ_DIR=\$(NORMAL_BUSYBOX_DIR)/src COMPILE_RESCUE=no" >> $par_fil
				echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe install INSTALL_DIR=\$(PRJ_DIR)/$par_whe/rootfs OBJ_DIR=\$(NORMAL_BUSYBOX_DIR)/src COMPILE_RESCUE=no" >> $par_fil
			fi
		fi
		if [ "$cur_type_flag" = "driver" ]
		then
			echo "	if [ -f \$(PRJ_DIR)/$par_whe/custom_install ]; then \\" >> $par_fil
			echo "		\$(PRJ_DIR)/$par_whe/custom_install install \$(PRJ_DIR)/$par_whe/rootfs \$(AUTOCONF_DIR) normal; \\" >> $par_fil
			echo "	fi" >> $par_fil
		fi
			echo "	if [ -d \$(PRJ_DIR)/$par_whe/rootfs ]; then \\" >> $par_fil
			echo "		cp -av \$(PRJ_DIR)/$par_whe/rootfs/* \$(FS_DIR); \\" >> $par_fil
			echo "	fi" >> $par_fil
	fi	

	if [ "$par_num" = "5" ]
	then
		if [ "$cur_type_flag" != "rootfs-bs" ]
		then
			echo "ifeq (\$(MODULE_ONLY), yes)" >> $par_fil	
			echo "$par_mai-clean:" >> $par_fil
			echo "else" >> $par_fil
		fi
		if [ "$par_how" = "1" ]
		then
			echo "$par_mai-clean: $depend_cle" >> $par_fil
		elif [ "$par_how" = "0" ]
		then
			echo "$par_mai-clean: $par_sub-clean" >> $par_fil
		fi	
		if [ "$cur_type_flag" != "rootfs-bs" ]
		then
			echo "endif" >> $par_fil
		fi
	elif [ "$par_num" = "4" ]
	then
			echo "$par_mai-clean:" >> $par_fil
	fi
	
	if [ "$cur_type_flag" = "driver" ]
	then
		echo "	if [ -f \$(PRJ_DIR)/$par_whe/custom_install ]; then \\" >> $par_fil
		echo "		\$(PRJ_DIR)/$par_whe/custom_install uninstall \$(PRJ_DIR)/$par_whe/rootfs \$(AUTOCONF_DIR) normal; \\" >> $par_fil
		echo "	fi" >> $par_fil
	fi
	if [ "$par_dir" != ".git" ]
	then
		if [ "$cur_type_flag" = "driver" ]
		then
			echo "ifeq (\$(CONFIG_RESCUE_SYSTEM), y)" >> $par_fil	
			echo "	if [ -f \$(PRJ_DIR)/$par_whe/custom_install ]; then \\" >> $par_fil
			echo "		\$(PRJ_DIR)/$par_whe/custom_install uninstall \$(PRJ_DIR)/$par_whe/rootfs-rescue \$(AUTOCONF_DIR) rescue; \\" >> $par_fil
			echo "	fi" >> $par_fil
			echo "endif" >> $par_fil
		fi
	fi
	if [ "$par_dir" = ".git" ]
	then
		if [ "$cur_type_flag" != "rootfs-bs" ]
		then
			echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe clean" >> $par_fil
			echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe distclean" >> $par_fil
		else
			echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe clean OBJ_DIR=\$(NORMAL_BUSYBOX_DIR)/src" >> $par_fil
			echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe distclean OBJ_DIR=\$(NORMAL_BUSYBOX_DIR)/src" >> $par_fil
		fi
		if [ "$cur_type_flag" = "example" ]
		then
			echo "	rm -rf \$(PRJ_DIR)/$par_whe/example" >> $par_fil
		else
			echo "	rm -rf \$(PRJ_DIR)/$par_whe/rootfs" >> $par_fil
			echo "ifeq (\$(CONFIG_RESCUE_SYSTEM), y)" >> $par_fil	
			if [ "$cur_type_flag" = "driver" ]
			then
				echo "	if [ -f \$(PRJ_DIR)/$par_whe/custom_install ]; then \\" >> $par_fil
				echo "		\$(PRJ_DIR)/$par_whe/custom_install uninstall \$(PRJ_DIR)/$par_whe/rootfs-rescue \$(AUTOCONF_DIR) rescue; \\" >> $par_fil
				echo "	fi" >> $par_fil
			fi
			if [ "$cur_type_flag" = "rootfs-bs" ]
			then
				echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe clean OBJ_DIR=\$(RESCUE_BUSYBOX_DIR)/src" >> $par_fil
				echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe distclean OBJ_DIR=\$(RESCUE_BUSYBOX_DIR)/src" >> $par_fil
			fi
			echo "	rm -rf \$(PRJ_DIR)/$par_whe/rootfs-rescue" >> $par_fil
			echo "endif" >> $par_fil
		fi
	fi	
	echo "" >> $par_fil
}
###for 22 type###
function generate_middleware_type()
{
	par_mai=${para_arr[0]}
	par_sub=${para_arr[1]}
	par_fil=${para_arr[2]}
	par_whe=${para_arr[3]}
	par_num=${para_arr[4]}
	par_dir=${para_arr[5]}
	par_tye=${para_arr[6]}
	par_how=${para_arr[7]}
    
	if [ "$par_how" = "1" ]
	then
		depend_mak=`echo $par_sub | sed 's/,/ /g'`
		depend_cle=`echo $par_sub | sed 's/,/-clean /g'`
		depend_cle=`echo $depend_cle | sed 's/$/-clean /g'`
	fi
  	
	if [ "$cur_src_flag" = "source" ]
	then
		par_dir=".git"
	fi
  	
	if [ "$par_num" = "5" ]
	then
		echo "ifeq (\$(MODULE_ONLY), yes)" >> $par_fil	
		echo "$par_mai:" >> $par_fil
		echo "else" >> $par_fil
		if [ "$par_how" = "1" ]
		then
			echo "$par_mai: $depend_mak" >> $par_fil
		elif [ "$par_how" = "0" ]
		then
			echo "$par_mai: $par_sub" >> $par_fil
		fi
		echo "endif" >> $par_fil
	elif [ "$par_num" = "4" ]
	then
		echo "$par_mai:" >> $par_fil
	fi
  	
	if [ "$cur_rescue_flag" = "only_rescue" ]
	then 
		echo "ifeq (\$(CONFIG_RESCUE_SYSTEM), y)" >> $par_fil	
		if [ "$par_dir" = ".git" ]
		then
			echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe all COMPILE_RESCUE=yes" >> $par_fil
			echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe install LIB_INS_DIR=\$(PRJ_DIR)/$par_whe/middleware INSTALL_DIR=\$(PRJ_DIR)/$par_whe/rootfs COMPILE_RESCUE=yes" >> $par_fil
		fi
		echo "	if [ -d \$(PRJ_DIR)/$par_whe/rootfs ]; then \\" >> $par_fil
		echo "		cp -av \$(PRJ_DIR)/$par_whe/rootfs/* \$(RESCUE_FS_DIR); \\" >> $par_fil
                echo "	fi" >> $par_fil
		echo "	if [ -d \$(PRJ_DIR)/$par_whe/middleware ]; then \\" >> $par_fil
                echo "		cp -av \$(PRJ_DIR)/$par_whe/middleware/* \$(MIDDLEWARE_INS_DIR); \\" >> $par_fil
                echo "	fi" >> $par_fil
		echo "endif" >> $par_fil	
	elif [ "$cur_rescue_flag" = "rescue" ] || [ "$cur_rescue_flag" = "compile_rescue" ]
	then
		if [ "$par_dir" = ".git" ]
		then
			echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe all COMPILE_RESCUE=no" >> $par_fil
			echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe install LIB_INS_DIR=\$(PRJ_DIR)/$par_whe/middleware INSTALL_DIR=\$(PRJ_DIR)/$par_whe/rootfs COMPILE_RESCUE=no" >> $par_fil
		fi
		echo "	if [ -d \$(PRJ_DIR)/$par_whe/rootfs ]; then \\" >> $par_fil
		echo "		cp -av \$(PRJ_DIR)/$par_whe/rootfs/* \$(FS_DIR); \\" >> $par_fil
		echo "	fi" >> $par_fil
		echo "ifeq (\$(CONFIG_RESCUE_SYSTEM), y)" >> $par_fil	
		echo "	if [ -d \$(PRJ_DIR)/$par_whe/rootfs ]; then \\" >> $par_fil
		echo "		cp -av \$(PRJ_DIR)/$par_whe/rootfs/* \$(RESCUE_FS_DIR); \\" >> $par_fil
		echo "	fi" >> $par_fil
		echo "endif" >> $par_fil	
		echo "	if [ -d \$(PRJ_DIR)/$par_whe/middleware ]; then \\" >> $par_fil
		echo "		cp -av \$(PRJ_DIR)/$par_whe/middleware/* \$(MIDDLEWARE_INS_DIR); \\" >> $par_fil
		echo "	fi" >> $par_fil
	else
		if [ "$par_dir" = ".git" ]
		then
		echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe all" >> $par_fil
		echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe install LIB_INS_DIR=\$(PRJ_DIR)/$par_whe/middleware INSTALL_DIR=\$(PRJ_DIR)/$par_whe/rootfs" >> $par_fil
		fi
		echo "	if [ -d \$(PRJ_DIR)/$par_whe/rootfs ]; then \\" >> $par_fil
		echo "		cp -av \$(PRJ_DIR)/$par_whe/rootfs/* \$(FS_DIR); \\" >> $par_fil
		echo "	fi" >> $par_fil
		echo "	if [ -d \$(PRJ_DIR)/$par_whe/middleware ]; then \\" >> $par_fil
                echo "		cp -av \$(PRJ_DIR)/$par_whe/middleware/* \$(MIDDLEWARE_INS_DIR); \\" >> $par_fil
                echo "	fi" >> $par_fil
	fi
				
	if [ "$par_num" = "5" ]
	then
		echo "ifeq (\$(MODULE_ONLY), yes)" >> $par_fil	
		echo "$par_mai-clean:" >> $par_fil
		echo "else" >> $par_fil
		if [ "$par_how" = "1" ]
		then
			echo "$par_mai-clean: $depend_cle" >> $par_fil
		elif [ "$par_how" = "0" ]
		then
			echo "$par_mai-clean: $par_sub-clean" >> $par_fil
		fi
		echo "endif" >> $par_fil
	elif [ "$par_num" = "4" ]
	then
		echo "$par_mai-clean:" >> $par_fil
	fi
		
	if [ "$par_dir" = ".git" ]
	then
		echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe clean" >> $par_fil
		echo "	\$(MAKE) -C \$(PRJ_DIR)/$par_whe distclean" >> $par_fil
		echo "	rm -rf \$(PRJ_DIR)/$par_whe/rootfs" >> $par_fil  
		echo "	rm -rf \$(PRJ_DIR)/$par_whe/middleware" >> $par_fil  
	fi
	echo "" >> $par_fil
}

#abstract include file
function find_include()
{
	for line in `cat $1`
	do
		include=`echo $line | sed -n "s/<\(.*\)>/\1/p"`
		if [ "$include" != "" ]
		then
			echo $include
			break
		else
			echo ""
		fi
	done
}

#get every line type
function judge_format()
{
	line_judg=$1 
   
	if echo $line_judg | grep "^path=.*" 1>/dev/null
	then
		return 8
	elif echo $line_judg | grep "^depend_module=.*" 1>/dev/null
	then 
		return 7
	elif echo $line_judg | grep "^type=.*" 1>/dev/null
	then
		return 5
	elif echo $line_judg | grep "^\[.*\]" 1>/dev/null
	then
		if echo $line_judg | grep "^\[common\]" 1>/dev/null
		then
			return 9
		else
			return 6
		fi
	elif echo $line_judg | grep "^\#.*" 1>/dev/null
	then
		return 4
	elif echo $line_judg | grep "<.*>" 1>/dev/null
	then
		return 3
	elif echo $line_judg | grep "^$" 1>/dev/null
	then
		return 2
	else
		return 1
	fi
}

#check reduplication
function check_reduplication()
{
	empty=0
	for line in `cat $1`
	do
		module=`echo $line | sed -n "s/\[\(.*\)\]/\1/p"`
		module_so=`echo $line | sed -n "s/{\(.*\)}/\1/p"`

		if [ "$module_so" != "" ]
		then
			arr_check[$arr_check_index]=$module_so
			let arr_check_index++
			empty=1
			continue
		fi

		if [ "$module" != "" ]
		then
			arr_check[$arr_check_index]=$module
			let arr_check_index++
			empty=1
		fi
	done
	
	if [ $empty = 1 ]
	then
		file_stop[$file_stop_index]=$1
		let file_stop_index++
		file_stop[$file_stop_index]=$arr_check_index
		let file_stop_index++
	fi	
}

#check format
function check_format()
{
	line_num=0
	common_flag=0
	while read line
	do
		pre_result=$judge_result
		judge_format $line
		judge_result=$?
		let line_num++
    
		###if [common],shoule not have path=/depend_module/type=###
		if [ "$common_flag" = "1" ]
		then
			if [ "$judge_result" = 8 ]||[ "$judge_result" = 7 ]||[ "$judge_result" = 5 ]
			then
				result="format wrong: $line_num($1)->should not have 'path' ,'depend_module' or 'type' in module '[common]'"	
				return	1
			fi
		fi
    
		###if [common],don't judge###
		if [ "$judge_result" = 9 ]
		then
			common_flag=1
		fi
    
		if [ "$judge_result" = 6 ]
		then
			common_flag=0
		fi
    
		if [ "$common_flag" = "1" ]
		then
			continue
		fi
    
		###make sure []-path-depend/type###
		if [ "$square" != "1" ] && [ "$square" != "2" ] 
		then
			square="0"
		fi
    
		if [ "$square" = "1" ]
		then
			if [ $judge_result != 8 ]
			then
				result="format wrong: $line_num($1)->please add 'path' behind module '[]'"	
				return	1
			elif [ $judge_result = 8 ]
			then
				square_flag="1"
			fi
		fi  
    
		if [ "$square" = "2" ]
		then
			if [ $judge_result != 7 ]&&[ $judge_result != 5 ]
			then
				result="format wrong: $line_num($1)->please add 'depend_module' or 'type' behind 'path'"	
				return	1
			elif [ $judge_result = 7 ]||[ $judge_result = 5 ]
			then
				square_flag="0"
				square="0"
			fi
		fi 
    
		if [ "$depend_exist" = "1" ]
		then
			depend_exist="0"
			if [ $judge_result != 5 ]
			then
				result="format wrong: $line_num($1)->please add 'type=' behind 'depend_module'"	
				return	1
			fi
		fi
    
		###<>-nothing###
		if [ "$sharp_bracket" = "1" ]
		then
			sharp_bracket="0"
			if [ $judge_result != 4 ]&&[ $judge_result != 2 ]
			then
				result="format wrong: $line_num($1)->there should not be something behind '<>' "	
				return	1
			fi
		fi
    
		case $judge_result	in
		1)
		result="format wrong: $line_num($1) ->hasn't this format"	
		return	1
		;;
		3)
		sharp_bracket="1"
		;;
		5)
		if [ $pre_result != 0 ]
		then
			if [ $pre_result != 8 ]&&[ $pre_result != 7 ]
			then
				result="format wrong: $line_num($1)->'type' should be after 'depend_module' or 'path'"	
				return	1
			fi
		fi
		;;
		6)
		square="1"
		common_flag=0
		;;
		7)
		depend_exist="1"
		if [ $pre_result != 0 ]
		then
			if [ $pre_result != 8 ]
			then
				result="format wrong: $line_num($1)->please place 'depend_module' after 'path'"	
				return	1
			fi	
		fi
		;;
		8)
		if [ $pre_result != 0 ]
		then
			if [ $pre_result = 3 ]
			then
				result="format wrong:$line_num($1)->please delete 'path'"	
				return	1
			fi
    	
			if [ $pre_result != 6 ]
			then
				result="format wrong: $line_num($1)->'path' should be behind module '[]'"	
				return	1
			fi
    	
			if [ "$square_flag" = "1" ]
			then
				square_flag=0
				square="2"
			fi
		fi
		;;
		*)
		;;
		esac
	done < $1 
	if [ $judge_result != 2 ]
	then
		result="format wrong: $line_num($1) ,please add a space line at the end"	
		return	1
	fi
}

# $1: type string
# $2 section name
check_type_flag()
{
	type_string=$1
	type_temp=""
	rescue_flag=0
	type_flag=0
	nosrc_flag=0
	end_while=0
	
	while [ "$end_while" = "0" ]
	do
		next_string=`echo $type_string | sed -n "s/|\(.*\)/\1/p"`
		if [ "$next_string" != "" ]
		then
			type_temp=`echo ${type_string%%|*}`
			type_string=`echo ${type_string#*|}`
		else
			type_temp=$type_string
			end_while=1
		fi
		if [ "$type_temp" = "only_rescue" ] || [ "$type_temp" = "rescue" ] || [ "$type_temp" = "compile_rescue" ]
		then
			if [ "$rescue_flag" = "0" ]
			then
				rescue_flag=1
				cur_rescue_flag=$type_temp
			else
				echo "ERROR: rescue flag repeat please check [$2] type !!!"
				rm -rf $dst_file
				exit 8
			fi
		elif [ "$type_temp" = "rootfs" ] || [ "$type_temp" = "driver" ] || [ "$type_temp" = "app" ] || [ "$type_temp" = "bootloader" ] || [  "$type_temp" = "kernel" ] || [  "$type_temp" = "tool" ] || [ "$type_temp" = "middleware" ] || [ "$type_temp" = "rootfs-bs" ] || [ "$type_temp" = "example" ]
		then
			if [ "$type_flag" = "0" ]
			then
				type_flag=1
				cur_type_flag=$type_temp
			else
				echo "ERROR: type flag repeat please check [$2] type !!!"
				rm -rf $dst_file
				exit 8
			fi
		elif [ "$type_temp" = "source" ]
		then
			if [ "$nosrc_flag" = "0" ]
			then
				nosrc_flag=1
				cur_src_flag=$type_temp
			else
				echo "ERROR: nosrc flag repeat please check [$2] type !!!"
				rm -rf $dst_file
				exit 8
			fi
		else
				echo "ERROR: invalid flag string please check [$2] type !!!"
				rm -rf $dst_file
				exit 8			
		fi
	done
}

#####create dst file Makefile.mod(1):for [non-common]###
function all_files_generate()
{
	unset result
	unset module_arr
	unset	module_name
	index=0
	index_so=0
	flag_so=0
	flag=0
	for line in `cat $1`
	do
		module=`echo $line | sed -n "s/\[\(.*\)\]/\1/p"`
		
		if [ "$module" != "" ]&&[ "$module" != "common" ]
		then
			module_name[$index]=$module
			module_all[$index_all]=$module
			flag=1
			let index++
			let index_all++
		fi
	done
	
	module_count=${#module_name[@]}
	[ $module_count -eq 0 ] && return 0
  
	###output modules typle
	if [ "$1" = "release_modules" ]
	then
		echo
		echo
		echo "#####release_modules: release to customer,code is opened to customer#####"
	elif [ "$1" = "modules" ]
	then
		echo
		echo 
		echo "#####modules: this is used for the sonix staff#####"
	fi
  
	if [	$module_count = 0 ] && [	$module_num = 0 ]
	then
		echo ":none modules in this file"
	fi

	###generate Makefile.mod
	index=0
	flag_dri=0
	flag_app=0
	flag_mid=0
	while :
	do
		section=${module_name[$index]}
		path=`read_norkey $1 $section path`
		depend_module=`read_norkey $1 $section depend_module`
		type=`read_norkey $1 $section type`
		

		if [ $module_count != 0 ]
		then
			echo -n $section
			let output_count++
			num=`echo -n $section | wc -c`
			if [ "$num" -lt "8" ]; then
				echo -n -e "\t\t\t"
			elif [ "$num" -lt "16" ]; then
				echo -n -e "\t\t"
			elif [ "$num" -lt "24" ]; then
				echo -n -e "\t"
			fi
			if [ $output_count -ge 3 ]; then
				echo
				output_count=0
			fi
		fi	
		
		if [ ! -d "$project_dir/$path" ]
		then
			result="dir '$path' doesn't exist"
			return 2
		fi
  
		if echo $path | grep "^driver.*" 1>/dev/null
		then
			if [ $flag_dri = "0" ]
			then
				flag_dri=1
				echo "##############################" >> $2
				echo "###those are driver modules###" >> $2
				echo "##############################" >> $2
				echo "" >> $2
			fi
		elif echo $path | grep "^app.*" 1>/dev/null
		then
			if [ $flag_app = "0" ]
			then
				flag_app=1
				echo "##############################" >> $2
				echo "###those are app modules######" >> $2
				echo "##############################" >> $2
				echo "" >> $2
			fi
		elif echo $path | grep "^middleware.*" 1>/dev/null
		then
			if [ $flag_mid = "0" ]
			then
				flag_mid=1
				echo "##################################" >> $2
				echo "###those are middleware modules###" >> $2
				echo "##################################" >> $2
				echo "" >> $2
			fi
		fi
		
		which_depend_type="0"
		has_depend="5"
		if [ "$depend_module" != "null" ]
		then
			if echo $depend_module | grep "," 1>/dev/null
			then
				which_depend_type="1"
			fi
		else
			has_depend="4"
		fi
	 	 
		########
		unset para_arr
		para_arr[0]=$section
		para_arr[1]=$depend_module
		para_arr[2]=$2
		para_arr[3]=$path
		para_arr[4]=$has_depend

		cur_rescue_flag=""
		cur_type_flag=""
		cur_src_flag=""
		check_type_flag $type $section
	
		if [ "$cur_type_flag" = "driver" ] || [ "$cur_type_flag" = "app" ] || [ "$cur_type_flag" = "rootfs-bs" ] || [ "$cur_type_flag" = "example" ] 
		then
			para_arr[5]=$git_exist
			para_arr[6]=$type
			para_arr[7]=$which_depend_type
			generate_app_driver_bs_type ${para_arr[@]}
		fi
	  
		if [ "$cur_type_flag" = "middleware" ]
		then
			para_arr[5]=$git_exist
			para_arr[6]=$type
			para_arr[7]=$which_depend_type
			generate_middleware_type ${para_arr[@]}  		
		fi
	   
		if [ "$cur_type_flag" = "rootfs" ]
		then
			if [ "$cur_src_flag" = "" ]
			then
				echo "ERROR: rootfs must have source type flag , please check [$section] type !!!"
				exit 8
			fi
			para_arr[5]=$which_depend_type
			generate_rootfs_type ${para_arr[@]}	
		fi
	   
		if [ "$cur_type_flag" = "kernel" ]
		then
			para_arr[5]=$git_exist
                        para_arr[6]=$type
                        para_arr[7]=$which_depend_type
			generate_kernel_type ${para_arr[@]}
		fi

		if [ "$cur_type_flag" = "bootloader" ]
		then
			para_arr[5]=$git_exist
                        para_arr[6]=$type
                        para_arr[7]=$which_depend_type
			generate_bootloader_type ${para_arr[@]}
		fi

		if [ "$cur_type_flag" = "tool" ]
		then
			echo "$section=\$(PRJ_DIR)/$path" >> $2
			echo "" >> $2
		fi
	      
		let index++
		if [ $index -ge $module_count ]
		then
			break	
		fi
	done
	
}

create_def_version() 
{ 
	mod_version=$1 
	date_time=`date +%Y%m%d_%H%M` 
	echo "#ifndef __SONIX_MOD_VERSION_H" > $mod_version 
	echo "#define __SONIX_MOD_VERSION_H" >> $mod_version 
	echo "" >> $mod_version 

	for line in `cat $release_file` 
	do 
		module=`echo $line | sed -n "s/^\[\(.*\)\]/\1/p"` 
		if [ "$module" = "" ] || [ "$module" = "common" ] 
		then 
			continue 
		fi 

		module=`echo $module | tr "[\-]" "[_]"` 
		module=`echo $module | tr "[.]" "[_]"` 
		module=`echo $module | tr "[a-z]" "[A-Z]"` 

		str_time="#define $module""_TIME \"$date_time\"" 
		echo $str_time >> $mod_version 
		str_commit="#define $module""_HASH \"local build\"" 
		echo $str_commit >> $mod_version 
		str_version="#define $module""_BRANCH \"null\"" 
		echo $str_version >> $mod_version 
		echo "" >> $mod_version     
		if [ "$module" = "BOARD_INFO" ] 
		then 
			echo $str_time > $boardinfo_version_file 
			echo $str_commit >> $boardinfo_version_file     
			echo $str_version >> $boardinfo_version_file 
		fi 
	done 
	echo "" >> $mod_version 
	echo "#endif" >> $mod_version 
} 

###main###
script_dir=`cd "$(dirname "$0")";pwd`
project_dir=`cd "$script_dir/..";pwd`
parse_file=""

cur_type_flag=""
cur_rescue_flag=""
cur_src_flag=""
###parameter analyse###
if [ $# -lt 1 ]
then
	parse_file="modules"
else
	parse_file=$1
fi

boardinfo_version_file=$project_dir/board-info/.version
version_header_file=$script_dir/include/generated/snx_mod_version.h 
release_file=$script_dir/release_modules 
version_file=$script_dir/.mod_version 
# create default .mod_version 
if [ ! -f  "$version_file" ] 
then 
	create_def_version $version_file 
fi 

if [ ! -f $parse_file ]
then
	echo "'$parse_file' config file can not find."
	exit 2
fi

###find include file###
include_file=`find_include $parse_file`
if [ "$include_file" != "" ]
then
	if [ ! -f $include_file ]
	then
		echo "Error! Can't find $include_file"
		exit 3
	else
		file_name[0]=$include_file
		file_name[1]=$parse_file
	fi
else
	file_name[0]=$parse_file
fi

###find target file###
delete_dir=`pwd`
delete_file=$delete_dir/Makefile.mod

###count amount of file###
file_count=${#file_name[@]}

###check format###
index_file=0
while :
do 
	file=${file_name[$index_file]}
	check_format $file
	if [ $? -ne 0 ]
	then
		echo "reason: $result"
		exit 6
	fi
	let index_file++
	if [ $index_file -ge $file_count ]
	then
		break
	fi
done

###check modules reduplication###
unset file_stop
file_stop_index=0
unset arr_check
arr_check_index=0
index_file=0
while :
do 
	file=${file_name[$index_file]}
	check_reduplication $file
	if [ $? -ne 0 ]
	then
		echo "fail to set environment in the step of executing 'check_reduplication()' in checking module reduplication"
		exit 6
	fi
	let index_file++
	if [ $index_file -ge $file_count ]
	then
		break
	fi
done

arr_check_count=${#arr_check[@]}
check_num=0
while :
do 
	active_name=${arr_check[$check_num]}
	let compare_num=$check_num+1
	while	:
	do
		compare_name=${arr_check[$compare_num]}
    
		###reduplication comes out
		if [ "$active_name" = "$compare_name" ]
		then
			file_stop_num=${#file_stop[@]}
			find_index=1
			find_or_ac=0
			find_or_co=0
			while	:
			do
				what_num=${file_stop[$find_index]}
        
				if [ $find_or_ac = 0 ]
				then
					if [ $what_num -gt $check_num ]
					then
						let find_it_acindex=$find_index-1
						find_it_active=${file_stop[$find_it_acindex]}
						find_or_ac=1
					fi
				fi
        
				if [ $find_or_co = 0 ]
				then
					if [ $what_num -gt $compare_num ]
					then
						let find_it_coindex=$find_index-1
						find_it_compare=${file_stop[$find_it_coindex]}
						find_or_co=1
					fi
				fi
        
				let find_index+=2
				if [ $find_index -ge $file_stop_num ]
				then
					break
				fi
			done

			echo "format wrong: '$active_name' in '$find_it_active' and '$compare_name' in '$find_it_compare' reduplication"
			exit 6
		fi
    
		let compare_num++
		if [ $compare_num -ge $arr_check_count ]
		then
			break
		fi
	done
	let check_num++
	if [ $check_num -ge $arr_check_count ]
	then
		break
	fi
done


###judge if in charge of git###
git_dir=`pwd`
git_exist=`find_project_dir $git_dir`
git_exist=${git_exist##*/}

#####create dst file Makefile.mod(1):for [non-common]###
rm -rf $delete_file
dst_file=Makefile.mod
touch $dst_file
if [ $? -ne 0 ]
then
	echo "create file  'Makefile.mod' fail"
	rm -rf $delete_file
	exit 5
fi
echo "#This file is automatically generated" > $dst_file
echo "" >> $dst_file

#####create dst file Makefile.mod(3):for [common]###
index_all=0
index_file=0
while :
do 
	file=${file_name[$index_file]}
	find_common $file $dst_file
	if [ $? -ne 0 ]
	then 
		echo "fail to set environment : $result"
		rm -rf $delete_file
		exit 6
	fi
	let index_file++
	if [ $index_file -ge $file_count ]
	then
		break
	fi
done

index_all=0
index_file=0
while :
do 
	file=${file_name[$index_file]}
	all_files_generate $file $dst_file
	if [ $? -ne 0 ]
	then 
		echo "fail to set environment : $result"
		rm -rf $delete_file
		exit 6
	fi
	let index_file++
	if [ $index_file -ge $file_count ]
	then
		break
	fi
done

#####create dst file Makefile.mod(2):for [common]###
index_index=0
while :
do 
	o_module=${module_all[$index_index]}
	get_this=$get_this+$o_module
	let index_index++
	if [ $index_index -ge $index_all ]
	then
		break
	fi
done

get_this=${get_this#*+}
get_this=`echo $get_this | sed 's/+/ /g'`
echo "snx_modules :=$get_this" >> $dst_file
echo "" >> $dst_file

#####create dst file Makefile.mod(3):for [common]###
#index_all=0
#index_file=0
#while :
#do 
#	file=${file_name[$index_file]}
#	find_common $file $dst_file
#	if [ $? -ne 0 ]
#	then 
#		echo "fail to set environment : $result"
#		rm -rf $delete_file
#		exit 6
#	fi
#	let index_file++
#	if [ $index_file -ge $file_count ]
#	then
#		break
#	fi
#done
echo
echo "set environment sucessfully!"
