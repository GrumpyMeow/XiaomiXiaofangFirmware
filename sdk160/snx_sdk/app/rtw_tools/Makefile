MAKE            ?= make
PWD             := $(shell pwd)
ARCH			?= arm
TARGET			?= $(ARCH)-linux
CROSS_COMPILE	?= $(TARGET)-
INSTALL_DIR		?= $(PWD)/rootfs
#BIN_INSTALL_DIR	:= $(INSTALL_DIR)/usr/bin
SRC_DIR		= $(PWD)/hostapd
SRC_DIR2		= $(PWD)/wpa_supplicant
CPP     	:= $(CROSS_COMPILE)g++
CC      	:= $(CROSS_COMPILE)gcc
AR      	:= $(CROSS_COMPILE)ar
RANLIB      := $(CROSS_COMPILE)ranlib


.PHONY: all clean distclean install

all:

		$(MAKE) -C $(SRC_DIR) all;	\
		$(MAKE) -C $(SRC_DIR2) all;	
		#mkdir -p $(SRC_DIR)/../rootfs/usr/bin/;  	\
		#/bin/cp -f $(SRC_DIR)/iw $(SRC_DIR)/../rootfs/usr/bin/; 

clean:
		$(MAKE) -C $(SRC_DIR) $@;	
		$(MAKE) -C $(SRC_DIR2) $@;	

install:
		#$(MAKE) -C $(SRC_DIR) $@ INSTALL_DIR=$(abspath $(BIN_INSTALL_DIR));


