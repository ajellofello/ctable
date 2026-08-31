#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "libtable.h"

/* These are parameters required for the FNV-1
 * hashing function. I picked them to create
 * 32-bit hash value once done.
 *
 * I got the values from WikiPedia:
 * <https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function#FNV_hash_parameters>
 */
#define FNV_OFFSET 0x811c9dc5
#define FNV_PRIME  0x01000193

uint32_t fnvhash(char* dat)
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

void* xrealloc(void *p, size_t size)
{
  void* mem = realloc(p, size);

  if (mem == NULL) { exit(1); }
  return mem;
}

void* xmalloc(size_t size)
{
  void* mem = malloc(size);

  if (mem == NULL) { exit(1); }
  return mem;
}

void* xcalloc(size_t n, size_t size)
{
  void* mem = calloc(n, size);

  if (mem == NULL) { exit(1); }
  return mem;
}

bool getbucket(const struct table_t table, char* key, struct tableitem_t** bucket_ptr)
{
  uint32_t hashval = (fnvhash(key) % table.cap);
  struct tableitem_t* bucket;
  *bucket_ptr = bucket = &table.items[hashval];

  if (bucket->empty) { return false; }

  while (strcmp(bucket->key, key) != 0)
  {
    hashval = ((hashval + fnvhash(key)) % table.cap);
    *bucket_ptr = bucket = &table.items[hashval];

    if (bucket->empty) { return false; }
  }

  return true;
}

bool tableinit(size_t basesize, struct table_t* table)
{
  if (basesize < 8) { return false; }

  *table = (struct table_t){
    .cap = basesize,
    .items = xcalloc(basesize, sizeof(struct tableitem_t))
  };

  for (int i = 0; i < table->cap; i++)
    table->items[i].empty = true;

  return true;
}

void tablefree(struct table_t* table)
{
  for (int i = 0; i < table->cap; i++)
    if (table->items[i].val != NULL) { free(table->items[i].val); }
  free(table->items);
}

bool tableput(struct table_t* table, char* key, void* val, size_t valsize)
{
  /* For each new 5 elements added allocate 8 extra spots in memory */
  if ((table->len % 5) == 0) { xrealloc(table->items, (table->cap += 8)); }

  struct tableitem_t* bucket = NULL;
  if (getbucket(*table, key, &bucket)) { return false; }

  *bucket = (struct tableitem_t){
    .key = key,
    .empty = false
  };

  bucket->val = xmalloc(valsize);
  memcpy(bucket->val, val, valsize);
  table->len++;
  return true;
}

bool tableget(const struct table_t table, char* key, struct tableitem_t* item)
{
  struct tableitem_t* bucket;
  if (!getbucket(table, key, &bucket)) { return false; }

  *item = *bucket;
  return true;
}

bool tabledel(struct table_t* table, char* key)
{
  struct tableitem_t* bucket;
  if (!getbucket(*table, key, &bucket)) { return false; }

  bucket->empty = true;
  table->len--;
  return true;
}

bool tableup(struct table_t* table, char* key, void* val, size_t valsize)
{
  struct tableitem_t* bucket;
  if (!getbucket(*table, key, &bucket)) { return false; }

  memcpy(bucket->val, val, valsize);
  return true;
}

