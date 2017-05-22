PATCH_DIR	?= $(shell pwd)
SRC_DIR		?= $(PATCH_DIR)/../src

.PHONY: .patched clean

.patched: 0001_snx_msg_tag \
	  0003_pre_allcate_algo_enhance \
	  0005_fix_default_thread_stack_size \
	  0006_fcse-patch \
	  0009_Reduce-tty-number \
	  0013_Fix-netfilter-config \
	  0015_EHCI-error-check-qtd-token \
	  0017_video-codec-mbrc \
	  0018_no-hz_dma \
	  0019_net_usb_rtl8152 \
	  0020_Fullspeed_Lock \
	  0021_timer_latency \
	  0022_no_snxmac
	$(Q)if [ ! -e $(PATCH_DIR)/.patched ]; then \
		touch $(PATCH_DIR)/.patched; \
	fi

clean: 0022_no_snxmac_clean \
	0021_timer_latency_clean \
	0020_Fullspeed_Lock_clean \
	0019_net_usb_rtl8152_clean \
	0018_no-hz_dma_clean \
	0017_video-codec-mbrc_clean \
	0015_EHCI-error-check-qtd-token_clean \
	0013_Fix-netfilter-config_clean \
	0009_Reduce-tty-number_clean \
	0006_fcse-patch_clean \
	0005_fix_default_thread_stack_size_clean \
	0003_pre_allcate_algo_enhance_clean \
	0001_snx_msg_tag_clean
	$(Q)if [ -e $(PATCH_DIR)/.patched ]; then \
		rm -f $(PATCH_DIR)/.patched; \
	fi

0001_snx_msg_tag:
	$(Q)if [ ! -e $(PATCH_DIR)/.patched ]; then \
		patch -d $(SRC_DIR) -p0 < $(PATCH_DIR)/0001_snx_msg_tag.patch; \
	fi

0001_snx_msg_tag_clean:
	$(Q)if [ -e $(PATCH_DIR)/.patched ]; then \
		patch -R -d $(SRC_DIR) -p0 < $(PATCH_DIR)/0001_snx_msg_tag.patch; \
	fi

0003_pre_allcate_algo_enhance:
	$(Q)if [ ! -e $(PATCH_DIR)/.patched ]; then \
		patch -d $(SRC_DIR) -p2 < $(PATCH_DIR)/0003_pre_allcate_algo_enhance.patch; \
	fi

0003_pre_allcate_algo_enhance_clean:
	$(Q)if [ -e $(PATCH_DIR)/.patched ]; then \
		patch -R -d $(SRC_DIR) -p2 < $(PATCH_DIR)/0003_pre_allcate_algo_enhance.patch; \
	fi

0005_fix_default_thread_stack_size:
	$(Q)if [ ! -e $(PATCH_DIR)/.patched ]; then \
		patch -d $(SRC_DIR) -p2 < $(PATCH_DIR)/0005_fix_default_thread_stack_size_to_1024k_bytes.patch; \
	fi

0005_fix_default_thread_stack_size_clean:
	$(Q)if [ -e $(PATCH_DIR)/.patched ]; then \
		patch -R -d $(SRC_DIR) -p2 < $(PATCH_DIR)/0005_fix_default_thread_stack_size_to_1024k_bytes.patch; \
	fi

0006_fcse-patch:
	$(Q)if [ ! -e $(PATCH_DIR)/.patched ]; then \
		patch -d $(SRC_DIR) -p2 < $(PATCH_DIR)/0006_fcse-patch.patch; \
	fi

0006_fcse-patch_clean:
	$(Q)if [ -e $(PATCH_DIR)/.patched ]; then \
		patch -R -d $(SRC_DIR) -p2 < $(PATCH_DIR)/0006_fcse-patch.patch; \
	fi

0009_Reduce-tty-number:
	$(Q)if [ ! -e $(PATCH_DIR)/.patched ]; then \
		patch -d $(SRC_DIR) -p2 < $(PATCH_DIR)/0009_Reduce-tty-number.patch; \
	fi

0009_Reduce-tty-number_clean:
	$(Q)if [ -e $(PATCH_DIR)/.patched ]; then \
		patch -R -d $(SRC_DIR) -p2 < $(PATCH_DIR)/0009_Reduce-tty-number.patch; \
	fi

