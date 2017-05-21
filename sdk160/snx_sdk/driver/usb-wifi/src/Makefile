PWD		:= $(shell pwd)
MAKE            ?= make
INSTALL_DIR	?= $(PWD)/../
DRIVER_SRC_DIR	:= $(PWD)/driver
TEST_SRC_DIR	:= $(PWD)/test
TEST_INS_DIR	:= $(INSTALL_DIR)/driver-test-ap
BUILD_TEST	?= NO


.PHONY: all clean install
all:
	$(MAKE) -C $(DRIVER_SRC_DIR) $@ KERNEL_DIR=$(abspath $(KERNEL_DIR))

clean: 
	$(MAKE) -C $(DRIVER_SRC_DIR) $@

install:
	$(MAKE) -C $(DRIVER_SRC_DIR) $@ INSTALL_DIR=$(abspath $(INSTALL_DIR))
	@ if [ "$(findstring YES,$(BUILD_TEST))" ]; then \
		$(MAKE) -C $(TEST_SRC_DIR) $@ INSTALL_DIR=$(abspath $(TEST_INS_DIR)); \
	fi;

