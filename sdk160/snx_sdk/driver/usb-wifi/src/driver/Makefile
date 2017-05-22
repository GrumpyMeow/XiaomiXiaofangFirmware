PWD		:= $(shell pwd)
MAKE            ?= make
ARCH		?= arm
CROSS_COMPILE	?= $(ARCH)-linux-
INSTALL_DIR	?= $(PWD)/../../
vKERNEL		?= 2.6.35.12
DRIVER_INS_DIR	:= $(INSTALL_DIR)/lib/modules/$(vKERNEL)/kernel/drivers
DAT_DIR		:= $(INSTALL_DIR)

STRIP		:= $(CROSS_COMPILE)strip

export ARCH CROSS_COMPILE

#include the snx_sdk.conf
-include $(AUTOCONF_DIR)/config/snx_sdk.conf

SUB_DIRS-y :=
SUB_DIRS-n :=
SUB_DIRS-  :=

SUB_DIRS-$(CONFIG_MODULE_USB_WIFI_RT3070AP) += rt3070_rt5370AP_v2.7.1.0
SUB_DIRS-$(CONFIG_MODULE_USB_WIFI_RT5370) += rt5370
SUB_DIRS-$(CONFIG_MODULE_USB_WIFI_RTL8188EUS) += rtl8188eus
SUB_DIRS-$(CONFIG_MODULE_USB_WIFI_RTL8188EUS_4_1_8) += rtl8188EUS_v4.1.8_9499
SUB_DIRS-$(CONFIG_MODULE_USB_WIFI_RTL8188EUS_4_3_0_3) += rtl8188EUS_v4.3.0.3_10997
SUB_DIRS-$(CONFIG_MODULE_USB_WIFI_RTL8188EUS_4_3_0_8) += rtl8188EUS_linux_v4.3.0.8_13968.20150417
SUB_DIRS-$(CONFIG_MODULE_USB_WIFI_RTL8188EUS_4_3_15) += rtl8188EUS_v4.3.15_13239_simpleconfig
SUB_DIRS-$(CONFIG_MODULE_USB_WIFI_RTL8191SU) += rtl8191su
#SUB_DIRS-$(CONFIG_MODULE_USB_WIFI_MT7601U) += mt7601u
SUB_DIRS-$(CONFIG_MODULE_USB_WIFI_MT7601U) += Sonix_MT7601_v3.0.0.9
SUB_DIRS-$(CONFIG_MODULE_USB_WIFI_MT7601U_STA_SMCT) += mt7601u_sta_smct_v1_5
SUB_DIRS-$(CONFIG_MODULE_USB_WIFI_MT7601U_AP) += MT7601U_LinuxAP_3.0.0.1_20130802
SUB_DIRS-$(CONFIG_MODULE_USB_WIFI_RTL8188EUS_4_3_08_13968) += rtl8188EUS_linux_v4.3.0.8_13968.20150417

SUB_DIRS-$(CONFIG_MODULE_USB_WIFI_RTL8188C_8192C) += rtl8188C_8192C_usb_linux_v4.0.2_9000.20130911
#SUB_DIRS-$(CONFIG_MODULE_USB_WIFI_BCM43143B0) += bcmdhd-usb-1.88.56.3.x
SUB_DIRS-$(CONFIG_MODULE_USB_WIFI_BCM43143B0) += bcmdhd-usb.1.88.56.3.x.hik

.PHONY: all clean install

precheck:
	@ if [ -z "$(AUTOCONF_DIR)" ]; then \
		echo "Error! Please set 'AUTOCONF' directory by 'AUTOCONF_DIR' variable"; \
		exit 1; \
	else \
		if [ ! -e "$(AUTOCONF_DIR)/config/snx_sdk.conf" ]; then \
			echo "include/config/snx_sdk.conf is missing."; \
			exit 1; \
		fi; \
	fi;


all: precheck
	@ if [ -z "$(KERNEL_DIR)" ]; then \
		echo "Error! Please set kernel directory by 'KERNEL_DIR' variable"; \
		exit 1; \
	fi;
	@ for dir in $(SUB_DIRS-n); do echo "yes: " $$dir; done
	@ for dir in $(SUB_DIRS-y); do echo "no: " $$dir; done
	@ for dir in $(SUB_DIRS-); do echo "unset: " $$dir; done
	
	@ for dir in $(SUB_DIRS-y); do $(MAKE) -C $$dir KERNELDIR=$(abspath $(KERNEL_DIR)/src) INSTALLDIR=$(abspath $(DRIVER_INS_DIR)) || exit 1; done

clean:
	@ for dir in $(SUB_DIRS-y) $(SUB_DIRS-n) $(SUB_DIRS-); do $(MAKE) -C $$dir $@ || exit 1; done

install: precheck
	@ for dir in $(SUB_DIRS-y); do $(MAKE) -C $$dir $@ INSTALLDIR=$(abspath $(DRIVER_INS_DIR)) DAT_DIR=$(abspath $(DAT_DIR)) || exit 1; done

	$(STRIP) -d $(DRIVER_INS_DIR)/8188eu.ko
#	$(STRIP) -d $(DRIVER_INS_DIR)/8712u.ko
#	$(STRIP) -d $(DRIVER_INS_DIR)/rt5370sta.ko

