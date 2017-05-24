MAKE            ?= make
PWD             := $(shell pwd)
SRC_DIR		?= $(PWD)/src
INSTALL_DIR	?= $(PWD)/rootfs

.PHONY: all clean distclean install

all: 
	$(MAKE) -C $(SRC_DIR)

clean:
	$(MAKE) -C $(SRC_DIR) $@


install:
	$(MAKE) -C $(SRC_DIR) $@ INSTALL_DIR=$(abspath $(INSTALL_DIR))

