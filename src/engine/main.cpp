// ===================================================================
//  main.cpp  —  The Elite Low-Latency Trading Engine
// ===================================================================
//
//  NEW EXTREME OPTIMIZATIONS:
//    1. CPU Core Pinning (Thread Affinity)
//    2. Lock-Free SPSC Ring Buffer (LMAX Disruptor Pattern)
//    3. Zero-Allocation Memory Pools
//    4. SIMD (AVX2) Fast Memory Copy
//
//  HOW TO COMPILE (from the temp_repo folder):
//    g++ -std=c++11 -mavx2 -o trading_engine src/engine/main.cpp -I src -lws2_32 -lcrypt32
//
// ===================================================================

#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <cstring>
#include <immintrin.h> // For AVX SIMD Instructions
#include <windows.h>   // For SetThreadAffinityMask and Sleep()

#include "common/network.h"
#include "websocket_server.h"
#include "codecs/NSE/SPECS/9_38/NSE_Msgs.h"
#include "codecs/NSE/SPECS/9_38/NSE_Handler.h"
#include "codecs/NSE/SPECS/9_38/NSE_Encoder.h"
#include "common/stopwatch.h"

// Extreme Optimizations
#include "memory_pool.h"
#include "ring_buffer.h"

// Payload passed between threads via the Ring Buffer
struct TradePayload {
    char data[1024];
    int size;
};

// Global Lock-Free Queue (Capacity must be power of 2)
RingBuffer<TradePayload> tx_queue(1024);

// Global WebSocket Server (to stream to the React UI)
WebSocketServer* global_ws = nullptr;

// ===================================================================
// SIMD Fast Copy (AVX2 256-bit Memory Move)
// ===================================================================
// Instead of copying byte-by-byte, we copy 32 bytes in a single CPU cycle.
inline void simd_fast_copy(void* dest, const void* src, size_t count) {
#ifdef __AVX2__
    char* d = static_cast<char*>(dest);
    const char* s = static_cast<const char*>(src);
    size_t i = 0;
    // Copy 32 bytes at a time
    for (; i + 32 <= count; i += 32) {
        __m256i chunk = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(s + i));
        _mm256_storeu_si256(reinterpret_cast<__m256i*>(d + i), chunk);
    }
    // Handle remainder
    for (; i < count; ++i) {
        d[i] = s[i];
    }
#else
    std::memcpy(dest, src, count);
#endif
}

// ===================================================================
// THREAD 1: Network I/O (Pinned to CPU Core 0)
// ===================================================================
DWORD WINAPI network_thread_func(LPVOID lpParam) {
    // 1. Pin this thread to CPU Core 0 (Bitmask 0x01)
    SetThreadAffinityMask(GetCurrentThread(), 1);
    std::cout << "[NETWORK THREAD] Pinned to CPU Core 0." << std::endl;

    SocketClient client("127.0.0.1", 9038);
    if (!client.isConnected()) {
        std::cerr << "[NETWORK THREAD] Mock exchange not running!" << std::endl;
        return 0;
    }

    TradePayload payload;
    char recvBuffer[1024];

    while (true) {
        // Poll the lock-free queue in nanoseconds (no mutexes!)
        if (tx_queue.pop(payload)) {
            
            Stopwatch timer;
            timer.start();

            // Broadcast to React UI (for demo purposes)
            if (global_ws) {
                global_ws->broadcastBinary(payload.data, payload.size);
            }

            // Send to exchange
            if (!client.sendData(payload.data, payload.size)) {
                break;
            }

            // Blocking receive (Mocking the exchange response)
            int bytesRead = client.receive(recvBuffer, sizeof(recvBuffer));
            if (bytesRead > 0) {
                timer.stop();
                if (global_ws) {
                    global_ws->broadcastBinary(recvBuffer, bytesRead);
                }
                
                recvBuffer[bytesRead] = '\0';
                std::cout << "[NETWORK] Sent Order -> Rcvd: " << recvBuffer 
                          << " | Latency: " << (timer.latency() / 1000.0) << " us" << std::endl;
            }
        }
    }
    return 0;
}

// ===================================================================
// THREAD 2: Trading Strategy (Pinned to CPU Core 1)
// ===================================================================
DWORD WINAPI strategy_thread_func(LPVOID lpParam) {
    // 1. Pin this thread to CPU Core 1 (Bitmask 0x02)
    SetThreadAffinityMask(GetCurrentThread(), 2);
    std::cout << "[STRATEGY THREAD] Pinned to CPU Core 1." << std::endl;

    // 2. Instantiate Zero-Allocation Memory Pool (10 Megabytes)
    MemoryPool pool(10 * 1024 * 1024);
    std::cout << "[STRATEGY THREAD] Pre-allocated 10MB Memory Arena." << std::endl;

    std::vector<char> encode_buf(1024, 0); // Legacy buffer for encoder

    while (true) {
        // --- 1. Memory Pool Allocation (1 nanosecond) ---
        void* mem = pool.allocate(sizeof(OrderEntryRequest));
        
        // Use Placement New to construct the object in pre-allocated memory
        OrderEntryRequest* order = new (mem) OrderEntryRequest();
        order->setUserId(1001);
        order->setVolume(500);

        // --- 2. Encode ---
        Status encodeStatus;
        Encoder<DefaultNSEHandler> encoder;
        encoder.encode(encode_buf, *order, encodeStatus);

        int encodedSize = static_cast<int>(encodeStatus.getNextStart() - encode_buf.data());

        // --- 3. SIMD Fast Copy to Payload ---
        TradePayload payload;
        payload.size = encodedSize;
        simd_fast_copy(payload.data, encode_buf.data(), encodedSize);

        // --- 4. Lock-Free Push to Network Thread (~15 nanoseconds) ---
        while (!tx_queue.push(payload)) {
            // Spin-wait if queue is full
        }

        // --- 5. Reset Memory Pool for next burst ---
        pool.reset();

        // Throttle for the demo so we can watch it on the Web UI
        Sleep(2000);
    }
    return 0;
}

// ===================================================================
// MAIN: Orchestration
// ===================================================================
int main() {
    std::cout << "============================================" << std::endl;
    std::cout << "  ELITE HFT TRADING ENGINE (AVX2 Enabled)" << std::endl;
    std::cout << "============================================" << std::endl;

    // Start UI WebSockets
    WebSocketServer wsServer(8080);
    global_ws = &wsServer;

    // Spawn isolated threads using Windows native API
    HANDLE hNetThread = CreateThread(NULL, 0, network_thread_func, NULL, 0, NULL);
    HANDLE hStratThread = CreateThread(NULL, 0, strategy_thread_func, NULL, 0, NULL);

    // Main thread just services WebSockets for the UI
    while (true) {
        wsServer.poll();
        Sleep(10);
    }

    WaitForSingleObject(hNetThread, INFINITE);
    WaitForSingleObject(hStratThread, INFINITE);
    return 0;
}
