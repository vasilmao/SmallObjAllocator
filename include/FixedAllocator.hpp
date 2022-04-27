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
        ChunkBase(void* memory);
        ~ChunkBase();
      protected:
        unsigned char* memory_ = nullptr;
    };
    class Chunk : private ChunkBase {
      public:
        Chunk(size_t block_size, unsigned char blocks);

        Chunk() = delete;
        Chunk(const Chunk& other) = delete;

        Chunk(Chunk&& other);
        void* Allocate(size_t block_size); // yeah, this block size is equal to block_size in constructor.
        // Why? imagine: you have vector of chunks of same size, every contains same block size
        // vs
        // FixedAllocator contains one block size for all chunks (255 size_ts vs one size_t)
        void Deallocate(void* ptr, size_t block_size);

        bool HasFreeStorage();
        bool ContainsMemory(void* ptr, size_t block_size, unsigned char blocks);

      private:
        unsigned char first_available_block_ = 0; // index of the first free block
        unsigned char blocks_available_ = 0;      // number of free blocks
    };
  
  private:
    size_t block_size_;
    Vector<Chunk> chunks_;
    size_t alloc_chunk_index_ = -1;
    size_t dealloc_chunk_index_ = -1;
};