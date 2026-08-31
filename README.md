# IMPLEMENTATION

This hash table uses [_open addressing_](https://en.wikipedia.org/wiki/Open_addressing) through [_double hashing_](https://en.wikipedia.org/wiki/Double_hashing)
to handle collisions. I used the hashing function [FNV-1](https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function) because I heard
about it most :p

This hash table saves _keys_ as _strings_ while saving the _values_ as _longs_ this is because
using void pointers had too many issues including:

1. if the pointer went out of the current scope the item
in the table would be looking at trash

2. if the item is changed in the calling function the value in 
the database will change as well

So this sadly means that if you want to use something other than
`long` you will have to change that yourself. It is only changes
to the header and function & structure definitions as the implementations
won't change.

# RESOURCES

- [Hash Tables](https://en.wikipedia.org/wiki/Hash_table)
- [Open Addressing](https://en.wikipedia.org/wiki/Open_addressing)
- [FNV-1 Hash](https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function)
- [Double Hashing](https://en.wikipedia.org/wiki/Double_hashing)
- [Lazy Deletions](https://en.wikipedia.org/wiki/Lazy_deletion)

***THANKS WIKIPEDIA <3*** 

