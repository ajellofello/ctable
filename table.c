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


