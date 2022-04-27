#include "FixedAllocator.hpp"

template<typename T>
class Allocator {
  public:
    Allocator();
    T* Allocate();
    void Deallocate(T* ptr);
  private:
    static FixedAllocator fixed_allocator_;
};

template<typename T>
Allocator<T>::Allocator() : fixed_allocator_{siezof(T)} {}

template<typename T>
T* Allocator<T>::Allocate() {
    return fixed_allocator_.Allocate();
}

template<typename T>
void Allocator<T>::Deallocate(T* ptr) {
    fixed_allocator_.Deallocate(ptr);
}