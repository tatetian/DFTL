#include "dftl.h"
#include "misc.h"
#include "mem.h"
#include "cmt.h"

/* ========================================================================= *
 * Macros, Data Structure and Gloal Variables 
 * ========================================================================= */

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

UINT32 GTD[GTD_ENTRIES];	

UINT32 g_ftl_read_buf_id;
UINT32 g_ftl_write_buf_id;

typedef struct {

} ftl_metadata;

/* ========================================================================= *
 * Private Function Declarations 
 * ========================================================================= */

static void sanity_check(void);
static void build_bad_blk_list(void);
static void format(void);
static BOOL32 check_format_mark(void);
static void load_metadata();

/* ========================================================================= *
 * Private Functions 
 * ========================================================================= */

static void sanity_check(void)
{
	UINT32 dram_requirement = RD_BUF_BYTES + WR_BUF_BYTES + COPY_BUF_BYTES
		+ FTL_BUF_BYTES + HIL_BUF_BYTES + TEMP_BUF_BYTES 
		+ BAD_BLK_BMP_BYTES + VCOUNT_BYTES;

	BUG_ON("out of DRAM", dram_requirement > DRAM_SIZE ||
			      sizeof(ftl_metadata) > BYTES_PER_PAGE);
}

static void build_bad_blk_list(void)
{
/*  
	UINT32 bank, num_entries, result, vblk_offset;
	scan_list_t* scan_list = (scan_list_t*) TEMP_BUF_ADDR;
  
	mem_set_dram(BAD_BLK_BMP_ADDR, NULL, BAD_BLK_BMP_BYTES);

	disable_irq();

	flash_clear_irq();

	for (bank = 0; bank < NUM_BANKS; bank++)
	{
		SETREG(FCP_CMD, FC_COL_ROW_READ_OUT);
		SETREG(FCP_BANK, REAL_BANK(bank));
		SETREG(FCP_OPTION, FO_E);
		SETREG(FCP_DMA_ADDR, (UINT32) scan_list);
		SETREG(FCP_DMA_CNT, SCAN_LIST_SIZE);
		SETREG(FCP_COL, 0);
		SETREG(FCP_ROW_L(bank), SCAN_LIST_PAGE_OFFSET);
		SETREG(FCP_ROW_H(bank), SCAN_LIST_PAGE_OFFSET);

		SETREG(FCP_ISSUE, NULL);
		while ((GETREG(WR_STAT) & 0x00000001) != 0);
		while (BSP_FSM(bank) != BANK_IDLE);

		num_entries = NULL;
		result = OK;

		if (BSP_INTR(bank) & FIRQ_DATA_CORRUPT)
		{
			result = FAIL;
		}
		else
		{
			UINT32 i;

			num_entries = read_dram_16(&(scan_list->num_entries));

			if (num_entries > SCAN_LIST_ITEMS)
			{
				result = FAIL;
			}
			else
			{
				for (i = 0; i < num_entries; i++)
				{
					UINT16 entry = read_dram_16(scan_list->list + i);
					UINT16 pblk_offset = entry & 0x7FFF;

					if (pblk_offset == 0 || pblk_offset >= PBLKS_PER_BANK)
					{
						#if OPTION_REDUCED_CAPACITY == FALSE
						result = FAIL;
						#endif
					}
					else
					{
						write_dram_16(scan_list->list + i, pblk_offset);
					}
				}
			}
		}

		if (result == FAIL)
		{
			num_entries = 0;
		}
		else
		{
			write_dram_16(&(scan_list->num_entries), 0);
		}

		g_bad_blk_count[bank] = 0;

		for (vblk_offset = 1; vblk_offset < VBLKS_PER_BANK; vblk_offset++)
		{
			BOOL32 bad = FALSE;

			#if OPTION_2_PLANE
			{
				UINT32 pblk_offset;

				pblk_offset = vblk_offset * NUM_PLANES;

				if (mem_search_equ_dram(scan_list, sizeof(UINT16), num_entries, pblk_offset) < num_entries)
				{
					bad = TRUE;
				}

				pblk_offset = vblk_offset * NUM_PLANES + 1;

				if (mem_search_equ_dram(scan_list, sizeof(UINT16), num_entries, pblk_offset) < num_entries)
				{
					bad = TRUE;
				}
			}
			#else
			{
				if (mem_search_equ_dram(scan_list, sizeof(UINT16), num_entries, vblk_offset) < num_entries)
				{
					bad = TRUE;
				}
			}
			#endif

			if (bad)
			{
				g_bad_blk_count[bank]++;
				set_bit_dram(BAD_BLK_BMP_ADDR + bank*(VBLKS_PER_BANK/8 + 1), vblk_offset);
			}
		}
	}
*/
}

