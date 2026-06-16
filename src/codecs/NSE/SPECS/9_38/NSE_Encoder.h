#pragma once
#include "NSE_Msgs.h"
#include "../../../../common/status.h"
#include "../../../../common/utils.h"




template <typename HandlerType>
class Encoder {
    

    
    template <typename U>
    inline typename std::enable_if<std::is_enum<U>::value, void>::type
    _encode(char *&start, char *end, const U &field, Status &status) noexcept
    {
        if (status.getStatus() != StatusEnum::PARSING) return;
        
        if (start + sizeof(field) > end)  
        {
            status.updateStatus(StatusEnum::BUFFER_OVERFLOW);
            return;
        }

        if (field == U::UNKNOWN)
        {
            status.updateStatus(StatusEnum::INVALID_OBJECT);
            return;
        }

        *reinterpret_cast<U *>(start) = field;
        start += sizeof(field);
        status.updateNextStart(start);  
    }

    template <typename U>
    inline typename std::enable_if<!std::is_enum<U>::value, void>::type
    _encode(char *&start, char *end, const U &field, Status &status) noexcept
    {
        if (status.getStatus() != StatusEnum::PARSING) return;
        
        if (start + sizeof(field) > end)  
        {
            status.updateStatus(StatusEnum::BUFFER_OVERFLOW);
            return;
        }

        *reinterpret_cast<U *>(start) = field;
        start += sizeof(field);
        status.updateNextStart(start);  
    }

    
    template <typename U>
    void _encode(char *&start, char *end, const std::vector<U> &field, Status &status) noexcept {
        
        if (status.getStatus() != StatusEnum::PARSING)
            return;  
        
        for (const auto &element : field) {
            _encode(start, end, element, status);
            if (status.getStatus() != StatusEnum::PARSING) return;  // Exit loop on overflow
        }
    }


    // Specialization for encoding vectors of fields dependent on bitfields
    template <typename U, typename B>
    void _encode(char *&start, char *end, const std::vector<U> &field, const std::vector<B> &bitfields, Status &status) noexcept
    {
        if (status.getStatus() != StatusEnum::PARSING)
            return;  

        for (const auto &element : field)
        {
            _encode(start, end, element, bitfields, status);
            
            if (status.getStatus() != StatusEnum::PARSING)
                return;  
        }
    }

    
    template <size_t len>
    void _encode(char *&start, char *end, const std::array<char, len> &field, Status &status) noexcept
    {
        
        if (status.getStatus() != StatusEnum::PARSING)
            return;  

        for (const auto &element : field)
        {
            _encode(start, end, element, status);
            
            if (status.getStatus() != StatusEnum::PARSING)
                return;  
        }
    }
    
