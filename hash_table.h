#ifndef _SHASHTBL_H
#define _SHASHTBL_H

#include "jasmine.h"

// hash node
typedef struct _hashnode {
    UINT32 key;
    UINT32 val;
    struct _hashnode* next;
} hashnode;

// static hash table
typedef struct _hash_table {
    	UINT32 size;
    	UINT32 capacity;
	hashnode** buckets;
	UINT32 num_buckets;
	hashnode* node_pool;
	UINT32 pool_size;
	hashnode* free_nodes;
} hash_table;

//////////////////////////
// hash table API
//////////////////////////
void	hash_table_init(hash_table*  ht,    UINT32 const capacity, 
		       hashnode** buckets,   UINT32 const num_buckets,
		       hashnode*  node_pool, UINT32 const pool_size);
BOOL32 	hash_table_get(hash_table* ht, UINT32 const key, UINT32 *val);
BOOL32 	hash_table_insert(hash_table* ht, UINT32 const key, UINT32 const val);
BOOL32 	hash_table_update(hash_table* ht, UINT32 const key, UINT32 const newval);
BOOL32 	hash_table_remove(hash_table* ht, UINT32 const key);

#define hash_table_is_full(ht) (ht->size == ht->capacity)

#endif // _SHASHTBL_H
