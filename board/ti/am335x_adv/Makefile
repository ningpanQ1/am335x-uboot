# SPDX-License-Identifier: GPL-2.0+
#
# Makefile
#
# Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/

ifeq ($(CONFIG_$(SPL_)SKIP_LOWLEVEL_INIT),)
obj-y	:= mux.o
endif

obj-y	+= board.o

ifndef CONFIG_SPL_BUILD
ifdef CONFIG_ADV_OTA_SUPPORT
obj-y	+= command.o bcb.o
endif
endif
