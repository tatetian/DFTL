#ifndef __CACHE_H
#define __CACHE_H

#include "jasmine.h"

#define CACHE_ADDR		DRAM_BASE 
#define NUM_CACHE_BUFFERS	32
#define CACHE_BYTES		NUM_CACHE_BUFFERS * BYTES_PER_PAGE 

void cache_get(UINT32 const bank, UINT32 const vpn)


#endif
