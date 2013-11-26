#include <stdlib.h>
#include "hash_table.h"
#include "misc.h"

int main(void) 
{
	hash_table _ht;
	hash_table* ht = &_ht;
	UINT32 capacity = 4;
	UINT32 num_buckets = 16;
	hashnode** buckets = malloc(sizeof(hashnode*) * num_buckets);
	UINT32 pool_size = capacity;
	hashnode* pool = malloc(sizeof(hashnode) * pool_size);

	UINT32 val; 
	BOOL32 res;

	hash_table_init(ht, capacity, buckets, num_buckets, 
			pool, pool_size);
	
	res = hash_table_get(ht, 0, &val);
	BUG_ON("return non-existent element", res == 0);
	
	res = hash_table_insert(ht, 8, 8);
	BUG_ON("insertion failure", res != 0);
	res = hash_table_insert(ht, 128, 821);
	BUG_ON("insertion failure", res != 0);
	res = hash_table_insert(ht, 787998, 1);
	BUG_ON("insertion failure", res != 0);
	res = hash_table_insert(ht, 0, 1);
	BUG_ON("insertion failure", res != 0);

	res = hash_table_insert(ht, 0, 1);
	BUG_ON("insertion to full table is successful", res == 0);

	res = hash_table_get(ht, 787998, &val);
	BUG_ON("val wrong", val != 1);

	res = hash_table_update(ht, 787998, 2);
	res = hash_table_get(ht, 787998, &val);
	BUG_ON("val wrong", val != 2);

	res = hash_table_update(ht, 789, 0);
	BUG_ON("update to non-existant element successful", res == 0);

	free(buckets);
	free(pool);
}
