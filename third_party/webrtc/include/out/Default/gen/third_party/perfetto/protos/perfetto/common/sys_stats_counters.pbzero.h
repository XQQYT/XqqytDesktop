// Autogenerated by the ProtoZero compiler plugin. DO NOT EDIT.

#ifndef PERFETTO_PROTOS_PROTOS_PERFETTO_COMMON_SYS_STATS_COUNTERS_PROTO_H_
#define PERFETTO_PROTOS_PROTOS_PERFETTO_COMMON_SYS_STATS_COUNTERS_PROTO_H_

#include <stddef.h>
#include <stdint.h>

#include "perfetto/protozero/field_writer.h"
#include "perfetto/protozero/message.h"
#include "perfetto/protozero/packed_repeated_fields.h"
#include "perfetto/protozero/proto_decoder.h"
#include "perfetto/protozero/proto_utils.h"


namespace perfetto {
namespace protos {
namespace pbzero {

enum MeminfoCounters : int32_t {
  MEMINFO_UNSPECIFIED = 0,
  MEMINFO_MEM_TOTAL = 1,
  MEMINFO_MEM_FREE = 2,
  MEMINFO_MEM_AVAILABLE = 3,
  MEMINFO_BUFFERS = 4,
  MEMINFO_CACHED = 5,
  MEMINFO_SWAP_CACHED = 6,
  MEMINFO_ACTIVE = 7,
  MEMINFO_INACTIVE = 8,
  MEMINFO_ACTIVE_ANON = 9,
  MEMINFO_INACTIVE_ANON = 10,
  MEMINFO_ACTIVE_FILE = 11,
  MEMINFO_INACTIVE_FILE = 12,
  MEMINFO_UNEVICTABLE = 13,
  MEMINFO_MLOCKED = 14,
  MEMINFO_SWAP_TOTAL = 15,
  MEMINFO_SWAP_FREE = 16,
  MEMINFO_DIRTY = 17,
  MEMINFO_WRITEBACK = 18,
  MEMINFO_ANON_PAGES = 19,
  MEMINFO_MAPPED = 20,
  MEMINFO_SHMEM = 21,
  MEMINFO_SLAB = 22,
  MEMINFO_SLAB_RECLAIMABLE = 23,
  MEMINFO_SLAB_UNRECLAIMABLE = 24,
  MEMINFO_KERNEL_STACK = 25,
  MEMINFO_PAGE_TABLES = 26,
  MEMINFO_COMMIT_LIMIT = 27,
  MEMINFO_COMMITED_AS = 28,
  MEMINFO_VMALLOC_TOTAL = 29,
  MEMINFO_VMALLOC_USED = 30,
  MEMINFO_VMALLOC_CHUNK = 31,
  MEMINFO_CMA_TOTAL = 32,
  MEMINFO_CMA_FREE = 33,
  MEMINFO_GPU = 34,
  MEMINFO_ZRAM = 35,
  MEMINFO_MISC = 36,
  MEMINFO_ION_HEAP = 37,
  MEMINFO_ION_HEAP_POOL = 38,
};

constexpr MeminfoCounters MeminfoCounters_MIN = MeminfoCounters::MEMINFO_UNSPECIFIED;
constexpr MeminfoCounters MeminfoCounters_MAX = MeminfoCounters::MEMINFO_ION_HEAP_POOL;


PERFETTO_PROTOZERO_CONSTEXPR14_OR_INLINE
const char* MeminfoCounters_Name(::perfetto::protos::pbzero::MeminfoCounters value) {
  switch (value) {
  case ::perfetto::protos::pbzero::MeminfoCounters::MEMINFO_UNSPECIFIED:
    return "MEMINFO_UNSPECIFIED";

  case ::perfetto::protos::pbzero::MeminfoCounters::MEMINFO_MEM_TOTAL:
    return "MEMINFO_MEM_TOTAL";

  case ::perfetto::protos::pbzero::MeminfoCounters::MEMINFO_MEM_FREE:
    return "MEMINFO_MEM_FREE";

  case ::perfetto::protos::pbzero::MeminfoCounters::MEMINFO_MEM_AVAILABLE:
    return "MEMINFO_MEM_AVAILABLE";

  case ::perfetto::protos::pbzero::MeminfoCounters::MEMINFO_BUFFERS:
    return "MEMINFO_BUFFERS";

  case ::perfetto::protos::pbzero::MeminfoCounters::MEMINFO_CACHED:
    return "MEMINFO_CACHED";

  case ::perfetto::protos::pbzero::MeminfoCounters::MEMINFO_SWAP_CACHED:
    return "MEMINFO_SWAP_CACHED";

  case ::perfetto::protos::pbzero::MeminfoCounters::MEMINFO_ACTIVE:
    return "MEMINFO_ACTIVE";

  case ::perfetto::protos::pbzero::MeminfoCounters::MEMINFO_INACTIVE:
    return "MEMINFO_INACTIVE";

  case ::perfetto::protos::pbzero::MeminfoCounters::MEMINFO_ACTIVE_ANON:
    return "MEMINFO_ACTIVE_ANON";

  case ::perfetto::protos::pbzero::MeminfoCounters::MEMINFO_INACTIVE_ANON:
    return "MEMINFO_INACTIVE_ANON";

  case ::perfetto::protos::pbzero::MeminfoCounters::MEMINFO_ACTIVE_FILE:
    return "MEMINFO_ACTIVE_FILE";

  case ::perfetto::protos::pbzero::MeminfoCounters::MEMINFO_INACTIVE_FILE:
    return "MEMINFO_INACTIVE_FILE";

  case ::perfetto::protos::pbzero::MeminfoCounters::MEMINFO_UNEVICTABLE:
    return "MEMINFO_UNEVICTABLE";

  case ::perfetto::protos::pbzero::MeminfoCounters::MEMINFO_MLOCKED:
    return "MEMINFO_MLOCKED";

  case ::perfetto::protos::pbzero::MeminfoCounters::MEMINFO_SWAP_TOTAL:
    return "MEMINFO_SWAP_TOTAL";

  case ::perfetto::protos::pbzero::MeminfoCounters::MEMINFO_SWAP_FREE:
    return "MEMINFO_SWAP_FREE";

  case ::perfetto::protos::pbzero::MeminfoCounters::MEMINFO_DIRTY:
    return "MEMINFO_DIRTY";

  case ::perfetto::protos::pbzero::MeminfoCounters::MEMINFO_WRITEBACK:
    return "MEMINFO_WRITEBACK";

  case ::perfetto::protos::pbzero::MeminfoCounters::MEMINFO_ANON_PAGES:
    return "MEMINFO_ANON_PAGES";

  case ::perfetto::protos::pbzero::MeminfoCounters::MEMINFO_MAPPED:
    return "MEMINFO_MAPPED";

  case ::perfetto::protos::pbzero::MeminfoCounters::MEMINFO_SHMEM:
    return "MEMINFO_SHMEM";

  case ::perfetto::protos::pbzero::MeminfoCounters::MEMINFO_SLAB:
    return "MEMINFO_SLAB";

  case ::perfetto::protos::pbzero::MeminfoCounters::MEMINFO_SLAB_RECLAIMABLE:
    return "MEMINFO_SLAB_RECLAIMABLE";

  case ::perfetto::protos::pbzero::MeminfoCounters::MEMINFO_SLAB_UNRECLAIMABLE:
    return "MEMINFO_SLAB_UNRECLAIMABLE";

  case ::perfetto::protos::pbzero::MeminfoCounters::MEMINFO_KERNEL_STACK:
    return "MEMINFO_KERNEL_STACK";

  case ::perfetto::protos::pbzero::MeminfoCounters::MEMINFO_PAGE_TABLES:
    return "MEMINFO_PAGE_TABLES";

  case ::perfetto::protos::pbzero::MeminfoCounters::MEMINFO_COMMIT_LIMIT:
    return "MEMINFO_COMMIT_LIMIT";

  case ::perfetto::protos::pbzero::MeminfoCounters::MEMINFO_COMMITED_AS:
    return "MEMINFO_COMMITED_AS";

  case ::perfetto::protos::pbzero::MeminfoCounters::MEMINFO_VMALLOC_TOTAL:
    return "MEMINFO_VMALLOC_TOTAL";

  case ::perfetto::protos::pbzero::MeminfoCounters::MEMINFO_VMALLOC_USED:
    return "MEMINFO_VMALLOC_USED";

  case ::perfetto::protos::pbzero::MeminfoCounters::MEMINFO_VMALLOC_CHUNK:
    return "MEMINFO_VMALLOC_CHUNK";

  case ::perfetto::protos::pbzero::MeminfoCounters::MEMINFO_CMA_TOTAL:
    return "MEMINFO_CMA_TOTAL";

  case ::perfetto::protos::pbzero::MeminfoCounters::MEMINFO_CMA_FREE:
    return "MEMINFO_CMA_FREE";

  case ::perfetto::protos::pbzero::MeminfoCounters::MEMINFO_GPU:
    return "MEMINFO_GPU";

  case ::perfetto::protos::pbzero::MeminfoCounters::MEMINFO_ZRAM:
    return "MEMINFO_ZRAM";

  case ::perfetto::protos::pbzero::MeminfoCounters::MEMINFO_MISC:
    return "MEMINFO_MISC";

  case ::perfetto::protos::pbzero::MeminfoCounters::MEMINFO_ION_HEAP:
    return "MEMINFO_ION_HEAP";

  case ::perfetto::protos::pbzero::MeminfoCounters::MEMINFO_ION_HEAP_POOL:
    return "MEMINFO_ION_HEAP_POOL";
  }
  return "PBZERO_UNKNOWN_ENUM_VALUE";
}

enum VmstatCounters : int32_t {
  VMSTAT_UNSPECIFIED = 0,
  VMSTAT_NR_FREE_PAGES = 1,
  VMSTAT_NR_ALLOC_BATCH = 2,
  VMSTAT_NR_INACTIVE_ANON = 3,
  VMSTAT_NR_ACTIVE_ANON = 4,
  VMSTAT_NR_INACTIVE_FILE = 5,
  VMSTAT_NR_ACTIVE_FILE = 6,
  VMSTAT_NR_UNEVICTABLE = 7,
  VMSTAT_NR_MLOCK = 8,
  VMSTAT_NR_ANON_PAGES = 9,
  VMSTAT_NR_MAPPED = 10,
  VMSTAT_NR_FILE_PAGES = 11,
  VMSTAT_NR_DIRTY = 12,
  VMSTAT_NR_WRITEBACK = 13,
  VMSTAT_NR_SLAB_RECLAIMABLE = 14,
  VMSTAT_NR_SLAB_UNRECLAIMABLE = 15,
  VMSTAT_NR_PAGE_TABLE_PAGES = 16,
  VMSTAT_NR_KERNEL_STACK = 17,
  VMSTAT_NR_OVERHEAD = 18,
  VMSTAT_NR_UNSTABLE = 19,
  VMSTAT_NR_BOUNCE = 20,
  VMSTAT_NR_VMSCAN_WRITE = 21,
  VMSTAT_NR_VMSCAN_IMMEDIATE_RECLAIM = 22,
  VMSTAT_NR_WRITEBACK_TEMP = 23,
  VMSTAT_NR_ISOLATED_ANON = 24,
  VMSTAT_NR_ISOLATED_FILE = 25,
  VMSTAT_NR_SHMEM = 26,
  VMSTAT_NR_DIRTIED = 27,
  VMSTAT_NR_WRITTEN = 28,
  VMSTAT_NR_PAGES_SCANNED = 29,
  VMSTAT_WORKINGSET_REFAULT = 30,
  VMSTAT_WORKINGSET_ACTIVATE = 31,
  VMSTAT_WORKINGSET_NODERECLAIM = 32,
  VMSTAT_NR_ANON_TRANSPARENT_HUGEPAGES = 33,
  VMSTAT_NR_FREE_CMA = 34,
  VMSTAT_NR_SWAPCACHE = 35,
  VMSTAT_NR_DIRTY_THRESHOLD = 36,
  VMSTAT_NR_DIRTY_BACKGROUND_THRESHOLD = 37,
  VMSTAT_PGPGIN = 38,
  VMSTAT_PGPGOUT = 39,
  VMSTAT_PGPGOUTCLEAN = 40,
  VMSTAT_PSWPIN = 41,
  VMSTAT_PSWPOUT = 42,
  VMSTAT_PGALLOC_DMA = 43,
  VMSTAT_PGALLOC_NORMAL = 44,
  VMSTAT_PGALLOC_MOVABLE = 45,
  VMSTAT_PGFREE = 46,
  VMSTAT_PGACTIVATE = 47,
  VMSTAT_PGDEACTIVATE = 48,
  VMSTAT_PGFAULT = 49,
  VMSTAT_PGMAJFAULT = 50,
  VMSTAT_PGREFILL_DMA = 51,
  VMSTAT_PGREFILL_NORMAL = 52,
  VMSTAT_PGREFILL_MOVABLE = 53,
  VMSTAT_PGSTEAL_KSWAPD_DMA = 54,
  VMSTAT_PGSTEAL_KSWAPD_NORMAL = 55,
  VMSTAT_PGSTEAL_KSWAPD_MOVABLE = 56,
  VMSTAT_PGSTEAL_DIRECT_DMA = 57,
  VMSTAT_PGSTEAL_DIRECT_NORMAL = 58,
  VMSTAT_PGSTEAL_DIRECT_MOVABLE = 59,
  VMSTAT_PGSCAN_KSWAPD_DMA = 60,
  VMSTAT_PGSCAN_KSWAPD_NORMAL = 61,
  VMSTAT_PGSCAN_KSWAPD_MOVABLE = 62,
  VMSTAT_PGSCAN_DIRECT_DMA = 63,
  VMSTAT_PGSCAN_DIRECT_NORMAL = 64,
  VMSTAT_PGSCAN_DIRECT_MOVABLE = 65,
  VMSTAT_PGSCAN_DIRECT_THROTTLE = 66,
  VMSTAT_PGINODESTEAL = 67,
  VMSTAT_SLABS_SCANNED = 68,
  VMSTAT_KSWAPD_INODESTEAL = 69,
  VMSTAT_KSWAPD_LOW_WMARK_HIT_QUICKLY = 70,
  VMSTAT_KSWAPD_HIGH_WMARK_HIT_QUICKLY = 71,
  VMSTAT_PAGEOUTRUN = 72,
  VMSTAT_ALLOCSTALL = 73,
  VMSTAT_PGROTATED = 74,
  VMSTAT_DROP_PAGECACHE = 75,
  VMSTAT_DROP_SLAB = 76,
  VMSTAT_PGMIGRATE_SUCCESS = 77,
  VMSTAT_PGMIGRATE_FAIL = 78,
  VMSTAT_COMPACT_MIGRATE_SCANNED = 79,
  VMSTAT_COMPACT_FREE_SCANNED = 80,
  VMSTAT_COMPACT_ISOLATED = 81,
  VMSTAT_COMPACT_STALL = 82,
  VMSTAT_COMPACT_FAIL = 83,
  VMSTAT_COMPACT_SUCCESS = 84,
  VMSTAT_COMPACT_DAEMON_WAKE = 85,
  VMSTAT_UNEVICTABLE_PGS_CULLED = 86,
  VMSTAT_UNEVICTABLE_PGS_SCANNED = 87,
  VMSTAT_UNEVICTABLE_PGS_RESCUED = 88,
  VMSTAT_UNEVICTABLE_PGS_MLOCKED = 89,
  VMSTAT_UNEVICTABLE_PGS_MUNLOCKED = 90,
  VMSTAT_UNEVICTABLE_PGS_CLEARED = 91,
  VMSTAT_UNEVICTABLE_PGS_STRANDED = 92,
  VMSTAT_NR_ZSPAGES = 93,
  VMSTAT_NR_ION_HEAP = 94,
  VMSTAT_NR_GPU_HEAP = 95,
  VMSTAT_ALLOCSTALL_DMA = 96,
  VMSTAT_ALLOCSTALL_MOVABLE = 97,
  VMSTAT_ALLOCSTALL_NORMAL = 98,
  VMSTAT_COMPACT_DAEMON_FREE_SCANNED = 99,
  VMSTAT_COMPACT_DAEMON_MIGRATE_SCANNED = 100,
  VMSTAT_NR_FASTRPC = 101,
  VMSTAT_NR_INDIRECTLY_RECLAIMABLE = 102,
  VMSTAT_NR_ION_HEAP_POOL = 103,
  VMSTAT_NR_KERNEL_MISC_RECLAIMABLE = 104,
  VMSTAT_NR_SHADOW_CALL_STACK_BYTES = 105,
  VMSTAT_NR_SHMEM_HUGEPAGES = 106,
  VMSTAT_NR_SHMEM_PMDMAPPED = 107,
  VMSTAT_NR_UNRECLAIMABLE_PAGES = 108,
  VMSTAT_NR_ZONE_ACTIVE_ANON = 109,
  VMSTAT_NR_ZONE_ACTIVE_FILE = 110,
  VMSTAT_NR_ZONE_INACTIVE_ANON = 111,
  VMSTAT_NR_ZONE_INACTIVE_FILE = 112,
  VMSTAT_NR_ZONE_UNEVICTABLE = 113,
  VMSTAT_NR_ZONE_WRITE_PENDING = 114,
  VMSTAT_OOM_KILL = 115,
  VMSTAT_PGLAZYFREE = 116,
  VMSTAT_PGLAZYFREED = 117,
  VMSTAT_PGREFILL = 118,
  VMSTAT_PGSCAN_DIRECT = 119,
  VMSTAT_PGSCAN_KSWAPD = 120,
  VMSTAT_PGSKIP_DMA = 121,
  VMSTAT_PGSKIP_MOVABLE = 122,
  VMSTAT_PGSKIP_NORMAL = 123,
  VMSTAT_PGSTEAL_DIRECT = 124,
  VMSTAT_PGSTEAL_KSWAPD = 125,
  VMSTAT_SWAP_RA = 126,
  VMSTAT_SWAP_RA_HIT = 127,
  VMSTAT_WORKINGSET_RESTORE = 128,
  VMSTAT_ALLOCSTALL_DEVICE = 129,
  VMSTAT_ALLOCSTALL_DMA32 = 130,
  VMSTAT_BALLOON_DEFLATE = 131,
  VMSTAT_BALLOON_INFLATE = 132,
  VMSTAT_BALLOON_MIGRATE = 133,
  VMSTAT_CMA_ALLOC_FAIL = 134,
  VMSTAT_CMA_ALLOC_SUCCESS = 135,
  VMSTAT_NR_FILE_HUGEPAGES = 136,
  VMSTAT_NR_FILE_PMDMAPPED = 137,
  VMSTAT_NR_FOLL_PIN_ACQUIRED = 138,
  VMSTAT_NR_FOLL_PIN_RELEASED = 139,
  VMSTAT_NR_SEC_PAGE_TABLE_PAGES = 140,
  VMSTAT_NR_SHADOW_CALL_STACK = 141,
  VMSTAT_NR_SWAPCACHED = 142,
  VMSTAT_NR_THROTTLED_WRITTEN = 143,
  VMSTAT_PGALLOC_DEVICE = 144,
  VMSTAT_PGALLOC_DMA32 = 145,
  VMSTAT_PGDEMOTE_DIRECT = 146,
  VMSTAT_PGDEMOTE_KSWAPD = 147,
  VMSTAT_PGREUSE = 148,
  VMSTAT_PGSCAN_ANON = 149,
  VMSTAT_PGSCAN_FILE = 150,
  VMSTAT_PGSKIP_DEVICE = 151,
  VMSTAT_PGSKIP_DMA32 = 152,
  VMSTAT_PGSTEAL_ANON = 153,
  VMSTAT_PGSTEAL_FILE = 154,
  VMSTAT_THP_COLLAPSE_ALLOC = 155,
  VMSTAT_THP_COLLAPSE_ALLOC_FAILED = 156,
  VMSTAT_THP_DEFERRED_SPLIT_PAGE = 157,
  VMSTAT_THP_FAULT_ALLOC = 158,
  VMSTAT_THP_FAULT_FALLBACK = 159,
  VMSTAT_THP_FAULT_FALLBACK_CHARGE = 160,
  VMSTAT_THP_FILE_ALLOC = 161,
  VMSTAT_THP_FILE_FALLBACK = 162,
  VMSTAT_THP_FILE_FALLBACK_CHARGE = 163,
  VMSTAT_THP_FILE_MAPPED = 164,
  VMSTAT_THP_MIGRATION_FAIL = 165,
  VMSTAT_THP_MIGRATION_SPLIT = 166,
  VMSTAT_THP_MIGRATION_SUCCESS = 167,
  VMSTAT_THP_SCAN_EXCEED_NONE_PTE = 168,
  VMSTAT_THP_SCAN_EXCEED_SHARE_PTE = 169,
  VMSTAT_THP_SCAN_EXCEED_SWAP_PTE = 170,
  VMSTAT_THP_SPLIT_PAGE = 171,
  VMSTAT_THP_SPLIT_PAGE_FAILED = 172,
  VMSTAT_THP_SPLIT_PMD = 173,
  VMSTAT_THP_SWPOUT = 174,
  VMSTAT_THP_SWPOUT_FALLBACK = 175,
  VMSTAT_THP_ZERO_PAGE_ALLOC = 176,
  VMSTAT_THP_ZERO_PAGE_ALLOC_FAILED = 177,
  VMSTAT_VMA_LOCK_ABORT = 178,
  VMSTAT_VMA_LOCK_MISS = 179,
  VMSTAT_VMA_LOCK_RETRY = 180,
  VMSTAT_VMA_LOCK_SUCCESS = 181,
  VMSTAT_WORKINGSET_ACTIVATE_ANON = 182,
  VMSTAT_WORKINGSET_ACTIVATE_FILE = 183,
  VMSTAT_WORKINGSET_NODES = 184,
  VMSTAT_WORKINGSET_REFAULT_ANON = 185,
  VMSTAT_WORKINGSET_REFAULT_FILE = 186,
  VMSTAT_WORKINGSET_RESTORE_ANON = 187,
  VMSTAT_WORKINGSET_RESTORE_FILE = 188,
};

constexpr VmstatCounters VmstatCounters_MIN = VmstatCounters::VMSTAT_UNSPECIFIED;
constexpr VmstatCounters VmstatCounters_MAX = VmstatCounters::VMSTAT_WORKINGSET_RESTORE_FILE;


PERFETTO_PROTOZERO_CONSTEXPR14_OR_INLINE
const char* VmstatCounters_Name(::perfetto::protos::pbzero::VmstatCounters value) {
  switch (value) {
  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_UNSPECIFIED:
    return "VMSTAT_UNSPECIFIED";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_NR_FREE_PAGES:
    return "VMSTAT_NR_FREE_PAGES";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_NR_ALLOC_BATCH:
    return "VMSTAT_NR_ALLOC_BATCH";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_NR_INACTIVE_ANON:
    return "VMSTAT_NR_INACTIVE_ANON";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_NR_ACTIVE_ANON:
    return "VMSTAT_NR_ACTIVE_ANON";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_NR_INACTIVE_FILE:
    return "VMSTAT_NR_INACTIVE_FILE";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_NR_ACTIVE_FILE:
    return "VMSTAT_NR_ACTIVE_FILE";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_NR_UNEVICTABLE:
    return "VMSTAT_NR_UNEVICTABLE";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_NR_MLOCK:
    return "VMSTAT_NR_MLOCK";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_NR_ANON_PAGES:
    return "VMSTAT_NR_ANON_PAGES";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_NR_MAPPED:
    return "VMSTAT_NR_MAPPED";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_NR_FILE_PAGES:
    return "VMSTAT_NR_FILE_PAGES";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_NR_DIRTY:
    return "VMSTAT_NR_DIRTY";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_NR_WRITEBACK:
    return "VMSTAT_NR_WRITEBACK";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_NR_SLAB_RECLAIMABLE:
    return "VMSTAT_NR_SLAB_RECLAIMABLE";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_NR_SLAB_UNRECLAIMABLE:
    return "VMSTAT_NR_SLAB_UNRECLAIMABLE";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_NR_PAGE_TABLE_PAGES:
    return "VMSTAT_NR_PAGE_TABLE_PAGES";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_NR_KERNEL_STACK:
    return "VMSTAT_NR_KERNEL_STACK";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_NR_OVERHEAD:
    return "VMSTAT_NR_OVERHEAD";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_NR_UNSTABLE:
    return "VMSTAT_NR_UNSTABLE";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_NR_BOUNCE:
    return "VMSTAT_NR_BOUNCE";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_NR_VMSCAN_WRITE:
    return "VMSTAT_NR_VMSCAN_WRITE";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_NR_VMSCAN_IMMEDIATE_RECLAIM:
    return "VMSTAT_NR_VMSCAN_IMMEDIATE_RECLAIM";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_NR_WRITEBACK_TEMP:
    return "VMSTAT_NR_WRITEBACK_TEMP";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_NR_ISOLATED_ANON:
    return "VMSTAT_NR_ISOLATED_ANON";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_NR_ISOLATED_FILE:
    return "VMSTAT_NR_ISOLATED_FILE";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_NR_SHMEM:
    return "VMSTAT_NR_SHMEM";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_NR_DIRTIED:
    return "VMSTAT_NR_DIRTIED";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_NR_WRITTEN:
    return "VMSTAT_NR_WRITTEN";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_NR_PAGES_SCANNED:
    return "VMSTAT_NR_PAGES_SCANNED";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_WORKINGSET_REFAULT:
    return "VMSTAT_WORKINGSET_REFAULT";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_WORKINGSET_ACTIVATE:
    return "VMSTAT_WORKINGSET_ACTIVATE";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_WORKINGSET_NODERECLAIM:
    return "VMSTAT_WORKINGSET_NODERECLAIM";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_NR_ANON_TRANSPARENT_HUGEPAGES:
    return "VMSTAT_NR_ANON_TRANSPARENT_HUGEPAGES";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_NR_FREE_CMA:
    return "VMSTAT_NR_FREE_CMA";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_NR_SWAPCACHE:
    return "VMSTAT_NR_SWAPCACHE";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_NR_DIRTY_THRESHOLD:
    return "VMSTAT_NR_DIRTY_THRESHOLD";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_NR_DIRTY_BACKGROUND_THRESHOLD:
    return "VMSTAT_NR_DIRTY_BACKGROUND_THRESHOLD";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_PGPGIN:
    return "VMSTAT_PGPGIN";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_PGPGOUT:
    return "VMSTAT_PGPGOUT";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_PGPGOUTCLEAN:
    return "VMSTAT_PGPGOUTCLEAN";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_PSWPIN:
    return "VMSTAT_PSWPIN";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_PSWPOUT:
    return "VMSTAT_PSWPOUT";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_PGALLOC_DMA:
    return "VMSTAT_PGALLOC_DMA";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_PGALLOC_NORMAL:
    return "VMSTAT_PGALLOC_NORMAL";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_PGALLOC_MOVABLE:
    return "VMSTAT_PGALLOC_MOVABLE";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_PGFREE:
    return "VMSTAT_PGFREE";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_PGACTIVATE:
    return "VMSTAT_PGACTIVATE";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_PGDEACTIVATE:
    return "VMSTAT_PGDEACTIVATE";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_PGFAULT:
    return "VMSTAT_PGFAULT";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_PGMAJFAULT:
    return "VMSTAT_PGMAJFAULT";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_PGREFILL_DMA:
    return "VMSTAT_PGREFILL_DMA";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_PGREFILL_NORMAL:
    return "VMSTAT_PGREFILL_NORMAL";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_PGREFILL_MOVABLE:
    return "VMSTAT_PGREFILL_MOVABLE";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_PGSTEAL_KSWAPD_DMA:
    return "VMSTAT_PGSTEAL_KSWAPD_DMA";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_PGSTEAL_KSWAPD_NORMAL:
    return "VMSTAT_PGSTEAL_KSWAPD_NORMAL";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_PGSTEAL_KSWAPD_MOVABLE:
    return "VMSTAT_PGSTEAL_KSWAPD_MOVABLE";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_PGSTEAL_DIRECT_DMA:
    return "VMSTAT_PGSTEAL_DIRECT_DMA";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_PGSTEAL_DIRECT_NORMAL:
    return "VMSTAT_PGSTEAL_DIRECT_NORMAL";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_PGSTEAL_DIRECT_MOVABLE:
    return "VMSTAT_PGSTEAL_DIRECT_MOVABLE";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_PGSCAN_KSWAPD_DMA:
    return "VMSTAT_PGSCAN_KSWAPD_DMA";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_PGSCAN_KSWAPD_NORMAL:
    return "VMSTAT_PGSCAN_KSWAPD_NORMAL";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_PGSCAN_KSWAPD_MOVABLE:
    return "VMSTAT_PGSCAN_KSWAPD_MOVABLE";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_PGSCAN_DIRECT_DMA:
    return "VMSTAT_PGSCAN_DIRECT_DMA";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_PGSCAN_DIRECT_NORMAL:
    return "VMSTAT_PGSCAN_DIRECT_NORMAL";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_PGSCAN_DIRECT_MOVABLE:
    return "VMSTAT_PGSCAN_DIRECT_MOVABLE";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_PGSCAN_DIRECT_THROTTLE:
    return "VMSTAT_PGSCAN_DIRECT_THROTTLE";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_PGINODESTEAL:
    return "VMSTAT_PGINODESTEAL";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_SLABS_SCANNED:
    return "VMSTAT_SLABS_SCANNED";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_KSWAPD_INODESTEAL:
    return "VMSTAT_KSWAPD_INODESTEAL";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_KSWAPD_LOW_WMARK_HIT_QUICKLY:
    return "VMSTAT_KSWAPD_LOW_WMARK_HIT_QUICKLY";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_KSWAPD_HIGH_WMARK_HIT_QUICKLY:
    return "VMSTAT_KSWAPD_HIGH_WMARK_HIT_QUICKLY";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_PAGEOUTRUN:
    return "VMSTAT_PAGEOUTRUN";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_ALLOCSTALL:
    return "VMSTAT_ALLOCSTALL";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_PGROTATED:
    return "VMSTAT_PGROTATED";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_DROP_PAGECACHE:
    return "VMSTAT_DROP_PAGECACHE";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_DROP_SLAB:
    return "VMSTAT_DROP_SLAB";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_PGMIGRATE_SUCCESS:
    return "VMSTAT_PGMIGRATE_SUCCESS";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_PGMIGRATE_FAIL:
    return "VMSTAT_PGMIGRATE_FAIL";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_COMPACT_MIGRATE_SCANNED:
    return "VMSTAT_COMPACT_MIGRATE_SCANNED";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_COMPACT_FREE_SCANNED:
    return "VMSTAT_COMPACT_FREE_SCANNED";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_COMPACT_ISOLATED:
    return "VMSTAT_COMPACT_ISOLATED";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_COMPACT_STALL:
    return "VMSTAT_COMPACT_STALL";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_COMPACT_FAIL:
    return "VMSTAT_COMPACT_FAIL";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_COMPACT_SUCCESS:
    return "VMSTAT_COMPACT_SUCCESS";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_COMPACT_DAEMON_WAKE:
    return "VMSTAT_COMPACT_DAEMON_WAKE";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_UNEVICTABLE_PGS_CULLED:
    return "VMSTAT_UNEVICTABLE_PGS_CULLED";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_UNEVICTABLE_PGS_SCANNED:
    return "VMSTAT_UNEVICTABLE_PGS_SCANNED";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_UNEVICTABLE_PGS_RESCUED:
    return "VMSTAT_UNEVICTABLE_PGS_RESCUED";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_UNEVICTABLE_PGS_MLOCKED:
    return "VMSTAT_UNEVICTABLE_PGS_MLOCKED";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_UNEVICTABLE_PGS_MUNLOCKED:
    return "VMSTAT_UNEVICTABLE_PGS_MUNLOCKED";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_UNEVICTABLE_PGS_CLEARED:
    return "VMSTAT_UNEVICTABLE_PGS_CLEARED";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_UNEVICTABLE_PGS_STRANDED:
    return "VMSTAT_UNEVICTABLE_PGS_STRANDED";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_NR_ZSPAGES:
    return "VMSTAT_NR_ZSPAGES";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_NR_ION_HEAP:
    return "VMSTAT_NR_ION_HEAP";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_NR_GPU_HEAP:
    return "VMSTAT_NR_GPU_HEAP";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_ALLOCSTALL_DMA:
    return "VMSTAT_ALLOCSTALL_DMA";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_ALLOCSTALL_MOVABLE:
    return "VMSTAT_ALLOCSTALL_MOVABLE";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_ALLOCSTALL_NORMAL:
    return "VMSTAT_ALLOCSTALL_NORMAL";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_COMPACT_DAEMON_FREE_SCANNED:
    return "VMSTAT_COMPACT_DAEMON_FREE_SCANNED";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_COMPACT_DAEMON_MIGRATE_SCANNED:
    return "VMSTAT_COMPACT_DAEMON_MIGRATE_SCANNED";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_NR_FASTRPC:
    return "VMSTAT_NR_FASTRPC";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_NR_INDIRECTLY_RECLAIMABLE:
    return "VMSTAT_NR_INDIRECTLY_RECLAIMABLE";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_NR_ION_HEAP_POOL:
    return "VMSTAT_NR_ION_HEAP_POOL";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_NR_KERNEL_MISC_RECLAIMABLE:
    return "VMSTAT_NR_KERNEL_MISC_RECLAIMABLE";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_NR_SHADOW_CALL_STACK_BYTES:
    return "VMSTAT_NR_SHADOW_CALL_STACK_BYTES";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_NR_SHMEM_HUGEPAGES:
    return "VMSTAT_NR_SHMEM_HUGEPAGES";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_NR_SHMEM_PMDMAPPED:
    return "VMSTAT_NR_SHMEM_PMDMAPPED";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_NR_UNRECLAIMABLE_PAGES:
    return "VMSTAT_NR_UNRECLAIMABLE_PAGES";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_NR_ZONE_ACTIVE_ANON:
    return "VMSTAT_NR_ZONE_ACTIVE_ANON";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_NR_ZONE_ACTIVE_FILE:
    return "VMSTAT_NR_ZONE_ACTIVE_FILE";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_NR_ZONE_INACTIVE_ANON:
    return "VMSTAT_NR_ZONE_INACTIVE_ANON";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_NR_ZONE_INACTIVE_FILE:
    return "VMSTAT_NR_ZONE_INACTIVE_FILE";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_NR_ZONE_UNEVICTABLE:
    return "VMSTAT_NR_ZONE_UNEVICTABLE";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_NR_ZONE_WRITE_PENDING:
    return "VMSTAT_NR_ZONE_WRITE_PENDING";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_OOM_KILL:
    return "VMSTAT_OOM_KILL";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_PGLAZYFREE:
    return "VMSTAT_PGLAZYFREE";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_PGLAZYFREED:
    return "VMSTAT_PGLAZYFREED";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_PGREFILL:
    return "VMSTAT_PGREFILL";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_PGSCAN_DIRECT:
    return "VMSTAT_PGSCAN_DIRECT";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_PGSCAN_KSWAPD:
    return "VMSTAT_PGSCAN_KSWAPD";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_PGSKIP_DMA:
    return "VMSTAT_PGSKIP_DMA";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_PGSKIP_MOVABLE:
    return "VMSTAT_PGSKIP_MOVABLE";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_PGSKIP_NORMAL:
    return "VMSTAT_PGSKIP_NORMAL";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_PGSTEAL_DIRECT:
    return "VMSTAT_PGSTEAL_DIRECT";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_PGSTEAL_KSWAPD:
    return "VMSTAT_PGSTEAL_KSWAPD";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_SWAP_RA:
    return "VMSTAT_SWAP_RA";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_SWAP_RA_HIT:
    return "VMSTAT_SWAP_RA_HIT";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_WORKINGSET_RESTORE:
    return "VMSTAT_WORKINGSET_RESTORE";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_ALLOCSTALL_DEVICE:
    return "VMSTAT_ALLOCSTALL_DEVICE";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_ALLOCSTALL_DMA32:
    return "VMSTAT_ALLOCSTALL_DMA32";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_BALLOON_DEFLATE:
    return "VMSTAT_BALLOON_DEFLATE";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_BALLOON_INFLATE:
    return "VMSTAT_BALLOON_INFLATE";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_BALLOON_MIGRATE:
    return "VMSTAT_BALLOON_MIGRATE";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_CMA_ALLOC_FAIL:
    return "VMSTAT_CMA_ALLOC_FAIL";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_CMA_ALLOC_SUCCESS:
    return "VMSTAT_CMA_ALLOC_SUCCESS";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_NR_FILE_HUGEPAGES:
    return "VMSTAT_NR_FILE_HUGEPAGES";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_NR_FILE_PMDMAPPED:
    return "VMSTAT_NR_FILE_PMDMAPPED";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_NR_FOLL_PIN_ACQUIRED:
    return "VMSTAT_NR_FOLL_PIN_ACQUIRED";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_NR_FOLL_PIN_RELEASED:
    return "VMSTAT_NR_FOLL_PIN_RELEASED";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_NR_SEC_PAGE_TABLE_PAGES:
    return "VMSTAT_NR_SEC_PAGE_TABLE_PAGES";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_NR_SHADOW_CALL_STACK:
    return "VMSTAT_NR_SHADOW_CALL_STACK";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_NR_SWAPCACHED:
    return "VMSTAT_NR_SWAPCACHED";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_NR_THROTTLED_WRITTEN:
    return "VMSTAT_NR_THROTTLED_WRITTEN";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_PGALLOC_DEVICE:
    return "VMSTAT_PGALLOC_DEVICE";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_PGALLOC_DMA32:
    return "VMSTAT_PGALLOC_DMA32";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_PGDEMOTE_DIRECT:
    return "VMSTAT_PGDEMOTE_DIRECT";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_PGDEMOTE_KSWAPD:
    return "VMSTAT_PGDEMOTE_KSWAPD";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_PGREUSE:
    return "VMSTAT_PGREUSE";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_PGSCAN_ANON:
    return "VMSTAT_PGSCAN_ANON";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_PGSCAN_FILE:
    return "VMSTAT_PGSCAN_FILE";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_PGSKIP_DEVICE:
    return "VMSTAT_PGSKIP_DEVICE";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_PGSKIP_DMA32:
    return "VMSTAT_PGSKIP_DMA32";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_PGSTEAL_ANON:
    return "VMSTAT_PGSTEAL_ANON";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_PGSTEAL_FILE:
    return "VMSTAT_PGSTEAL_FILE";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_THP_COLLAPSE_ALLOC:
    return "VMSTAT_THP_COLLAPSE_ALLOC";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_THP_COLLAPSE_ALLOC_FAILED:
    return "VMSTAT_THP_COLLAPSE_ALLOC_FAILED";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_THP_DEFERRED_SPLIT_PAGE:
    return "VMSTAT_THP_DEFERRED_SPLIT_PAGE";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_THP_FAULT_ALLOC:
    return "VMSTAT_THP_FAULT_ALLOC";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_THP_FAULT_FALLBACK:
    return "VMSTAT_THP_FAULT_FALLBACK";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_THP_FAULT_FALLBACK_CHARGE:
    return "VMSTAT_THP_FAULT_FALLBACK_CHARGE";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_THP_FILE_ALLOC:
    return "VMSTAT_THP_FILE_ALLOC";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_THP_FILE_FALLBACK:
    return "VMSTAT_THP_FILE_FALLBACK";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_THP_FILE_FALLBACK_CHARGE:
    return "VMSTAT_THP_FILE_FALLBACK_CHARGE";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_THP_FILE_MAPPED:
    return "VMSTAT_THP_FILE_MAPPED";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_THP_MIGRATION_FAIL:
    return "VMSTAT_THP_MIGRATION_FAIL";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_THP_MIGRATION_SPLIT:
    return "VMSTAT_THP_MIGRATION_SPLIT";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_THP_MIGRATION_SUCCESS:
    return "VMSTAT_THP_MIGRATION_SUCCESS";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_THP_SCAN_EXCEED_NONE_PTE:
    return "VMSTAT_THP_SCAN_EXCEED_NONE_PTE";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_THP_SCAN_EXCEED_SHARE_PTE:
    return "VMSTAT_THP_SCAN_EXCEED_SHARE_PTE";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_THP_SCAN_EXCEED_SWAP_PTE:
    return "VMSTAT_THP_SCAN_EXCEED_SWAP_PTE";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_THP_SPLIT_PAGE:
    return "VMSTAT_THP_SPLIT_PAGE";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_THP_SPLIT_PAGE_FAILED:
    return "VMSTAT_THP_SPLIT_PAGE_FAILED";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_THP_SPLIT_PMD:
    return "VMSTAT_THP_SPLIT_PMD";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_THP_SWPOUT:
    return "VMSTAT_THP_SWPOUT";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_THP_SWPOUT_FALLBACK:
    return "VMSTAT_THP_SWPOUT_FALLBACK";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_THP_ZERO_PAGE_ALLOC:
    return "VMSTAT_THP_ZERO_PAGE_ALLOC";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_THP_ZERO_PAGE_ALLOC_FAILED:
    return "VMSTAT_THP_ZERO_PAGE_ALLOC_FAILED";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_VMA_LOCK_ABORT:
    return "VMSTAT_VMA_LOCK_ABORT";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_VMA_LOCK_MISS:
    return "VMSTAT_VMA_LOCK_MISS";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_VMA_LOCK_RETRY:
    return "VMSTAT_VMA_LOCK_RETRY";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_VMA_LOCK_SUCCESS:
    return "VMSTAT_VMA_LOCK_SUCCESS";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_WORKINGSET_ACTIVATE_ANON:
    return "VMSTAT_WORKINGSET_ACTIVATE_ANON";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_WORKINGSET_ACTIVATE_FILE:
    return "VMSTAT_WORKINGSET_ACTIVATE_FILE";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_WORKINGSET_NODES:
    return "VMSTAT_WORKINGSET_NODES";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_WORKINGSET_REFAULT_ANON:
    return "VMSTAT_WORKINGSET_REFAULT_ANON";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_WORKINGSET_REFAULT_FILE:
    return "VMSTAT_WORKINGSET_REFAULT_FILE";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_WORKINGSET_RESTORE_ANON:
    return "VMSTAT_WORKINGSET_RESTORE_ANON";

  case ::perfetto::protos::pbzero::VmstatCounters::VMSTAT_WORKINGSET_RESTORE_FILE:
    return "VMSTAT_WORKINGSET_RESTORE_FILE";
  }
  return "PBZERO_UNKNOWN_ENUM_VALUE";
}

} // Namespace.
} // Namespace.
} // Namespace.
#endif  // Include guard.
