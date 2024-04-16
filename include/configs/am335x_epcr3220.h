/*
 * am335x_evm.h
 *
 * Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef __CONFIG_AM335X_EPCR3220A1_H
#define __CONFIG_AM335X_EPCR3220A1_H

#define CONFIG_MEM_MICRON_1G

#include <configs/ti_am335x_common.h>
#include <linux/sizes.h>

#undef CONFIG_SPL_AM33XX_ENABLE_RTC32K_OSC

#define CONFIG_ADV_OTA_SUPPORT
#ifdef CONFIG_ADV_OTA_SUPPORT
#define CONFIG_CMD_READ
#endif

/* Clock Defines */
#define V_OSCK				24000000  /* Clock output from T2 */
#define V_SCLK				(V_OSCK)

#define CONFIG_SYS_BOARD_NAME		"epcr3220a1"

#define BOOT_TARGET_DEVICES(func) \
	func(MMC, mmc, 0) \
	func(MMC, mmc, 1)

#include <config_distro_bootcmd.h>

#ifndef CONFIG_SPL_BUILD
#include <environment/ti/dfu.h>

#define CFG_EXTRA_ENV_SETTINGS \
	DEFAULT_LINUX_BOOT_ENV \
	"bootdir=/boot\0" \
	"bootfile=zImage\0" \
	"fdtfile=undefined\0" \
	"finduuid=part uuid mmc ${mmcdev}:2 uuid\0" \
	"console=ttyS0,115200n8\0" \
	"mmcdev=0\0" \
	"mmcrootfstype=ext4 rootwait\0" \
	"optargs=\0" \
	"ramroot=/dev/ram0 rw\0" \
	"ramrootfstype=ext2\0" \
	"ramargs=setenv bootargs console=${console} " \
		"${optargs} " \
		"root=${ramroot} " \
		"rootfstype=${ramrootfstype}\0" \
	"args_mmc=run finduuid;setenv bootargs earlycon console=${console} " \
		"${optargs} " \
		"root=PARTUUID=${uuid} rw " \
		"rootfstype=${mmcrootfstype}\0" \
	"loadimage=load mmc ${bootpart} ${loadaddr} ${bootdir}/${bootfile}\0" \
	"loadfdt=load mmc ${bootpart} ${fdtaddr} ${bootdir}/${fdtfile}\0" \
	"loadramdisk=load mmc ${mmcdev} ${rdaddr} ramdisk.gz\0" \
	"ramboot=echo Booting from ramdisk ...; " \
		"run ramargs; " \
		"bootz ${loadaddr} ${rdaddr} ${fdtaddr}\0" \
	"mmcloados=run args_mmc; " \
		"if run loadfdt; then " \
			"bootz ${loadaddr} - ${fdtaddr}; " \
		"else " \
			"echo WARN: Cannot load the DT, try to bootz; " \
			"bootz; " \
		"fi;\0" \
	"mmcboot=" \
		"if mmc rescan; then " \
			"echo SD/MMC found on device ${mmcdev};" \
			"if run loadimage; then " \
				"run mmcloados;" \
			"fi;" \
		"fi;\0" \
	"findfdt="\
		"if test $board_name = epcr3220a1; then " \
			"setenv fdtfile am335x-epcr3220a1.dtb; fi; " \
		"if test $fdtfile = undefined; then " \
			"echo WARNING: Could not determine device tree to use; fi; \0" \
	"init_console=" \
		"setenv console ttyS0,115200n8;\0" \
	"bootcmd_adv_mmc=mmc dev ${mmcdev}; " \
		"setenv bootpart ${mmcdev}:2 ;" \
		"run mmcboot\0" \
	"distro_bootcmd= run bootcmd_adv_mmc\0"
#endif

/* NS16550 Configuration */
#define CFG_SYS_NS16550_COM1		0x44e09000	/* Base EVM has UART0 */
#define CFG_SYS_NS16550_COM2		0x48022000	/* UART1 */
#define CFG_SYS_NS16550_COM3		0x48024000	/* UART2 */
#define CFG_SYS_NS16550_COM4		0x481a6000	/* UART3 */
#define CFG_SYS_NS16550_COM5		0x481a8000	/* UART4 */
#define CFG_SYS_NS16550_COM6		0x481aa000	/* UART5 */

