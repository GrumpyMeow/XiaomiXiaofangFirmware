################################################################
#
# SONIX SDK Makefile 
#
################################################################

# Do not:
# o  print "Entering directory ...";
MAKEFLAGS += --no-print-directory

# Avoid funny character set dependencies
unexport LC_ALL
LC_COLLATE=C
LC_NUMERIC=C
export LC_COLLATE LC_NUMERIC


# To put more focus on warnings, be less verbose as default
# Use 'make V=1' to see the full commands

ifeq ("$(origin V)", "command line")
  KBUILD_VERBOSE = $(V)
endif
ifndef KBUILD_VERBOSE
  KBUILD_VERBOSE = 0
endif

ifeq ("$(origin F)", "command line")
  ENV_FILE = $(F)
endif
ifndef ENV_FILE
  ENV_FILE := 
endif

# That's our default target when none is given on the command line
PHONY := all
all:

# Cancel implicit rules on top Makefile
$(PWD)/Makefile Makefile: ;


srctree		:= $(PWD)
export srctree


KCONFIG_CONFIG	:= .config

ifneq ($(KCONFIG_CONFIG),$(wildcard $(KCONFIG_CONFIG)))
skip-makefile := y
endif


# SHELL used by kbuild
CONFIG_SHELL := $(shell if [ -x "$$BASH" ]; then echo $$BASH; \
	  else if [ -x /bin/bash ]; then echo /bin/bash; \
	  else echo sh; fi ; fi)

HOSTCC       = gcc
HOSTCXX      = g++
HOSTCFLAGS   = -Wall -Wmissing-prototypes -Wstrict-prototypes -O2 -fomit-frame-pointer
HOSTCXXFLAGS = -O2


# If KBUILD_VERBOSE equals 0 then the above command will be hidden.
# If KBUILD_VERBOSE equals 1 then the above command is displayed.

ifeq ($(KBUILD_VERBOSE),1)
  quiet =
  Q =
else
  quiet=quiet_
  Q = @
endif

# If the user is running make -s (silent mode), suppress echoing of
# commands

ifneq ($(findstring s,$(MAKEFLAGS)),)
  quiet=silent_
endif

export quiet Q KBUILD_VERBOSE


# We need some generic definitions (do not try to remake the file).
$(srctree)/scripts/Kbuild.include: ;
include $(srctree)/scripts/Kbuild.include

export CONFIG_SHELL HOSTCC HOSTCFLAGS

# Make variables (CC, etc...)
MAKE		:= make
ARCH		?= arm
TARGET		?= $(ARCH)-linux
CROSS_COMPILE	?= $(TARGET)-
PERL		:= perl

BUILD_PWD	?= $(abspath $(PWD))
PRJ_DIR		?= $(abspath $(PWD)/../)

CROSSTOOL_DIR	:= $(PRJ_DIR)/toolchain/crosstool-4.5.2
PATH		:= $(CROSSTOOL_DIR)/bin:$(PATH)
IMGTOOL_DIR	:= $(PRJ_DIR)/toolchain/image-tool
PHY_SF_DIR	:= $(PRJ_DIR)/toolchain/image-tool/phy_sf
SYSPARSE	:= $(IMGTOOL_DIR)/sysparser.pl
KERNEL_SRC_DIR      := $(PRJ_DIR)/kernel/linux-2.6.35.12
NORMAL_KERNEL_DIR      := $(PRJ_DIR)/kernel/linux-2.6.35.12/obj/normal
RESCUE_KERNEL_DIR      := $(PRJ_DIR)/kernel/linux-2.6.35.12/obj/rescue
BUSYBOX_SRC_DIR := $(PRJ_DIR)/filesystem/busybox-1.22.1
NORMAL_BUSYBOX_DIR      := $(PRJ_DIR)/filesystem/busybox-1.22.1/obj/normal
RESCUE_BUSYBOX_DIR      := $(PRJ_DIR)/filesystem/busybox-1.22.1/obj/rescue
RESCUE_FS_DIR	:= $(PRJ_DIR)/rootfs-rescue
COMPILE_RESCUE	:= no

