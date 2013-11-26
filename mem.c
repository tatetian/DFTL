#include "mem.h"
#include "misc.h"

static UINT32 _memory[DRAM_SIZE/4];

void mem_set_dram(UINT32 addr, UINT32 const val, UINT32 num_bytes)
{
	BUG_ON("invalid address", addr >= DRAM_SIZE || addr & 3 != 0);
	BUG_ON("invalid num_bytes", num_bytes & 3 != 0);

	while(num_bytes) {
		_memory[addr/4] = val;
		addr += 4;
		num_bytes -= 4;
	}
}

