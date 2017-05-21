PWD		:= $(shell pwd)
INSTALL_DIR	?= ../../driver-test-ap

.PHONY: install
install:
	@ if [ ! -d $(INSTALL_DIR) ]; \
	then \
		install -d $(INSTALL_DIR); \
	fi
	install -c wifi.sh $(INSTALL_DIR)

