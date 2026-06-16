// ===================================================================
//  mock_nse_exchange.cpp  —  A Fake NSE Exchange (TCP Server)
// ===================================================================
//
//  WHAT THIS DOES:
//    1. Starts a TCP server on localhost port 9038.
//    2. Waits for our Trading Engine (main.cpp) to connect.
//    3. Receives raw binary packets from the engine.
//    4. Decodes the packets using our auto-generated Decoder.
//    5. Prints the decoded message fields to the console.
//    6. Sends back a simple "ACK" (acknowledgment) response.
//
//  HOW TO COMPILE (from the temp_repo folder):
//    g++ -std=c++11 -o mock_exchange tests/mock_nse_exchange.cpp -I src -lws2_32
//
//  HOW TO RUN:
//    .\mock_exchange.exe
//    (Then run trading_engine.exe in another terminal)
//
// ===================================================================

#include <iostream>
#include <vector>
#include <cstring>

// Our simple networking wrapper (hides all Winsock2 complexity)
#include "common/network.h"

// Our auto-generated codec headers
#include "codecs/NSE/SPECS/9_38/NSE_Msgs.h"
#include "codecs/NSE/SPECS/9_38/NSE_Handler.h"
#include "codecs/NSE/SPECS/9_38/NSE_Decoder.h"
#include "codecs/NSE/SPECS/9_38/NSE_Stream.h"


// ===================================================================
//  ExchangeHandler  —  What happens when a message is decoded
// ===================================================================
//  The Decoder calls these functions automatically after decoding.
//  We just print the decoded fields to the console.
// ===================================================================
struct ExchangeHandler {

    // Called when a SignOnRequest is successfully decoded
    void operator()(const SignOnRequest& msg, Status& status) noexcept {
        std::cout << "\n========================================" << std::endl;
        std::cout << "[EXCHANGE] Received SignOnRequest!" << std::endl;
        std::cout << "  UserId   : " << msg.getUserId()  << std::endl;
        std::cout << "  UserId2  : " << msg.getUserId2() << std::endl;
        std::cout << "  ErrorCode: " << msg.getErrorCode() << std::endl;
        std::cout << "========================================\n" << std::endl;
    }

    // Called when an OrderEntryRequest is successfully decoded
    void operator()(const OrderEntryRequest& msg, Status& status) noexcept {
        std::cout << "\n========================================" << std::endl;
        std::cout << "[EXCHANGE] Received OrderEntryRequest!" << std::endl;
        std::cout << "  UserId  : " << msg.getUserId()  << std::endl;
        std::cout << "  TokenNo : " << msg.getTokenNo()  << std::endl;
        std::cout << "  Price   : " << msg.getPrice()    << std::endl;
        std::cout << "  Volume  : " << msg.getVolume()   << std::endl;
        std::cout << "========================================\n" << std::endl;
    }

    // Called when the message type is unknown or an error occurs
    void operator()(Status& status) noexcept {
        std::cerr << "[EXCHANGE] ERROR: " << status.getInfo() << std::endl;
    }
};


// ===================================================================
//  MAIN  —  The Exchange Server Entry Point
// ===================================================================
int main() {
    std::cout << "============================================" << std::endl;
    std::cout << "  MOCK NSE EXCHANGE  (port 9038)" << std::endl;
    std::cout << "============================================" << std::endl;

    // Step 1: Create the server and listen on port 9038
    SocketServer server(9038);
    if (!server.isValid()) return 1;

    // Step 2: Wait for our trading engine to connect
    if (!server.waitForClient()) return 1;

    // Step 3: Prepare the decoder
    Decoder<ExchangeHandler> decoder;

    // Step 4: Main receive loop — keep reading packets from the client
    char buffer[4096];   // Raw binary receive buffer

    while (true) {
        // Read raw bytes from the trading engine
        int bytesRead = server.receive(buffer, sizeof(buffer));

        if (bytesRead <= 0) {
            std::cout << "[EXCHANGE] Client disconnected. Shutting down." << std::endl;
            break;
        }

        std::cout << "[EXCHANGE] Received " << bytesRead << " bytes." << std::endl;

        // Decode the raw binary message directly
        // (decodeBinary works on raw bytes — no hex conversion needed)
        Status status;
        decoder.decodeBinary(buffer, bytesRead, status);

        if (status.getStatus() == StatusEnum::COMPLETE) {
            // Send back a simple ACK: just echo the first 4 bytes (transaction code area)
            const char ack[] = "ACK";
            server.sendData(ack, 3);
            std::cout << "[EXCHANGE] Sent ACK to client." << std::endl;
        } else {
            std::cerr << "[EXCHANGE] Decode error: " << status.getInfo() << std::endl;
        }
    }

    std::cout << "[EXCHANGE] Server stopped." << std::endl;
    return 0;
}
