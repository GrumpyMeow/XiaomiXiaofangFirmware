cmd_/home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/os/linux/../../chips/rt33xx.o := arm-linux-gcc -Wp,-MD,/home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/os/linux/../../chips/.rt33xx.o.d  -nostdinc -isystem /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/toolchain/crosstool-4.5.2/bin/../lib/gcc/arm-unknown-linux-uclibcgnueabi/4.5.2/include -I/home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include -Iinclude  -I/home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include -include include/generated/autoconf.h -I/home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/buildscript/include   -I/home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/os/linux -D__KERNEL__ -mlittle-endian   -I/home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/mach-sn986xx/include -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -Os -marm -mabi=aapcs-linux -mno-thumb-interwork -funwind-tables -D__LINUX_ARM_ARCH__=5 -march=armv5te -mtune=arm926ej-s -msoft-float -Uarm -Wframe-larger-than=1024 -fno-stack-protector -fomit-frame-pointer -g -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack -DAGGREGATION_SUPPORT -DPIGGYBACK_SUPPORT -DWMM_SUPPORT -DLINUX -Wall -Wstrict-prototypes -Wno-trigraphs -DSYSTEM_LOG_SUPPORT -DRT28xx_MODE=STA -DCHIPSET=5370 -DRESOURCE_PRE_ALLOC -DCONFIG_STA_SUPPORT -DDBG -DWPA_SUPPLICANT_SUPPORT -DNATIVE_WPA_SUPPLICANT_SUPPORT -DRALINK_ATE -DCONFIG_RT2880_ATE_CMD_NEW -DRALINK_QA -DDOT11_N_SUPPORT -DLED_CONTROL_SUPPORT -DRTMP_MAC_USB -DRT30xx -DRT33xx -DRT3070 -DRT3370 -DRT5370 -DRTMP_USB_SUPPORT -DRTMP_TIMER_TASK_SUPPORT -DRTMP_RF_RW_SUPPORT -DRTMP_EFUSE_SUPPORT -DRTMP_INTERNAL_TX_ALC -DhSPECIFIC_BCN_BUF_SUPPORT -DRTMP_FREQ_CALIBRATION_SUPPORT -DSPECIFIC_VCORECAL_SUPPORT -DCONFIG_5VT_ENHANCE -O2   -I/home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/include  -DMODULE -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(rt33xx)"  -D"KBUILD_MODNAME=KBUILD_STR(rt5370sta)"  -c -o /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/os/linux/../../chips/rt33xx.o /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/os/linux/../../chips/rt33xx.c

