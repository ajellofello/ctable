#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "table.h"

/* These are parameters required for the FNV-1
 * hashing function. I picked them to create
 * 32-bit hash value once done.
 *
 * I got the values from WikiPedia:
 * <https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function#FNV_hash_parameters>
 */
#define FNV_OFFSET 0x811c9dc5
#define FNV_PRIME  0x01000193

uint32_t fnv_hash(char* dat)
{
  uint32_t hash = FNV_OFFSET;
  char c;

  while ((c = *dat++))
  {
    hash *= FNV_PRIME;
    hash ^= c;
  }

  return hash;
}

void* xcalloc(size_t n, size_t size)
{
  void* mem = calloc(n, size);

  if (mem == NULL) { exit(1); }
  return mem;
}

bool table_init(size_t cap, struct table_t* table)
{
  if (cap < 8) { return false; }

  *table = (struct table_t){
    .cap = cap,
    .items = xcalloc(cap, sizeof(struct tableitem_t))
  };

  for (int i = 0; i < table->cap; i++)
    table->items[i].empty = true;

  return true;
}

bool table_put(struct table_t* table, char* key, void* value)
{
  uint32_t hashval = (fnv_hash(key) % table->cap);
  struct tableitem_t* bucket = &table->items[hashval];

  while (!bucket->empty)
  {
    if (strcmp(key, bucket->key) == 0) { return false; }

    hashval = ((hashval + fnv_hash(key)) % table->cap);
    bucket = &table->items[hashval];
  }

  *bucket = (struct tableitem_t){
    .key = key,
    .val = value,
    .empty = false 
  };
  return true;
}

bool table_get(const struct table_t table, char* key, struct tableitem_t* item)
{
  uint32_t hashval = (fnv_hash(key) % table.cap);
  struct tableitem_t* bucket = &table.items[hashval];

  if (bucket->empty) { return false; }

  while (strcmp(key, bucket->key) != 0)
  {
    hashval = ((hashval + fnv_hash(key)) % table.cap);
    bucket = &table.items[hashval];

    if (bucket->empty) { return false; }
  }

  *item = *bucket;
  return true;
}

bool table_del(struct table_t* table, char* key)
{
  uint32_t hashval = (fnv_hash(key) % table->cap);
  struct tableitem_t* bucket = &table->items[hashval];

  if (bucket->empty) { return false; }

  while (strcmp(bucket->key, key) != 0)
  {
    hashval = ((hashval + fnv_hash(key)) % table->cap);
    bucket = &table->items[hashval];

    if (bucket->empty) { return false; }
  }

  bucket->empty = true;
  return true;
}

bool table_up(struct table_t* table, char* key, void* newval)
{
  uint32_t hashval = (fnv_hash(key) % table->cap);
  struct tableitem_t* bucket = &table->items[hashval];

  if (bucket->empty) { return false; }

  while (strcmp(bucket->key, key) != 0)
  {
    hashval = ((hashval + fnv_hash(key)) % table->cap);
    bucket = &table->items[hashval];

    if (bucket->empty) { return false; }
  }

  bucket->val = newval;
  return true;
}

