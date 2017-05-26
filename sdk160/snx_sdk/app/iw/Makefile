MAKE            ?= make
PWD             := $(shell pwd)
ARCH			?= arm
TARGET			?= $(ARCH)-linux
CROSS_COMPILE	?= $(TARGET)-
INSTALL_DIR		?= $(PWD)/rootfs
BIN_INSTALL_DIR	:= $(INSTALL_DIR)/usr/bin
SRC_DIR		= $(PWD)/src

.PHONY: all clean distclean install

all:
		export PKG_CONFIG_PATH=$(PWD)/../libnl/output/lib/pkgconfig;			\
		$(MAKE) -C $(SRC_DIR) iw;	\
		/bin/cp -f $(SRC_DIR)/iw $(SRC_DIR)/../../rootfs/usr/bin/; 

clean:
		$(MAKE) -C $(SRC_DIR) $@;	

install:
		$(MAKE) -C $(SRC_DIR) $@ INSTALL_DIR=$(abspath $(BIN_INSTALL_DIR));


