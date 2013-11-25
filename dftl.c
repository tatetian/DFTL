#include "dftl.h"
#include "misc.h"


/* ========================================================================= *
 * Macros, Data Structure and Gloal Variables 
 * ========================================================================= */

#define COUNT_BUCKETS(TOTAL, BUCKET_SIZE) \
	( ((TOTAL) + (BUCKET_SIZE) - 1) / (BUCKET_SIZE) )

/* *
 * PMT = page-level mapping table
 *
 *   Let's do some simple math to calculate the number of entries in PMT.
 * For a 64GB flash with 16KB page, PMT_ENTRIES = 64GB / 16KB = 4 millions. 
 * For now, it is only 32.
 * */
#define PMT_ENTRIES		(PAGES_PER_BANK * NUM_BANKS)
#define PMT_ENTRIES_PER_PAGE	(BYTES_PER_PAGE / sizeof(UINT32))
#define PMT_PAGES		COUNT_BUCKETS(PMT_ENTRIES, PMT_ENTRIES_PER_PAGE)

/* *
 * GTD = global translation table
 *
 *   Let's do some simple math to calculate the number of entries in GTD.
 * For a 64GB flash with 16KB page, GTD_ENTRIES = (64GB / 16KB) / (16KB / 4
 * bytes) = 1024. In other words, the size of GTD is 4KB. 
 * */
#define GTD_ENTRIES		PMT_PAGES
#define GTD_SIZE		(GTD_ENTRIES * sizeof(UINT32))
#define GTD_ENTRIES_PER_PAGE	PMT_ENTRIES_PER_PAGE
#define GTD_PAGES		COUNT_BUCKETS(GTD_ENTRIES, GTD_ENTRIES_PER_PAGE)

UINT32 g_ftl_read_buf_id;
UINT32 g_ftl_write_buf_id;

UINT32 GTD[GTD_ENTRIES];	// global translation directory

/* ========================================================================= *
 * Private Function Declarations 
 * ========================================================================= */

void load_metadata();

/* ========================================================================= *
 * Public API 
 * ========================================================================= */

void ftl_open(void) {
	g_ftl_read_buf_id = g_ftl_write_buf_id = 0;

	load_metadata();
}

void ftl_read(UINT32 const lba, UINT32 const num_sectors) {

}

void ftl_write(UINT32 const lba, UINT32 const num_sectors) {

}

void ftl_test_write(UINT32 const lba, UINT32 const num_sectors) {

}

void ftl_flush(void) {

}

void ftl_isr(void) {

}

/* ========================================================================= *
 * Private Functions 
 * ========================================================================= */

void load_metadata() {

}
