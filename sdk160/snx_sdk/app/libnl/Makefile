MAKE            ?= make
PWD             := $(shell pwd)
ARCH			?= arm
TARGET			?= $(ARCH)-linux
CROSS_COMPILE	?= $(TARGET)-
INSTALL_DIR		?= $(PWD)/output
BIN_INSTALL_DIR	:= $(INSTALL_DIR)/usr/bin

SRC_DIR		= $(PWD)/src
INSTALL_DIR	= $(PWD)/output

.PHONY: all clean distclean install

all:
	cd $(SRC_DIR); 	\
	echo $(TARGET);	\
	./configure --host=$(TARGET) --target=$(TARGET) --prefix=$(abspath $(INSTALL_DIR)); 	\
	$(MAKE) -C $(SRC_DIR) $@;				
	$(MAKE) -C $(SRC_DIR) install INSTALL_DIR=$(abspath $(INSTALL_DIR)); 

clean:
	$(MAKE) -C $(SRC_DIR) $@;

install:	
	

