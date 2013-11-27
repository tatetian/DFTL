#include <stdlib.h>
#include "cmt.h"
#include "misc.h"

int main(void)
{
	UINT32 res;
	UINT32 lpn, vpn, is_dirty;

	cmt_init();

	res = cmt_is_full();
	BUG_ON("is full", res);

	res = cmt_get(0, &vpn);
	BUG_ON("get successful", res == 0);

	res = cmt_add(0, 100);
	res += cmt_add(1, 1);
	BUG_ON("add failure", res != 0);

	res = cmt_is_full();
	BUG_ON("not full", res == 0);

	res = cmt_add(200, 400);
	res += cmt_add(3890123, 2);
	BUG_ON("less failure", res != 2);

	cmt_get(0, &vpn);
	BUG_ON("wrong vpn", vpn != 100);
	cmt_get(1, &vpn);
	BUG_ON("wrong vpn", vpn != 1);

	res = cmt_add(200, 400);
	res += cmt_add(3890123, 2);
	BUG_ON("any failure", res != 0);

	res = cmt_get(200, &vpn);
	BUG_ON("wrong vpn", vpn != 400);
	res = cmt_get(3890123, &vpn);
	BUG_ON("wrong vpn", vpn != 2);
	BUG_ON("get failure", res != 0);

	res = cmt_is_full();
	BUG_ON("not full", res == 0);

	res = cmt_evict(&lpn, &vpn, &is_dirty);
	BUG_ON("any error", res != 0);
	BUG_ON("lpn not 0", lpn != 0);
	BUG_ON("vpn not 100", vpn != 100);
	BUG_ON("dirty", is_dirty);

	cmt_add(201, 444);
	cmt_update(1, 2);

	res = cmt_evict(&lpn, &vpn, &is_dirty);
	BUG_ON("any error", res != 0);
	BUG_ON("lpn not 0", lpn != 1);
	BUG_ON("vpn not 100", vpn != 2);
	BUG_ON("not dirty", !is_dirty);
}
