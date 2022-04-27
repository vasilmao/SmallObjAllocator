#pragma once

#include "FixedAllocator.hpp"

template<typename T>
class Allocator {
  public:
    static T* Allocate();
    static void Deallocate(T* ptr);
  private:
    static FixedAllocator fixed_allocator_;
};


template<typename T>
FixedAllocator Allocator<T>::fixed_allocator_{sizeof(T)};

template<typename T>
T* Allocator<T>::Allocate() {
    return static_cast<T*>(fixed_allocator_.Allocate());
}

template<typename T>
void Allocator<T>::Deallocate(T* ptr) {
    fixed_allocator_.Deallocate(ptr);
}