#pragma once
#include "NSE_Msgs.h"
#include "../../../../common/status.h"
#include <iostream>
#include <string>

// NSE_Handler.h
// This is a base "handler" that the Decoder calls after successfully decoding
// a message. You can inherit from this or replace it with your own custom handler.
//
// The Decoder is templated: Decoder<YourHandler>
// Your handler must implement operator() for each message type it wants to handle.
//
// Example usage:
//   struct MyHandler {
//       void operator()(const SignOnRequest& msg, Status& status) { ... }
//       void operator()(const OrderEntryRequest& msg, Status& status) { ... }
//       void operator()(Status& status) { /* error case */ }
//   };

struct DefaultNSEHandler
{
    // Called when a SignOnRequest is successfully decoded
    void operator()(const SignOnRequest& msg, Status& status) noexcept
    {
        std::cout << "[DefaultNSEHandler] SignOnRequest received.\n";
        std::cout << "  - User ID   : " << msg.getUserId() << "\n";
        std::cout << "  - Broker ID : " << std::string(msg.getBrokerId().data(), msg.getBrokerId().size()) << "\n";
        
        if (msg.getErrorCode() != 0) {
            std::cerr << "  -> SignOn Failed with Error Code: " << msg.getErrorCode() << "\n";
        } else {
            std::cout << "  -> SignOn Successful.\n";
        }
        
        status.updateStatus(StatusEnum::COMPLETE);
    }

    // Called when an OrderEntryRequest is successfully decoded
    void operator()(const OrderEntryRequest& msg, Status& status) noexcept
    {
        std::cout << "[DefaultNSEHandler] OrderEntryRequest received.\n";
        std::cout << "  - Token No : " << msg.getTokenNo() << "\n";
        std::cout << "  - Symbol   : " << std::string(msg.getSymbol().data(), msg.getSymbol().size()) << "\n";
        std::cout << "  - Price    : " << msg.getPrice() << "\n";
        std::cout << "  - Volume   : " << msg.getVolume() << "\n";
        
        if (msg.getBuy_SellIndicator() == 1) {
            std::cout << "  -> Action  : BUY\n";
        } else if (msg.getBuy_SellIndicator() == 2) {
            std::cout << "  -> Action  : SELL\n";
        } else {
            std::cout << "  -> Action  : UNKNOWN (" << msg.getBuy_SellIndicator() << ")\n";
        }
        
        // Example basic pre-trade risk check logic
        if (msg.getVolume() > 10000) {
            std::cerr << "  -> [RISK REJECT] Volume exceeds maximum threshold!\n";
            status.updateStatus(StatusEnum::INVALID_PAYLOAD);
        } else {
            std::cout << "  -> [RISK ACCEPT] Order passed pre-trade checks.\n";
            status.updateStatus(StatusEnum::COMPLETE);
        }
    }

    // Called when the message type is unknown or an error occurs
    void operator()(Status& status) noexcept
    {
        std::cerr << "[DefaultNSEHandler] Error occurred during message processing.\n";
        std::cerr << "  - Status Info : " << status.getInfo() << "\n";
        
        if (status.getStatus() == StatusEnum::BUFFER_OVERFLOW) {
            std::cerr << "  -> Critical: Buffer size limit exceeded. Adjust memory pool sizing.\n";
        } else if (status.getStatus() == StatusEnum::INVALID_MESSAGE_TYPE) {
            std::cerr << "  -> Warning: Received an unknown transaction code.\n";
        }
    }
};
