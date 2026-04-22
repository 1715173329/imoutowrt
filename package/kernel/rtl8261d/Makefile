# SPDX-License-Identifier: GPL-2.0-only

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=rtl8261d
PKG_RELEASE:=1

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/RuijieNetworksCommunity/rtl8261-phy-driver.git
PKG_SOURCE_DATE:=2026-06-02
PKG_SOURCE_VERSION:=799af1493ce181a0a087d7b38639209fbcda2f26
PKG_MIRROR_HASH:=9a4feaa59f4a61fb11dd42b6921df71166d6ff7778e49bf9d411c5a55637db11

PKG_LICENSE:=GPL-2.0-only
PKG_LICENSE_FILES:=LICENSE
PKG_MAINTAINER:=StarField Xu <air_jinkela@163.com>

PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk

define KernelPackage/phy-rtl8261d
  SUBMENU:=Network Devices
  TITLE:=Realtek RTL8261D 10 Gigabit PHY driver
  FILES:=$(PKG_BUILD_DIR)/src/rtl8261d.ko
  AUTOLOAD:=$(call AutoLoad,18,rtl8261d,1)
endef

define Build/Compile
	+$(KERNEL_MAKE) $(PKG_JOBS) \
		M="$(PKG_BUILD_DIR)/src" \
		CONFIG_REALTEK_PHY_RTL8261D=m \
		modules
endef

$(eval $(call KernelPackage,phy-rtl8261d))
