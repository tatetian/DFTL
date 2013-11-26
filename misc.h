#ifndef __MISC_H
#define __MISC_H

#include <stdio.h>
#include <stdlib.h>
#include "jasmine.h"

#define BUG_ON(MESSAGE, COND) do {\
	if (COND) {\
		printf(MESSAGE);\
		led_blink();\
		while(1);\
	}\
} while(0);

#endif
