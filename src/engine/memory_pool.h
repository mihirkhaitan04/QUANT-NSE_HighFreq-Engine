#ifndef MEMORY_POOL_H
#define MEMORY_POOL_H

#include <cstdint>
#include <cstdlib>
#include <stdexcept>

// ============================================================================
// Zero-Allocation Memory Pool (Arena Allocator)
// ============================================================================
// In High-Frequency Trading, dynamically allocating memory (new/malloc) during 
// a live trade is strictly forbidden because the OS takes hundreds of nanoseconds
// to find free RAM. 
//
// This MemoryPool pre-allocates a massive contiguous block of RAM at startup.
// When a trade needs memory, it simply increments a pointer in 1 nanosecond.
// ============================================================================

class MemoryPool {
private:
    uint8_t* buffer_;
    size_t capacity_;
    size_t offset_;

public:
    explicit MemoryPool(size_t capacity_bytes) 
        : capacity_(capacity_bytes), offset_(0) {
        
        // Pre-allocate the entire block of RAM at once
        buffer_ = static_cast<uint8_t*>(std::malloc(capacity_));
        if (!buffer_) {
            throw std::runtime_error("Failed to pre-allocate memory pool");
        }
    }

    ~MemoryPool() {
        if (buffer_) {
            std::free(buffer_);
        }
    }

    // Grab a slice of memory in O(1) time (typically ~1 nanosecond)
    void* allocate(size_t size) {
        if (offset_ + size > capacity_) {
            // In a real HFT system, we would wrap around or handle this cleanly.
            // For this engine, we just throw if we run out.
            throw std::runtime_error("Memory Pool OOM (Out of Memory)");
        }
        
        void* ptr = buffer_ + offset_;
        offset_ += size;
        return ptr;
    }

    // Reset the pool offset. Extremely fast O(1) operation.
    // Call this after a burst of trades is finished to reuse the memory.
    void reset() {
        offset_ = 0;
    }

    // Delete copy constructors to prevent accidental expensive copies
    MemoryPool(const MemoryPool&) = delete;
    MemoryPool& operator=(const MemoryPool&) = delete;
};

#endif // MEMORY_POOL_H