SCRIPTS_DIR	:= $(srctree)/scripts
AUTOCONF_DIR	:= $(srctree)/include
LIBNVRAM_DIR	:= $(AUTOCONF_DIR)/libnvram

MIDDLEWARE_INS_DIR	?= $(PRJ_DIR)/middleware/_install
INSTALL_DIR	?= $(PRJ_DIR)/filesystem/rootfs/src/root
DIST_DIR	?= $(PRJ_DIR)/image
FS_DIR		?= $(PRJ_DIR)/rootfs
EXAMPLE_DIR	?= $(PRJ_DIR)/example
HW_DIR		?= $(PRJ_DIR)/board-info
OPENSSL_DIR	?= $(PRJ_DIR)/middleware/openssl

IPTABLES_DIR	:= $(PRJ_DIR)/app/iptables-1.4.1
LIBSONIX_DIR	:= $(PRJ_DIR)/app/libsonix

#
# Images 
#

UBOOT_FILE	:= $(DIST_DIR)/u-boot.bin 
KERNEL_FILE	:= $(DIST_DIR)/uImage
ROOTFS_R_FILE	:= $(DIST_DIR)/rootfs.cramfs
ROOTFS_RW_FILE	:= $(DIST_DIR)/rootfs.jffs2
ULOGO_FILE	:= $(DIST_DIR)/u-logo.bmp
ENGINE_FILE	:= $(DIST_DIR)/engine.bin
DONE_UBOOT	:= $(DIST_DIR)/UBOOT.bin
DONE_KERNEL	:= $(DIST_DIR)/KERNEL.bin
DONE_ROOTFS_R	:= $(DIST_DIR)/ROOTFS-R.bin
DONE_NVRAM	:= $(DIST_DIR)/nvram.bin
ENCYPT_KEY	:= "1234567890"


export ARCH CROSS_COMPILE
export CROSSTOOL_DIR
export KERNEL_SRC_DIR BUSYBOX_SRC_DIR NORMAL_KERNEL_DIR RESCUE_KERNEL_DIR NORMAL_BUSYBOX_DIR RESCUE_BUSYBOX_DIR
export INSTALL_DIR MIDDLEWARE_INS_DIR DIST_DIR FS_DIR RESCUE_FS_DIR EXAMPLE_DIR IMGTOOL_DIR
export SCRIPTS_DIR AUTOCONF_DIR
export LIBNVRAM_DIR
export IPTABLES_DIR LIBSONIX_DIR
export HW_DIR
export OPENSSL_DIR
export sdk_version ENCYPT_KEY
# ===========================================================================
# Rules shared between *config targets and build targets

# Basic helpers built in scripts/
PHONY += scripts_basic
scripts_basic:
	$(Q)$(MAKE) $(build)=scripts/basic
	$(Q)rm -f .tmp_quiet_recordmcount

# To avoid any implicit rule to kick in, define an empty command.
scripts/basic/%: scripts_basic ;


# To make sure we do not include .config for any of the *config targets
# catch them early, and hand them over to scripts/kconfig/Makefile
# It is allowed to specify more targets when calling make, including
# mixing *config targets and build targets.
# For example 'make oldconfig all'.
# Detect when mixed targets is specified, and make a second invocation
# of make so .config is not included in this case either (for *config).

no-dot-config-targets := help

#The default target
config-targets := 0
#mixed-targets  := 0
dot-config     := 1

ifneq ($(filter $(no-dot-config-targets), $(MAKECMDGOALS)),)
	ifeq ($(filter-out $(no-dot-config-targets), $(MAKECMDGOALS)),)
		dot-config := 0
	endif
silent=1
endif

ifneq ($(filter config %config,$(MAKECMDGOALS)),)
	config-targets := 1
endif

ifeq ($(config-targets),1)
# ===========================================================================
# *config targets only - make sure prerequisites are updated, and descend
# in scripts/kconfig to make the *config target

export KBUILD_DEFCONFIG KBUILD_KCONFIG

#SETUP_ENV := $(shell ./setup_env.sh $(ENV_FILE))
Makefile.mod: $(ENV_FILE)
	./setup_env.sh $(ENV_FILE)

