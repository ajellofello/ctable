#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ctable.h"

#define LIB "ctable"
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

uint32_t fnvhash(const char* key)
{
  uint32_t hash = FNV_OFFSET;
  char c;

  while ((c = *key++))
  {
    hash *= FNV_PRIME;
    hash ^= c;
  }

  return hash;
}

void* xrealloc(void *p, size_t size)
{
  void* mem = realloc(p, size);

  if (mem == NULL)
  {
    perror("realloc");
    exit(1);
  }
  return mem;
}

void* xmalloc(size_t size)
{
  void* mem = malloc(size);

  if (mem == NULL)
  {
    perror("malloc");
    exit(1);
  }
  return mem;
}

void* xcalloc(size_t n, size_t size)
{
  void* mem = calloc(n, size);

  if (mem == NULL)
  {
    perror("calloc");
    exit(1);
  }
  return mem;
}

bool getbucket(const ctable_t table, const char* key, ctableitem_t** bucket_ptr)
{
  uint32_t hashval = (fnvhash(key) % table.cap);
  ctableitem_t* bucket;
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

ctable_t* ctablecreate(size_t basesize)
{
  if (basesize <= 0)
  {
    fprintf(stderr, LIB": tablecreate(): the base size must be greater than 0\n");
    exit(1);
  }

  ctable_t* table = xmalloc(sizeof(ctable_t));
  *table = (ctable_t){
    .cap = basesize,
    .items = xcalloc(basesize, sizeof(ctableitem_t))
  };

  for (int i = 0; i < table->cap; i++)
    table->items[i].empty = true;

  return table;
}

void ctablefree(ctable_t* table)
{
  for (int i = 0; i < table->cap; i++)
  {
    if (table->items[i].key != NULL) { free(table->items[i].key); }
    if (table->items[i].val != NULL) { free(table->items[i].val); }
  }
  free(table->items);
  free(table);
}

bool ctableput(ctable_t* table, const char* key, const void* val, const size_t size)
{
  if ((table->cap - table->len) <= ALLOC_POINT) { xrealloc(table->items, (table->cap += 8)); }

  ctableitem_t* bucket;
  if (getbucket(*table, key, &bucket)) { return false; }

  *bucket = (ctableitem_t){
    .key = xmalloc(strlen(key)),
    .val = xmalloc(size),
    .empty = false
  };

  strcpy(bucket->key, key);
  memcpy(bucket->val, val, size);
  table->len++;
  return true;
}

bool ctableget(const ctable_t table, const char* key, ctableitem_t* item)
{
  ctableitem_t* bucket;
  if (!getbucket(table, key, &bucket)) { return false; }

  *item = *bucket;
  return true;
}

bool ctabledel(ctable_t* table, const char* key)
{
  ctableitem_t* bucket;
  if (!getbucket(*table, key, &bucket)) { return false; }

  bucket->empty = true;
  table->len--;
  return true;
}

bool ctableup(ctable_t* table, const char* key, const void* val, const size_t size)
{
  ctableitem_t* bucket;
  if (!getbucket(*table, key, &bucket)) { return false; }

  memcpy(bucket->val, val, size);
  return true;
}

