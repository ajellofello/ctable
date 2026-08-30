#ifndef TABLE_H
#define TABLE_H

#include <stdbool.h>
#include <stddef.h>

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

struct table_t init(size_t cap);
void table_insert(struct table_t* table, char* key, void* value);

#endif
