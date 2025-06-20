# MemGuard and MemPol Evaluation on DynamIQ Arm Systems

This repository contains the code and configuration used for the experiments described in our paper:

> Ashutosh Pradhan, Daniele Ottaviano, Yi Jiang, Haozheng Huang,
> Jiajia Zhang, Alexander Zuepke, Andrea Bastoni, Marco Caccamo,
> *"Predictable Memory Bandwidth Regulation for DynamIQ Arm Systems"*,
> in Proceedings of the 31st IEEE International Conference on Embedded
> and Real-Time Computing Systems and Applications (RTCSA), Singapore, Aug. 2025.

In the paper, we analyze, port, and evaluate **MemGuard** and **MemPol** on two modern Arm-based commercial-off-the-shelf (COTS) platforms:

- **Rockchip RK3588** (Orange Pi 5 Plus)  
- **NVIDIA Jetson AGX Orin**

The study targets **DSU-based Arm MPSoCs** and demonstrates the feasibility and performance of software-based memory bandwidth regulation strategies on these architectures.

---

## Overview

We evaluate two memory regulation strategies based on performance monitoring counters (PMCs):

- **MemGuard**: An interrupt-based memory bandwidth regulator  
- **MemPol**: A polling-based memory bandwidth regulator

Both were ported and deployed using the **Jailhouse hypervisor**, a minimal partitioning hypervisor that relies on Linux to boot the system before taking control.

---

## Jailhouse Integration

All modifications for the MemGuard and MemPol experiments are integrated into the **`Minerva` fork of Jailhouse**.

🔗 [Minerva Jailhouse Fork](https://github.com/Minervasys/jailhouse)

Jailhouse is used to configure and start isolated VMs, including a bare-metal MemPol regulator running on a dedicated core.

The Minerva fork also includes the MemGuard implementation used in our evaluation.

---

## MemPol Setup Notes

The main source code for MemPol is available at:

🔗 [MemPol](https://gitlab.com/azuepke/mempol)

To evaluate **MemPol** on the target platforms, we executed it on application-level cores rather than low-power cores because:

- On RK3588, the integrated Cortex-M0 cores are undocumented and not publicly accessible.  
- On AGX Orin, the small cores (e.g., Cortex-R5, Cortex-A9) are reserved for firmware tasks and are not user-programmable with the default configuration.

Thus, MemPol was launched from a **Jailhouse VM running on a dedicated Cortex-A55 (RK3588) or Cortex-A78AE (Orin) core**. 
The corresponding Jailhouse configuration files are included in this repository.

---

### Memory Mapping Requirement

To function correctly, MemPol requires its reserved memory region to be mapped as **Normal (cached) memory** in the device tree. For this purpose, we provide a companion Linux driver:

🔗 [MemPol Driver](https://github.com/rtsl-cps-tum/mempol_driver)

This driver ensures that the memory used by MemPol is correctly reserved and mapped as cached memory, rather than as I/O memory.

---
