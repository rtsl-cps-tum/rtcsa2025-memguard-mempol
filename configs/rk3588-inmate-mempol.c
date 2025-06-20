/**
 * Inmate Demo for RK3588
 * Root Cell Config - rk3588.c
 * Meant to be used for the MemPol code
 */


 /* 
 * jailhouse cell create rk3588-inmate-mempol.cell
 * jailhouse cell load inmate-mempol linux-loader.bin -a 0x0 -s "kernel=0x200000" -a 0x1000 kernel.bin -a 0x200000
 * jailhouse cell start inmate-mempol
 * jailhouse cell load 1 linux-loader.bin -a 0x0 -s "kernel=0x200000" -a 0x1000 kernel.bin -a 0x200000
 */

#include <jailhouse/types.h>
#include <jailhouse/cell-config.h>
#include <jailhouse/mem-pol.h>

struct 
{
    struct jailhouse_cell_desc cell;
    __u64 cpus[1];
    struct jailhouse_memory mem_regions[1 + 3 + 1 + 1];
    // struct jailhouse_irqchip irqchips[4];
} __attribute__ ((packed)) config = {
    .cell = {
        .signature = JAILHOUSE_CELL_DESC_SIGNATURE,
        .revision = JAILHOUSE_CONFIG_REVISION,
        .architecture = JAILHOUSE_ARM64,
        .name = "inmate-mempol",
        .flags = JAILHOUSE_CELL_PASSIVE_COMMREG | JAILHOUSE_CELL_VIRTUAL_CONSOLE_PERMITTED,
        
        .cpu_set_size = sizeof(config.cpus),
		.num_memory_regions = ARRAY_SIZE(config.mem_regions),

        .console = {
            /* UART 3, interrupt 366 (SPI 334) 
            This is /dev/ttyS3 (picocom orangepi.2) in Orange Pi 5 Plus Linux kernel 6.13*/ 

			.address = 0xfeb50000,
			.type = JAILHOUSE_CON_TYPE_8250,
			.flags = JAILHOUSE_CON_ACCESS_MMIO |
					JAILHOUSE_CON_REGDIST_4,
		},
    },

    .cpus = {
        0b00001000,
    },

    .mem_regions = {
        /*UART 3*/{
            .phys_start = 0xfeb50000, 
			.virt_start = 0xfeb50000, 
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
					JAILHOUSE_MEM_IO | JAILHOUSE_MEM_ROOTSHARED,
        },
        /**
		 * RAM for Linux Loader
		 * 1 MB Region to hold the hold the code of linux loader
		 * Doesn't need to be this big
		 * */ {
            .phys_start = 0x0b000000,
            .virt_start = 0x0,
            .size = 0x00200000,
            .flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
					JAILHOUSE_MEM_EXECUTE | JAILHOUSE_MEM_LOADABLE | 
					JAILHOUSE_MEM_ROOTSHARED,
        },
        /**
		 * RAM for Mempol Code
		 * 16 MB Region to hold the hold the main code of mempol
		 * Doesn't need to be this big
		 * */ {
            .phys_start = 0x0b200000, // 0x00200000
            .virt_start = 0x00200000,
            .size = 0x00004000,
            .flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
					JAILHOUSE_MEM_LOADABLE | JAILHOUSE_MEM_ROOTSHARED, 
					// JAILHOUSE_MEM_EXECUTE | JAILHOUSE_MEM_LOADABLE|
        },
		/**
		 * RAM for Mempol Code
		 * 16 MB Region to hold the hold the main code of mempol
		 * Doesn't need to be this big
		 * */ {
            .phys_start = 0x0b204000,
            .virt_start = 0x00204000,
            .size = 0x0001c000,
            .flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE | 
					JAILHOUSE_MEM_ROOTSHARED, //JAILHOUSE_MEM_IO ,
        },
		/* CoreSight Registers on RK3588 */ {
			.phys_start = 0xfd100000, 
			.virt_start = 0xfd100000,
			.size = 0x40000,
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
    // .irqchips = {
	// 	/* GIC */ {
	// 		.address = 0xfe600000,
	// 		.pin_base = 32,
	// 		.pin_bitmap = {
	// 			0, 0, 0, 0,
	// 		},
	// 	},
	// 	/* GIC */ {
	// 		.address = 0xfe600000,
	// 		.pin_base = 160,
	// 		.pin_bitmap = {
	// 			0, 0, 0, 0,
	// 		},
	// 	},
	// 	/* GIC */ {
	// 		.address = 0xfe600000,
	// 		.pin_base = 288,
	// 		.pin_bitmap = {
	// 			0, 0, (1u << (366 - 352)), 0,
	// 		},
	// 	},
	// 	/* GIC */ {
	// 		.address = 0xfe600000,
	// 		.pin_base = 416,
	// 		.pin_bitmap = {
	// 			0, (0xfu << (460 - 448)), 0, 0,
	// 		},
	// 	},
	// },
};
