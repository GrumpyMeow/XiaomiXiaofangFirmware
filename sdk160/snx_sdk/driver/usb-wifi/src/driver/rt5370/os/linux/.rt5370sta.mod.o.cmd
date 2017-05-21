cmd_/home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/os/linux/rt5370sta.mod.o := arm-linux-gcc -Wp,-MD,/home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/os/linux/.rt5370sta.mod.o.d  -nostdinc -isystem /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/toolchain/crosstool-4.5.2/bin/../lib/gcc/arm-unknown-linux-uclibcgnueabi/4.5.2/include -I/home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/include -Iinclude  -I/home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include -include include/generated/autoconf.h -I/home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/buildscript/include   -I/home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/os/linux -D__KERNEL__ -mlittle-endian   -I/home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/arch/arm/mach-sn986xx/include -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -Os -marm -mabi=aapcs-linux -mno-thumb-interwork -funwind-tables -D__LINUX_ARM_ARCH__=5 -march=armv5te -mtune=arm926ej-s -msoft-float -Uarm -Wframe-larger-than=1024 -fno-stack-protector -fomit-frame-pointer -g -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack -DAGGREGATION_SUPPORT -DPIGGYBACK_SUPPORT -DWMM_SUPPORT -DLINUX -Wall -Wstrict-prototypes -Wno-trigraphs -DSYSTEM_LOG_SUPPORT -DRT28xx_MODE=STA -DCHIPSET=5370 -DRESOURCE_PRE_ALLOC -DCONFIG_STA_SUPPORT -DDBG -DWPA_SUPPLICANT_SUPPORT -DNATIVE_WPA_SUPPLICANT_SUPPORT -DRALINK_ATE -DCONFIG_RT2880_ATE_CMD_NEW -DRALINK_QA -DDOT11_N_SUPPORT -DLED_CONTROL_SUPPORT -DRTMP_MAC_USB -DRT30xx -DRT33xx -DRT3070 -DRT3370 -DRT5370 -DRTMP_USB_SUPPORT -DRTMP_TIMER_TASK_SUPPORT -DRTMP_RF_RW_SUPPORT -DRTMP_EFUSE_SUPPORT -DRTMP_INTERNAL_TX_ALC -DhSPECIFIC_BCN_BUF_SUPPORT -DRTMP_FREQ_CALIBRATION_SUPPORT -DSPECIFIC_VCORECAL_SUPPORT -DCONFIG_5VT_ENHANCE -O2   -I/home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/include  -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(rt5370sta.mod)"  -D"KBUILD_MODNAME=KBUILD_STR(rt5370sta)"  -DMODULE -c -o /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/os/linux/rt5370sta.mod.o /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/os/linux/rt5370sta.mod.c

deps_/home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/os/linux/rt5370sta.mod.o := \
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/os/linux/rt5370sta.mod.c \
    $(wildcard include/config/module/unload.h) \
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
  /home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/kernel/linux-2.6.35.12/src/include/linux/vermagic.h \
  include/generated/utsrelease.h \

/home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/os/linux/rt5370sta.mod.o: $(deps_/home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/os/linux/rt5370sta.mod.o)

$(deps_/home/dev/SN986_1.50_037a_20151022_1049/snx_sdk/driver/usb-wifi/src/driver/rt5370/os/linux/rt5370sta.mod.o):
