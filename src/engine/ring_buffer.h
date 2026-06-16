#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <atomic>
#include <vector>
#include <stdexcept>

// ============================================================================
// Lock-Free Single-Producer Single-Consumer (SPSC) Ring Buffer
// ============================================================================
// Standard std::mutex locks force threads to pause and wait for the OS to 
// wake them up, causing massive latency spikes (context switches).
// 
// This RingBuffer uses Hardware Memory Barriers (std::atomic) instead of locks.
// Thread A (Network) pushes packets, and Thread B (Trading Strategy) pops them.
// Time to pass a message between threads: ~15 nanoseconds.
// ============================================================================

template <typename T>
class RingBuffer {
private:
    std::vector<T> buffer_;
    size_t capacity_;
    size_t mask_;

    // Use Cache-Line padding to prevent "False Sharing" between CPU cores
    // (Padding variables so they don't sit on the same 64-byte hardware cache line)
    alignas(64) std::atomic<size_t> head_{0};
    alignas(64) std::atomic<size_t> tail_{0};

public:
    explicit RingBuffer(size_t power_of_two_capacity) {
        // Capacity must be a power of 2 for fast bitwise modulo
        if (power_of_two_capacity == 0 || (power_of_two_capacity & (power_of_two_capacity - 1)) != 0) {
            throw std::invalid_argument("Capacity must be a power of 2");
        }
        
        capacity_ = power_of_two_capacity;
        mask_ = capacity_ - 1;
        buffer_.resize(capacity_);
    }

    // Called by Producer Thread (Network I/O)
    bool push(const T& item) {
        size_t current_tail = tail_.load(std::memory_order_relaxed);
        size_t next_tail = (current_tail + 1) & mask_;

        if (next_tail == head_.load(std::memory_order_acquire)) {
            return false; // Buffer is full
        }

        buffer_[current_tail] = item;
        tail_.store(next_tail, std::memory_order_release);
        return true;
    }

    // Called by Consumer Thread (Trading Strategy)
    bool pop(T& item) {
        size_t current_head = head_.load(std::memory_order_relaxed);

        if (current_head == tail_.load(std::memory_order_acquire)) {
            return false; // Buffer is empty
        }

        item = buffer_[current_head];
        head_.store((current_head + 1) & mask_, std::memory_order_release);
        return true;
    }
};

#endif // RING_BUFFER_H
