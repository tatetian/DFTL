#ifndef __CMT_H
#define __CMT_H
#include "jasmine.h"

/* ========================================================================== 
 * CMT(Cached Mapping Table) Public API 
 * ========================================================================*/
void   cmt_init(void);

BOOL32 cmt_visit(UINT32 const lpn, UINT32* vpn);
BOOL32 cmt_add(UINT32 const lpn, UINT32 const vpn);
BOOL32 cmt_upate(UINT32 const lpn, UINT32 const new_vpn);
BOOL32 cmt_evict_entry(UINT32 *lpn, UINT32 *vpn, BOOL32 *is_dirty);

BOOL32 cmt_is_full();
#endif
