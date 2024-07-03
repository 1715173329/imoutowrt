include $(TOPDIR)/rules.mk

PKG_NAME:=aic8800
PKG_RELEASE:=1

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/radxa-pkg/aic8800.git
PKG_SOURCE_DATE:=2024-06-24
PKG_SOURCE_VERSION:=75fd5545a3e7a8ec2c2b022f0088cc352ad2b623
PKG_MIRROR_HASH:=8b675d2f1b5c9e93430f6f922dad5ae001ffbec8a65295d5ee2b317a5e56a9f5

PKG_BUILD_PARALLEL:=1

STAMP_CONFIGURED_DEPENDS := $(STAGING_DIR)/usr/include/mac80211-backport/backport/autoconf.h

include $(INCLUDE_DIR)/kernel.mk
include $(INCLUDE_DIR)/package.mk

define Package/aic8800-pcie-firmware
  SECTION:=firmware
  CATEGORY:=Firmware
  TITLE:=Aicsemi aic8800 PCIe firmware
endef

define Package/aic8800-sdio-firmware
  SECTION:=firmware
  CATEGORY:=Firmware
  TITLE:=Aicsemi aic8800 SDIO firmware
  CONFLICTS:=aic8800-pcie-firmware
endef

define Package/aic8800-usb-firmware
  SECTION:=firmware
  CATEGORY:=Firmware
  TITLE:=Aicsemi aic8800 USB firmware
  CONFLICTS:=aic8800-pcie-firmware aic8800-sdio-firmware
endef

define KernelPackage/aic8800-pcie
  SUBMENU:=Wireless Drivers
  TITLE:=Aicsemi aic8800 Wi-Fi PCIe support
  DEPENDS:=@PCIE_SUPPORT +kmod-cfg80211 +@DRIVER_11N_SUPPORT +@DRIVER_11AX_SUPPORT +aic8800-pcie-firmware
  FILES:=$(PKG_BUILD_DIR)/src/PCIE/driver_fw/driver/aic8800/aic8800_fdrv/aic8800D80_fdrv.ko
  AUTOLOAD:=$(call AutoProbe,aic8800D80_fdrv)
endef

define KernelPackage/aic8800-sdio
  SUBMENU:=Wireless Drivers
  TITLE:=Aicsemi aic8800 Wi-Fi SDIO support
  DEPENDS:=+kmod-mmc +kmod-cfg80211 +@DRIVER_11N_SUPPORT +@DRIVER_11AX_SUPPORT +aic8800-sdio-firmware
  CONFLICTS:=kmod-aic8800-pcie
  FILES:= \
	$(PKG_BUILD_DIR)/src/SDIO/driver_fw/driver/aic8800/aic8800_bsp/aic8800_bsp.ko \
	$(PKG_BUILD_DIR)/src/SDIO/driver_fw/driver/aic8800/aic8800_fdrv/aic8800_fdrv.ko
  AUTOLOAD:=$(call AutoProbe,aic8800_bsp aic8800_fdrv)
endef

define KernelPackage/aic8800-sdio-bt
  SUBMENU:=Other modules
  TITLE:=Aicsemi aic8800 Bluetooth SDIO support
  DEPENDS:=+kmod-mmc +kmod-bluetooth +aic8800-sdio-firmware
  FILES:=$(PKG_BUILD_DIR)/src/SDIO/driver_fw/driver/aic8800/aic8800_btlpm/aic8800_btlpm.ko
  AUTOLOAD:=$(call AutoProbe,aic8800_btlpm)
endef

define KernelPackage/aic8800-usb
  SUBMENU:=Wireless Drivers
  TITLE:=Aicsemi aic8800 Wi-Fi USB support
  DEPENDS:=+kmod-usb-core +kmod-cfg80211 +@DRIVER_11N_SUPPORT +@DRIVER_11AX_SUPPORT +aic8800-usb-firmware
  CONFLICTS:=kmod-aic8800-pcie kmod-aic8800-sdio
  FILES:= \
	$(PKG_BUILD_DIR)/src/USB/driver_fw/drivers/aic8800/aic_load_fw/aic_load_fw.ko \
	$(PKG_BUILD_DIR)/src/USB/driver_fw/drivers/aic8800/aic8800_fdrv/aic8800_fdrv.ko
  AUTOLOAD:=$(call AutoProbe,aic_load_fw aic8800_fdrv)
