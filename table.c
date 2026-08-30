#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

struct tableitem_t
{
  char* key;
  void* val;
  bool  empty;
};

struct table_t
{
  struct tableitem_t* items;
  size_t cap;
  size_t len;
};

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

struct table_t init(size_t cap)
{
  struct table_t table = {
    .cap = cap,
    .items = calloc(cap, sizeof(struct tableitem_t))
  };

  for (int i = 0; i < table.cap; i++)
    table.items[i].empty = true;

  return table;
}

void table_insert(struct table_t* table, char* key, void* value)
{
  uint32_t hashval = (fnv_hash(key) % table->cap);
  struct tableitem_t* bucket = &table->items[hashval];

  while (!bucket->empty)
  {
    hashval = ((hashval + fnv_hash(key)) % table->cap);
    bucket = &table->items[hashval];
  }

  *bucket = (struct tableitem_t){
    .key = key,
    .val = value,
    .empty = false 
  };
}

