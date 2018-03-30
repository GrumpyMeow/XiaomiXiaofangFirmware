MAKE            ?= make
PWD             := $(shell pwd)
ARCH			?= arm
TARGET			?= $(ARCH)-linux
CROSS_COMPILE	?= $(TARGET)-
INSTALL_DIR		?= $(PWD)/rootfs
BIN_INSTALL_DIR	:= $(INSTALL_DIR)/usr/bin
SRC_DIR		= $(PWD)/src
CPP     	:= $(CROSS_COMPILE)g++
CC      	:= $(CROSS_COMPILE)gcc
AR      	:= $(CROSS_COMPILE)ar
RANLIB      := $(CROSS_COMPILE)ranlib
export PKG_CONFIG_PATH =$(abspath $(PWD)/../libnl/output/lib/pkgconfig )


.PHONY: all clean distclean install

all:

		$(MAKE) -C $(SRC_DIR) iw;	\
		mkdir -p $(SRC_DIR)/../rootfs/usr/bin/;  	\
		/bin/cp -f $(SRC_DIR)/iw $(SRC_DIR)/../rootfs/usr/bin/; 
		mkdir -p $(SRC_DIR)/../rootfs/lib/;  	\
		/bin/cp -f $(PWD)/../libnl/output/lib/libnl-genl-3.so.200 $(SRC_DIR)/../rootfs/lib/; \
		/bin/cp -f $(PWD)/../libnl/output/lib/libnl-3.so.200 $(SRC_DIR)/../rootfs/lib/;

clean:
		$(MAKE) -C $(SRC_DIR) $@;	

install:
		$(MAKE) -C $(SRC_DIR) $@ INSTALL_DIR=$(abspath $(BIN_INSTALL_DIR)) DESTDIR=$(abspath $(BIN_INSTALL_DIR));


