/*
 * Memory pools library, Public interface
 *
 * API Overview
 *
 * This package provides a memory allocation subsystem based on pools of
 * homogenous objects.
 *
 * Instrumentation is available for reporting memory utilization both
 * on a per-data-structure basis and system wide.
 *
 * There are two main types defined in this API.
 *
 *    pool manager: A singleton object that acts as a factory for
 *                  pool allocators. It also is used for global
 *                  instrumentation, such as reporting all blocks
 *                  in use across all data structures. The pool manager
 *                  creates and provides individual memory pools
 *                  upon request to application code.
 *
 *    memory pool:  An object for allocating homogenous memory blocks.
 *
 * Global identifiers in this module use the following prefixes:
 *    bcm_mpm_*     Memory pool manager
 *    bcm_mp_*      Memory pool
 *
 * There are two main types of memory pools:
 *
 *    prealloc: The contiguous memory block of objects can either be supplied
 *              by the client or malloc'ed by the memory manager. The objects are
 *              allocated out of a block of memory and freed back to the block.
 *
 *    heap:     The memory pool allocator uses the heap (malloc/free) for memory.
 *              In this case, the pool allocator is just providing statistics
 *              and instrumentation on top of the heap, without modifying the heap
 *              allocation implementation.
 *
 * Copyright (C) 2013, Broadcom Corporation. All Rights Reserved.
 * 
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * $Id$
 */

#ifndef _BCM_MPOOL_PUB_H
#define _BCM_MPOOL_PUB_H 1

#include <typedefs.h> 





struct osl_info;


struct bcmstrbuf;


struct bcm_mpm_mgr;
typedef struct bcm_mpm_mgr *bcm_mpm_mgr_h;


struct bcm_mp_pool;
typedef struct bcm_mp_pool *bcm_mp_pool_h;



#define BCM_MP_NAMELEN 8



typedef struct bcm_mp_stats {
	char name[BCM_MP_NAMELEN];  
	unsigned int objsz;         
	uint16 nobj;                
	uint16 num_alloc;           
	uint16 high_water;          
	uint16 failed_alloc;        
} bcm_mp_stats_t;





int bcm_mpm_init(struct osl_info *osh, int max_pools, bcm_mpm_mgr_h *mgrp);



int bcm_mpm_deinit(bcm_mpm_mgr_h *mgrp);


int bcm_mpm_create_prealloc_pool(bcm_mpm_mgr_h mgr,
                                 unsigned int obj_sz,
                                 int nobj,
                                 void *memstart,
                                 unsigned int memsize,
                                 char poolname[BCM_MP_NAMELEN],
                                 bcm_mp_pool_h *newp);



int bcm_mpm_delete_prealloc_pool(bcm_mpm_mgr_h mgr, bcm_mp_pool_h *poolp);


int bcm_mpm_create_heap_pool(bcm_mpm_mgr_h mgr, unsigned int obj_sz,
                             char poolname[BCM_MP_NAMELEN],
                             bcm_mp_pool_h *newp);



int bcm_mpm_delete_heap_pool(bcm_mpm_mgr_h mgr, bcm_mp_pool_h *poolp);



int bcm_mpm_stats(bcm_mpm_mgr_h mgr, bcm_mp_stats_t *stats, int *nentries);



int bcm_mpm_dump(bcm_mpm_mgr_h mgr, struct bcmstrbuf *b);



int bcm_mpm_get_obj_size(bcm_mpm_mgr_h mgr, unsigned int obj_sz, unsigned int *padded_obj_sz);






void* bcm_mp_alloc(bcm_mp_pool_h pool);


int bcm_mp_free(bcm_mp_pool_h pool, void *objp);


int bcm_mp_stats(bcm_mp_pool_h pool, bcm_mp_stats_t *stats);



int bcm_mp_dump(bcm_mp_pool_h pool, struct bcmstrbuf *b);


#endif 
