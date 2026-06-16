#!/bin/bash
# ===================================================================
#  load_bpf.sh  —  Jenkins/Docker Deployment Script for Kernel Shield
# ===================================================================
#  This script is designed to be executed during the deployment 
#  phase on the production Linux server or inside a privileged Docker
#  container.
#
#  It compiles the C program into eBPF bytecode and attaches it
#  to the network interface (eth0).
# ===================================================================

set -e

# Configuration
INTERFACE="eth0"
BPF_SOURCE="risk_check.c"
BPF_OBJECT="risk_check.o"

echo "============================================"
echo "  Deploying eBPF Kernel Shield"
echo "============================================"

# Step 1: Compile the C program to eBPF bytecode using Clang
# We use -target bpf to tell LLVM to generate kernel BPF bytecode instead of x86 instructions.
echo "[1/3] Compiling $BPF_SOURCE to $BPF_OBJECT..."
clang -O2 -g -Wall -target bpf -c $BPF_SOURCE -o $BPF_OBJECT

if [ ! -f "$BPF_OBJECT" ]; then
    echo "ERROR: Compilation failed!"
    exit 1
fi

# Step 2: Detach any old eBPF programs on the interface to avoid conflicts
echo "[2/3] Cleaning up old XDP programs on $INTERFACE..."
ip link set dev $INTERFACE xdp off || true

# Step 3: Attach the new Kernel Shield to the network interface using XDP
# 'xdpgeneric' is used here for maximum compatibility, but in a real HFT 
# environment you would use 'xdpdrv' to load it directly onto the NIC hardware.
echo "[3/3] Attaching $BPF_OBJECT to $INTERFACE..."
ip link set dev $INTERFACE xdp obj $BPF_OBJECT sec xdp

echo "============================================"
echo "  SUCCESS! Kernel Shield is ACTIVE."
echo "  Any OrderEntryRequest with Volume > 10000"
echo "  will now be dropped in microseconds."
echo "============================================"

# Note to view drops: you can use `bpftool map dump name drop_counter`