void format(void)
{

}

BOOL32 check_format_mark(void)
{
	return 1;
}

void load_metadata() {

}

/* ========================================================================= *
 * Public API 
 * ========================================================================= */

void ftl_open(void) {
	led(0);
    	sanity_check();
	build_bad_blk_list();
	
	/* if this is the first time after reloading firmware */
	if (check_format_mark() == FALSE)
		format();

        load_metadata();

	g_ftl_read_buf_id = g_ftl_write_buf_id = 0;

	// init CMT
	cmt_init();
}

static UINT32 load_PMT(UINT32 const lpn)
{
	//UINT32 pmt_page_index = lpn % PMT_ENTRIES_PER_PAGE;
	return 0;
}

static UINT32 save_PMT(UINT32 const lpn)
{
//	UINT32 pmt_page_index = lpn % PMT_ENTRIES_PER_PAGE;
	return 0;	
}

static UINT32 get_vpn(UINT32 const lpn)
{
	UINT32 vpn;
/*  
	if (cmt_get(lpn, &vpn)) {	// if lpn is not cached
		if (cmt_is_full()) {	// and cache is full
			victim_lpn = cmt_evict_entry();
			load_
			pmt_vpn = GTD[gtd_index];
			// if victim_lpn --> vpn is dirty, then write back	
		}

	}*/
	return vpn;
}

void ftl_read(UINT32 const lba, UINT32 const num_sectors) 
{
	/*  UINT32 remain_sects, num_sectors_to_read;
    	UINT32 lpn, sect_offset;
    	UINT32 bank, vpn;

    	lpn          = lba / SECTORS_PER_PAGE;
    	sect_offset  = lba % SECTORS_PER_PAGE;
    	remain_sects = num_sectors;

	while (remain_sects != 0)
	{
        	if ((sect_offset + remain_sects) < SECTORS_PER_PAGE)
            		num_sectors_to_read = remain_sects;
        	else
            		num_sectors_to_read = SECTORS_PER_PAGE - sect_offset;
		
		bank = get_num_bank(lpn); // page striping
		vpn  = get_vpn(lpn);

        if (vpn != NULL)
        {
            nand_page_ptread_to_host(bank,
                                     vpn / PAGES_PER_BLK,
                                     vpn % PAGES_PER_BLK,
                                     sect_offset,
                                     num_sectors_to_read);
        }
        // The host is requesting to read a logical page that has never been written to.
        else
        {
			UINT32 next_read_buf_id = (g_ftl_read_buf_id + 1) % NUM_RD_BUFFERS;

			mem_set_dram(RD_BUF_PTR(g_ftl_read_buf_id) + sect_offset*BYTES_PER_SECTOR,
                         0xFFFFFFFF, num_sectors_to_read*BYTES_PER_SECTOR);

			flash_finish();

			SETREG(BM_STACK_RDSET, next_read_buf_id);	// change bm_read_limit
			SETREG(BM_STACK_RESET, 0x02);				// change bm_read_limit

			g_ftl_read_buf_id = next_read_buf_id;
        }
        sect_offset   = 0;
        remain_sects -= num_sectors_to_read;
        lpn++;
    }
}
*/
}

void ftl_write(UINT32 const lba, UINT32 const num_sectors) {

}

void ftl_test_write(UINT32 const lba, UINT32 const num_sectors) {

}

void ftl_flush(void) {

}

void ftl_isr(void) {

}
