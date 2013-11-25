#ifndef __MISC_H
#define __MISC_H

#include <stdio.h>
#include <stdlib.h>

#define BUG_ON(MESSAGE, COND) do {\
	if (COND) {\
		printf(MESSAGE);\
		exit(1);\
	}\
} while(0);

#endif
