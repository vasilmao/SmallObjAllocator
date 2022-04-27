#pragma once

#include <cstdlib>

#include "Vector.hpp"

class FixedAllocator {
  public:
    FixedAllocator(size_t block_size);
    void* Allocate();
    void Deallocate(void* ptr);

  private:
    class ChunkBase {
      public:
        ChunkBase() = delete;
        ChunkBase(void* memory);
        ChunkBase(const ChunkBase& other) = delete;
        ChunkBase(ChunkBase&& other);
        ChunkBase& operator=(const ChunkBase& other) = delete;
        ChunkBase& operator=(ChunkBase&& other);
        ~ChunkBase();
      protected:
        unsigned char* memory_ = nullptr;
      private:
        void Swap(ChunkBase& other);
    };

    class Chunk : private ChunkBase {
      public:
        Chunk(size_t block_size, unsigned char blocks);

        void* Allocate(size_t block_size);
        void Deallocate(void* ptr, size_t block_size);

        bool HasFreeStorage();
        bool ContainsMemory(void* ptr, size_t block_size, unsigned char blocks);

      private:
        unsigned char first_available_block_ = 0; // index of the first free block
        unsigned char blocks_available_ = 0;      // number of free blocks
    };
  
  private:
    size_t block_size_ = -1;
    Vector<Chunk> chunks_;
    size_t alloc_chunk_index_ = -1;
    size_t dealloc_chunk_index_ = -1;
};