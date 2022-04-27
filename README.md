# SmallObjAllocator
Allocator writen while reading Alexandrescu's "Modern c++ design"

## How to use: Fixed Allocator

FixedAllocator needs block size in constructor, then Allocate() will always give you memory of this size, Deallocate(ptr) deallocates it