    void _encode(char*& start, char* end, const SignOnRequest& signOnRequest, Status& status) noexcept
        {
            
            _encode(start, end, signOnRequest.getTransactionCode(), status);
            _encode(start, end, signOnRequest.getLogTime(), status);
            _encode(start, end, signOnRequest.getAlphaChar(), status);
            _encode(start, end, signOnRequest.getUserId(), status);
            _encode(start, end, signOnRequest.getErrorCode(), status);
            _encode(start, end, signOnRequest.getTimestamp(), status);
            _encode(start, end, signOnRequest.getTimeStamp1(), status);
            _encode(start, end, signOnRequest.getTimeStamp2(), status);
            _encode(start, end, signOnRequest.getMessageLength(), status);
            _encode(start, end, signOnRequest.getUserId2(), status);
            _encode(start, end, signOnRequest.getReserved_SOR1(), status);
            _encode(start, end, signOnRequest.getPassword(), status);
            _encode(start, end, signOnRequest.getReserved_SOR2(), status);
            _encode(start, end, signOnRequest.getNewPassword(), status);
            _encode(start, end, signOnRequest.getTraderName(), status);
            _encode(start, end, signOnRequest.getLastPasswordChangeDate(), status);
            _encode(start, end, signOnRequest.getBrokerId(), status);
            _encode(start, end, signOnRequest.getReserved_SOR3(), status);
            _encode(start, end, signOnRequest.getVersionNumber(), status);
            _encode(start, end, signOnRequest.getReserved_SOR4(), status);
            _encode(start, end, signOnRequest.getWsClassName(), status);
            _encode(start, end, signOnRequest.getReserved_SOR5(), status);
            _encode(start, end, signOnRequest.getBrokerName(), status);
            _encode(start, end, signOnRequest.getReservedEnd_SOR1(), status);
            _encode(start, end, signOnRequest.getReservedEnd_SOR2(), status);
            _encode(start, end, signOnRequest.getReservedEnd_SOR3(), status);
        }void _encode(char*& start, char* end, const OrderEntryRequest& orderEntryRequest, Status& status) noexcept
        {
            
            _encode(start, end, orderEntryRequest.getTransactionCode(), status);
            _encode(start, end, orderEntryRequest.getLogTime(), status);
            _encode(start, end, orderEntryRequest.getAlphaChar(), status);
            _encode(start, end, orderEntryRequest.getUserId(), status);
            _encode(start, end, orderEntryRequest.getErrorCode(), status);
            _encode(start, end, orderEntryRequest.getTimestamp(), status);
            _encode(start, end, orderEntryRequest.getTimeStamp1(), status);
            _encode(start, end, orderEntryRequest.getTimeStamp2(), status);
            _encode(start, end, orderEntryRequest.getMessageLength(), status);
            _encode(start, end, orderEntryRequest.getParticipantType(), status);
            _encode(start, end, orderEntryRequest.getReserved_OER1(), status);
            _encode(start, end, orderEntryRequest.getTokenNo(), status);
            _encode(start, end, orderEntryRequest.getInstrumentName(), status);
            _encode(start, end, orderEntryRequest.getSymbol(), status);
            _encode(start, end, orderEntryRequest.getExpiryDate(), status);
            _encode(start, end, orderEntryRequest.getStrikePrice(), status);
            _encode(start, end, orderEntryRequest.getOptionType(), status);
            _encode(start, end, orderEntryRequest.getCALevel(), status);
            _encode(start, end, orderEntryRequest.getReserved_OER2(), status);
            _encode(start, end, orderEntryRequest.getOrderType(), status);
            _encode(start, end, orderEntryRequest.getOrderNumber(), status);
            _encode(start, end, orderEntryRequest.getAccountNumber(), status);
            _encode(start, end, orderEntryRequest.getBookType(), status);
            _encode(start, end, orderEntryRequest.getBuy_SellIndicator(), status);
            _encode(start, end, orderEntryRequest.getDisclosedVolume(), status);
            _encode(start, end, orderEntryRequest.getReserved_OER3(), status);
            _encode(start, end, orderEntryRequest.getVolume(), status);
            _encode(start, end, orderEntryRequest.getReserved_OER4(), status);
            _encode(start, end, orderEntryRequest.getPrice(), status);
            _encode(start, end, orderEntryRequest.getTriggerPrice(), status);
            _encode(start, end, orderEntryRequest.getGoodTillDate(), status);
            _encode(start, end, orderEntryRequest.getReserved_OER5(), status);
            _encode(start, end, orderEntryRequest.getOpen_Close(), status);
            _encode(start, end, orderEntryRequest.getSettlor(), status);
            _encode(start, end, orderEntryRequest.getPro_ClientIndicator(), status);
            _encode(start, end, orderEntryRequest.getSettlementPeriod(), status);
            _encode(start, end, orderEntryRequest.getReserved_OER6(), status);
            _encode(start, end, orderEntryRequest.getPAN(), status);
            _encode(start, end, orderEntryRequest.getReserved_OER7(), status);
        }
public:
    
    template <typename T>
    void encode(const std::vector<char> &buffer, const T &msg, Status &status)
    {
        char *start = const_cast<char *>(buffer.data());
        char *end = start + buffer.size();
        HandlerType handler;
        _encode(start, end, msg, status);

        
        if (status.getStatus() == StatusEnum::PARSING)
            status.updateStatus(StatusEnum::COMPLETE);
        handler(status);
    }
};

