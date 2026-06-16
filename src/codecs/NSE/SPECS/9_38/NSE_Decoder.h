
#pragma once
#include "../../../../common/status.h"
#include "../../../../common/utils.h"
#include "NSE_Handler.h"
#include "NSE_Msgs.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <cstring>
// MessagesEnum: maps each message name to its TransactionCode value.
// The Decoder uses this to identify which message type is in an incoming payload.
enum MessagesEnum : uint16_t
{
    SIGNONREQUEST = 2300,
    ORDERENTRYREQUEST = 2000,
};

enum TypeLocationEnum : size_t
{
    MESSAGE_LOC = 0,      // Byte offset in payload where the TransactionCode lives (first field)
    PARAMGROUP_LOC = 2    // Byte offset where param group type code lives
};

template <typename HandlerType>
class Decoder {
    
// Member variables to hold decoded fields for various custom datatypes
SignOnRequest signOnRequest_;OrderEntryRequest orderEntryRequest_;
    

    // Extracts the message type code from a specific byte offset in the payload
    inline uint16_t _getType(char*& start, char*& end, size_t loc, Status& status)
    {
        if (status.getStatus() != StatusEnum::PARSING) return 0;
        if (start + loc + sizeof(uint16_t) > end)
        {
            status.updateStatus(StatusEnum::NEED_MORE_DATA);
            return 0;
        }
        uint16_t type(*reinterpret_cast<uint16_t*>(start+loc));
        return type;
    }

    // Decodes a field of the given type
    template<typename FieldType>
    inline FieldType _decode(char*& start, char* end, Status& status)
    {
        if (status.getStatus() != StatusEnum::PARSING) return FieldType{};
        if (start + sizeof(FieldType) > end)
        {
            status.updateStatus(StatusEnum::NEED_MORE_DATA);
            return FieldType{};
        }

        FieldType field(*reinterpret_cast<FieldType *>(start));
        start += sizeof(FieldType);
        return field;
    }

