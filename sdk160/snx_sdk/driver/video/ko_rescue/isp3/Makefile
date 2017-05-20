PWD		:= $(shell pwd)
ARCH		?= arm
CROSS_COMPILE	?= $(ARCH)-linux-
vKERNEL		?= 2.6.35.12
INSTALL_DIR	?= ../../../lib/modules/$(vKERNEL)/kernel/drivers
FIRMWARE_DIR	?= ../../../root/etc_default/firmware
KO_INSTALL_DIR	?= ../../../ko/isp3
#EXTRA_AFLAGS		+= -I$(abspath $(PWD))

######### Sonix version control ############
KBUILD_EXTMOD   ?= $(PWD)
VERSION_FILE    := $(KBUILD_EXTMOD)/version.c
DRV_VERSION     := $(shell grep "define MODULE_VERSION" $(VERSION_FILE) | cut -f 2)
EXTRA_CFLAGS    += -DDRV_VERSION='${DRV_VERSION}'
######### Sonix version control ############

export ARCH CROSS_COMPILE

-include $(AUTOCONF_DIR)/config/snx_sdk.conf

INS_SENSOR		:=

ifdef CONFIG_VIDEO_SENSOR_OV9715
INS_SENSOR		+= ov9715
endif

ifdef CONFIG_VIDEO_SENSOR_OV2715
INS_SENSOR		+= ov2715
endif

ifdef CONFIG_VIDEO_SENSOR_IMX132
INS_SENSOR		+= imx132
endif

ifdef CONFIG_VIDEO_SENSOR_AR0130
INS_SENSOR		+= ar0130
endif

ifdef CONFIG_VIDEO_SENSOR_IMX188
INS_SENSOR		+= imx188
endif

ifdef CONFIG_VIDEO_SENSOR_OV2659
INS_SENSOR		+= ov2659
endif

ifdef CONFIG_VIDEO_SENSOR_SNX111
INS_SENSOR		+= snx111
endif

ifdef CONFIG_VIDEO_SENSOR_OV9772
INS_SENSOR		+= ov9772
endif

ifdef CONFIG_VIDEO_SENSOR_OV9750
INS_SENSOR		+= ov9750
endif

ifdef CONFIG_VIDEO_SENSOR_OV2643
INS_SENSOR		+= ov2643
endif

ifdef CONFIG_VIDEO_SENSOR_IMX238
INS_SENSOR		+= imx238
endif

ifdef CONFIG_VIDEO_SENSOR_AR0330
INS_SENSOR		+= ar0330
endif

ifdef CONFIG_VIDEO_SENSOR_MT9V139
INS_SENSOR		+= mt9v139
endif

ifdef CONFIG_VIDEO_SENSOR_H22
INS_SENSOR		+= h22
endif

ifdef CONFIG_VIDEO_SENSOR_H42
INS_SENSOR		+= h42
endif

ifdef CONFIG_VIDEO_SENSOR_TW9912
INS_SENSOR		+= tw9912
endif

ifdef CONFIG_VIDEO_SENSOR_OV7675
INS_SENSOR		+= ov7675
endif

ifdef CONFIG_VIDEO_SENSOR_CS4101K
INS_SENSOR		+= cs4101k
endif

ifdef CONFIG_VIDEO_SENSOR_CS1211K
INS_SENSOR		+= cs1211k
endif

ifdef CONFIG_VIDEO_SENSOR_IMX225
INS_SENSOR		+= imx225
endif

ifdef CONFIG_VIDEO_SENSOR_IMX322
INS_SENSOR		+= imx322
endif

ifdef CONFIG_VIDEO_SENSOR_OV9732
INS_SENSOR		+= ov9732
endif

ifdef CONFIG_VIDEO_SENSOR_OV7725
INS_SENSOR		+= ov7725
endif

ifdef CONFIG_VIDEO_SENSOR_GC1024
INS_SENSOR		+= gc1024
endif

ifdef CONFIG_VIDEO_SENSOR_OV2740
INS_SENSOR		+= ov2740
endif

ifdef CONFIG_VIDEO_SENSOR_SC2035
INS_SENSOR		+= sc2035
endif

ifdef CONFIG_VIDEO_SENSOR_SC2135
INS_SENSOR		+= sc2135
endif

INS_MODULE 		:= snx_isp

OBJS = snx_isp_sensor.o snx_isp_ae.o snx_isp_af.o \
			snx_isp_awb.o snx_isp_ui.o snx_isp_md.o snx_isp_pm.o  \
				snx_isp_osd.o snx_isp_iq.o snx_isp_dsp.o snx_isp_video.o

$(INS_MODULE)-objs := $(OBJS)

obj-m	:= $(INS_MODULE).o

modules:
	@ if [ -z "$(KERNEL_DIR)" ]; then \
		echo "Error! Please set kernel directory by 'KERNEL_DIR' variable"; \
		exit 1; \
	fi;
	$(MAKE) -C ./sensor KERNEL_DIR=$(abspath $(KERNEL_DIR))
	$(MAKE) -C ./dsp KERNEL_DIR=$(abspath $(KERNEL_DIR)) && sh dsp.sh > snx_isp_dsp.S
	$(MAKE) -C $(KERNEL_DIR)/src M=$(PWD) modules
	$(MAKE) -C ./sensor install KO_INSTALL_DIR=$(abspath $(KO_INSTALL_DIR))
	install -c $(INS_MODULE).ko $(KO_INSTALL_DIR)
	install -c Makefile $(KO_INSTALL_DIR)

.PHONY: clean
clean:
	$(MAKE) -C ./sensor clean
	$(MAKE) -C ./dsp clean
	-rm -rf *.S *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions Module.symvers modules.order

install:
	@ if [ ! -d $(INSTALL_DIR) ]; \
	then \
		install -d $(INSTALL_DIR); \
	fi
	if [ ! -d $(FIRMWARE_DIR) ]; \
	then \
		install -d $(FIRMWARE_DIR); \
	fi
	truncate -s 0 $(FIRMWARE_DIR)/sensor.list;
	for ss in $(INS_SENSOR); do echo "$$ss" >> $(FIRMWARE_DIR)/sensor.list; done
	for ss in $(INS_SENSOR); do install -c $(KO_INSTALL_DIR)/sensor/$$ss.ko $(INSTALL_DIR); done
	install -c $(abspath $(KO_INSTALL_DIR))/$(INS_MODULE).ko $(INSTALL_DIR)


uninstall:
	@ if [ ! -d $(FIRMWARE_DIR) ]; \
	then \
		install -d $(FIRMWARE_DIR); \
	fi
	@ if [ ! -d $(INSTALL_DIR) ]; \
	then \
		install -d $(INSTALL_DIR); \
	fi
	rm -rf	$(FIRMWARE_DIR)/sensor.list
	for ss in $(INS_SENSOR); do rm -rf  $(INSTALL_DIR)/$$ss.ko; done
	rm -rf  $(INSTALL_DIR)/$(INS_MODULE).ko

