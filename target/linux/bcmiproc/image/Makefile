# SPDX-License-Identifier: GPL-2.0-only
#
# Copyright (C) 2016-2017 Yousong Zhou <yszhou4tech@gmail.com>
# Copyright (C) 2018 Jianhui Zhao <jianhuizhao329@gmail.com>
# Copyright (C) 2019 Samik Gupta <samik.gupta@broadcom.com>
# Copyright (C) 2023 Tianling Shen <cnsztl@immortalwrt.org>

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/image.mk

define Image/InstallKernel
	$(foreach k,$(filter Image,$(KERNELNAME)), \
		$(CP) $(KDIR)/$(KERNELNAME) $(BIN_DIR)/$(IMG_PREFIX)$(if $(PROFILE_SANITIZED),-$(PROFILE_SANITIZED))-$(k) \
	)
	$(foreach d,$(wildcard $(KDIR)/image-*.dtb), \
		$(CP) $(d) $(BIN_DIR)/$(IMG_PREFIX)$(if $(PROFILE_SANITIZED),-$(PROFILE_SANITIZED)).dtb \
	)
endef

define Image/Build/gzip
	gzip -f9n $(BIN_DIR)/$(IMG_PREFIX)$(if $(PROFILE_SANITIZED),-$(PROFILE_SANITIZED))-rootfs-$(1).img
endef

$(eval $(call Image/gzip-ext4-padded-squashfs))

define Image/Build
	$(call Image/Build/$(1))
	$(CP) $(KDIR)/root.$(1) $(BIN_DIR)/$(IMG_PREFIX)$(if $(PROFILE_SANITIZED),-$(PROFILE_SANITIZED))-rootfs-$(1).img
	$(call Image/Build/gzip/$(1))
endef

### Devices ###
define Device/Default
  PROFILES := Default
  DEVICE_DTS = broadcom$(if $$(DTS_SUBDIR),/$$(DTS_SUBDIR))/$(lastword $(subst _, ,$(1)))
endef

include $(SUBTARGET).mk

$(eval $(call BuildImage))
