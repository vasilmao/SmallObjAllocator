# SmallObjAllocator
Allocator writen while reading Alexandrescu's "Modern c++ design"

## How to use: Fixed Allocator

FixedAllocator needs block size in constructor, then Allocate() will always give you memory of this size, Deallocate(ptr) deallocates it

## How to use: TypedAllocator

Allocator<T>::Allocate() gives you pointer to allocated T, Allocator<T>::Deallocate(T* ptr) deallocates it (they dont call constructors and destructors)
