# IMPLEMENTATION

This hash table uses [_open addressing_](https://en.wikipedia.org/wiki/Open_addressing) through [_double hashing_](https://en.wikipedia.org/wiki/Double_hashing)
to handle collisions. I used the hashing function [FNV-1](https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function) because I heard
about it most :p

This hash table saves _keys_ as _strings_ while saving the _values_ as _void pointers_
which means you can use any type you want for the values. Sadly this also means you
have to dereference and cast the pointer before using it.

The void pointer implementation uses `memcpy()` to copy the data that the pointer
is pointing to into the value of the table item, so the table item doesn't have to be
linked to the item the caller used which means you can update the original value and 
the value in the table won't change. Also this separates the lifetime of the item's value
from the lifetime of the original value.

a custom version of `calloc()`, `malloc()` & `realloc()` are used `xcalloc()`, `xmalloc()` &
`xrealloc()` which basically just exit from the program if any of them fail with a status 
code of `1`.

# RESOURCES

- [Hash Tables](https://en.wikipedia.org/wiki/Hash_table)
- [Open Addressing](https://en.wikipedia.org/wiki/Open_addressing)
- [FNV-1 Hash](https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function)
- [Double Hashing](https://en.wikipedia.org/wiki/Double_hashing)
- [Lazy Deletions](https://en.wikipedia.org/wiki/Lazy_deletion)

***THANKS WIKIPEDIA <3*** 

