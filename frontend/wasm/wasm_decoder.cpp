#include <emscripten/bind.h>
#include <emscripten.h>
#include <string>

// Include our auto-generated low-latency Codecs
#include "../../src/codecs/NSE/SPECS/9_38/NSE_Msgs.h"
#include "../../src/codecs/NSE/SPECS/9_38/NSE_Handler.h"
#include "../../src/codecs/NSE/SPECS/9_38/NSE_Decoder.h"

using namespace emscripten;

// Global variable to store the JSON result from the handler
std::string global_json_result = "";

// The Handler that catches the decoded objects
struct WasmDecoderHandler {
    void operator()(const SignOnRequest& msg, Status& status) noexcept {
        // Construct a simple JSON string manually (No external JSON library needed)
        global_json_result = "{"
            "\"type\":\"SIGNON\","
            "\"typeName\":\"SignOnRequest\","
            "\"userId\":\"" + std::to_string(msg.getUserId()) + "\","
            "\"volume\":\"-\""
        "}";
    }

    void operator()(const OrderEntryRequest& msg, Status& status) noexcept {
        global_json_result = "{"
            "\"type\":\"ORDER\","
            "\"typeName\":\"OrderEntry\","
            "\"userId\":\"" + std::to_string(msg.getUserId()) + "\","
            "\"volume\":\"" + std::to_string(msg.getVolume()) + "\""
        "}";
    }

    void operator()(Status& status) noexcept {
        global_json_result = "{"
            "\"type\":\"UNKNOWN\","
            "\"typeName\":\"Unknown\","
            "\"userId\":\"-\","
            "\"volume\":\"-\""
        "}";
    }
};

// The function exported to Javascript
std::string decodeBinaryWASM(uintptr_t bufferPtr, int length) {
    global_json_result = ""; // Reset
    
    // Cast the WASM memory pointer back into a char buffer
    const char* buffer = reinterpret_cast<const char*>(bufferPtr);
    
    // Create decoder
    Decoder<WasmDecoderHandler> decoder;
    Status status;
    
    // Perform ultra-fast C++ binary decoding
    decoder.decodeBinary(buffer, length, status);
    
    if (global_json_result.empty()) {
        return "{\"type\":\"ERROR\", \"typeName\":\"Decode Error\", \"userId\":\"-\", \"volume\":\"-\"}";
    }
    
    return global_json_result;
}

// Emscripten Binding (Exposes decodeBinaryWASM to window.Module)
EMSCRIPTEN_BINDINGS(nse_wasm_module) {
    function("decodeBinaryWASM", &decodeBinaryWASM);
}
