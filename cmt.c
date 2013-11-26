#include "cmt.h"
#include "hash_table.h"

#define CMT_ENTRIES		4

/* CMT is implemented as a hash_table */
#define CMT_HT_CAPACITY		CMT_ENTRIES
#define CMT_HT_BUFFER_SIZE	CMT_ENTRIES * sizeof(cmt_node)
#define CMT_HT_LOAD_FACTOR	0.75
#define CMT_HT_NUM_BUCKETS 	((UINT32)(CMT_HT_CAPACITY / CMT_HT_LOAD_FACTOR))

typedef struct _cmt_node {
	hash_node hn;
	struct _cmt_node *next;
	UINT32	flag;
} cmt_node;

static UINT8  		_cmt_ht_buffer[CMT_HT_BUFFER_SIZE];
static hash_node* 	_cmt_ht_buckets[CMT_HT_NUM_BUCKETS];
static hash_table 	_cmt_ht;

/* the highest bit of value is used a dirty flag */
#define DIRTY_FLAG	( 1 << (sizeof(UINT32)-1) )

void cmt_init(void) 
{
	hash_table_init(&_cmt_ht, CMT_HT_CAPACITY, 
			sizeof(cmt_node), _cmt_ht_buffer, CMT_HT_BUFFER_SIZE,
			_cmt_ht_buckets, CMT_HT_NUM_BUCKETS);
}

BOOL32 cmt_get(UINT32 const lpn, UINT32 *vpn) 
{
	return hash_table_get(&_cmt_ht, lpn, vpn);
}

BOOL32 cmt_is_dirty(UINT32 const lpn)
{
	cmt_node* node = (cmt_node*) hash_table_get_node(&_cmt_ht, lpn);
	if (!node) return FALSE;
	return node->flag & DIRTY_FLAG;
}

BOOL32 cmt_is_full() 
{
	return hash_table_is_full(&_cmt_ht);
}

BOOL32 cmt_add(UINT32 const lpn, UINT32 const vpn)
{
	cmt_node* node;
	BOOL32 res = hash_table_insert(&_cmt_ht, lpn, vpn);

	if (res) return 1;

	node = (cmt_node*)(_cmt_ht.last_used_node);
	node->flag = 0;
	return 0;
}

BOOL32 cmt_upate(UINT32 const lpn, UINT32 const new_vpn)
{
	cmt_node* node;
	BOOL32 res = hash_table_update(&_cmt_ht, lpn, new_vpn);

	if (res) return 1;

	node = (cmt_node*)(_cmt_ht.last_used_node);
	node->flag &= DIRTY_FLAG;
	return 0;
}

BOOL32 cmt_remove(UINT32 const lpn)
{
	return hash_table_remove(&_cmt_ht, lpn);	
}