config: Makefile.mod scripts_basic FORCE
	$(Q)mkdir -p include/config
	$(Q)$(MAKE) $(build)=scripts/kconfig $@
	$(Q)if [ .config -nt include/config/snx_sdk.conf ]; then \
		$(MAKE) $(build)=scripts/kconfig silentoldconfig; \
	fi

	$(Q)$(MAKE) -C $(HW_DIR)/gpio/ > /dev/null
	$(Q)if ! [ -d include/generated ]; then \
		mkdir -p include/generated;	\
	fi;
	$(Q)if [ -e $(HW_DIR)/gpio/snx_gpio_conf.h ]; then \
		mv $(HW_DIR)/gpio/snx_gpio_conf.h include/generated/snx_gpio_conf.h; \
	else \
		echo "No snx_gpio_conf.h is generated."; \
		exit 1; \
	fi;

	$(Q)$(MAKE) -C $(HW_DIR)/nvram/ > /dev/null
	$(Q)if ! [ -d include/generated ]; then \
                mkdir -p include/generated;     \
        fi;
	$(Q)if [ -e $(HW_DIR)/nvram/nvram.h ]; then \
                mv $(HW_DIR)/nvram/nvram.h include/generated/nvram.h; \
        else \
                echo "No nvram.h is generated."; \
        fi;

	$(Q)cp .mod_version include/generated/snx_mod_version.h
	$(Q)if ! [ -d $(DIST_DIR) ]; then \
                mkdir -p $(DIST_DIR);   \
        fi;

	$(Q)if [ -e $(HW_DIR)/nvram/nvram.bin ]; then \
                mv $(HW_DIR)/nvram/nvram.bin $(DIST_DIR)/nvram.bin; \
        else \
                echo "No nvram.bin is generated."; \
        fi;

	$(Q)if ! [ -d $(LIBNVRAM_DIR) ]; then \
                mkdir -p $(LIBNVRAM_DIR);       \
        fi;

	$(Q)if [ -e include/generated/nvram.h ] && [ -e $(DIST_DIR)/nvram.bin ]; then \
                cp include/generated/nvram.h $(LIBNVRAM_DIR)/nvram.h; \
                mkdir -p $(KERNEL_SRC_DIR)/src/include/libnvram; \
                ln -sf $(LIBNVRAM_DIR)/nvram.h $(KERNEL_SRC_DIR)/src/include/libnvram/nvram.h; \
        else \
                echo "No nvram.h or nvram.bin is generated."; \
                echo "Please check it to fix it"; \
		exit 1; \
        fi;

#	$(Q)if egrep "^CONFIG_CUSTOM_KERNEL_SETTING=y" .config > /dev/null; then \
#		$(MAKE) -C $(KERNEL_SRC_DIR) menuconfig OBJ_DIR=$(NORMAL_KERNEL_DIR)/src COMPILE_RESCUE=no; \
#	fi

#	$(Q)if egrep "^CONFIG_CUSTOM_KERNEL_RESCUE_SETTING=y" .config > /dev/null; then \
#		$(MAKE) -C $(KERNEL_SRC_DIR) menuconfig OBJ_DIR=$(RESCUE_KERNEL_DIR)/src COMPILE_RESCUE=yes; \
#	fi

#	$(Q)if egrep "^CONFIG_CUSTOM_BUSYBOX_SETTING=y" .config > /dev/null; then \
#		$(MAKE) -C $(BUSYBOX_SRC_DIR) menuconfig OBJ_DIR=$(NORMAL_BUSYBOX_DIR)/src COMPILE_RESCUE=no; \
#	fi

