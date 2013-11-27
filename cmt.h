#ifndef __CMT_H
#define __CMT_H
#include "jasmine.h"

#define CMT_ENTRIES		4

/* ========================================================================== 
 * CMT(Cached Mapping Table) Public API 
 * ========================================================================*/
void   cmt_init(void);

BOOL32 cmt_get(UINT32 const lpn, UINT32* vpn);
BOOL32 cmt_add(UINT32 const lpn, UINT32 const vpn);
BOOL32 cmt_update(UINT32 const lpn, UINT32 const new_vpn);
BOOL32 cmt_evict(UINT32 *lpn, UINT32 *vpn, BOOL32 *is_dirty);

BOOL32 cmt_is_full();
#endif
