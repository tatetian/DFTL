#ifndef	__DFTL_H 
#define __DFTL_H

#include "jasmine.h"
#include "mem.h"

/* ========================================================================= *
 * DRAM Segmentation
 * ========================================================================= */

#define RD_BUF_ADDR		DRAM_BASE 
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
#define BAD_BLK_BMP_BYTES       (((NUM_VBLKS / 8) + DRAM_ECC_UNIT - 1) / DRAM_ECC_UNIT * DRAM_ECC_UNIT)

// page mapping table
#define PAGE_MAP_ADDR           (BAD_BLK_BMP_ADDR + BAD_BLK_BMP_BYTES)
#define PAGE_MAP_BYTES          ((NUM_LPAGES * sizeof(UINT32) + BYTES_PER_SECTOR - 1) / BYTES_PER_SECTOR * BYTES_PER_SECTOR)

#define VCOUNT_ADDR                     (PAGE_MAP_ADDR + PAGE_MAP_BYTES)
#define VCOUNT_BYTES            ((NUM_BANKS * VBLKS_PER_BANK * sizeof(UINT32) + BYTES_PER_SECTOR - 1) / BYTES_PER_SECTOR * BYTES_PER_SECTOR)

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
