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

bool table_init(size_t cap, struct table_t* table);
bool table_put(struct table_t* table, char* key, void* value);
bool table_get(const struct table_t table, char* key, struct tableitem_t* item);
bool table_del(struct table_t* table, char* key);
bool table_up(struct table_t* table, char* key, void* newval);
#endif