deps_/home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/os/linux/../../chips/rt33xx.o := \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/os/linux/../../chips/rt33xx.c \
    $(wildcard include/config/sta/support.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/include/rt_config.h \
    $(wildcard include/config/h//.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/include/rtmp_comm.h \
    $(wildcard include/config/ap/support.h) \
    $(wildcard include/config/opmode/on/ap.h) \
    $(wildcard include/config/opmode/on/sta.h) \
    $(wildcard include/config/if/opmode/on/ap.h) \
    $(wildcard include/config/if/opmode/on/sta.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/include/rtmp_type.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/include/rtmp_os.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/include/os/rt_linux.h \
    $(wildcard include/config/apsta/mixed/support.h) \
    $(wildcard include/config/pm.h) \
    $(wildcard include/config/5vt/enhance.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/module.h \
    $(wildcard include/config/symbol/prefix.h) \
    $(wildcard include/config/modules.h) \
    $(wildcard include/config/modversions.h) \
    $(wildcard include/config/unused/symbols.h) \
    $(wildcard include/config/generic/bug.h) \
    $(wildcard include/config/kallsyms.h) \
    $(wildcard include/config/smp.h) \
    $(wildcard include/config/tracepoints.h) \
    $(wildcard include/config/tracing.h) \
    $(wildcard include/config/event/tracing.h) \
    $(wildcard include/config/ftrace/mcount/record.h) \
    $(wildcard include/config/module/unload.h) \
    $(wildcard include/config/constructors.h) \
    $(wildcard include/config/sysfs.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/list.h \
    $(wildcard include/config/debug/list.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/stddef.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/compiler.h \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/enable/warn/deprecated.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/compiler-gcc.h \
    $(wildcard include/config/arch/supports/optimized/inlining.h) \
    $(wildcard include/config/optimize/inlining.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/compiler-gcc4.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/poison.h \
    $(wildcard include/config/illegal/pointer/value.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/prefetch.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/types.h \
    $(wildcard include/config/uid16.h) \
    $(wildcard include/config/lbdaf.h) \
    $(wildcard include/config/phys/addr/t/64bit.h) \
    $(wildcard include/config/64bit.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/types.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/asm-generic/int-ll64.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/bitsperlong.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/asm-generic/bitsperlong.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/posix_types.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/posix_types.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/processor.h \
    $(wildcard include/config/arm/fcse.h) \
    $(wildcard include/config/mmu.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/ptrace.h \
    $(wildcard include/config/cpu/endian/be8.h) \
    $(wildcard include/config/arm/thumb.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/hwcap.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/cache.h \
    $(wildcard include/config/arm/l1/cache/shift.h) \
    $(wildcard include/config/aeabi.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/system.h \
    $(wildcard include/config/cpu/xsc3.h) \
    $(wildcard include/config/cpu/fa526.h) \
    $(wildcard include/config/arch/has/barriers.h) \
    $(wildcard include/config/arm/dma/mem/bufferable.h) \
    $(wildcard include/config/cpu/sa1100.h) \
    $(wildcard include/config/cpu/sa110.h) \
    $(wildcard include/config/cpu/32v6k.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/linkage.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/linkage.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/irqflags.h \
    $(wildcard include/config/trace/irqflags.h) \
    $(wildcard include/config/irqsoff/tracer.h) \
    $(wildcard include/config/preempt/tracer.h) \
    $(wildcard include/config/trace/irqflags/support.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/typecheck.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/irqflags.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/outercache.h \
    $(wildcard include/config/outer/cache/sync.h) \
    $(wildcard include/config/outer/cache.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/asm-generic/cmpxchg-local.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/asm-generic/cmpxchg.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/stat.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/stat.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/time.h \
    $(wildcard include/config/arch/uses/gettimeoffset.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/cache.h \
    $(wildcard include/config/arch/has/cache/line/size.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/kernel.h \
    $(wildcard include/config/snx/msg/tag.h) \
    $(wildcard include/config/preempt/voluntary.h) \
    $(wildcard include/config/debug/spinlock/sleep.h) \
    $(wildcard include/config/prove/locking.h) \
    $(wildcard include/config/printk.h) \
    $(wildcard include/config/dynamic/debug.h) \
    $(wildcard include/config/ring/buffer.h) \
    $(wildcard include/config/numa.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/toolchain/crosstool-4.5.2/bin/../lib/gcc/arm-unknown-linux-uclibcgnueabi/4.5.2/include/stdarg.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/bitops.h \
    $(wildcard include/config/generic/find/first/bit.h) \
    $(wildcard include/config/generic/find/last/bit.h) \
    $(wildcard include/config/generic/find/next/bit.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/bitops.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/asm-generic/bitops/non-atomic.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/asm-generic/bitops/fls64.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/asm-generic/bitops/sched.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/asm-generic/bitops/hweight.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/asm-generic/bitops/arch_hweight.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/asm-generic/bitops/const_hweight.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/asm-generic/bitops/lock.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/log2.h \
    $(wildcard include/config/arch/has/ilog2/u32.h) \
    $(wildcard include/config/arch/has/ilog2/u64.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/dynamic_debug.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/byteorder.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/byteorder/little_endian.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/swab.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/swab.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/byteorder/generic.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/bug.h \
    $(wildcard include/config/bug.h) \
    $(wildcard include/config/debug/bugverbose.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/asm-generic/bug.h \
    $(wildcard include/config/generic/bug/relative/pointers.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/seqlock.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/spinlock.h \
    $(wildcard include/config/debug/spinlock.h) \
    $(wildcard include/config/generic/lockbreak.h) \
    $(wildcard include/config/preempt.h) \
    $(wildcard include/config/debug/lock/alloc.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/preempt.h \
    $(wildcard include/config/debug/preempt.h) \
    $(wildcard include/config/preempt/notifiers.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/thread_info.h \
    $(wildcard include/config/compat.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/thread_info.h \
    $(wildcard include/config/arm/thumbee.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/fpstate.h \
    $(wildcard include/config/vfpv3.h) \
    $(wildcard include/config/iwmmxt.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/domain.h \
    $(wildcard include/config/io/36.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/stringify.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/bottom_half.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/spinlock_types.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/spinlock_types_up.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/lockdep.h \
    $(wildcard include/config/lockdep.h) \
    $(wildcard include/config/lock/stat.h) \
    $(wildcard include/config/generic/hardirqs.h) \
    $(wildcard include/config/prove/rcu.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/rwlock_types.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/spinlock_up.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/rwlock.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/spinlock_api_up.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/atomic.h \
    $(wildcard include/config/generic/atomic64.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/asm-generic/atomic64.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/asm-generic/atomic-long.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/math64.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/div64.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/kmod.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/gfp.h \
    $(wildcard include/config/kmemcheck.h) \
    $(wildcard include/config/highmem.h) \
    $(wildcard include/config/zone/dma.h) \
    $(wildcard include/config/zone/dma32.h) \
    $(wildcard include/config/debug/vm.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/mmzone.h \
    $(wildcard include/config/force/max/zoneorder.h) \
    $(wildcard include/config/memory/hotplug.h) \
    $(wildcard include/config/sparsemem.h) \
    $(wildcard include/config/compaction.h) \
    $(wildcard include/config/arch/populates/node/map.h) \
    $(wildcard include/config/discontigmem.h) \
    $(wildcard include/config/flat/node/mem/map.h) \
    $(wildcard include/config/cgroup/mem/res/ctlr.h) \
    $(wildcard include/config/no/bootmem.h) \
    $(wildcard include/config/have/memory/present.h) \
    $(wildcard include/config/have/memoryless/nodes.h) \
    $(wildcard include/config/need/node/memmap/size.h) \
    $(wildcard include/config/need/multiple/nodes.h) \
    $(wildcard include/config/have/arch/early/pfn/to/nid.h) \
    $(wildcard include/config/flatmem.h) \
    $(wildcard include/config/sparsemem/extreme.h) \
    $(wildcard include/config/nodes/span/other/nodes.h) \
    $(wildcard include/config/holes/in/zone.h) \
    $(wildcard include/config/arch/has/holes/memorymodel.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/wait.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/current.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/threads.h \
    $(wildcard include/config/nr/cpus.h) \
    $(wildcard include/config/base/small.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/numa.h \
    $(wildcard include/config/nodes/shift.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/init.h \
    $(wildcard include/config/hotplug.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/nodemask.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/bitmap.h \
    $(wildcard include/config/pre/allocate/algo/enhance.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/string.h \
    $(wildcard include/config/binary/printf.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/string.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/pageblock-flags.h \
    $(wildcard include/config/hugetlb/page.h) \
    $(wildcard include/config/hugetlb/page/size/variable.h) \
  include/generated/bounds.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/page.h \
    $(wildcard include/config/cpu/copy/v3.h) \
    $(wildcard include/config/cpu/copy/v4wt.h) \
    $(wildcard include/config/cpu/copy/v4wb.h) \
    $(wildcard include/config/cpu/copy/feroceon.h) \
    $(wildcard include/config/cpu/copy/fa.h) \
    $(wildcard include/config/cpu/xscale.h) \
    $(wildcard include/config/cpu/copy/v6.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/glue.h \
    $(wildcard include/config/cpu/arm610.h) \
    $(wildcard include/config/cpu/arm710.h) \
    $(wildcard include/config/cpu/abrt/lv4t.h) \
    $(wildcard include/config/cpu/abrt/ev4.h) \
    $(wildcard include/config/cpu/abrt/ev4t.h) \
    $(wildcard include/config/cpu/abrt/ev5tj.h) \
    $(wildcard include/config/cpu/abrt/ev5t.h) \
    $(wildcard include/config/cpu/abrt/ev6.h) \
    $(wildcard include/config/cpu/abrt/ev7.h) \
    $(wildcard include/config/cpu/pabrt/legacy.h) \
    $(wildcard include/config/cpu/pabrt/v6.h) \
    $(wildcard include/config/cpu/pabrt/v7.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/memory.h \
    $(wildcard include/config/page/offset.h) \
    $(wildcard include/config/thumb2/kernel.h) \
    $(wildcard include/config/dram/size.h) \
    $(wildcard include/config/dram/base.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/const.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/mach-sn986xx/include/mach/memory.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/sizes.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/asm-generic/memory_model.h \
    $(wildcard include/config/sparsemem/vmemmap.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/asm-generic/getorder.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/memory_hotplug.h \
    $(wildcard include/config/have/arch/nodedata/extension.h) \
    $(wildcard include/config/memory/hotremove.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/notifier.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/errno.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/errno.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/asm-generic/errno.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/asm-generic/errno-base.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/mutex.h \
    $(wildcard include/config/debug/mutexes.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/mutex-debug.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/rwsem.h \
    $(wildcard include/config/rwsem/generic/spinlock.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/rwsem-spinlock.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/srcu.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/topology.h \
    $(wildcard include/config/sched/smt.h) \
    $(wildcard include/config/sched/mc.h) \
    $(wildcard include/config/use/percpu/numa/node/id.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/cpumask.h \
    $(wildcard include/config/cpumask/offstack.h) \
    $(wildcard include/config/hotplug/cpu.h) \
    $(wildcard include/config/debug/per/cpu/maps.h) \
    $(wildcard include/config/disable/obsolete/cpumask/functions.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/smp.h \
    $(wildcard include/config/use/generic/smp/helpers.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/percpu.h \
    $(wildcard include/config/need/per/cpu/embed/first/chunk.h) \
    $(wildcard include/config/need/per/cpu/page/first/chunk.h) \
    $(wildcard include/config/have/setup/per/cpu/area.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/pfn.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/percpu.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/asm-generic/percpu.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/percpu-defs.h \
    $(wildcard include/config/debug/force/weak/per/cpu.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/topology.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/asm-generic/topology.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/mmdebug.h \
    $(wildcard include/config/debug/virtual.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/workqueue.h \
    $(wildcard include/config/debug/objects/work.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/timer.h \
    $(wildcard include/config/timer/stats.h) \
    $(wildcard include/config/debug/objects/timers.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/ktime.h \
    $(wildcard include/config/ktime/scalar.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/jiffies.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/timex.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/param.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/param.h \
    $(wildcard include/config/hz.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/timex.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/mach-sn986xx/include/mach/timex.h \
    $(wildcard include/config/system/platform/st58660fpga.h) \
    $(wildcard include/config/system/platform/sn98660.h) \
    $(wildcard include/config/pll/clk.h) \
    $(wildcard include/config/tick/clock/ratio.h) \
    $(wildcard include/config/special/hw/timer.h) \
    $(wildcard include/config/snx/log/timestamp.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/mach-sn986xx/include/mach/platform.h \
    $(wildcard include/config/system/platform/st58660.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/seq_file.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/buildscript/include/generated/snx_sdk_conf.h \
    $(wildcard include/config/module/sdc/support.h) \
    $(wildcard include/config/rootfs/update.h) \
    $(wildcard include/config/app/rp/pppoe.h) \
    $(wildcard include/config/app/smtpc.h) \
    $(wildcard include/config/app/hostapd.h) \
    $(wildcard include/config/nvram/part/size.h) \
    $(wildcard include/config/module/ahbdma/support.h) \
    $(wildcard include/config/rescue/update.h) \
    $(wildcard include/config/kernel/normal/def/config.h) \
    $(wildcard include/config/app/isp/tuning/tool.h) \
    $(wildcard include/config/system/apb/clock/ratio.h) \
    $(wildcard include/config/kernel/rescue/def/config.h) \
    $(wildcard include/config/system/series.h) \
    $(wildcard include/config/factory/update.h) \
    $(wildcard include/config/module/gpio/support.h) \
    $(wildcard include/config/app/galaxyserver.h) \
    $(wildcard include/config/enable/burnbin/log.h) \
    $(wildcard include/config/app/tsocks.h) \
    $(wildcard include/config/system/platform.h) \
    $(wildcard include/config/app/miniupnpc.h) \
    $(wildcard include/config/app/boa.h) \
    $(wildcard include/config/app/fwupdate.h) \
    $(wildcard include/config/video/sensor/ov9715.h) \
    $(wildcard include/config/isp/awb.h) \
    $(wildcard include/config/nvram/factory/size.h) \
    $(wildcard include/config/fw/encrypt/key.h) \
    $(wildcard include/config/system/serial/flash/support.h) \
    $(wildcard include/config/module/spi/support.h) \
    $(wildcard include/config/app/iptables.h) \
    $(wildcard include/config/system/ddr/w9751g6kb/32mx16.h) \
    $(wildcard include/config/module/usb/wifi/rt5370.h) \
    $(wildcard include/config/app/samba.h) \
    $(wildcard include/config/module/bus/mon/support.h) \
    $(wildcard include/config/app/wireless/tools.h) \
    $(wildcard include/config/app/mdnsresponder.h) \
    $(wildcard include/config/module/usb/3g/support.h) \
    $(wildcard include/config/module/pwm/support.h) \
    $(wildcard include/config/ddr/project.h) \
    $(wildcard include/config/module/usb/storage/support.h) \
    $(wildcard include/config/app/twoway/audio.h) \
    $(wildcard include/config/kernel/update.h) \
    $(wildcard include/config/nvram/part.h) \
    $(wildcard include/config/system/platform/sn98600.h) \
    $(wildcard include/config/app/web/admin.h) \
    $(wildcard include/config/etc/part/size.h) \
    $(wildcard include/config/module/tv/support.h) \
    $(wildcard include/config/module/rtc/support.h) \
    $(wildcard include/config/isp/af.h) \
    $(wildcard include/config/system/ddr360mhz.h) \
    $(wildcard include/config/app/ntp.h) \
    $(wildcard include/config/app/iperf.h) \
    $(wildcard include/config/module/video/support.h) \
    $(wildcard include/config/uboot/update.h) \
    $(wildcard include/config/etc/update.h) \
    $(wildcard include/config/module/iq/support.h) \
    $(wildcard include/config/module/timer/support.h) \
    $(wildcard include/config/kernel/part/size.h) \
    $(wildcard include/config/app/miniupnpd.h) \
    $(wildcard include/config/app/wpa/supplicant.h) \
    $(wildcard include/config/rescue/system.h) \
    $(wildcard include/config/rescue/system/part.h) \
    $(wildcard include/config/system/performance/clk.h) \
    $(wildcard include/config/app/ppp.h) \
    $(wildcard include/config/app/wpa/0/7/3.h) \
    $(wildcard include/config/app/sensor2tv.h) \
    $(wildcard include/config/app/ezipupdate.h) \
    $(wildcard include/config/app/snmp.h) \
    $(wildcard include/config/ddr/freq.h) \
    $(wildcard include/config/user/update.h) \
    $(wildcard include/config/module/usb/wifi/support.h) \
    $(wildcard include/config/module/crypto/support.h) \
    $(wildcard include/config/isp/ae.h) \
    $(wildcard include/config/rescue/part/size.h) \
    $(wildcard include/config/system/serial/flash/16m.h) \
    $(wildcard include/config/module/audio/support.h) \
    $(wildcard include/config/rootfs/part/size.h) \
    $(wildcard include/config/module/wdt/support.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/debugobjects.h \
    $(wildcard include/config/debug/objects.h) \
    $(wildcard include/config/debug/objects/free.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/elf.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/elf-em.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/elf.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/user.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/kobject.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/sysfs.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/kref.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/moduleparam.h \
    $(wildcard include/config/alpha.h) \
    $(wildcard include/config/ia64.h) \
    $(wildcard include/config/ppc64.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/tracepoint.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/rcupdate.h \
    $(wildcard include/config/rcu/torture/test.h) \
    $(wildcard include/config/tree/rcu.h) \
    $(wildcard include/config/tree/preempt/rcu.h) \
    $(wildcard include/config/tiny/rcu.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/completion.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/rcutree.h \
    $(wildcard include/config/no/hz.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/module.h \
    $(wildcard include/config/arm/unwind.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/trace/events/module.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/trace/define_trace.h \
  include/linux/version.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/slab.h \
    $(wildcard include/config/slab/debug.h) \
    $(wildcard include/config/failslab.h) \
    $(wildcard include/config/slub.h) \
    $(wildcard include/config/slob.h) \
    $(wildcard include/config/debug/slab.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/slub_def.h \
    $(wildcard include/config/slub/stats.h) \
    $(wildcard include/config/slub/debug.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/kmemtrace.h \
    $(wildcard include/config/kmemtrace.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/trace/events/kmem.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/kmemleak.h \
    $(wildcard include/config/debug/kmemleak.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/interrupt.h \
    $(wildcard include/config/pm/sleep.h) \
    $(wildcard include/config/generic/irq/probe.h) \
    $(wildcard include/config/proc/fs.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/irqreturn.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/irqnr.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/hardirq.h \
    $(wildcard include/config/virt/cpu/accounting.h) \
    $(wildcard include/config/irq/time/accounting.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/ftrace_irq.h \
    $(wildcard include/config/ftrace/nmi/enter.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/hardirq.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/irq.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/mach-sn986xx/include/mach/irqs.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/irq_cpustat.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/hrtimer.h \
    $(wildcard include/config/high/res/timers.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/rbtree.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/pci.h \
    $(wildcard include/config/pci/iov.h) \
    $(wildcard include/config/pcieaspm.h) \
    $(wildcard include/config/pci/msi.h) \
    $(wildcard include/config/pci.h) \
    $(wildcard include/config/pcie/ecrc.h) \
    $(wildcard include/config/ht/irq.h) \
    $(wildcard include/config/pci/domains.h) \
    $(wildcard include/config/pci/quirks.h) \
    $(wildcard include/config/pci/mmconfig.h) \
    $(wildcard include/config/hotplug/pci.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/pci_regs.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/mod_devicetable.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/ioport.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/device.h \
    $(wildcard include/config/of.h) \
    $(wildcard include/config/debug/devres.h) \
    $(wildcard include/config/devtmpfs.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/klist.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/pm.h \
    $(wildcard include/config/pm/runtime.h) \
    $(wildcard include/config/pm/ops.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/device.h \
    $(wildcard include/config/dmabounce.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/pm_wakeup.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/io.h \
    $(wildcard include/config/has/ioport.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/io.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/mach-sn986xx/include/mach/io.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/pci_ids.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/pci.h \
    $(wildcard include/config/pci/host/ite8152.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/asm-generic/pci-dma-compat.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/dma-mapping.h \
    $(wildcard include/config/has/dma.h) \
    $(wildcard include/config/have/dma/attrs.h) \
    $(wildcard include/config/need/dma/map/state.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/err.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/dma-attrs.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/bug.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/scatterlist.h \
    $(wildcard include/config/debug/sg.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/scatterlist.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/asm-generic/scatterlist.h \
    $(wildcard include/config/need/sg/dma/length.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/mm.h \
    $(wildcard include/config/sysctl.h) \
    $(wildcard include/config/stack/growsup.h) \
    $(wildcard include/config/ksm.h) \
    $(wildcard include/config/debug/pagealloc.h) \
    $(wildcard include/config/hibernation.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/prio_tree.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/debug_locks.h \
    $(wildcard include/config/debug/locking/api/selftests.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/mm_types.h \
    $(wildcard include/config/split/ptlock/cpus.h) \
    $(wildcard include/config/want/page/debug/flags.h) \
    $(wildcard include/config/aio.h) \
    $(wildcard include/config/mm/owner.h) \
    $(wildcard include/config/mmu/notifier.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/auxvec.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/auxvec.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/page-debug-flags.h \
    $(wildcard include/config/page/poisoning.h) \
    $(wildcard include/config/page/debug/something/else.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/mmu.h \
    $(wildcard include/config/cpu/has/asid.h) \
    $(wildcard include/config/arm/fcse/best/effort.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/range.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/pgtable.h \
    $(wildcard include/config/arm/fcse/guaranteed.h) \
    $(wildcard include/config/highpte.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/asm-generic/4level-fixup.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/proc-fns.h \
    $(wildcard include/config/cpu/arm7tdmi.h) \
    $(wildcard include/config/cpu/arm720t.h) \
    $(wildcard include/config/cpu/arm740t.h) \
    $(wildcard include/config/cpu/arm9tdmi.h) \
    $(wildcard include/config/cpu/arm920t.h) \
    $(wildcard include/config/cpu/arm922t.h) \
    $(wildcard include/config/cpu/arm925t.h) \
    $(wildcard include/config/cpu/arm926t.h) \
    $(wildcard include/config/cpu/arm940t.h) \
    $(wildcard include/config/cpu/arm946e.h) \
    $(wildcard include/config/cpu/arm1020.h) \
    $(wildcard include/config/cpu/arm1020e.h) \
    $(wildcard include/config/cpu/arm1022.h) \
    $(wildcard include/config/cpu/arm1026.h) \
    $(wildcard include/config/cpu/mohawk.h) \
    $(wildcard include/config/cpu/feroceon.h) \
    $(wildcard include/config/cpu/v6.h) \
    $(wildcard include/config/cpu/v7.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/cpu-single.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/mach-sn986xx/include/mach/vmalloc.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/pgtable-hwdef.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/fcse.h \
    $(wildcard include/config/arm/fcse/debug.h) \
    $(wildcard include/config/arm/fcse/dynpid.h) \
    $(wildcard include/config/arm/fcse/messages.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/sched.h \
    $(wildcard include/config/sched/debug.h) \
    $(wildcard include/config/detect/softlockup.h) \
    $(wildcard include/config/detect/hung/task.h) \
    $(wildcard include/config/core/dump/default/elf/headers.h) \
    $(wildcard include/config/bsd/process/acct.h) \
    $(wildcard include/config/taskstats.h) \
    $(wildcard include/config/audit.h) \
    $(wildcard include/config/inotify/user.h) \
    $(wildcard include/config/epoll.h) \
    $(wildcard include/config/posix/mqueue.h) \
    $(wildcard include/config/keys.h) \
    $(wildcard include/config/perf/events.h) \
    $(wildcard include/config/schedstats.h) \
    $(wildcard include/config/task/delay/acct.h) \
    $(wildcard include/config/fair/group/sched.h) \
    $(wildcard include/config/rt/group/sched.h) \
    $(wildcard include/config/blk/dev/io/trace.h) \
    $(wildcard include/config/cc/stackprotector.h) \
    $(wildcard include/config/sysvipc.h) \
    $(wildcard include/config/auditsyscall.h) \
    $(wildcard include/config/rt/mutexes.h) \
    $(wildcard include/config/task/xacct.h) \
    $(wildcard include/config/cpusets.h) \
    $(wildcard include/config/cgroups.h) \
    $(wildcard include/config/futex.h) \
    $(wildcard include/config/fault/injection.h) \
    $(wildcard include/config/latencytop.h) \
    $(wildcard include/config/function/graph/tracer.h) \
    $(wildcard include/config/have/unstable/sched/clock.h) \
    $(wildcard include/config/debug/stack/usage.h) \
    $(wildcard include/config/cgroup/sched.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/capability.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/cputime.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/asm-generic/cputime.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/sem.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/ipc.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/ipcbuf.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/sembuf.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/signal.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/signal.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/asm-generic/signal-defs.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/sigcontext.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/siginfo.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/asm-generic/siginfo.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/path.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/pid.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/proportions.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/percpu_counter.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/seccomp.h \
    $(wildcard include/config/seccomp.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/rculist.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/rtmutex.h \
    $(wildcard include/config/debug/rt/mutexes.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/plist.h \
    $(wildcard include/config/debug/pi/list.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/resource.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/resource.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/asm-generic/resource.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/task_io_accounting.h \
    $(wildcard include/config/task/io/accounting.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/latencytop.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/cred.h \
    $(wildcard include/config/debug/credentials.h) \
    $(wildcard include/config/security.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/key.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/sysctl.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/selinux.h \
    $(wildcard include/config/security/selinux.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/aio.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/aio_abi.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/uio.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/cachetype.h \
    $(wildcard include/config/cpu/cache/vivt.h) \
    $(wildcard include/config/cpu/cache/vipt.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/asm-generic/pgtable.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/page-flags.h \
    $(wildcard include/config/pageflags/extended.h) \
    $(wildcard include/config/arch/uses/pg/uncached.h) \
    $(wildcard include/config/memory/failure.h) \
    $(wildcard include/config/swap.h) \
    $(wildcard include/config/s390.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/vmstat.h \
    $(wildcard include/config/vm/event/counters.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/dma-mapping.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/asm-generic/dma-coherent.h \
    $(wildcard include/config/have/generic/dma/coherent.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/mach/pci.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/mach-sn986xx/include/mach/hardware.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/mach-sn986xx/include/mach/regs-irq.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/mach-sn986xx/include/mach/regs-mac.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/mach-sn986xx/include/mach/regs-serial.h \
    $(wildcard include/config/baudrate.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/mach-sn986xx/include/mach/regs-sys.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/mach-sn986xx/include/mach/regs-timer.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/mach-sn986xx/include/mach/regs-wtd.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/netdevice.h \
    $(wildcard include/config/dcb.h) \
    $(wildcard include/config/wlan.h) \
    $(wildcard include/config/ax25.h) \
    $(wildcard include/config/mac80211/mesh.h) \
    $(wildcard include/config/tr.h) \
    $(wildcard include/config/net/ipip.h) \
    $(wildcard include/config/net/ipgre.h) \
    $(wildcard include/config/ipv6/sit.h) \
    $(wildcard include/config/ipv6/tunnel.h) \
    $(wildcard include/config/netpoll.h) \
    $(wildcard include/config/rps.h) \
    $(wildcard include/config/net/poll/controller.h) \
    $(wildcard include/config/fcoe.h) \
    $(wildcard include/config/wireless/ext.h) \
    $(wildcard include/config/net/dsa.h) \
    $(wildcard include/config/net/ns.h) \
    $(wildcard include/config/net/dsa/tag/dsa.h) \
    $(wildcard include/config/net/dsa/tag/trailer.h) \
    $(wildcard include/config/netpoll/trap.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/if.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/socket.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/socket.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/sockios.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/sockios.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/hdlc/ioctl.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/if_ether.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/skbuff.h \
    $(wildcard include/config/nf/conntrack.h) \
    $(wildcard include/config/bridge/netfilter.h) \
    $(wildcard include/config/xfrm.h) \
    $(wildcard include/config/net/sched.h) \
    $(wildcard include/config/net/cls/act.h) \
    $(wildcard include/config/ipv6/ndisc/nodetype.h) \
    $(wildcard include/config/net/dma.h) \
    $(wildcard include/config/network/secmark.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/kmemcheck.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/net.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/random.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/ioctl.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/ioctl.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/asm-generic/ioctl.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/fcntl.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/fcntl.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/asm-generic/fcntl.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/ratelimit.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/textsearch.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/net/checksum.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/uaccess.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/unified.h \
    $(wildcard include/config/arm/asm/unified.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/checksum.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/in6.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/dmaengine.h \
    $(wildcard include/config/async/tx/disable/channel/switch.h) \
    $(wildcard include/config/dma/engine.h) \
    $(wildcard include/config/async/tx/dma.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/if_packet.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/if_link.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/netlink.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/pm_qos_params.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/miscdevice.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/major.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/delay.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/delay.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/ethtool.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/net/net_namespace.h \
    $(wildcard include/config/ipv6.h) \
    $(wildcard include/config/ip/dccp.h) \
    $(wildcard include/config/netfilter.h) \
    $(wildcard include/config/wext/core.h) \
    $(wildcard include/config/net.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/net/netns/core.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/net/netns/mib.h \
    $(wildcard include/config/xfrm/statistics.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/net/snmp.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/snmp.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/net/netns/unix.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/net/netns/packet.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/net/netns/ipv4.h \
    $(wildcard include/config/ip/multiple/tables.h) \
    $(wildcard include/config/ip/mroute.h) \
    $(wildcard include/config/ip/mroute/multiple/tables.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/net/inet_frag.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/net/netns/ipv6.h \
    $(wildcard include/config/ipv6/multiple/tables.h) \
    $(wildcard include/config/ipv6/mroute.h) \
    $(wildcard include/config/ipv6/mroute/multiple/tables.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/net/dst_ops.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/net/netns/dccp.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/net/netns/x_tables.h \
    $(wildcard include/config/bridge/nf/ebtables.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/netfilter.h \
    $(wildcard include/config/netfilter/debug.h) \
    $(wildcard include/config/nf/nat/needed.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/in.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/net/flow.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/proc_fs.h \
    $(wildcard include/config/proc/devicetree.h) \
    $(wildcard include/config/proc/kcore.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/fs.h \
    $(wildcard include/config/dnotify.h) \
    $(wildcard include/config/quota.h) \
    $(wildcard include/config/fsnotify.h) \
    $(wildcard include/config/inotify.h) \
    $(wildcard include/config/fs/posix/acl.h) \
    $(wildcard include/config/debug/writecount.h) \
    $(wildcard include/config/file/locking.h) \
    $(wildcard include/config/block.h) \
    $(wildcard include/config/fs/xip.h) \
    $(wildcard include/config/migration.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/limits.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/kdev_t.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/dcache.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/radix-tree.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/semaphore.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/fiemap.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/quota.h \
    $(wildcard include/config/quota/netlink/interface.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/dqblk_xfs.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/dqblk_v1.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/dqblk_v2.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/dqblk_qtree.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/nfs_fs_i.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/nfs.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/sunrpc/msg_prot.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/inet.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/magic.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/net/netns/xfrm.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/xfrm.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/seq_file_net.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/net/dsa.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/etherdevice.h \
    $(wildcard include/config/have/efficient/unaligned/access.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/unaligned.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/unaligned/le_byteshift.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/unaligned/be_byteshift.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/unaligned/generic.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/wireless.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/if_arp.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/ctype.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/vmalloc.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/usb.h \
    $(wildcard include/config/usb/devicefs.h) \
    $(wildcard include/config/usb/mon.h) \
    $(wildcard include/config/usb/device/class.h) \
    $(wildcard include/config/usb/suspend.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/usb/ch9.h \
    $(wildcard include/config/size.h) \
    $(wildcard include/config/att/one.h) \
    $(wildcard include/config/att/selfpower.h) \
    $(wildcard include/config/att/wakeup.h) \
    $(wildcard include/config/att/battery.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/net/iw_handler.h \
    $(wildcard include/config/wext/priv.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/unistd.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include/asm/unistd.h \
    $(wildcard include/config/oabi/compat.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/kthread.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/include/os/rt_linux_cmm.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/include/os/rt_os.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/include/link_list.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/include/rtmp_cmd.h \
    $(wildcard include/config/init.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/include/iface/iface_util.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/include/rtmp_def.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/include/oid.h \
    $(wildcard include/config/status.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/include/rtmp_chip.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/include/chip/rt3070.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/include/chip/mac_usb.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/include/rtmp_type.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/include/chip/rtmp_mac.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/include/chip/rtmp_phy.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/include/rtmp_iface.h \
    $(wildcard include/config/.h) \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/include/iface/rtmp_usb.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/include/rtusb_io.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/include/wpa_cmm.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/include/dot11i_wpa.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/include/rtmp_dot11.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/include/chip/rt30xx.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/include/chip/rt3370.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/include/chip/rt33xx.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/include/chip/rt5390.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/include/rtmp_timer.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/include/mlme.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/include/rtmp_dot11.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/include/crypt_md5.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/include/crypt_sha2.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/include/crypt_hmac.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/include/rt_config.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/include/crypt_aes.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/include/crypt_arc4.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/include/rtmp.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/include/spectrum_def.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/include/wsc.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/include/rt_led.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/include/frq_cal.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/include/ap.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/include/wpa.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/include/dfs.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/include/chlist.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/include/spectrum.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/include/rt_os_util.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/include/eeprom.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/include/rtmp_mcu.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/include/rt_os_net.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/include/chip/chip_id.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/include/rt_ate.h \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/include/sta_cfg.h \

/home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/os/linux/../../chips/rt33xx.o: $(deps_/home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/os/linux/../../chips/rt33xx.o)

$(deps_/home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/os/linux/../../chips/rt33xx.o):
