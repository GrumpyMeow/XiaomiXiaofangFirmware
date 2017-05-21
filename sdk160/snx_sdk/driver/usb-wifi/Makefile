PWD		:= $(shell pwd)
MAKE            ?= make
SRC_DIR		:= $(PWD)/src
INSTALL_DIR	?= $(PWD)


.PHONY: all clean distclean install

all:
	$(MAKE) -C $(SRC_DIR) $@ KERNEL_DIR=$(abspath $(KERNEL_DIR))


clean:
	$(MAKE) -C $(SRC_DIR) $@

install:
	$(MAKE) -C $(SRC_DIR) $@ INSTALL_DIR=$(abspath $(INSTALL_DIR))

