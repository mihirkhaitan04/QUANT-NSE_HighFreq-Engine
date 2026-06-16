#include <iostream>
#include <vector>
#include "src/codecs/NSE/SPECS/9_38/NSE_Msgs.h"
#include "src/codecs/NSE/SPECS/9_38/NSE_Handler.h"
#include "src/codecs/NSE/SPECS/9_38/NSE_Decoder.h"
#include "src/codecs/NSE/SPECS/9_38/NSE_Encoder.h"
#include "src/codecs/NSE/SPECS/9_38/NSE_Stream.h"

int main() {
    std::cout << "Testing compilation of generated codec headers..." << std::endl;
    
    Decoder<DefaultNSEHandler> decoder;
    Encoder<DefaultNSEHandler> encoder;
    
    SignOnRequest req;
    req.setUserId(123);
    req.setUserId2(456);
    
    std::cout << "Compilation successful!" << std::endl;
    return 0;
}