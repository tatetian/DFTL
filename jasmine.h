#ifndef	JASMINE_H
#define	JASMINE_H

/* ========================================================================= *
 * Size Constants 
 * ========================================================================= */
#define DRAM_BASE		0
#define	DRAM_SIZE		16384	// 16KB	
#define	NUM_BANKS_MAX		2	
#define NUM_BANKS		2

// every sector is 512 bytes
#define	BYTES_PER_SECTOR		512

// every page is 2KB
#define	SECTORS_PER_PAGE		4
#define BYTES_PER_PAGE			(BYTES_PER_SECTOR * SECTORS_PER_PAGE)

// every block is 8KB
#define PAGES_PER_VBLK			4
#define	SECTORS_PER_VBLK		(SECTORS_PER_PAGE * PAGES_PER_VBLK)
#define BYTES_PER_VBLK			(BYTES_PER_SECTOR * SECTORS_PER_VBLK)

// every bank is 32KB
#define VBLKS_PER_BANK			4
#define SECTORS_PER_BANK		(SECTORS_PER_VBLK * VBLKS_PER_BANK)
#define PAGES_PER_BANK			(PAGES_PER_VBLK   * VBLKS_PER_BANK)
#define BYTES_PER_BANK			(BYTES_PER_SECTOR * SECTORS_PER_BANK)

// 4 byte ECC parity is appended to the end of every 128 byte data
// The amount of DRAM space that you can use is reduced.
#define	DRAM_ECC_UNIT			128

#define NUM_VBLKS			(VBLKS_PER_BANK * NUM_BANKS)

#define NUM_PSECTORS			SECTORS_PER_BANK * NUM_BANKS
#define NUM_LSECTORS			(4 + NUM_PSECTORS * 7 / 8)
#define MAX_LBA				(NUM_LSECTORS - 1)



/* ========================================================================= *
 * Types 
 * ========================================================================= */

#ifdef TRUE
#undef TRUE
#endif

#ifdef FALSE
#undef FALSE
#endif

#ifdef NULL
#undef NULL
#endif

typedef	unsigned char		BOOL8;
typedef	unsigned short		BOOL16;
typedef	unsigned int		BOOL32;
typedef	unsigned char		UINT8;
typedef	unsigned short		UINT16;
typedef	unsigned int		UINT32;
typedef unsigned long long	UINT64;


#define	TRUE		1
#define	FALSE		0
#define	NULL		0
#define	OK			TRUE
#define	FAIL		FALSE
#define	INVALID8	((UINT8) -1)
#define	INVALID16	((UINT16) -1)
#define	INVALID32	((UINT32) -1)

/* scan list */
#define SCAN_LIST_SIZE				BYTES_PER_PAGE
#define SCAN_LIST_ITEMS				((SCAN_LIST_SIZE / sizeof(UINT16)) - 1)

typedef struct {
	UINT16	num_entries;
	UINT16	list[SCAN_LIST_ITEMS];
} scan_list_t;

/* ========================================================================= *
 * Macro helper functions 
 * ========================================================================= */

#define MIN(X, Y)				((X) > (Y) ? (Y) : (X))
#define MAX(X, Y)				((X) > (Y) ? (X) : (Y))

#define led(state)
#define led_blink()	exit(1)
#define disable_irq() 	
#define flash_clear_irq()

#define uart_print(message)	printf("%s\n", message);

#define REAL_BANK(bank)		(bank)
#endif
