FROM ubuntu:22.04

# Avoid tzdata prompts
ENV DEBIAN_FRONTEND=noninteractive

# Install dependencies required for eBPF compilation and loading
RUN apt-get update && apt-get install -y \
    clang \
    llvm \
    libbpf-dev \
    iproute2 \
    linux-headers-generic \
    gcc-multilib \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /opt/kernel_shield

# Copy the eBPF C code and deployment script
COPY risk_check.c .
COPY load_bpf.sh .

# Ensure the script is executable
RUN chmod +x load_bpf.sh

# eBPF/XDP requires high privileges to attach to the network interface.
# Run this container with: docker run --privileged --network host ...
ENTRYPOINT ["./load_bpf.sh"]
