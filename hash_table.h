#ifndef _SHASHTBL_H
#define _SHASHTBL_H

#include "jasmine.h"

// hash node
typedef struct _hash_node{
    UINT32 key;
    UINT32 val;
    struct _hash_node* next;
} hash_node;

// static hash table
typedef struct {
    	UINT32 		size;
    	UINT32 		capacity;
	hash_node** 	buckets;	/* pre-allocated memory for buckets */
	UINT32 		num_buckets;
	hash_node* 	last_used_node;	/* for fast re-access */
	/* memory management related fields */
	UINT8  		node_size;	/* in bytes */
	UINT8* 		node_buffer;	/* used to allocate memory for hash nodes */
	UINT32 		buffer_size;	/* in bytes */
	hash_node* 	free_nodes;
} hash_table;

//////////////////////////
// hash table API
//////////////////////////
void	hash_table_init(hash_table*  ht,    UINT32 const capacity, 
		       UINT8 node_size, /* user may choose to use custom data 
					   structure that includes hash_node */
		       UINT8*  node_buffer,   UINT32 const buffer_size,
		       hash_node** buckets,   UINT32 const num_buckets);
BOOL32 	hash_table_get(hash_table* ht, UINT32 const key, UINT32 *val);
hash_node* hash_table_get_node(hash_table* ht, UINT32 const key);
BOOL32 	hash_table_insert(hash_table* ht, UINT32 const key, UINT32 const val);
BOOL32 	hash_table_update(hash_table* ht, UINT32 const key, UINT32 const newval);
BOOL32 	hash_table_remove(hash_table* ht, UINT32 const key);

#define hash_table_is_full(ht) ((ht)->size == (ht)->capacity)

#endif // _SHASHTBL_H
