#ifndef LIBTABLE_H
#define LIBTABLE_H

#include <stdbool.h>
#include <stddef.h>

struct tableitem_t
{
  char* key;
  long val;
  bool empty;
};

struct table_t
{
  struct tableitem_t* items;
  size_t cap;
  size_t len;
};

extern bool tableinit(size_t cap, struct table_t* table);
extern void tablefree(struct table_t* table);
extern bool tableput(struct table_t* table, char* key, long val);
extern bool tableget(const struct table_t table, char* key, struct tableitem_t* item);
extern bool tabledel(struct table_t* table, char* key);
extern bool tableup(struct table_t* table, char* key, long val);

#endif
