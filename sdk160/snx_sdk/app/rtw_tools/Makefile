MAKE            ?= make
PWD             := $(shell pwd)
ARCH			?= arm
TARGET			?= $(ARCH)-linux
CROSS_COMPILE	?= $(TARGET)-
INSTALL_DIR		?= $(PWD)/rootfs
SRC_DIR = $(PWD)/hostapd
SRC_DIR2 = $(PWD)/wpa_supplicant
CPP := $(CROSS_COMPILE)g++
CC := $(CROSS_COMPILE)gcc
AR := $(CROSS_COMPILE)ar
RANLIB := $(CROSS_COMPILE)ranlib


.PHONY: all clean distclean install

all:

		
		#$(MAKE) -C $(SRC_DIR) install;	\
		
		$(MAKE) -C $(SRC_DIR2) all;\		
		$(MAKE) -C $(SRC_DIR2) install;	
		#$(MAKE) -C $(SRC_DIR) all;	

clean:
		$(MAKE) -C $(SRC_DIR) $@;	
		$(MAKE) -C $(SRC_DIR2) $@;	

install:
		#$(MAKE) -C $(SRC_DIR) $@ INSTALL_DIR=$(abspath $(BIN_INSTALL_DIR));


