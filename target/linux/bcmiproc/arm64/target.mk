# SDPX-License-Identifier: GPL-2.0-only
#
# Copyright (C) 2018 Jianhui Zhao <jianhuizhao329@gmail.com>
# Copyright (C) 2019 Samik Gupta <samik.gupta@broadcom.com>
# Copyright (C) 2023 Tianling Shen <cnsztl@immortalwrt.org>

ARCH:=aarch64
CPU_TYPE:=cortex-a72
SUBTARGET:=arm64
BOARDNAME:=64-bit iProc based boards

define Target/Description
	Build image for boards based on 64-bit Broadcom iProc devices
endef
