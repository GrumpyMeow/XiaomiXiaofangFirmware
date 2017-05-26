MAKE            ?= make
PWD             := $(shell pwd)
ARCH			?= arm
TARGET			?= $(ARCH)-linux
CROSS_COMPILE	?= $(TARGET)-
INSTALL_DIR		?= $(PWD)/rootfs
BIN_INSTALL_DIR	:= $(INSTALL_DIR)/usr/bin/hostapd-0.8_rtw

SRC_DIR		= $(PWD)/src

.PHONY: all clean distclean install

all:
	for i in $(SRC_DIR);	\
	do						\
		$(MAKE) -C $$i $@;	\
	done

clean:
	for i in $(SRC_DIR);	\
	do						\
		$(MAKE) -C $$i $@;	\
	done

install:
	for i in $(SRC_DIR);	\
	do						\
		$(MAKE) -C $$i $@ INSTALL_DIR=$(abspath $(BIN_INSTALL_DIR)); \
	done