#	$(Q)if egrep "^CONFIG_CUSTOM_BUSYBOX_RESCUE_SETTING=y" .config > /dev/null; then \
#		$(MAKE) -C $(BUSYBOX_SRC_DIR) menuconfig OBJ_DIR=$(RESCUE_BUSYBOX_DIR)/src COMPILE_RESCUE=yes; \
#	fi
%config: Makefile.mod scripts_basic FORCE
	$(Q)mkdir -p include/config
	$(Q)$(MAKE) $(build)=scripts/kconfig $@
	$(Q)if [ .config -nt include/config/snx_sdk.conf ]; then \
		$(MAKE) $(build)=scripts/kconfig silentoldconfig; \
	fi
	
	$(Q)$(MAKE) -C $(HW_DIR)/gpio/ > /dev/null
	$(Q)if ! [ -d include/generated ]; then \
		mkdir -p include/generated;	\
	fi;
	$(Q)if [ -e $(HW_DIR)/gpio/snx_gpio_conf.h ]; then \
		mv $(HW_DIR)/gpio/snx_gpio_conf.h include/generated/snx_gpio_conf.h; \
	else \
		echo "No snx_gpio_conf.h is generated."; \
		exit 1; \
	fi;

	$(Q)$(MAKE) -C $(HW_DIR)/nvram/ > /dev/null

	$(Q)if ! [ -d include/generated ]; then \
                mkdir -p include/generated;     \
        fi;

	$(Q)if [ -e $(HW_DIR)/nvram/nvram.h ]; then \
                mv $(HW_DIR)/nvram/nvram.h include/generated/nvram.h; \
        else \
                echo "No nvram.h is generated."; \
        fi;

	$(Q)cp .mod_version include/generated/snx_mod_version.h
	$(Q)if ! [ -d $(DIST_DIR) ]; then \
                mkdir -p $(DIST_DIR);   \
        fi;
	$(Q)if [ -e $(HW_DIR)/nvram/nvram.bin ]; then \
                mv $(HW_DIR)/nvram/nvram.bin $(DIST_DIR)/nvram.bin; \
        else \
                echo "No nvram.bin is generated."; \
        fi;

	$(Q)if ! [ -d $(LIBNVRAM_DIR) ]; then \
                mkdir -p $(LIBNVRAM_DIR);       \
        fi;
	$(Q)if [ -e include/generated/nvram.h ] && [ -e $(DIST_DIR)/nvram.bin ]; then \
                cp include/generated/nvram.h $(LIBNVRAM_DIR)/nvram.h; \
                mkdir -p $(KERNEL_SRC_DIR)/src/include/libnvram; \
                ln -sf $(LIBNVRAM_DIR)/nvram.h $(KERNEL_SRC_DIR)/src/include/libnvram/nvram.h; \
        else \
                echo "No nvram.h or nvram.bin is generated."; \
                echo "Please check it to fix it"; \
		exit 1; \
        fi;
	
#	$(Q)if egrep "^CONFIG_CUSTOM_KERNEL_SETTING=y" .config > /dev/null; then \
#		$(MAKE) -C $(KERNEL_SRC_DIR) menuconfig OBJ_DIR=$(NORMAL_KERNEL_DIR)/src COMPILE_RESCUE=no; \
#	fi

#	$(Q)if egrep "^CONFIG_CUSTOM_KERNEL_RESCUE_SETTING=y" .config > /dev/null; then \
#		$(MAKE) -C $(KERNEL_SRC_DIR) menuconfig OBJ_DIR=$(RESCUE_KERNEL_DIR)/src COMPILE_RESCUE=yes; \
#	fi

#	$(Q)if egrep "^CONFIG_CUSTOM_BUSYBOX_SETTING=y" .config > /dev/null; then \
#		$(MAKE) -C $(BUSYBOX_SRC_DIR) menuconfig OBJ_DIR=$(NORMAL_BUSYBOX_DIR)/src COMPILE_RESCUE=no; \
#	fi

#	$(Q)if egrep "^CONFIG_CUSTOM_BUSYBOX_RESCUE_SETTING=y" .config > /dev/null; then \
#		$(MAKE) -C $(BUSYBOX_SRC_DIR) menuconfig OBJ_DIR=$(RESCUE_BUSYBOX_DIR)/src COMPILE_RESCUE=yes; \
#	fi
else
# ===========================================================================
# Build targets only - this includes vmlinux, arch specific targets, clean
# targets and others. In general all targets except *config targets.

# Additional helpers built in scripts/
# Carefully list dependencies so we do not try to build scripts twice
# in parallel
PHONY += scripts
scripts: scripts_basic include/config/snx_sdk.conf include/config/snx_sdk_tristate.conf
	$(Q)$(MAKE) $(build)=$(@)


ifeq ($(dot-config),1)
# Read in config
-include include/config/snx_sdk.conf

