#ifndef LIBTABLE_H
#define LIBTABLE_H

#include <stdbool.h>
#include <stddef.h>

typedef struct
{
  char* key;
  void* val;
  bool empty;
} tableitem_t;

typedef struct 
{
  tableitem_t* items;
  size_t cap;
  size_t len;
} table_t;

bool tablecreate(size_t basesize, table_t* table);
void tablefree(table_t* table);
bool tableput(table_t* table, char* key, void* val, size_t size);
bool tableget(const table_t table, char* key, tableitem_t* item);
bool tabledel(table_t* table, char* key);
bool tableup(table_t* table, char* key, void* val, size_t size);

#endif
