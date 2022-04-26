#include "FixedAllocator.hpp"
#include <cassert>

FixedAllocator::FixedAllocator(size_t block_size) : block_size_(block_size), chunks_{1, {block_size, chunk_size}} {}

void* FixedAllocator::Allocate() {
    if (alloc_chunk_index_ == -1 || chunks_[alloc_chunk_index_].HasFreeStorage()) {
        // not enough memory in allock_chunk, lets try to find new
        size_t i = 0;
        for (; i < chunks_.size(); ++i) {
            if (chunks_[i].HasFreeStorage()) {
                alloc_chunk_index_ = i;
                break;
            }
        }
        if (i == chunks_.size()) {
            // we need new chunk
            chunks_.push_back(Chunk{block_size_, chunk_size});
            alloc_chunk_index_ = i;
            dealloc_chunk_index_ = i;
        }
    }
    assert(alloc_chunk_index_ != -1);
    assert(chunks_[alloc_chunk_index_].HasFreeStorage());
    return chunks_[alloc_chunk_index_].Allocate(block_size_);
}

void FixedAllocator::Deallocate(void* ptr) {
    bool block_found = false;
    if (chunks_[dealloc_chunk_index_].ContainsMemory(ptr, block_size_, chunk_size)) {
        block_found = true;
    } else {
        for (size_t i = 1; dealloc_chunk_index_ - i >= 0 || dealloc_chunk_index_ + i < chunks_.size(); ++i) {
            size_t low_index = dealloc_chunk_index_ - i;
            size_t high_index = dealloc_chunk_index_ + i;
            if (low_index >= 0) {
                if (chunks_[low_index].ContainsMemory(ptr, block_size_, chunk_size)) {
                    dealloc_chunk_index_ = low_index;
                    block_found = true;
                    break;
                }
            }
            if (high_index < chunks_.size()) {
                if (chunks_[high_index].ContainsMemory(ptr, block_size_, chunk_size)) {
                    dealloc_chunk_index_ = high_index;
                    block_found = true;
                    break;
                }
            }
        }
    }
    // strategy: trying to find near the dealloc_chunk
    assert(block_found);
    chunks_[dealloc_chunk_index_].Deallocate(ptr, block_size_);
}