# Read in dependencies to all Kconfig* files, make sure to run
# oldconfig if changes are detected.
-include include/config/auto.conf.cmd

# To avoid any implicit rule to kick in, define an empty command
#$(KCONFIG_CONFIG) include/config/auto.conf.cmd: ;

# If .config is newer than include/config/snx_sdk.conf, someone tinkered
# with it and forgot to run make oldconfig.
# if auto.conf.cmd is missing then we are probably in a cleaned tree so
# we execute the config step to be sure to catch updated Kconfig files
#include/config/%.conf: $(KCONFIG_CONFIG) include/config/auto.conf.cmd
#	$(Q)$(MAKE) -f $(srctree)/Makefile silentoldconfig
#	$(Q)echo "Update autoconf.h"

else
# Dummy target needed, because used as prerequisite
include/config/snx_sdk.conf: ;
endif # $(dot-config)

include Makefile.version
include Makefile.menu
ENCYPT_KEY = "$(prefix)"

# We process the rest of the Makefile if this is the final invocation of make
ifeq ($(skip-makefile),)
include Makefile.mod

PHONY += bootloader kernel filesystem
all: bootloader kernel filesystem
ifeq ($(CONFIG_RESCUE_SYSTEM), y)
ifeq ($(MODULE_ONLY), yes)
kernel:
else
kernel: $(kernel) $(filesystem-rescue)
endif
	if [ -f $(DIST_DIR)/initramfs_data.cpio ]; then \
		cp -av $(DIST_DIR)/initramfs_data.cpio $(RESCUE_KERNEL_DIR)/src/usr/; \
	fi
	$(MAKE) -C $(KERNEL_SRC_DIR) all OBJ_DIR=$(RESCUE_KERNEL_DIR)/src COMPILE_RESCUE=yes
	$(MAKE) -C $(KERNEL_SRC_DIR) install INSTALL_DIR=$(KERNEL_SRC_DIR)/rescue_image OBJ_DIR=$(RESCUE_KERNEL_DIR)/src COMPILE_RESCUE=yes
	if [ -d $(KERNEL_SRC_DIR)/rescue_image ]; then \
                cp -av $(KERNEL_SRC_DIR)/rescue_image/* $(DIST_DIR); \
        fi
filesystem: $(filesystem) $(filesystem-rescue)
ifeq ($(MODULE_ONLY), yes)
$(filesystem) $(filesystem-rescue):
else
$(filesystem) $(filesystem-rescue): $(filesystem-bs) $(MODULES-y)
endif
else
kernel: $(kernel)
filesystem: $(filesystem)
ifeq ($(MODULE_ONLY), yes)
$(filesystem):
else
$(filesystem): $(filesystem-bs) $(MODULES-y)
endif
endif
bootloader: $(bootloader)
$(bootloader) $(kernel) $(filesystem-bs) $(MODULES-y): distribute-pre

distribute-pre:
	if ! [ -d $(DIST_DIR) ]; then \
		install -d $(DIST_DIR); \
	fi
	if ! [ -d $(EXAMPLE_DIR) ]; then \
		install -d $(EXAMPLE_DIR); \
	fi
	if ! [ -d $(FS_DIR) ]; then \
		install -d $(FS_DIR); \
	fi
	if ! [ -d $(MIDDLEWARE_INS_DIR) ]; then \
		install -d $(MIDDLEWARE_INS_DIR); \
	fi
ifeq ($(CONFIG_RESCUE_SYSTEM), y)
	if ! [ -d $(RESCUE_FS_DIR) ]; then \
		install -d $(RESCUE_FS_DIR); \
	fi
endif

phy_image	:= phy_sf
MODULES=$(MODULES-y) $(MODULES-n) $(MODULES-) $(bootloader) $(kernel) $(filesystem) $(filesystem-bs) $(phy_image)
showmodules:
	$(Q)count=0
	$(Q)for module in $(MODULES); \
	do \
	num=`echo -n $$module | wc -c`; \
	echo -n "$$module"; \
	if [ "$$num" -lt "8" ]; then \
		echo -n -e "\t\t\t"; \
	elif [ "$$num" -lt "16" ]; then \
		echo -n -e "\t\t"; \
	elif [ "$$num" -lt "24" ]; then \
		echo -n -e "\t"; \
	fi; \
	let count++; \
	if [ $$count -ge 3 ]; then \
		echo; \
		count=0; \
	fi; \
	done
	$(Q)echo

showallmodules:
	$(Q)count=0
	$(Q)for module in $(snx_modules); \
	do \
	num=`echo -n $$module | wc -c`; \
	echo -n "$$module"; \
	if [ "$$num" -lt "8" ]; then \
		echo -n -e "\t\t\t"; \
	elif [ "$$num" -lt "16" ]; then \
		echo -n -e "\t\t"; \
	elif [ "$$num" -lt "24" ]; then \
		echo -n -e "\t"; \
	fi; \
	let count++; \
	if [ $$count -ge 3 ]; then \
		echo; \
		count=0; \
	fi; \
	done
	$(Q)echo

#
# Make install (images)
#
ifeq ($(CONFIG_RESCUE_SYSTEM), y)
INCLUDE_RESCUE := rescueimage
else
INCLUDE_RESCUE := 
endif

PHONY += install
ifeq ($(CONFIG_RESCUE_SYSTEM), y)
install: bootimage kernelimage rootfsimage rescueimage firmware firmware_factory phy_sf
else
install: bootimage kernelimage rootfsimage firmware firmware_factory touchrescue phy_sf
endif

PHONY += touchrescue
touchrescue:
	touch $(DIST_DIR)/RESCUE.bin

PHONY += image
image: install

#
# Make bootimage (uboot + hwsetting + flashlayout)
#
PHONY += flash_layout
flash_layout:
	$(Q)$(MAKE) -C $(HW_DIR)/flash-layout serial_flashlayout.conf ADDTO_MOUNT_PARTITION=no && cd $(PRJ_DIR) || exit 1
#
# Make bootimage (uboot + hwsetting + flashlayout)
#
PHONY += bootimage
bootimage: flash_layout
	$(Q)$(MAKE) -C $(IMGTOOL_DIR) bootimage && cd $(PRJ_DIR) || exit 1
	$(Q)if [ -e $(IMGTOOL_DIR)/UBOOT.bin ]; then \
		mv $(IMGTOOL_DIR)/UBOOT.bin $(DIST_DIR)/UBOOT.bin; \
	else \
		echo "No UBOOT.bin is generated."; \
		exit 1; \
	fi;

#
# Make kernelimage 
#
PHONY += kernelimage
kernelimage:
	$(Q)$(MAKE) -C $(IMGTOOL_DIR) kernelimage && cd $(PRJ_DIR) || exit 1
	$(Q)if [ -e $(IMGTOOL_DIR)/KERNEL.bin ]; then \
		mv $(IMGTOOL_DIR)/KERNEL.bin $(DIST_DIR)/KERNEL.bin; \
	else \
		echo "No KERNEL.bin is generated."; \
		exit 1; \
	fi;

#
# Make rootfs-r 
#
PHONY += rootfsimage
rootfsimage:
	$(Q)$(MAKE) -C $(IMGTOOL_DIR) rootfsimage && cd $(PRJ_DIR) || exit 1
	$(Q)if [ -e $(IMGTOOL_DIR)/ROOTFS-R.bin ]; then \
		mv $(IMGTOOL_DIR)/ROOTFS-R.bin $(DIST_DIR)/ROOTFS-R.bin; \
	else \
		echo "No ROOTFS-R.bin is generated."; \
		exit 1; \
	fi;

PHONY += rootfs_rwimage
rootfs_rwimage:
	$(Q)$(MAKE) -C $(IMGTOOL_DIR) rootfs_rwimage && cd $(PRJ_DIR) || exit 1
	$(Q)if [ -e $(IMGTOOL_DIR)/ROOTFS-RW.bin ]; then \
		mv $(IMGTOOL_DIR)/ROOTFS-RW.bin $(DIST_DIR)/ROOTFS-RW.bin; \
	else \
		echo "No ROOTFS-RW.bin is generated."; \
		exit 1; \
	fi;
	
#
# Make engine 
#
PHONY += engine
engine:
	$(Q)$(MAKE) -C $(IMGTOOL_DIR) engine && cd $(PRJ_DIR) || exit 1
	$(Q)if [ -e $(IMGTOOL_DIR)/ENGINE.bin ]; then \
		mv $(IMGTOOL_DIR)/ENGINE.bin $(DIST_DIR)/ENGINE.bin; \
	else \
		echo "No ENGINE.bin is generated."; \
		exit 1; \
	fi;

#for packing the whole image

PHONY += firmware_factory
ifeq ($(MODULE_ONLY), yes)
firmware_factory:
else
firmware_factory: bootimage kernelimage rootfsimage $(INCLUDE_RESCUE)
endif
	$(Q)cd  $(IMGTOOL_DIR) && $(MAKE) firmware_factory && cd $(PRJ_DIR) || exit 1
ifeq ($(CONFIG_SYSTEM_PLATFORM_ST58660FPGA), y)
	$(Q)if [ -e $(IMGTOOL_DIR)/FIRMWARE_SB.bin ]; then \
                mv $(IMGTOOL_DIR)/FIRMWARE_SB.bin $(DIST_DIR)/FIRMWARE_660R_F.bin; \
        else \
                echo "No FIRMWARE_SB.bin is generated."; \
		exit 1; \
        fi;
else
ifeq ($(CONFIG_SYSTEM_PLATFORM_SN98660), y)
	$(Q)if [ -e $(IMGTOOL_DIR)/FIRMWARE_SB.bin ]; then \
                mv $(IMGTOOL_DIR)/FIRMWARE_SB.bin $(DIST_DIR)/FIRMWARE_660R_F.bin; \
        else \
                echo "No FIRMWARE_SB.bin is generated."; \
		exit 1; \
        fi;
else
	$(Q)if [ -e $(IMGTOOL_DIR)/FIRMWARE_SB.bin ]; then \
                mv $(IMGTOOL_DIR)/FIRMWARE_SB.bin $(DIST_DIR)/FIRMWARE_F.bin; \
        else \
                echo "No FIRMWARE_F.bin is generated."; \
		exit 1; \
        fi;
endif
endif

PHONY += firmware
ifeq ($(MODULE_ONLY), yes)
firmware:
else
firmware: kernelimage rootfsimage $(INCLUDE_RESCUE)
endif
	$(Q)cd  $(IMGTOOL_DIR) && $(MAKE) firmware && cd $(PRJ_DIR) || exit 1
ifeq ($(CONFIG_SYSTEM_PLATFORM_ST58660FPGA), y)
	$(Q)if [ -e $(IMGTOOL_DIR)/FIRMWARE_SB.bin ]; then \
                mv $(IMGTOOL_DIR)/FIRMWARE_SB.bin $(DIST_DIR)/FIRMWARE_660R.bin; \
        else \
                echo "No firmware_update is generated."; \
		exit 1; \
        fi;
else
ifeq ($(CONFIG_SYSTEM_PLATFORM_SN98660), y)
	$(Q)if [ -e $(IMGTOOL_DIR)/FIRMWARE_SB.bin ]; then \
                mv $(IMGTOOL_DIR)/FIRMWARE_SB.bin $(DIST_DIR)/FIRMWARE_660R.bin; \
        else \
                echo "No firmware_update is generated."; \
		exit 1; \
        fi;
else
	$(Q)if [ -e $(IMGTOOL_DIR)/FIRMWARE_SB.bin ]; then \
                mv $(IMGTOOL_DIR)/FIRMWARE_SB.bin $(DIST_DIR)/FIRMWARE.bin; \
        else \
                echo "No FIRMWARE.bin is generated."; \
		exit 1; \
        fi;
endif
endif

#for packing the sf_phy
PHONY += phy_sf 
ifeq ($(MODULE_ONLY), yes)
phy_sf:
else
phy_sf:bootimage kernelimage rootfsimage $(INCLUDE_RESCUE)
endif
	$(Q)cd  $(IMGTOOL_DIR) && $(MAKE) phy_sf && cd $(PRJ_DIR) || exit 1
	$(Q)if ! [ -e $(DIST_DIR)/PHY-SF.bin ]; then \
		echo "No PHY-SF.bin is generated."; \
		exit 1; \
	fi;
	$(Q)if ! [ -e $(DIST_DIR)/phy_sf_report.txt ]; then \
		echo "No phy_sf_report.txt is generated."; \
		exit 1; \
	fi;

ifeq ($(CONFIG_RESCUE_SYSTEM), y)
PHONY += rescueimage
rescueimage:
	$(Q)$(MAKE) -C $(IMGTOOL_DIR) rescueimage && cd $(PRJ_DIR) || exit 1
	$(Q)if [ -e $(IMGTOOL_DIR)/RESCUE.bin ]; then \
		mv $(IMGTOOL_DIR)/RESCUE.bin $(DIST_DIR)/RESCUE.bin; \
	else \
		echo "No RESCUE.bin is generated."; \
		exit 1; \
	fi;

endif

endif # skip-makefile



#
# Make clean/distclean
#
MODULES-y-clean=$(patsubst %, %-clean, $(MODULES-y))
MODULES-n-clean=$(patsubst %, %-clean, $(MODULES-n))
MODULES--clean=$(patsubst %, %-clean, $(MODULES-))

distribute-pre-clean:
	rm -rf $(FS_DIR)
	rm -rf $(EXAMPLE_DIR)
	rm -rf $(MIDDLEWARE_INS_DIR)
ifeq ($(CONFIG_RESCUE_SYSTEM), y)
	rm -rf $(RESCUE_FS_DIR)
endif

ifeq ($(skip-makefile),)
CLEAN-depend := $(MODULES-y-clean) $(bootloader)-clean $(kernel)-clean $(filesystem)-clean $(filesystem-bs)-clean
else
CLEAN-depend = 
endif

PHONY += imagetool-clean
imagetool-clean:
	$(Q)$(MAKE) -C $(IMGTOOL_DIR) clean
	$(Q)$(MAKE) -C $(HW_DIR)/hw-setting hwsetting-clean
	$(Q)$(MAKE) -C $(HW_DIR)/flash-layout clean

PHONY += clean
clean: $(CLEAN-depend) imagetool-clean distribute-pre-clean
	@echo	'make clean done'

PHONY += distclean
distclean: clean
	$(Q)find scripts \( -name '*.[oas]' -o -name '*.ko' -o -name '.*.cmd' \
		-o -name '.*.d' -o -name '.*.tmp' -o -name '*.mod.c' \) \
		-type f -print | xargs rm -f	
	$(Q)find scripts \( -name 'fixdep' -o -name 'docproc' -o -name 'split-include' \
		-o -name 'autoconf.h' -o -name '.config' -o -name '.config.old' \
		-o -name 'qconf' -o -name 'gconf' -o -name 'kxgettext' \
		-o -name 'mconf' -o -name 'conf' -o -name 'lxdialog' \) \
		-type f -print | xargs rm -f
	$(Q)rm -rf $(AUTOCONF_DIR)/*
	$(Q)rm -f $(KCONFIG_CONFIG)
	$(Q)rm -f ./*.mod
	$(Q)rm -f .config.old
	@echo 'make distclean done'


#
# Make help
#

PHONY += help
help:
	@echo  'Cleaning targets:'
	@echo  '  clean		  - Remove most generated files but keep the config and'
	@echo  '                    enough build support to build external modules'
	@echo  '  distclean	  -'
	@echo  ''
	@echo  'Configuration targets:'
	@$(MAKE) -f $(srctree)/scripts/kconfig/Makefile help
	@echo  ''
	@echo  '  all		  - Build all targets marked with [*]'
	@echo  '  install	  - Build all images'
	@echo  '  image		  - Build all images. same as make install'
	@echo  '  bootimage	  - Build bootimage after doing build uboot'
	@echo  '  kernelimage	  - Build kernelimage after doing build kernel'
	@echo  '  rootfsimage	  - Build rootfs'
	@echo  '  showmodules	  - show all the module name'
	@echo  '  [module name]	  - Build the module'
	@echo  '  [module name]-clean	  - Remove most generated file of the module'


endif #config-targets
#endif # mixed-target


PHONY += FORCE
FORCE:

# Declare the contents of the .PHONY variable as phony.  We keep that
# information in a variable so we can use it in if_changed and friends.
.PHONY: $(PHONY)