0013_Fix-netfilter-config:
	$(Q)if [ ! -e $(PATCH_DIR)/.patched ]; then \
		patch -d $(SRC_DIR) -p2 < $(PATCH_DIR)/0013_Fix-netfilter-config.patch; \
	fi

0013_Fix-netfilter-config_clean:
	$(Q)if [ -e $(PATCH_DIR)/.patched ]; then \
		patch -R -d $(SRC_DIR) -p2 < $(PATCH_DIR)/0013_Fix-netfilter-config.patch; \
	fi

0015_EHCI-error-check-qtd-token:
	$(Q)if [ ! -e $(PATCH_DIR)/.patched ]; then \
		patch -d $(SRC_DIR) -p2 < $(PATCH_DIR)/0015_EHCI-error-check-qtd-token.patch; \
	fi

0015_EHCI-error-check-qtd-token_clean:
	$(Q)if [ -e $(PATCH_DIR)/.patched ]; then \
		patch -R -d $(SRC_DIR) -p2 < $(PATCH_DIR)/0015_EHCI-error-check-qtd-token.patch; \
	fi

0017_video-codec-mbrc:
	$(Q)if [ ! -e $(PATCH_DIR)/.patched ]; then \
		patch -d $(SRC_DIR) -p2 < $(PATCH_DIR)/0017_video-codec-mbrc.patch; \
	fi

0017_video-codec-mbrc_clean:
	$(Q)if [ -e $(PATCH_DIR)/.patched ]; then \
		patch -R -d $(SRC_DIR) -p2 < $(PATCH_DIR)/0017_video-codec-mbrc.patch; \
	fi

0018_no-hz_dma:
	$(Q)if [ ! -e $(PATCH_DIR)/.patched ]; then \
		patch -d $(SRC_DIR) -p2 < $(PATCH_DIR)/0018_no-hz_dma.patch; \
	fi

0018_no-hz_dma_clean:
	$(Q)if [ -e $(PATCH_DIR)/.patched ]; then \
		patch -R -d $(SRC_DIR) -p2 < $(PATCH_DIR)/0018_no-hz_dma.patch; \
	fi

0019_net_usb_rtl8152:
	$(Q)if [ ! -e $(PATCH_DIR)/.patched ]; then \
		patch -d $(SRC_DIR) -p2 < $(PATCH_DIR)/0019_net_usb_rtl8152.patch; \
	fi

0019_net_usb_rtl8152_clean:
	$(Q)if [ -e $(PATCH_DIR)/.patched ]; then \
		patch -R -d $(SRC_DIR) -p2 < $(PATCH_DIR)/0019_net_usb_rtl8152.patch; \
	fi

0020_Fullspeed_Lock:
	$(Q)if [ ! -e $(PATCH_DIR)/.patched ]; then \
		patch -d $(SRC_DIR) -p2 < $(PATCH_DIR)/0020_Fullspeed_Lock.patch; \
	fi

0020_Fullspeed_Lock_clean:
	$(Q)if [ -e $(PATCH_DIR)/.patched ]; then \
		patch -R -d $(SRC_DIR) -p2 < $(PATCH_DIR)/0020_Fullspeed_Lock.patch; \
	fi

0021_timer_latency:
	$(Q)if [ ! -e $(PATCH_DIR)/.patched ]; then \
		patch -d $(SRC_DIR) -p2 < $(PATCH_DIR)/0021_timer_latency.patch; \
	fi

0021_timer_latency_clean:
	$(Q)if [ -e $(PATCH_DIR)/.patched ]; then \
		patch -R -d $(SRC_DIR) -p2 < $(PATCH_DIR)/0021_timer_latency.patch; \
	fi

0022_no_snxmac:
	$(Q)if [ ! -e $(PATCH_DIR)/.patched ]; then \
		patch -d $(SRC_DIR) -p2 < $(PATCH_DIR)/0022_no_snxmac.patch; \
	fi

0022_no_snxmac_clean:
	$(Q)if [ -e $(PATCH_DIR)/.patched ]; then \
		patch -R -d $(SRC_DIR) -p2 < $(PATCH_DIR)/0022_no_snxmac.patch; \
	fi
