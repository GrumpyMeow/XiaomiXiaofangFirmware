MAKE            ?= make
PWD             := $(shell pwd)
ARCH			?= arm
TARGET			?= $(ARCH)-linux
CROSS_COMPILE	?= $(TARGET)-
INSTALL_DIR		?= $(PWD)/rootfs
BIN_INSTALL_DIR	:= /usr/bin/

SRC_DIR		= $(PWD)/hostapd

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
		$(MAKE) -C $$i $@ DESTDIR=$(abspath $(INSTALL_DIR)) BINDIR=$(BIN_INSTALL_DIR); \
	done

