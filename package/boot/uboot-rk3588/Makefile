#
# Copyright (C) 2022 ImmortalWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=uboot-rk3588
PKG_RELEASE:=1

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/radxa/u-boot.git
PKG_SOURCE_DATE:=2023-01-12
PKG_SOURCE_VERSION:=5753b21aa92481ec3191fdf1f4d53274590ac5aa
PKG_MIRROR_HASH:=4ce948013f113c571297ec2ffb2a15451f5f2c7ef032084e9d659090fda40710

include $(INCLUDE_DIR)/u-boot.mk
include $(INCLUDE_DIR)/package.mk

define U-Boot/Default
  BUILD_TARGET:=rockchip
  UENV:=default
  HIDDEN:=1
endef

define U-Boot/rock-5b-rk3588
  BUILD_SUBTARGET:=armv8
  NAME:=Radxa ROCK 5B
  BUILD_DEVICES:= \
    radxa_rock-5b
  DEPENDS:=+PACKAGE_u-boot-rock-5b-rk3588:arm-trusted-firmware-rk3588
  PKG_BUILD_DEPENDS:=arm-trusted-firmware-rockchip
  ATF:=rk3588_bl31_v1.27.elf
  DDR:=rk3588_ddr_lp4_2112MHz_lp5_2736MHz_v1.08.bin
endef

UBOOT_TARGETS := \
  rock-5b-rk3588

UBOOT_CONFIGURE_VARS += USE_PRIVATE_LIBGCC=yes

UBOOT_MAKE_FLAGS += \
  BL31=$(STAGING_DIR_IMAGE)/$(ATF) spl/u-boot-spl.bin u-boot.dtb u-boot.itb \
  KCFLAGS=-Wno-error=address

define Build/Configure
	$(call Build/Configure/U-Boot)

	$(SED) 's#CONFIG_MKIMAGE_DTC_PATH=.*#CONFIG_MKIMAGE_DTC_PATH="$(PKG_BUILD_DIR)/scripts/dtc/dtc"#g' $(PKG_BUILD_DIR)/.config
endef

define Build/InstallDev
	$(INSTALL_DIR) $(STAGING_DIR_IMAGE)
	$(PKG_BUILD_DIR)/tools/mkimage -n rk3588 -T rksd -d \
		$(STAGING_DIR_IMAGE)/$(DDR):$(PKG_BUILD_DIR)/spl/u-boot-spl.bin $(PKG_BUILD_DIR)/idbloader.img
	$(CP) $(PKG_BUILD_DIR)/idbloader.img $(STAGING_DIR_IMAGE)/$(BUILD_VARIANT)-idbloader.img
	$(CP) $(PKG_BUILD_DIR)/u-boot.itb $(STAGING_DIR_IMAGE)/$(BUILD_VARIANT)-u-boot.itb
endef

define Package/u-boot/install/default
endef

$(eval $(call BuildPackage/U-Boot))
