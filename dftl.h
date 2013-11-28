#ifndef	__DFTL_H 
#define __DFTL_H

#include "jasmine.h"
#include "mem.h"
#include "cache.h"

#define COUNT_BUCKETS(TOTAL, BUCKET_SIZE) \
	( ((TOTAL) + (BUCKET_SIZE) - 1) / (BUCKET_SIZE) )

/* ========================================================================= *
 * DRAM Segmentation
 * ========================================================================= */
#define NUM_COPY_BUFFERS	NUM_BANKS_MAX
#define NUM_FTL_BUFFERS		NUM_BANKS
#define NUM_HIL_BUFFERS		1
#define NUM_TEMP_BUFFERS	1

#define DRAM_BYTES_OTHER	((NUM_COPY_BUFFERS + NUM_FTL_BUFFERS + NUM_HIL_BUFFERS + NUM_TEMP_BUFFERS) * BYTES_PER_PAGE \
+ CACHE_BYTES + BAD_BLK_BMP_BYTES + VCOUNT_BYTES)

#define NUM_RW_BUFFERS		((DRAM_SIZE - DRAM_BYTES_OTHER) / BYTES_PER_PAGE - 1)
#define NUM_RD_BUFFERS		(((NUM_RW_BUFFERS / 8) + NUM_BANKS - 1) / NUM_BANKS * NUM_BANKS)
#define NUM_WR_BUFFERS		(NUM_RW_BUFFERS - NUM_RD_BUFFERS)

#define RD_BUF_ADDR		(CACHE_ADDR + CACHE_BYTES)	
#define RD_BUF_BYTES            (NUM_RD_BUFFERS * BYTES_PER_PAGE)

#define WR_BUF_ADDR             (RD_BUF_ADDR + RD_BUF_BYTES)
#define WR_BUF_BYTES            (NUM_WR_BUFFERS * BYTES_PER_PAGE)

#define COPY_BUF_ADDR           (WR_BUF_ADDR + WR_BUF_BYTES)
#define COPY_BUF_BYTES          (NUM_COPY_BUFFERS * BYTES_PER_PAGE)

#define FTL_BUF_ADDR            (COPY_BUF_ADDR + COPY_BUF_BYTES)
#define FTL_BUF_BYTES           (NUM_FTL_BUFFERS * BYTES_PER_PAGE)

#define HIL_BUF_ADDR            (FTL_BUF_ADDR + FTL_BUF_BYTES)
#define HIL_BUF_BYTES           (NUM_HIL_BUFFERS * BYTES_PER_PAGE)

#define TEMP_BUF_ADDR           (HIL_BUF_ADDR + HIL_BUF_BYTES)
#define TEMP_BUF_BYTES          (NUM_TEMP_BUFFERS * BYTES_PER_PAGE)

// bitmap of initial bad blocks
#define BAD_BLK_BMP_ADDR        (TEMP_BUF_ADDR + TEMP_BUF_BYTES)
#define BAD_BLK_BMP_BYTES	(COUNT_BUCKETS(NUM_VBLKS / 8, DRAM_ECC_UNIT) * DRAM_ECC_UNIT)

#define VCOUNT_ADDR             (BAD_BLK_BMP_ADDR + BAD_BLK_BMP_BYTES)
#define VCOUNT_BYTES            (COUNT_BUCKETS(NUM_VBLKS, BYTES_PER_SECTOR) * BYTES_PER_SECTOR)

#define _COPY_BUF(RBANK)	(COPY_BUF_ADDR + (RBANK) * BYTES_PER_PAGE)
#define COPY_BUF(BANK)		_COPY_BUF(REAL_BANK(BANK))
#define FTL_BUF(BANK)       (FTL_BUF_ADDR + ((BANK) * BYTES_PER_PAGE))

/* ========================================================================= *
 * Public API 
 * ========================================================================= */

void ftl_open(void);
void ftl_read(UINT32 const lba, UINT32 const num_sectors);
void ftl_write(UINT32 const lba, UINT32 const num_sectors);
void ftl_test_write(UINT32 const lba, UINT32 const num_sectors);
void ftl_flush(void);
void ftl_isr(void);

#endif
