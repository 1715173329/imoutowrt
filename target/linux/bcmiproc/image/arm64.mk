# SPDX-License-Identifier: GPL-2.0-only
#
# Copyright (C) 2023 Tianling Shen <cnsztl@immortalwrt.org>

define Device/brcm_bcm958802a802x
  DEVICE_VENDOR := Stingray
  DEVICE_MODEL := PS225xx (BCM958802A802x)
  DTS_SUBDIR := stingray
endef
TARGET_DEVICES += brcm_bcm958802a802x
