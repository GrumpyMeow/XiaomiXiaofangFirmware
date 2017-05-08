PWD		:= $(shell pwd)
FIRMWARE_DIR	?= ../../root/etc_default/firmware
KO_INSTALL_DIR	?= ../../ko/isp3

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
INS_SENSOR              += cs1211k
endif

ifdef CONFIG_VIDEO_SENSOR_IMX225
INS_SENSOR		+= imx225
endif

ifdef CONFIG_VIDEO_SENSOR_IMX322
INS_SENSOR      += imx322
endif

ifdef CONFIG_VIDEO_SENSOR_OV9732
INS_SENSOR      += ov9732
endif

ifdef CONFIG_VIDEO_SENSOR_OV7725
INS_SENSOR		+= ov7725
endif

ifdef CONFIG_VIDEO_SENSOR_GC1024
INS_SENSOR              += gc1024
endif

ifdef CONFIG_VIDEO_SENSOR_OV2740
INS_SENSOR              += ov2740
endif

ifdef CONFIG_VIDEO_SENSOR_SC2035
INS_SENSOR              += sc2035
endif

ifdef CONFIG_VIDEO_SENSOR_SC2135
INS_SENSOR              += sc2135
endif

modules:
	@ if [ ! -d $(KO_INSTALL_DIR)/firmware ]; \
	then \
		install -d $(KO_INSTALL_DIR)/firmware; \
	fi	
	cp -rfa * $(KO_INSTALL_DIR)/firmware
	install -c Makefile $(KO_INSTALL_DIR)

.PHONY: clean
clean:

install:
	@ if [ ! -d $(INSTALL_DIR) ]; \
	then \
		install -d $(INSTALL_DIR); \
	fi
	if [ ! -d $(FIRMWARE_DIR) ]; \
	then \
		install -d $(FIRMWARE_DIR); \
	fi
	for ss in $(INS_SENSOR); do if [ ! -d $(FIRMWARE_DIR)/$$ss ]; then install -d $(FIRMWARE_DIR)/$$ss; fi; install -c $(KO_INSTALL_DIR)/firmware/$$ss/IQ.bin $(FIRMWARE_DIR)/$$ss; done


uninstall:
	@ if [ ! -d $(FIRMWARE_DIR) ]; \
	then \
		install -d $(FIRMWARE_DIR); \
	fi
	@ if [ ! -d $(INSTALL_DIR) ]; \
	then \
		install -d $(INSTALL_DIR); \
	fi
	for ss in $(INS_SENSOR); do rm -rf $(FIRMWARE_DIR)/$$ss; done


