#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "table.h"

#define LIB "table"
#define ALLOC_POINT 3
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

bool getbucket(const table_t table, char* key, tableitem_t** bucket_ptr)
{
  uint32_t hashval = (fnvhash(key) % table.cap);
  tableitem_t* bucket;
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

table_t tablecreate(size_t basesize)
{
  if (basesiz <= 0)
  {
    fprintf(stderr, LIB": tablecreate(): the base size must be greater than 0\n");
    exit(1);
  }

  table = xmalloc(sizeof(table_t));
  *table = (table_t){
    .cap = basesize,
    .items = xcalloc(basesize, sizeof(tableitem_t))
  };

  for (int i = 0; i < table->cap; i++)
    table->items[i].empty = true;

  return true;
}

void tablefree(table_t* table)
{
  for (int i = 0; i < table->cap; i++)
  {
    if (table->items[i].key != NULL) { free(table->items[i].key); }
    if (table->items[i].val != NULL) { free(table->items[i].val); }
  }
  free(table->items);
  free(table);
}

bool tableput(table_t* table, char* key, void* val, size_t valsize)
{
  if ((table->cap - table->len) <= ALLOC_POINT) { xrealloc(table->items, (table->cap += 8)); }

  tableitem_t* bucket;
  if (getbucket(*table, key, &bucket)) { return false; }

  *bucket = (tableitem_t){
    .key = strdup(key),
    .empty = false
  };

  bucket->val = xmalloc(valsize);
  memcpy(bucket->val, val, valsize);
  table->len++;
  return true;
}

bool tableget(const table_t table, char* key, tableitem_t* item)
{
  tableitem_t* bucket;
  if (!getbucket(table, key, &bucket)) { return false; }

  *item = *bucket;
  return true;
}

bool tabledel(table_t* table, char* key)
{
  tableitem_t* bucket;
  if (!getbucket(*table, key, &bucket)) { return false; }

  bucket->empty = true;
  table->len--;
  return true;
}

bool tableup(table_t* table, char* key, void* val, size_t valsize)
{
  tableitem_t* bucket;
  if (!getbucket(*table, key, &bucket)) { return false; }

  memcpy(bucket->val, val, valsize);
  return true;
}

