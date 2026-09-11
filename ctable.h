#ifndef LIBTABLE_H
#define LIBTABLE_H

#include <stdbool.h>
#include <stddef.h>

typedef struct
{
  char* key;
  void* val;
  bool empty;
} ctableitem_t;

typedef struct 
{
  ctableitem_t* items;
  size_t cap;
  size_t len;
} ctable_t;

ctable_t* ctablecreate(size_t basesize);
void ctablefree(ctable_t* table);
bool ctableput(ctable_t* table, const char* key, const void* val, const size_t size);
bool ctableget(const ctable_t table, const char* key, ctableitem_t* item);
bool ctabledel(ctable_t* table, const char* key);
bool ctableup(ctable_t* table, const char* key, const void* val, const size_t size);

#endif
