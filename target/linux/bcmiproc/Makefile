# SPDX-License-Identifier: GPL-2.0-only
#
# Copyright (C) 2018 Jianhui Zhao <jianhuizhao329@gmail.com>
# Copyright (C) 2019 Samik Gupta <samik.gupta@broadcom.com>
# Copyright (C) 2023 Tianling Shen <cnsztl@immortalwrt.org>

include $(TOPDIR)/rules.mk

BOARD:=bcmiproc
BOARDNAME:=Broadcom iProc
FEATURES:=fpu pci rtc usb ext4 rootfs-part ext4 squashfs targz
SUBTARGETS:=arm64

MAINTAINER:=Samik Gupta <samik.gupta@broadcom.com>

KERNEL_PATCHVER:=5.15

define Target/Description
	Build firmware images for Broadcom iProc SoC based boards.
endef

include $(INCLUDE_DIR)/target.mk

KERNELNAME:=Image

$(eval $(call BuildTarget))
