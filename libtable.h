#ifndef LIBTABLE_H
#define LIBTABLE_H

#include <stdbool.h>
#include <stddef.h>

struct tableitem_t
{
  char* key;
  void* val;
  bool empty;
};

struct table_t
{
  struct tableitem_t* items;
  size_t cap;
  size_t len;
};

bool tableinit(size_t basesize, struct table_t* table);
void tablefree(struct table_t* table);
bool tableput(struct table_t* table, char* key, void* val, size_t size);
bool tableget(const struct table_t table, char* key, struct tableitem_t* item);
bool tabledel(struct table_t* table, char* key);
bool tableup(struct table_t* table, char* key, void* val, size_t size);

#endif
