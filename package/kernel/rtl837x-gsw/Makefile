# SPDX-License-Identifier: GPL-2.0-only

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=switch-rtl837x
PKG_RELEASE:=1

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/RuijieNetworksCommunity/rtl837x-gsw-driver.git
PKG_SOURCE_DATE:=2026-04-21
PKG_SOURCE_VERSION:=de1c633939a1927517ea440190dca774d5c3c733
PKG_MIRROR_HASH:=ebb3bce40bdce3c4ad16db8ab40bf05c9a9e1c511c9e5735cddfc67a898a1686

PKG_LICENSE:=GPL-2.0-only
PKG_LICENSE_FILES:=LICENSE
PKG_MAINTAINER:=StarField Xu <air_jinkela@163.com>

PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk

define KernelPackage/switch-rtl837x
  SUBMENU:=Network Devices
  TITLE:=Realtek RTL837x switch driver
  FILES:=$(PKG_BUILD_DIR)/src/rtl837x_gsw.ko
  AUTOLOAD:=$(call AutoLoad,42,rtl837x_gsw,1)
  DEPENDS:=+kmod-swconfig
endef

EXTRA_CFLAGS:= -DCONFIG_RTL837x_GSW_PORT_MIB_FEATURE=y

define Build/Compile
	+$(KERNEL_MAKE) $(PKG_JOBS) \
		M="$(PKG_BUILD_DIR)/src" \
		EXTRA_CFLAGS="$(EXTRA_CFLAGS)" \
		CONFIG_RTL837x_GSW=m \
		modules
endef

$(eval $(call KernelPackage,switch-rtl837x))
