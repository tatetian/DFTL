#ifndef __CMT_H
#define __CMT_H
#include "jasmine.h"

/* ========================================================================== 
 * CMT(Cached Mapping Table) Public API 
 * ========================================================================*/
void   cmt_init(void);

BOOL32 cmt_get(UINT32 const lpn, UINT32* vpn);
BOOL32 cmt_is_dirty(UINT32 const lpn);
BOOL32 cmt_is_full();

BOOL32 cmt_add(UINT32 const lpn, UINT32 const vpn);
BOOL32 cmt_upate(UINT32 const lpn, UINT32 const new_vpn);
BOOL32 cmt_remove(UINT32 const lpn);

#endif
