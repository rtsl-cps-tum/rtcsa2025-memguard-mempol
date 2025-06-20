/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Jailhouse, a Linux-based partitioning hypervisor
 *
 * Configuration for AGX-Orin SoCs
 *
 * Copyright (c) 2024 Minerva Systems
 *
 * Authors:
 *  Alex Zuepke <alex.zuepke@minervasys.tech>
 *
 * This work is licensed under the terms of the GNU GPL, version 2.
 * See the COPYING file in the top-level directory.
 *
 * Change here and the root cell DTB accordingly to activate the other serials.
 */
/*
 * sudo jailhouse cell create orin-mempol-demo.cell
 * sudo jailhouse cell load orin-mempol-demo kernel.bin -a 0x80200000
 * sudo jailhouse cell start orin-mempol-demo
 */


#include <jailhouse/types.h>
#include <jailhouse/cell-config.h>

struct {
	struct jailhouse_cell_desc cell;
	__u64 cpus[1];
	struct jailhouse_memory mem_regions[5];
	struct jailhouse_irqchip irqchips[10];
} __attribute__((packed)) config = {
	.cell = {
		.signature = JAILHOUSE_CELL_DESC_SIGNATURE,
		.architecture = JAILHOUSE_ARM64,
		.revision = JAILHOUSE_CONFIG_REVISION,
		.name = "orin-mempol-demo",
		.flags = JAILHOUSE_CELL_PASSIVE_COMMREG,

		.cpu_set_size = sizeof(config.cpus),
		.num_memory_regions = ARRAY_SIZE(config.mem_regions),
		.num_irqchips = ARRAY_SIZE(config.irqchips),
		.num_pci_devices = 0,

		.cpu_reset_address = 0x80200000,

		.console = {
			/* uart0, interrupt 317 (SPI 285) */
			.address = 0x031d0000,
			.size = 0x00010000,
			.type = JAILHOUSE_CON_TYPE_8250,
			.flags = JAILHOUSE_CON_ACCESS_MMIO |
				 JAILHOUSE_CON_REGDIST_4,
		},
	},

	.cpus = {
		0b000000001000,
	},

	.mem_regions = {
		/* 128 KB memory region from 0x80200000 to 0x80220000 for Mempol */

		/* RAM for mempol */ {
			.phys_start = 0x80200000,
			.virt_start = 0x80200000,
			.size = 0x00004000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
			        JAILHOUSE_MEM_EXECUTE | JAILHOUSE_MEM_LOADABLE |
					JAILHOUSE_MEM_ROOTSHARED,
		},
		/* RAM for mempol (shared region) */ {
			.phys_start = 0x80204000,
			.virt_start = 0x80204000,
			.size = 0x0001c000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
			        JAILHOUSE_MEM_EXECUTE |
					JAILHOUSE_MEM_ROOTSHARED,
		},

		/* CoreSight Tegra234_A78 */ {
			.phys_start = 0x27000000,
			.virt_start = 0x27000000,
			.size = 0x01000000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
					JAILHOUSE_MEM_IO | JAILHOUSE_MEM_ROOTSHARED,
		},

		/* uart0 */ {
			.phys_start = 0x031d0000,
			.virt_start = 0x031d0000,
			.size = 0x10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
					JAILHOUSE_MEM_IO | JAILHOUSE_MEM_ROOTSHARED,
		},

		/* communication region */ {
			.virt_start = 0x80000000,
			.size = 0x00001000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
					JAILHOUSE_MEM_COMM_REGION,
		},

	},

	.irqchips = {
		/* GIC */ {
			.address = 0x0f400000,
			.pin_base = 32,
			.pin_bitmap = {
				0, 0, 0, 0,
			},
		},
		/* GIC */ {
			.address = 0x0f400000,
			.pin_base = 160,
			.pin_bitmap = {
				0, 0, 0, 0,
			},
		},
		/* GIC */ {
			.address = 0x0f400000,
			.pin_base = 288,
			.pin_bitmap = {
				(1u << (317 - 288)), 0, 0, 0,
			},
		},
		/* GIC */ {
			.address = 0x0f400000,
			.pin_base = 416,
			.pin_bitmap = {
				0, 0, 0, 0,
			},
		},
		/* GIC */ {
			.address = 0x0f400000,
			.pin_base = 544,
			.pin_bitmap = {
				0, (0xfu << (592 - 576)), 0, 0,
			},
		},
		/* GIC */ {
			.address = 0x0f400000,
			.pin_base = 672,
			.pin_bitmap = {
				0, 0, 0, 0,
			},
		},
		/* GIC */ {
			.address = 0x0f400000,
			.pin_base = 800,
			.pin_bitmap = {
				0, 0, 0, 0,
			},
		},
		/* GIC */ {
			.address = 0x0f400000,
			.pin_base = 928,
			.pin_bitmap = {
				0, 0, 0, 0,
			},
		},
	},

};