endef

define KernelPackage/aic8800-usb-bt
  SUBMENU:=Other modules
  TITLE:=Aicsemi aic8800 Bluetooth USB support
  DEPENDS:=+kmod-usb-core +kmod-bluetooth +aic8800-usb-firmware
  CONFLICTS:=kmod-aic8800-sdio-bt
  FILES:=$(PKG_BUILD_DIR)/src/USB/driver_fw/drivers/aic_btusb/aic_btusb.ko
  AUTOLOAD:=$(call AutoProbe,aic_btusb)
endef

NOSTDINC_FLAGS:= \
	$(KERNEL_NOSTDINC_FLAGS) \
	-I$(PKG_BUILD_DIR) \
	-I$(PKG_BUILD_DIR)/include \
	-I$(STAGING_DIR)/usr/include/mac80211-backport \
	-I$(STAGING_DIR)/usr/include/mac80211-backport/uapi \
	-I$(STAGING_DIR)/usr/include/mac80211 \
	-I$(STAGING_DIR)/usr/include/mac80211/uapi \
	-include backport/autoconf.h \
	-include backport/backport.h \
	-DBUILD_OPENWRT

define Build/Compile

ifneq ($(CONFIG_PACKAGE_kmod-aic8800-sdio)$(CONFIG_PACKAGE_kmod-aic8800-sdio-bt),)
	+$(KERNEL_MAKE) $(PKG_JOBS) \
		M="$(PKG_BUILD_DIR)/src/SDIO/driver_fw/driver/aic8800" \
		NOSTDINC_FLAGS="$(NOSTDINC_FLAGS)" \
		modules
endif
ifneq ($(CONFIG_PACKAGE_kmod-aic8800-pcie),)
	+$(KERNEL_MAKE) $(PKG_JOBS) \
		M="$(PKG_BUILD_DIR)/src/PCIE/driver_fw/driver/aic8800/aic8800_fdrv" \
		NOSTDINC_FLAGS="$(NOSTDINC_FLAGS)" \
		modules
endif
ifneq ($(CONFIG_PACKAGE_kmod-aic8800-usb),)
	+$(KERNEL_MAKE) $(PKG_JOBS) \
		M="$(PKG_BUILD_DIR)/src/USB/driver_fw/drivers/aic8800" \
		NOSTDINC_FLAGS="$(NOSTDINC_FLAGS)" \
		modules
endif
ifneq ($(CONFIG_PACKAGE_kmod-aic8800-usb-bt),)
	+$(KERNEL_MAKE) $(PKG_JOBS) \
		M="$(PKG_BUILD_DIR)/src/USB/driver_fw/drivers/aic_btusb" \
		NOSTDINC_FLAGS="$(NOSTDINC_FLAGS)" \
		modules
endif
endef

define Package/aic8800-pcie-firmware/install
	$(INSTALL_DIR) $(1)/lib/firmware
	$(CP) \
		$(PKG_BUILD_DIR)/src/PCIE/driver_fw/fw/aic8800D80 \
		$(1)/lib/firmware/
endef

define Package/aic8800-sdio-firmware/install
	$(INSTALL_DIR) $(1)/lib/firmware
	$(CP) \
		$(PKG_BUILD_DIR)/src/SDIO/driver_fw/fw/aic8800D80 \
		$(1)/lib/firmware/
endef

define Package/aic8800-usb-firmware/install
	$(INSTALL_DIR) $(1)/lib/firmware
	$(CP) \
		$(PKG_BUILD_DIR)/src/USB/driver_fw/fw/* \
		$(1)/lib/firmware/
	$(CP) \
		$(PKG_BUILD_DIR)/debian/patches/fmacfw_8800d80_u02.bin \
		$(1)/lib/firmware/aic8800D80/
endef

$(eval $(call BuildPackage,aic8800-pcie-firmware))
$(eval $(call BuildPackage,aic8800-sdio-firmware))
$(eval $(call BuildPackage,aic8800-usb-firmware))
$(eval $(call KernelPackage,aic8800-pcie))
$(eval $(call KernelPackage,aic8800-sdio))
$(eval $(call KernelPackage,aic8800-sdio-bt))
$(eval $(call KernelPackage,aic8800-usb))
$(eval $(call KernelPackage,aic8800-usb-bt))
