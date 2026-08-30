#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

struct tableitem_t
{
  char* key;
  void* val;
};

struct table_t
{
  struct tableitem_t* items;
  size_t cap;
  size_t len;
};

/* These are parameters required for the FNV-1
 * hashing function. I picked them to create
 * unsigned 32-bit hashes once done.
 *
 * I got the values from WikiPedia:
 * <https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function#FNV_hash_parameters>
 */
#define FNV_OFFSET 0x811c9dc5
#define FNV_PRIME  0x01000193

uint32_t fnv_hash(char* dat, size_t cap)
{
  /* This is a hashing function which hashes a string
   * through FNV-1 hashing function.
   *
   * I made a few modifications to the hash function
   * to make it fit our needs of saving data to a
   * hash table.
   *
   * 1. I made it only return unsigned values by
   * using abs() from stdlib.h
   *
   * 2. I modulo the result 32-bit hash by <cap>
   * which is the capacity of the table to make
   * sure we get a valid index
   */

  uint32_t hash = FNV_OFFSET;
  char c;

  while ((c = *dat++))
  {
    hash *= FNV_PRIME;
    hash ^= c;
  }

  return (abs(hash) % cap);
}

