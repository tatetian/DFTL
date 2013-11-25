#include "dftl.h"
#include "misc.h"

#define FTL_READ 	0
#define FTL_WRITE 	1

typedef struct _ftl_operation{
	UINT32 lba;
	UINT32 num_sectors;
	UINT32 type;
} ftl_operation;

void run_ftl(ftl_operation operations[], int num) {
	int i = 0;
	while(i < num) {
		if (operations[i].type == FTL_READ)
			ftl_read(operations[i].lba, operations[i].num_sectors);
		else if (operations[i].type == FTL_WRITE)
			ftl_write(operations[i].lba, operations[i].num_sectors);
		else
			BUG_ON("Wrong type for FTL operation", 1);
		i++;	
	}
}

void basic_test() {
	const int NUM_OPRS = 3;
	ftl_operation operations[NUM_OPRS] = {
		{0, 1, FTL_READ},
		{0, 1, FTL_WRITE},
		{0, 1, FTL_READ}
	};
	run_ftl(operations, NUM_OPRS);
}

int main() {
	basic_test();

	return 0;
}
