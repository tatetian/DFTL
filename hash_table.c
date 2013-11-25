//
// Lightweight static hash table source file
//
#include "hash_table.h"
#include "misc.h"

/**
 * Hash function : Robert Jenkins' 32 bit integer hash
 */
static UINT32 hash_function(UINT32 const key)
{
	UINT32 hash = key;

	hash = (hash + 0x7ed55d16) + (hash << 12);
	hash = (hash ^ 0xc761c23c) ^ (hash >> 19);
	hash = (hash + 0x165667b1) + (hash << 5);
	hash = (hash + 0xd3a2646c) ^ (hash << 9);
	hash = (hash + 0xfd7046c5) + (hash << 3);
	hash = (hash ^ 0xb55a4f09) ^ (hash >> 16);

	return hash;
}

void hash_table_init(hash_table*  ht,    UINT32 const capacity, 
		     hashnode** buckets,   UINT32 const num_buckets,
		     hashnode*  node_pool, UINT32 const pool_size) 
{
	BUG_ON("null pointer", ht == NULL || 
			       buckets == NULL || 
			       node_pool == NULL);
	BUG_ON("invalid argument", capacity <= 0 || 
				   capacity > num_buckets || 
				   capacity > pool_size);

	ht->size = 0;
	ht->capacity = capacity;
	ht->buckets  = buckets;
	ht->num_buckets = num_buckets;
	ht->node_pool = node_pool;
	ht->pool_size = pool_size;
	ht->free_nodes = NULL;
}

BOOL32 hash_table_get(hash_table* ht, UINT32 const key, UINT32 *val)
{
	hashnode* node;
	UINT32 hash_val;

	BUG_ON("null pointer", ht == NULL); 
	
	hash_val = hash_function(key) % ht->num_buckets;
	node = ht->buckets[hash_val];

	while (node) {
		if (node->key == key) {
			*val = node->val;
			return 0;
		}
		node = node->next;
        }
    	return 1;
}

BOOL32 	hash_table_insert(hash_table* ht, UINT32 const key, UINT32 const val)
{
	hashnode* new_node;
	UINT32 hash_val;

	BUG_ON("null pointer", ht == NULL);
	
	if (hash_table_is_full(ht))
		return 1;

	if (ht->free_nodes) {
		new_node = ht->free_nodes;
		ht->free_nodes = new_node->next;
		new_node->next = NULL;
	}
	else {
		new_node = & ht->node_pool[ht->size];
	}
	new_node->key = key;
	new_node->val = val;

	hash_val = hash_function(key) % ht->num_buckets;
	new_node->next = ht->buckets[hash_val];

	ht->buckets[hash_val] = new_node;
	ht->size += 1;
	return 0;
}

BOOL32 	hash_table_update(hash_table* ht, UINT32 const key, UINT32 const newval)
{
	hashnode* node;
	UINT32 hash_val;

	BUG_ON("null pointer", ht == NULL); 
	
	hash_val = hash_function(key) % ht->num_buckets;
	node = ht->buckets[hash_val];

	while (node) {
		if (node->key == key) {
			node->val = newval;
			return 0;
		}
		node = node->next;
        }
    	return 1;
}

BOOL32 	hash_table_remove(hash_table* ht, UINT32 const key)
{
	hashnode *node, *pre_node = NULL;
	UINT32 hash_val;

	BUG_ON("null pointer", ht == NULL); 
	
	hash_val = hash_function(key) % ht->num_buckets;
	node = ht->buckets[hash_val];

	while (node) {
		if (node->key == key) {
			if (pre_node)
				pre_node->next = node->next;
			else
				ht->buckets[hash_val] = node->next;
			node->next = ht->free_nodes;
			ht->free_nodes = node;
			ht->size -= 1;
			return 0;
		}	
		pre_node = node;
		node = node->next;
	}
	return 1;
}
