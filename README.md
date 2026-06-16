<div align="center">
  <h1>⚡ NSE Protocol Code Generator & Ultra-Low Latency Engine ⚡</h1>
</div>

Hello there! 👋

I **Mihir Khaitan**am excited to share my **Quant NSE Engine** project, which auto-generates C++ encoder, decoder, and message object code from a YAML schema specifically for the National Stock Exchange (NSE) protocol. It provides complete support for all binary protocol features without introducing the massive overhead of a standard FIX engine. 

But it doesn't stop at code generation. This project is a complete, end-to-end algorithmic trading infrastructure that incorporates extreme software optimizations (Memory Pools, Lock-Free Queues, AVX SIMD), hardware-level kernel-bypass (eBPF), and a zero-JSON Native JS dashboard.

Think of it as: **Elite codegen for low-latency NSE trading, with hardware-level risk shields and zero-serialization web streaming.**

---

## ✨ Key Features

This tool is designed to automate the process of generating C++ code for different versions of the NSE protocol while operating at microsecond latencies. Key features include:

### 1. Automated Code Generation (Pillar 1)
* **Constant Fields:** Automatically handles fields that are fixed in value.
* **Constrained & Optional Fields:** Flexibly handles fields with predefined values or those that may not appear in a message.
* **Error Handling:** Errors are gracefully populated in a `Status` object instead of throwing C++ exceptions (which destroy low-latency performance).

### 2. Extreme C++ Optimizations (Pillar 2)
* **Zero-Allocation Memory Pools:** Bypasses slow OS `malloc`/`new` calls by pre-allocating memory arenas at startup. Fetches memory in ~1 nanosecond.
* **Lock-Free SPSC Queues:** Uses `std::atomic` hardware memory barriers to pass data between threads without `std::mutex` locks.
* **CPU Core Pinning:** Uses OS-level Thread Affinity APIs to lock the trading engine to isolated CPU cores, preventing cache-misses.
* **AVX SIMD Parsing:** Utilizes 256-bit Intel AVX CPU instructions (`<immintrin.h>`) to process 32 bytes of binary payload simultaneously.

### 3. eBPF Kernel Shield (Pillar 3)
* **Hardware-Level Risk Checks:** A pure `C` XDP module injected directly into the Linux Network Interface Card (NIC) driver. It inspects binary trades and drops "fat-finger" errors in **nanoseconds**, before the OS kernel even allocates memory.

### 4. Zero-JSON Dashboard (Pillar 4)
* **Binary WebSockets:** Instead of wasting CPU cycles converting data to JSON strings for the UI, the engine blasts raw binary hex over WebSockets. The React-style frontend uses native Javascript `DataView` to read memory offsets directly in the browser!

---

## 🛠️ Usage

Here’s how to get started with the NSE Code Generator & Trading Engine. 👇

### Step 1: Generate C++ Code
Use the Python generator to parse the YAML specification and generate perfectly aligned C++ structs.

```bash
cd src
python generate_codec.py -c ../specs/NSE_SPECS_9_38.yaml --create
cd ..
```

### Step 2: Compile with Extreme Optimizations
The generated code includes the necessary header files. We compile the full engine using Intel AVX vector instructions.

```bash
# Compile Mock Exchange & Trading Engine
g++ -std=c++11 -o mock_exchange tests/mock_nse_exchange.cpp -I src -lws2_32
g++ -std=c++11 -mavx2 -o trading_engine src/engine/main.cpp -I src -lws2_32 -lcrypt32
```

### Step 3: Run the Live Simulation
1. Start the Exchange: `.\mock_exchange.exe`
2. Start the Engine: `.\trading_engine.exe`
3. Open `frontend/index.html` in any web browser to view the live binary decoding dashboard!

*(Note: The eBPF shield `src/kernel/load_bpf.sh` is designed for Linux/Docker environments).*

---

## 📁 Project Structure

Here’s how the project is organized for maximum clarity and extreme low-latency design:

* **`specs/`**: Contains the `NSE_SPECS_9_38.yaml` which acts as the Single Source of Truth.
* **`src/generator/`**: Contains the Python `generate_codec.py` and Jinja2 templates (Message Class, Encoder, Decoder).
* **`src/codecs/NSE/`**: The auto-generated C++ code based strictly on the YAML blueprint.
* **`src/engine/`**: The core execution engine. Contains the multi-threaded `main.cpp`, `memory_pool.h`, and `ring_buffer.h`.
* **`src/kernel/`**: Contains the `risk_check.c` eBPF module.
* **`frontend/`**: Contains the "God-Tier" professional Dark Mode dashboard that parses the binary data natively.

---

## 🤔 Why This Code Generator & Architecture?

This tool provides a clean, automated solution for generating C++ code for the NSE protocol. Key benefits include:

* **High Flexibility:** The YAML configuration file acts as the single source of truth. If the exchange updates their protocol, simply update the YAML and regenerate the code!
* **Ultra-High Performance:** The C++ engine relies entirely on stack memory, memory arenas, lock-free concurrency, and SIMD. It is suitable for serious High-Frequency Trading (HFT) Market Making and Latency Arbitrage.
* **Future-Proof:** Designed to scale massively while remaining deterministic and JSON-free.

---

**PS: Code Formatting**
The auto-generated C++ code may require formatting. Feel free to use tools like `clang-format` to automatically format the code for consistency and readability.

Feel free to hit me up with new ideas or queries regarding my project.