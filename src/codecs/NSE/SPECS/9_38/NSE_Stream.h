#pragma once
#include "NSE_Msgs.h"
#include <iostream>
#include <iomanip>
#include <ostream>
#include <array>
#include <vector>




    template<size_t length>
    std::ostream& operator<<(std::ostream& os, const std::array<char, length>& arr)
    {
        
        for(size_t idx = 0; idx < arr.size(); ++idx)
        {
            os << std::setw(2) << std::setfill('0') << static_cast<int>(arr[idx]);
        }
        return os;
    }  

  

std::ostream& operator<<(std::ostream& os, const SignOnRequest& signOnRequest)
        {
            

            os << "\n TransactionCode" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(signOnRequest.getTransactionCode());
            

            os << "\n LogTime" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(signOnRequest.getLogTime());
            

            os << "\n AlphaChar" << ": " << std::setw(2) << std::setfill('0') << signOnRequest.getAlphaChar();
            

            os << "\n UserId" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(signOnRequest.getUserId());
            

            os << "\n ErrorCode" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(signOnRequest.getErrorCode());
            

            os << "\n Timestamp" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(signOnRequest.getTimestamp());
            

            os << "\n TimeStamp1" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(signOnRequest.getTimeStamp1());
            

            os << "\n TimeStamp2" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(signOnRequest.getTimeStamp2());
            

            os << "\n MessageLength" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(signOnRequest.getMessageLength());
            

            os << "\n UserId2" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(signOnRequest.getUserId2());
            

            os << "\n Reserved_SOR1" << ": " << std::setw(2) << std::setfill('0') << signOnRequest.getReserved_SOR1();
            

            os << "\n Password" << ": " << std::setw(2) << std::setfill('0') << signOnRequest.getPassword();
            

            os << "\n Reserved_SOR2" << ": " << std::setw(2) << std::setfill('0') << signOnRequest.getReserved_SOR2();
            

            os << "\n NewPassword" << ": " << std::setw(2) << std::setfill('0') << signOnRequest.getNewPassword();
            

            os << "\n TraderName" << ": " << std::setw(2) << std::setfill('0') << signOnRequest.getTraderName();
            

            os << "\n LastPasswordChangeDate" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(signOnRequest.getLastPasswordChangeDate());
            

            os << "\n BrokerId" << ": " << std::setw(2) << std::setfill('0') << signOnRequest.getBrokerId();
            

            os << "\n Reserved_SOR3" << ": " << std::setw(2) << std::setfill('0') << signOnRequest.getReserved_SOR3();
            

            os << "\n VersionNumber" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(signOnRequest.getVersionNumber());
            

            os << "\n Reserved_SOR4" << ": " << std::setw(2) << std::setfill('0') << signOnRequest.getReserved_SOR4();
            

            os << "\n WsClassName" << ": " << std::setw(2) << std::setfill('0') << signOnRequest.getWsClassName();
            

            os << "\n Reserved_SOR5" << ": " << std::setw(2) << std::setfill('0') << signOnRequest.getReserved_SOR5();
            

            os << "\n BrokerName" << ": " << std::setw(2) << std::setfill('0') << signOnRequest.getBrokerName();
            

            os << "\n ReservedEnd_SOR1" << ": " << std::setw(2) << std::setfill('0') << signOnRequest.getReservedEnd_SOR1();
            

            os << "\n ReservedEnd_SOR2" << ": " << std::setw(2) << std::setfill('0') << signOnRequest.getReservedEnd_SOR2();
            

            os << "\n ReservedEnd_SOR3" << ": " << std::setw(2) << std::setfill('0') << signOnRequest.getReservedEnd_SOR3();
            
return os;
        }std::ostream& operator<<(std::ostream& os, const OrderEntryRequest& orderEntryRequest)
        {
            

            os << "\n TransactionCode" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(orderEntryRequest.getTransactionCode());
            

            os << "\n LogTime" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(orderEntryRequest.getLogTime());
            

            os << "\n AlphaChar" << ": " << std::setw(2) << std::setfill('0') << orderEntryRequest.getAlphaChar();
            

            os << "\n UserId" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(orderEntryRequest.getUserId());
            

            os << "\n ErrorCode" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(orderEntryRequest.getErrorCode());
            

            os << "\n Timestamp" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(orderEntryRequest.getTimestamp());
            

            os << "\n TimeStamp1" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(orderEntryRequest.getTimeStamp1());
            

            os << "\n TimeStamp2" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(orderEntryRequest.getTimeStamp2());
            

            os << "\n MessageLength" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(orderEntryRequest.getMessageLength());
            

            os << "\n ParticipantType" << ": " << std::setw(2) << std::setfill('0') << orderEntryRequest.getParticipantType();
            

            os << "\n Reserved_OER1" << ": " << std::setw(2) << std::setfill('0') << orderEntryRequest.getReserved_OER1();
            

            os << "\n TokenNo" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(orderEntryRequest.getTokenNo());
            

            os << "\n InstrumentName" << ": " << std::setw(2) << std::setfill('0') << orderEntryRequest.getInstrumentName();
            

            os << "\n Symbol" << ": " << std::setw(2) << std::setfill('0') << orderEntryRequest.getSymbol();
            

            os << "\n ExpiryDate" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(orderEntryRequest.getExpiryDate());
            

            os << "\n StrikePrice" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(orderEntryRequest.getStrikePrice());
            

            os << "\n OptionType" << ": " << std::setw(2) << std::setfill('0') << orderEntryRequest.getOptionType();
            

            os << "\n CALevel" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(orderEntryRequest.getCALevel());
            

            os << "\n Reserved_OER2" << ": " << std::setw(2) << std::setfill('0') << orderEntryRequest.getReserved_OER2();
            

            os << "\n OrderType" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(orderEntryRequest.getOrderType());
            

            os << "\n OrderNumber" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(orderEntryRequest.getOrderNumber());
            

            os << "\n AccountNumber" << ": " << std::setw(2) << std::setfill('0') << orderEntryRequest.getAccountNumber();
            

            os << "\n BookType" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(orderEntryRequest.getBookType());
            

            os << "\n Buy_SellIndicator" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(orderEntryRequest.getBuy_SellIndicator());
            

            os << "\n DisclosedVolume" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(orderEntryRequest.getDisclosedVolume());
            

            os << "\n Reserved_OER3" << ": " << std::setw(2) << std::setfill('0') << orderEntryRequest.getReserved_OER3();
            

            os << "\n Volume" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(orderEntryRequest.getVolume());
            

            os << "\n Reserved_OER4" << ": " << std::setw(2) << std::setfill('0') << orderEntryRequest.getReserved_OER4();
            

            os << "\n Price" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(orderEntryRequest.getPrice());
            

            os << "\n TriggerPrice" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(orderEntryRequest.getTriggerPrice());
            

            os << "\n GoodTillDate" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(orderEntryRequest.getGoodTillDate());
            

            os << "\n Reserved_OER5" << ": " << std::setw(2) << std::setfill('0') << orderEntryRequest.getReserved_OER5();
            

            os << "\n Open_Close" << ": " << std::setw(2) << std::setfill('0') << orderEntryRequest.getOpen_Close();
            

            os << "\n Settlor" << ": " << std::setw(2) << std::setfill('0') << orderEntryRequest.getSettlor();
            

            os << "\n Pro_ClientIndicator" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(orderEntryRequest.getPro_ClientIndicator());
            

            os << "\n SettlementPeriod" << ": " << std::setw(2) << std::setfill('0') << static_cast<int>(orderEntryRequest.getSettlementPeriod());
            

            os << "\n Reserved_OER6" << ": " << std::setw(2) << std::setfill('0') << orderEntryRequest.getReserved_OER6();
            

            os << "\n PAN" << ": " << std::setw(2) << std::setfill('0') << orderEntryRequest.getPAN();
            

            os << "\n Reserved_OER7" << ": " << std::setw(2) << std::setfill('0') << orderEntryRequest.getReserved_OER7();
            
return os;
        }  