/* PMIC support */
#define CONFIG_POWER_TPS65910
#define PMIC_VDD_ILMAX_1_5_A
#define PMIC_VIO_ILMAX_1_0_A

#ifdef CONFIG_MTD_RAW_NAND
/* NAND: device related configs */
/* NAND: driver related configs */
#define CFG_SYS_NAND_ECCPOS		{ 2, 3, 4, 5, 6, 7, 8, 9, \
					 10, 11, 12, 13, 14, 15, 16, 17, \
					 18, 19, 20, 21, 22, 23, 24, 25, \
					 26, 27, 28, 29, 30, 31, 32, 33, \
					 34, 35, 36, 37, 38, 39, 40, 41, \
					 42, 43, 44, 45, 46, 47, 48, 49, \
					 50, 51, 52, 53, 54, 55, 56, 57, }

#define CFG_SYS_NAND_ECCSIZE		512
#define CFG_SYS_NAND_ECCBYTES	14
#endif /* !CONFIG_MTD_RAW_NAND */

/* USB Device Firmware Update support */
#ifndef CONFIG_SPL_BUILD
#define DFUARGS \
	DFU_ALT_INFO_EMMC \
	DFU_ALT_INFO_MMC \
	DFU_ALT_INFO_RAM \
	DFU_ALT_INFO_NAND
#endif

/* SPI flash. */
/* MAC Address on SPI Flash */
#define CONFIG_MAC_ADDR_SPI_BUS   0
#define CONFIG_MAC_ADDR_SPI_CS    0
#define CONFIG_MAC_ADDR_SPI_HZ CONFIG_SF_DEFAULT_SPEED
#define CONFIG_MAC_ADDR_SPI_MODE   3
#define CONFIG_MAC_OFFSET       0x1D000

#define CONFIG_SPL_PARAM_ADDR  (0XC1000000)

#define CONFIG_MMC_DEVICE_MAX 2
#define CONFIG_ADVANTECH_EMMC_BOOT

/* Network. */
/* Enable Realtek phy driver */
#define CONFIG_PHY_REALTEK

#define CONFIG_ENABLE_EPHY0
#define CONFIG_EPHY0_PHY_ADDR		3
#define CONFIG_ENABLE_EPHY1
#define CONFIG_EPHY1_PHY_ADDR		7
#define CONFIG_ACTIVE_EPHY_NUM		2
#define CONFIG_DEFAULT_ACTIVE_EPHY	0

/*
 * NOR Size = 16 MiB
 * Number of Sectors/Blocks = 128
 * Sector Size = 128 KiB
 * Word length = 16 bits
 * Default layout:
 * 0x000000 - 0x07FFFF : U-Boot (512 KiB)
 * 0x080000 - 0x09FFFF : First copy of U-Boot Environment (128 KiB)
 * 0x0A0000 - 0x0BFFFF : Second copy of U-Boot Environment (128 KiB)
 * 0x0C0000 - 0x4BFFFF : Linux Kernel (4 MiB)
 * 0x4C0000 - 0xFFFFFF : Userland (11 MiB + 256 KiB)
 */
#if defined(CONFIG_NOR)
#define CFG_SYS_FLASH_BASE		(0x08000000)
#define CFG_SYS_FLASH_SIZE		0x01000000
#endif  /* NOR support */

#define GPIO_TO_PIN(bank, gpio)		(32 * (bank) + (gpio))
#define UART_POWER		GPIO_TO_PIN(2, 25)
#define PCIE_PWR_EN		GPIO_TO_PIN(3, 21)
#define PCIE_RST		GPIO_TO_PIN(2, 23)
#define ADV_WDT_EN		GPIO_TO_PIN(2, 5)
#define ADV_WDT_GPIO	GPIO_TO_PIN(2, 4)

#endif	/* ! __CONFIG_AM335X_EPCR3220A1_H */
