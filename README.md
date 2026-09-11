# DESCRIPTION

A simple C hash table implementation that uses [_open addressing_](https://en.wikipedia.org/wiki/Open_addressing) through [_double hashing_](https://en.wikipedia.org/wiki/Double_hashing)
to handle collisions.

It saves _keys_ as _strings_ while saving _values_ as _void pointers_

# NOTES

When calling `tableput()` or `tableup()` the value for the item will be copied into the
hash table's updated/inserted item, so that the lifetime of the given void pointer value
and the void pointer value of the hash table item are separate.

If any of C's allocators face an error the program will exit with a status code of `1`
and print `errno`.

# BUILDING

Simply clone the repo and run `make`

```
git clone https://github.com/ajellofello/table.git && cd table
mkdir build
make
```

`build/` should contain `table.o`, the created archive `libtable.a` as
well as the header `table.h`

# LINKS

- [Hash Tables](https://en.wikipedia.org/wiki/Hash_table)
- [Open Addressing](https://en.wikipedia.org/wiki/Open_addressing)
- [FNV-1 Hash](https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function)
- [Double Hashing](https://en.wikipedia.org/wiki/Double_hashing)
- [Lazy Deletions](https://en.wikipedia.org/wiki/Lazy_deletion)

***THANKS WIKIPEDIA <3*** 