    // Verifies a field against an expected value
    template<typename FieldType>
    inline void _verifyField(char*& start, char* end, FieldType verify, Status& status) noexcept
    {
        if (status.getStatus() != StatusEnum::PARSING) return;
        if (start + sizeof(FieldType) > end)
        {
            status.updateStatus(StatusEnum::NEED_MORE_DATA);
            return;
        }

        FieldType field(*reinterpret_cast<FieldType *>(start));
        start += sizeof(FieldType);

        if (field != verify)
        {
            status.updateStatus(StatusEnum::CORRUPTED_PAYLOAD);
            return;
        }
        return;
    }
    
    

// Decode for SignOnRequest class
        void _decodeSignOnRequest(char*& start, char* end, Status& status) noexcept
        {
            if (status.getStatus() != StatusEnum::PARSING) return;
            

            _verifyField(start, end, TranscodesEnum::SIGN_ON_REQUEST_IN, status);

            signOnRequest_.setLogTime(_decode<int32_t>(start, end, status));

            const char* alphaChar = start;
            signOnRequest_.setAlphaChar(alphaChar);
            start += StringLengthsEnum::ALPHACHAR;

            signOnRequest_.setUserId(_decode<int32_t>(start, end, status));

            signOnRequest_.setErrorCode(_decode<int16_t>(start, end, status));

            signOnRequest_.setTimestamp(_decode<int64_t>(start, end, status));

            signOnRequest_.setTimeStamp1(_decode<int64_t>(start, end, status));

            signOnRequest_.setTimeStamp2(_decode<int64_t>(start, end, status));

            signOnRequest_.setMessageLength(_decode<int16_t>(start, end, status));

            signOnRequest_.setUserId2(_decode<int32_t>(start, end, status));

            const char* reserved_SOR1 = start;
            signOnRequest_.setReserved_SOR1(reserved_SOR1);
            start += StringLengthsEnum::RESERVED_SOR1;

            const char* password = start;
            signOnRequest_.setPassword(password);
            start += StringLengthsEnum::PASSWORD;

            const char* reserved_SOR2 = start;
            signOnRequest_.setReserved_SOR2(reserved_SOR2);
            start += StringLengthsEnum::RESERVED_SOR2;

            const char* newPassword = start;
            signOnRequest_.setNewPassword(newPassword);
            start += StringLengthsEnum::NEWPASSWORD;

            const char* traderName = start;
            signOnRequest_.setTraderName(traderName);
            start += StringLengthsEnum::TRADERNAME;

            signOnRequest_.setLastPasswordChangeDate(_decode<int32_t>(start, end, status));

            const char* brokerId = start;
            signOnRequest_.setBrokerId(brokerId);
            start += StringLengthsEnum::BROKERID;

            const char* reserved_SOR3 = start;
            signOnRequest_.setReserved_SOR3(reserved_SOR3);
            start += StringLengthsEnum::RESERVED_SOR3;

            signOnRequest_.setVersionNumber(_decode<int32_t>(start, end, status));

            const char* reserved_SOR4 = start;
            signOnRequest_.setReserved_SOR4(reserved_SOR4);
            start += StringLengthsEnum::RESERVED_SOR4;

            const char* wsClassName = start;
            signOnRequest_.setWsClassName(wsClassName);
            start += StringLengthsEnum::WSCLASSNAME;

            const char* reserved_SOR5 = start;
            signOnRequest_.setReserved_SOR5(reserved_SOR5);
            start += StringLengthsEnum::RESERVED_SOR5;

            const char* brokerName = start;
            signOnRequest_.setBrokerName(brokerName);
            start += StringLengthsEnum::BROKERNAME;

            const char* reservedEnd_SOR1 = start;
            signOnRequest_.setReservedEnd_SOR1(reservedEnd_SOR1);
            start += StringLengthsEnum::RESERVEDEND_SOR1;

            const char* reservedEnd_SOR2 = start;
            signOnRequest_.setReservedEnd_SOR2(reservedEnd_SOR2);
            start += StringLengthsEnum::RESERVEDEND_SOR2;

            const char* reservedEnd_SOR3 = start;
            signOnRequest_.setReservedEnd_SOR3(reservedEnd_SOR3);
            start += StringLengthsEnum::RESERVEDEND_SOR3;
            if (status.getStatus() == StatusEnum::PARSING)
                status.updateStatus(StatusEnum::COMPLETE);
        }

// Decode for OrderEntryRequest class
        void _decodeOrderEntryRequest(char*& start, char* end, Status& status) noexcept
        {
            if (status.getStatus() != StatusEnum::PARSING) return;
            

            _verifyField(start, end, TranscodesEnum::MS_OE_REQUEST, status);

            orderEntryRequest_.setLogTime(_decode<int32_t>(start, end, status));

            const char* alphaChar = start;
            orderEntryRequest_.setAlphaChar(alphaChar);
            start += StringLengthsEnum::ALPHACHAR;

            orderEntryRequest_.setUserId(_decode<int32_t>(start, end, status));

            orderEntryRequest_.setErrorCode(_decode<int16_t>(start, end, status));

            orderEntryRequest_.setTimestamp(_decode<int64_t>(start, end, status));

            orderEntryRequest_.setTimeStamp1(_decode<int64_t>(start, end, status));

            orderEntryRequest_.setTimeStamp2(_decode<int64_t>(start, end, status));

            orderEntryRequest_.setMessageLength(_decode<int16_t>(start, end, status));

            const char* participantType = start;
            orderEntryRequest_.setParticipantType(participantType);
            start += StringLengthsEnum::PARTICIPANTTYPE;

            const char* reserved_OER1 = start;
            orderEntryRequest_.setReserved_OER1(reserved_OER1);
            start += StringLengthsEnum::RESERVED_OER1;

            orderEntryRequest_.setTokenNo(_decode<int32_t>(start, end, status));

            const char* instrumentName = start;
            orderEntryRequest_.setInstrumentName(instrumentName);
            start += StringLengthsEnum::INSTRUMENTNAME;

            const char* symbol = start;
            orderEntryRequest_.setSymbol(symbol);
            start += StringLengthsEnum::SYMBOL;

            orderEntryRequest_.setExpiryDate(_decode<int32_t>(start, end, status));

            orderEntryRequest_.setStrikePrice(_decode<int32_t>(start, end, status));

            const char* optionType = start;
            orderEntryRequest_.setOptionType(optionType);
            start += StringLengthsEnum::OPTIONTYPE;

            orderEntryRequest_.setCALevel(_decode<int16_t>(start, end, status));

            const char* reserved_OER2 = start;
            orderEntryRequest_.setReserved_OER2(reserved_OER2);
            start += StringLengthsEnum::RESERVED_OER2;

            orderEntryRequest_.setOrderType(_decode<int16_t>(start, end, status));

            orderEntryRequest_.setOrderNumber(_decode<int64_t>(start, end, status));

            const char* accountNumber = start;
            orderEntryRequest_.setAccountNumber(accountNumber);
            start += StringLengthsEnum::ACCOUNTNUMBER;

            orderEntryRequest_.setBookType(_decode<int16_t>(start, end, status));

            orderEntryRequest_.setBuy_SellIndicator(_decode<int16_t>(start, end, status));

            orderEntryRequest_.setDisclosedVolume(_decode<int32_t>(start, end, status));

            const char* reserved_OER3 = start;
            orderEntryRequest_.setReserved_OER3(reserved_OER3);
            start += StringLengthsEnum::RESERVED_OER3;

            orderEntryRequest_.setVolume(_decode<int32_t>(start, end, status));

            const char* reserved_OER4 = start;
            orderEntryRequest_.setReserved_OER4(reserved_OER4);
            start += StringLengthsEnum::RESERVED_OER4;

            orderEntryRequest_.setPrice(_decode<int32_t>(start, end, status));

            orderEntryRequest_.setTriggerPrice(_decode<int32_t>(start, end, status));

            orderEntryRequest_.setGoodTillDate(_decode<int32_t>(start, end, status));

            const char* reserved_OER5 = start;
            orderEntryRequest_.setReserved_OER5(reserved_OER5);
            start += StringLengthsEnum::RESERVED_OER5;

            const char* open_Close = start;
            orderEntryRequest_.setOpen_Close(open_Close);
            start += StringLengthsEnum::OPEN_CLOSE;

            const char* settlor = start;
            orderEntryRequest_.setSettlor(settlor);
            start += StringLengthsEnum::SETTLOR;

            orderEntryRequest_.setPro_ClientIndicator(_decode<int16_t>(start, end, status));

            orderEntryRequest_.setSettlementPeriod(_decode<int16_t>(start, end, status));

            const char* reserved_OER6 = start;
            orderEntryRequest_.setReserved_OER6(reserved_OER6);
            start += StringLengthsEnum::RESERVED_OER6;

            const char* pAN = start;
            orderEntryRequest_.setPAN(pAN);
            start += StringLengthsEnum::PAN;

            const char* reserved_OER7 = start;
            orderEntryRequest_.setReserved_OER7(reserved_OER7);
            start += StringLengthsEnum::RESERVED_OER7;
            if (status.getStatus() == StatusEnum::PARSING)
                status.updateStatus(StatusEnum::COMPLETE);
        }
public:
    void decode(const std::vector<char> &hexPayload, Status &status) noexcept
    {
        // Convert hexadecimal payload to binary data
        std::vector<char> payload(hexPayload.size() / 2);
        for (size_t i = 0; i < hexPayload.size(); i += 2)
        {
            payload[i / 2] = static_cast<char>(hexPairToByte(hexPayload[i], hexPayload[i + 1]));
        }
        char *start = const_cast<char *>(payload.data());
        char *end = start + payload.size();

        HandlerType handler;
        MessagesEnum messageType = static_cast<MessagesEnum>(_getType(start, end, TypeLocationEnum::MESSAGE_LOC, status));if(messageType == MessagesEnum::SIGNONREQUEST){
                    _decodeSignOnRequest(start, end, status);
                    handler(signOnRequest_, status);
                }else if(messageType == MessagesEnum::ORDERENTRYREQUEST){
                    _decodeOrderEntryRequest(start, end, status);
                    handler(orderEntryRequest_, status);
                }else
                {
                    status.updateStatus(StatusEnum::INVALID_MESSAGE_TYPE);
                    handler(status);
                }
    }

    // Decode raw binary data directly (for TCP network payloads)
    void decodeBinary(const char* data, int length, Status& status) noexcept
    {
        char *start = const_cast<char *>(data);
        char *end = start + length;

        HandlerType handler;
        MessagesEnum messageType = static_cast<MessagesEnum>(_getType(start, end, TypeLocationEnum::MESSAGE_LOC, status));if(messageType == MessagesEnum::SIGNONREQUEST){
                    _decodeSignOnRequest(start, end, status);
                    handler(signOnRequest_, status);
                }else if(messageType == MessagesEnum::ORDERENTRYREQUEST){
                    _decodeOrderEntryRequest(start, end, status);
                    handler(orderEntryRequest_, status);
                }else
                {
                    status.updateStatus(StatusEnum::INVALID_MESSAGE_TYPE);
                    handler(status);
                }
    }SignOnRequest getSignOnRequest()
        {
            return signOnRequest_;
        }OrderEntryRequest getOrderEntryRequest()
        {
            return orderEntryRequest_;
        }};

