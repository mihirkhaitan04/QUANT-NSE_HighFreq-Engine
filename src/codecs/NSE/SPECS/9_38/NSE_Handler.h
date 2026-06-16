#pragma once
#include "NSE_Msgs.h"
#include "../../../../common/status.h"

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
        (void)msg; (void)status;
        // TODO: Add your SignOnRequest handling logic here
    }

    // Called when an OrderEntryRequest is successfully decoded
    void operator()(const OrderEntryRequest& msg, Status& status) noexcept
    {
        (void)msg; (void)status;
        // TODO: Add your OrderEntryRequest handling logic here
    }

    // Called when the message type is unknown or an error occurs
    void operator()(Status& status) noexcept
    {
        (void)status;
        // TODO: Add your error handling logic here
    }
};
