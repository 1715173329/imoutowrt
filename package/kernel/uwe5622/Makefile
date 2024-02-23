# SPDX-License-Identifier: GPL-2.0-only
#
# Copyright (C) 2024 ImmortalWrt.org

include $(TOPDIR)/rules.mk

PKG_NAME:=uwe5622
PKG_RELEASE:=1

PKG_SOURCE_URL:=https://github.com/TSSKiller/uwe5622.git
PKG_SOURCE_PROTO:=git
PKG_SOURCE_DATE:=2023-10-08
PKG_SOURCE_VERSION:=18a317b7b5603e38e9f2d54083ab94c49857f0a4
PKG_MIRROR_HASH:=d5d904ef1ee0f852f5e7d09cd152c0fe782f25df5c48866f25f19803512819da

PKG_BUILD_PARALLEL:=1

STAMP_CONFIGURED_DEPENDS := $(STAGING_DIR)/usr/include/mac80211-backport/backport/autoconf.h

include $(INCLUDE_DIR)/kernel.mk
include $(INCLUDE_DIR)/package.mk

define KernelPackage/uwe5622
  SUBMENU:=Wireless Drivers
  TITLE:=UWE5622 wireless drivers
  DEPENDS:=+kmod-cfg80211 +kmod-crypto-sha256 +kmod-mmc +@DRIVER_11AC_SUPPORT
  FILES:=$(PKG_BUILD_DIR)/unisocwcn/uwe5622_bsp_sdio.ko
  AUTOLOAD:=$(call AutoProbe,uwe5622_bsp_sdio)
endef

NOSTDINC_FLAGS:= \
	$(KERNEL_NOSTDINC_FLAGS) \
	-I$(PKG_BUILD_DIR)/unisocwcn/include \
	-I$(PKG_BUILD_DIR)/unisocwcn/platform \
	-I$(STAGING_DIR)/usr/include/mac80211-backport \
	-I$(STAGING_DIR)/usr/include/mac80211-backport/uapi \
	-I$(STAGING_DIR)/usr/include/mac80211 \
	-I$(STAGING_DIR)/usr/include/mac80211/uapi \
	-include backport/autoconf.h \
	-include backport/backport.h

NOSTDINC_FLAGS+= \
	-DRTW_SINGLE_WIPHY \
	-DRTW_USE_CFG80211_STA_EVENT \
	-DCONFIG_IOCTL_CFG80211 \
	-DBUILD_OPENWRT

ifeq ($(CONFIG_BIG_ENDIAN),y)
NOSTDINC_FLAGS+= -DCONFIG_BIG_ENDIAN
else
NOSTDINC_FLAGS+= -DCONFIG_LITTLE_ENDIAN
endif

define Build/Compile
	+$(KERNEL_MAKE) $(PKG_JOBS) \
		M="$(PKG_BUILD_DIR)/unisocwcn" \
		NOSTDINC_FLAGS="$(NOSTDINC_FLAGS)" \
		CONFIG_AW_WIFI_DEVICE_UWE5622=y \
		modules
	+$(KERNEL_MAKE) $(PKG_JOBS) \
		M="$(PKG_BUILD_DIR)/unisocwifi" \
		NOSTDINC_FLAGS="$(NOSTDINC_FLAGS)" \
		CONFIG_WLAN_UWE5622=m \
		CONFIG_SPRDWL_NG=m \
		modules
endef

$(eval $(call KernelPackage,uwe5622))
