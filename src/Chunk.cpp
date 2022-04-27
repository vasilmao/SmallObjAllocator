#include "FixedAllocator.hpp"
#include "cassert"

FixedAllocator::Chunk::Chunk(size_t block_size, unsigned char blocks) : blocks_available_(blocks) {
    // memory = new unsigned char[block_size * blocks];
    memory_ = static_cast<unsigned char*>(malloc(block_size * blocks));
    first_available_block_ = 0;
    unsigned char* p = memory_;
    for (unsigned char i = 0; i != blocks; p += block_size) {
        *p = ++i; // free blocks have link to the next free block
        // last one points to the block that doesnt exists
    }
}

FixedAllocator::Chunk::Chunk(FixedAllocator::Chunk&& other) {
    memory_ = other.memory_;
    other.memory_ = nullptr;

    first_available_block_ = other.first_available_block_;
    blocks_available_ = other.blocks_available_;
}

void* FixedAllocator::Chunk::Allocate(size_t block_size) {
    if (!blocks_available_) return nullptr;
    unsigned char* result = memory_ + (first_available_block_ * block_size);
    first_available_block_ = *result; // contains index of next free block
    --blocks_available_;
    return result;
}

void FixedAllocator::Chunk::Deallocate(void* ptr, size_t block_size) {
    assert(ptr >= memory_);
    unsigned char* to_release = static_cast<unsigned char*>(ptr);
    assert((to_release - memory_) % block_size == 0);
    first_available_block_ = static_cast<unsigned char>((to_release - memory_) / block_size);
    assert(first_available_block_ == ((to_release - memory_) / block_size));
    ++blocks_available_;
}

bool FixedAllocator::Chunk::HasFreeStorage() {
    return blocks_available_ != 0;
}

bool FixedAllocator::Chunk::ContainsMemory(void* ptr, size_t block_size, unsigned char blocks) {
    return (memory_ <= ptr) && (ptr <= memory_ + (block_size * blocks));
}

FixedAllocator::Chunk::~Chunk() {
    if (memory_ != nullptr) {
        // delete[] memory_;
        free(memory_);
    }
}