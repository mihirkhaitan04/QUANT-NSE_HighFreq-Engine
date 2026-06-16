// ===================================================================
//  risk_check.c  —  eBPF/XDP Kernel Shield for HFT Risk Checks
// ===================================================================
//  This program runs directly on the Linux Network Interface Card (NIC).
//  It inspects incoming and outgoing packets BEFORE the OS kernel
//  allocates memory for them.
//
//  PURPOSE:
//    1. Parse the packet (Ethernet -> IP -> TCP)
//    2. Identify NSE 'OrderEntryRequest' payloads (TransactionCode = 2000)
//    3. Inspect the 'Volume' field at byte offset 132 in the payload
//    4. If Volume > 10000, drop the packet instantly (XDP_DROP)
//
//  HOW TO COMPILE (For Docker / Linux Jenkins Pipeline):
//    clang -O2 -g -Wall -target bpf -c risk_check.c -o risk_check.o
// ===================================================================

#include <linux/bpf.h>
#include <linux/if_ether.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/in.h>

// Macro to place the program in the 'xdp' ELF section
#define SEC(NAME) __attribute__((section(NAME), used))

// eBPF Helper for Endianness
#define bpf_htons(x) __builtin_bswap16(x)

// NSE Protocol Constants
#define NSE_PORT 9038
#define ORDER_ENTRY_TX_CODE 2000
#define MAX_ALLOWED_VOLUME 10000
#define VOLUME_OFFSET 132

// eBPF map to store metrics (dropped packet count)
struct {
    __uint(type, BPF_MAP_TYPE_PERCPU_ARRAY);
    __uint(max_entries, 1);
    __type(key, __u32);
    __type(value, __u64);
} drop_counter SEC(".maps");

// Main XDP Hook
SEC("xdp")
int nse_risk_check(struct xdp_md *ctx) {
    // 1. Establish strict boundaries (eBPF verifier requirement)
    void *data_end = (void *)(long)ctx->data_end;
    void *data     = (void *)(long)ctx->data;

    // 2. Parse Ethernet Header
    struct ethhdr *eth = data;
    if ((void *)(eth + 1) > data_end) {
        return XDP_PASS;
    }

    // We only care about IPv4 traffic
    if (eth->h_proto != bpf_htons(ETH_P_IP)) {
        return XDP_PASS;
    }

    // 3. Parse IP Header
    struct iphdr *ip = (struct iphdr *)(eth + 1);
    if ((void *)(ip + 1) > data_end) {
        return XDP_PASS;
    }

    // We only care about TCP traffic
    if (ip->protocol != IPPROTO_TCP) {
        return XDP_PASS;
    }

    // 4. Parse TCP Header
    // IP header length is dynamic, calculated via ip->ihl * 4
    struct tcphdr *tcp = (struct tcphdr *)((unsigned char *)ip + (ip->ihl * 4));
    if ((void *)(tcp + 1) > data_end) {
        return XDP_PASS;
    }

    // We only care about traffic going to the NSE Exchange Port
    if (tcp->dest != bpf_htons(NSE_PORT)) {
        return XDP_PASS;
    }

    // 5. Locate the TCP Payload (where the NSE Binary message begins)
    // TCP header length is dynamic, calculated via tcp->doff * 4
    unsigned char *payload = (unsigned char *)tcp + (tcp->doff * 4);
    
    // Ensure the payload is large enough to contain our Volume field
    // TransactionCode (2 bytes) + ... + Volume (4 bytes at offset 132) -> 136 bytes total needed
    if ((void *)(payload + VOLUME_OFFSET + 4) > data_end) {
        return XDP_PASS; // Packet too small to be our target order
    }

    // 6. Inspect the TransactionCode (first 2 bytes)
    __u16 *transaction_code = (__u16 *)payload;
    if (*transaction_code != ORDER_ENTRY_TX_CODE) {
        return XDP_PASS; // Not an OrderEntryRequest, allow it
    }

    // 7. Inspect the Volume field (at offset 132)
    __u32 *volume = (__u32 *)(payload + VOLUME_OFFSET);

    // 8. FAT FINGER CHECK (The Risk Filter)
    if (*volume > MAX_ALLOWED_VOLUME) {
        // Log the drop in our BPF map
        __u32 key = 0;
        __u64 *count = bpf_map_lookup_elem(&drop_counter, &key);
        if (count) {
            __sync_fetch_and_add(count, 1);
        }

        // Instantly kill the packet before the OS even sees it!
        return XDP_DROP; 
    }

    // Safe order, allow it through to the exchange
    return XDP_PASS;
}

// BPF License requirement
char _license[] SEC("license") = "GPL";
