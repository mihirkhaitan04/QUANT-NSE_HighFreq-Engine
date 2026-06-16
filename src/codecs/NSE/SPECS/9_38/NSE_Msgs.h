
#pragma once
#include <vector>
#include <array>
#include <unordered_map>
#include <cstdint>
#include <cstring>



    enum StringLengthsEnum: size_t {ALPHACHAR = 2,RESERVED_SOR1 = 8,PASSWORD = 8,RESERVED_SOR2 = 8,NEWPASSWORD = 8,TRADERNAME = 26,BROKERID = 5,RESERVED_SOR3 = 3,RESERVED_SOR4 = 66,WSCLASSNAME = 14,RESERVED_SOR5 = 7,BROKERNAME = 25,RESERVEDEND_SOR1 = 16,RESERVEDEND_SOR2 = 16,RESERVEDEND_SOR3 = 16,PARTICIPANTTYPE = 1,RESERVED_OER1 = 13,INSTRUMENTNAME = 6,SYMBOL = 10,OPTIONTYPE = 2,RESERVED_OER2 = 10,ACCOUNTNUMBER = 10,RESERVED_OER3 = 8,RESERVED_OER4 = 4,RESERVED_OER5 = 49,OPEN_CLOSE = 1,SETTLOR = 12,RESERVED_OER6 = 22,PAN = 10,RESERVED_OER7 = 66,};

enum TranscodesEnum: uint16_t {SIGN_ON_REQUEST_IN = 2300,MS_OE_REQUEST = 2000};
        
        static const std::unordered_map<uint16_t, TranscodesEnum> transcodesEnumOptions = {{ 2300, TranscodesEnum::SIGN_ON_REQUEST_IN },{ 2000, TranscodesEnum::MS_OE_REQUEST }};

class SignOnRequest {
            
                static constexpr  int16_t transactionCode_= TranscodesEnum::SIGN_ON_REQUEST_IN;int32_t logTime_;std::array<char,StringLengthsEnum::ALPHACHAR>  alphaChar_;int32_t userId_;int16_t errorCode_;int64_t timestamp_;int64_t timeStamp1_;int64_t timeStamp2_;int16_t messageLength_;int32_t userId2_;std::array<char,StringLengthsEnum::RESERVED_SOR1>  reserved_SOR1_;std::array<char,StringLengthsEnum::PASSWORD>  password_;std::array<char,StringLengthsEnum::RESERVED_SOR2>  reserved_SOR2_;std::array<char,StringLengthsEnum::NEWPASSWORD>  newPassword_;std::array<char,StringLengthsEnum::TRADERNAME>  traderName_;int32_t lastPasswordChangeDate_;std::array<char,StringLengthsEnum::BROKERID>  brokerId_;std::array<char,StringLengthsEnum::RESERVED_SOR3>  reserved_SOR3_;int32_t versionNumber_;std::array<char,StringLengthsEnum::RESERVED_SOR4>  reserved_SOR4_;std::array<char,StringLengthsEnum::WSCLASSNAME>  wsClassName_;std::array<char,StringLengthsEnum::RESERVED_SOR5>  reserved_SOR5_;std::array<char,StringLengthsEnum::BROKERNAME>  brokerName_;std::array<char,StringLengthsEnum::RESERVEDEND_SOR1>  reservedEnd_SOR1_;std::array<char,StringLengthsEnum::RESERVEDEND_SOR2>  reservedEnd_SOR2_;std::array<char,StringLengthsEnum::RESERVEDEND_SOR3>  reservedEnd_SOR3_;
        public:
            SignOnRequest(): logTime_(0), alphaChar_{}, userId_(0), errorCode_(0), timestamp_(0), timeStamp1_(0), timeStamp2_(0), messageLength_(0), userId2_(0), reserved_SOR1_{}, password_{}, reserved_SOR2_{}, newPassword_{}, traderName_{}, lastPasswordChangeDate_(0), brokerId_{}, reserved_SOR3_{}, versionNumber_(0), reserved_SOR4_{}, wsClassName_{}, reserved_SOR5_{}, brokerName_{}, reservedEnd_SOR1_{}, reservedEnd_SOR2_{}, reservedEnd_SOR3_{}{
        
    }
    SignOnRequest(int32_t logTime, const char* alphaChar, int32_t userId, int16_t errorCode, int64_t timestamp, int64_t timeStamp1, int64_t timeStamp2, int16_t messageLength, int32_t userId2, const char* reserved_SOR1, const char* password, const char* reserved_SOR2, const char* newPassword, const char* traderName, int32_t lastPasswordChangeDate, const char* brokerId, const char* reserved_SOR3, int32_t versionNumber, const char* reserved_SOR4, const char* wsClassName, const char* reserved_SOR5, const char* brokerName, const char* reservedEnd_SOR1, const char* reservedEnd_SOR2, const char* reservedEnd_SOR3):logTime_(logTime), alphaChar_(), userId_(userId), errorCode_(errorCode), timestamp_(timestamp), timeStamp1_(timeStamp1), timeStamp2_(timeStamp2), messageLength_(messageLength), userId2_(userId2), reserved_SOR1_(), password_(), reserved_SOR2_(), newPassword_(), traderName_(), lastPasswordChangeDate_(lastPasswordChangeDate), brokerId_(), reserved_SOR3_(), versionNumber_(versionNumber), reserved_SOR4_(), wsClassName_(), reserved_SOR5_(), brokerName_(), reservedEnd_SOR1_(), reservedEnd_SOR2_(), reservedEnd_SOR3_() {
        std::memcpy(alphaChar_.data(), alphaChar, StringLengthsEnum::ALPHACHAR);std::memcpy(reserved_SOR1_.data(), reserved_SOR1, StringLengthsEnum::RESERVED_SOR1);std::memcpy(password_.data(), password, StringLengthsEnum::PASSWORD);std::memcpy(reserved_SOR2_.data(), reserved_SOR2, StringLengthsEnum::RESERVED_SOR2);std::memcpy(newPassword_.data(), newPassword, StringLengthsEnum::NEWPASSWORD);std::memcpy(traderName_.data(), traderName, StringLengthsEnum::TRADERNAME);std::memcpy(brokerId_.data(), brokerId, StringLengthsEnum::BROKERID);std::memcpy(reserved_SOR3_.data(), reserved_SOR3, StringLengthsEnum::RESERVED_SOR3);std::memcpy(reserved_SOR4_.data(), reserved_SOR4, StringLengthsEnum::RESERVED_SOR4);std::memcpy(wsClassName_.data(), wsClassName, StringLengthsEnum::WSCLASSNAME);std::memcpy(reserved_SOR5_.data(), reserved_SOR5, StringLengthsEnum::RESERVED_SOR5);std::memcpy(brokerName_.data(), brokerName, StringLengthsEnum::BROKERNAME);std::memcpy(reservedEnd_SOR1_.data(), reservedEnd_SOR1, StringLengthsEnum::RESERVEDEND_SOR1);std::memcpy(reservedEnd_SOR2_.data(), reservedEnd_SOR2, StringLengthsEnum::RESERVEDEND_SOR2);std::memcpy(reservedEnd_SOR3_.data(), reservedEnd_SOR3, StringLengthsEnum::RESERVEDEND_SOR3);}
            
    void reset(){logTime_ = 0;alphaChar_.fill('0');userId_ = 0;errorCode_ = 0;timestamp_ = 0;timeStamp1_ = 0;timeStamp2_ = 0;messageLength_ = 0;userId2_ = 0;reserved_SOR1_.fill('0');password_.fill('0');reserved_SOR2_.fill('0');newPassword_.fill('0');traderName_.fill('0');lastPasswordChangeDate_ = 0;brokerId_.fill('0');reserved_SOR3_.fill('0');versionNumber_ = 0;reserved_SOR4_.fill('0');wsClassName_.fill('0');reserved_SOR5_.fill('0');brokerName_.fill('0');reservedEnd_SOR1_.fill('0');reservedEnd_SOR2_.fill('0');reservedEnd_SOR3_.fill('0');}
            

        
            inline const int16_t getTransactionCode() const noexcept {return transactionCode_;}
            inline int16_t getTransactionCodeCopy() const noexcept {return transactionCode_;}

        
            inline const int32_t& getLogTime() const noexcept {return logTime_;}
            inline int32_t& getLogTimeRef() noexcept {return logTime_;}
            inline int32_t getLogTimeCopy() const noexcept {return logTime_;}
            inline void setLogTime(int32_t logTime) noexcept { logTime_ = logTime;}

        
            inline const std::array<char, StringLengthsEnum::ALPHACHAR>& getAlphaChar() const noexcept { return alphaChar_; }
            inline std::array<char, StringLengthsEnum::ALPHACHAR>& getAlphaCharRef() noexcept { return alphaChar_; }
            inline std::array<char, StringLengthsEnum::ALPHACHAR> getAlphaCharCopy() const noexcept { return alphaChar_; }
            inline void setAlphaChar(const char* alphaChar) noexcept {
                
                std::size_t length = std::min<std::size_t>(StringLengthsEnum::ALPHACHAR, std::strlen(alphaChar));
                std::memcpy(alphaChar_.data(), alphaChar, length);
                for(size_t i = length; i < StringLengthsEnum::ALPHACHAR; ++i ){ alphaChar_[i] = 0;}
            }

        
            inline const int32_t& getUserId() const noexcept {return userId_;}
            inline int32_t& getUserIdRef() noexcept {return userId_;}
            inline int32_t getUserIdCopy() const noexcept {return userId_;}
            inline void setUserId(int32_t userId) noexcept { userId_ = userId;}

        
            inline const int16_t& getErrorCode() const noexcept {return errorCode_;}
            inline int16_t& getErrorCodeRef() noexcept {return errorCode_;}
            inline int16_t getErrorCodeCopy() const noexcept {return errorCode_;}
            inline void setErrorCode(int16_t errorCode) noexcept { errorCode_ = errorCode;}

        
            inline const int64_t& getTimestamp() const noexcept {return timestamp_;}
            inline int64_t& getTimestampRef() noexcept {return timestamp_;}
            inline int64_t getTimestampCopy() const noexcept {return timestamp_;}
            inline void setTimestamp(int64_t timestamp) noexcept { timestamp_ = timestamp;}

        
            inline const int64_t& getTimeStamp1() const noexcept {return timeStamp1_;}
            inline int64_t& getTimeStamp1Ref() noexcept {return timeStamp1_;}
            inline int64_t getTimeStamp1Copy() const noexcept {return timeStamp1_;}
            inline void setTimeStamp1(int64_t timeStamp1) noexcept { timeStamp1_ = timeStamp1;}

        
            inline const int64_t& getTimeStamp2() const noexcept {return timeStamp2_;}
            inline int64_t& getTimeStamp2Ref() noexcept {return timeStamp2_;}
            inline int64_t getTimeStamp2Copy() const noexcept {return timeStamp2_;}
            inline void setTimeStamp2(int64_t timeStamp2) noexcept { timeStamp2_ = timeStamp2;}

        
            inline const int16_t& getMessageLength() const noexcept {return messageLength_;}
            inline int16_t& getMessageLengthRef() noexcept {return messageLength_;}
            inline int16_t getMessageLengthCopy() const noexcept {return messageLength_;}
            inline void setMessageLength(int16_t messageLength) noexcept { messageLength_ = messageLength;}

        
            inline const int32_t& getUserId2() const noexcept {return userId2_;}
            inline int32_t& getUserId2Ref() noexcept {return userId2_;}
            inline int32_t getUserId2Copy() const noexcept {return userId2_;}
            inline void setUserId2(int32_t userId2) noexcept { userId2_ = userId2;}

        
            inline const std::array<char, StringLengthsEnum::RESERVED_SOR1>& getReserved_SOR1() const noexcept { return reserved_SOR1_; }
            inline std::array<char, StringLengthsEnum::RESERVED_SOR1>& getReserved_SOR1Ref() noexcept { return reserved_SOR1_; }
            inline std::array<char, StringLengthsEnum::RESERVED_SOR1> getReserved_SOR1Copy() const noexcept { return reserved_SOR1_; }
            inline void setReserved_SOR1(const char* reserved_SOR1) noexcept {
                
                std::size_t length = std::min<std::size_t>(StringLengthsEnum::RESERVED_SOR1, std::strlen(reserved_SOR1));
                std::memcpy(reserved_SOR1_.data(), reserved_SOR1, length);
                for(size_t i = length; i < StringLengthsEnum::RESERVED_SOR1; ++i ){ reserved_SOR1_[i] = 0;}
            }

        
            inline const std::array<char, StringLengthsEnum::PASSWORD>& getPassword() const noexcept { return password_; }
            inline std::array<char, StringLengthsEnum::PASSWORD>& getPasswordRef() noexcept { return password_; }
            inline std::array<char, StringLengthsEnum::PASSWORD> getPasswordCopy() const noexcept { return password_; }
            inline void setPassword(const char* password) noexcept {
                
                std::size_t length = std::min<std::size_t>(StringLengthsEnum::PASSWORD, std::strlen(password));
                std::memcpy(password_.data(), password, length);
                for(size_t i = length; i < StringLengthsEnum::PASSWORD; ++i ){ password_[i] = 0;}
            }

        
            inline const std::array<char, StringLengthsEnum::RESERVED_SOR2>& getReserved_SOR2() const noexcept { return reserved_SOR2_; }
            inline std::array<char, StringLengthsEnum::RESERVED_SOR2>& getReserved_SOR2Ref() noexcept { return reserved_SOR2_; }
            inline std::array<char, StringLengthsEnum::RESERVED_SOR2> getReserved_SOR2Copy() const noexcept { return reserved_SOR2_; }
            inline void setReserved_SOR2(const char* reserved_SOR2) noexcept {
                
                std::size_t length = std::min<std::size_t>(StringLengthsEnum::RESERVED_SOR2, std::strlen(reserved_SOR2));
                std::memcpy(reserved_SOR2_.data(), reserved_SOR2, length);
                for(size_t i = length; i < StringLengthsEnum::RESERVED_SOR2; ++i ){ reserved_SOR2_[i] = 0;}
            }

        
            inline const std::array<char, StringLengthsEnum::NEWPASSWORD>& getNewPassword() const noexcept { return newPassword_; }
            inline std::array<char, StringLengthsEnum::NEWPASSWORD>& getNewPasswordRef() noexcept { return newPassword_; }
            inline std::array<char, StringLengthsEnum::NEWPASSWORD> getNewPasswordCopy() const noexcept { return newPassword_; }
            inline void setNewPassword(const char* newPassword) noexcept {
                
                std::size_t length = std::min<std::size_t>(StringLengthsEnum::NEWPASSWORD, std::strlen(newPassword));
                std::memcpy(newPassword_.data(), newPassword, length);
                for(size_t i = length; i < StringLengthsEnum::NEWPASSWORD; ++i ){ newPassword_[i] = 0;}
            }

        
            inline const std::array<char, StringLengthsEnum::TRADERNAME>& getTraderName() const noexcept { return traderName_; }
            inline std::array<char, StringLengthsEnum::TRADERNAME>& getTraderNameRef() noexcept { return traderName_; }
            inline std::array<char, StringLengthsEnum::TRADERNAME> getTraderNameCopy() const noexcept { return traderName_; }
            inline void setTraderName(const char* traderName) noexcept {
                
                std::size_t length = std::min<std::size_t>(StringLengthsEnum::TRADERNAME, std::strlen(traderName));
                std::memcpy(traderName_.data(), traderName, length);
                for(size_t i = length; i < StringLengthsEnum::TRADERNAME; ++i ){ traderName_[i] = 0;}
            }

        
            inline const int32_t& getLastPasswordChangeDate() const noexcept {return lastPasswordChangeDate_;}
            inline int32_t& getLastPasswordChangeDateRef() noexcept {return lastPasswordChangeDate_;}
            inline int32_t getLastPasswordChangeDateCopy() const noexcept {return lastPasswordChangeDate_;}
            inline void setLastPasswordChangeDate(int32_t lastPasswordChangeDate) noexcept { lastPasswordChangeDate_ = lastPasswordChangeDate;}

        
            inline const std::array<char, StringLengthsEnum::BROKERID>& getBrokerId() const noexcept { return brokerId_; }
            inline std::array<char, StringLengthsEnum::BROKERID>& getBrokerIdRef() noexcept { return brokerId_; }
            inline std::array<char, StringLengthsEnum::BROKERID> getBrokerIdCopy() const noexcept { return brokerId_; }
            inline void setBrokerId(const char* brokerId) noexcept {
                
                std::size_t length = std::min<std::size_t>(StringLengthsEnum::BROKERID, std::strlen(brokerId));
                std::memcpy(brokerId_.data(), brokerId, length);
                for(size_t i = length; i < StringLengthsEnum::BROKERID; ++i ){ brokerId_[i] = 0;}
            }

        
            inline const std::array<char, StringLengthsEnum::RESERVED_SOR3>& getReserved_SOR3() const noexcept { return reserved_SOR3_; }
            inline std::array<char, StringLengthsEnum::RESERVED_SOR3>& getReserved_SOR3Ref() noexcept { return reserved_SOR3_; }
            inline std::array<char, StringLengthsEnum::RESERVED_SOR3> getReserved_SOR3Copy() const noexcept { return reserved_SOR3_; }
            inline void setReserved_SOR3(const char* reserved_SOR3) noexcept {
                
                std::size_t length = std::min<std::size_t>(StringLengthsEnum::RESERVED_SOR3, std::strlen(reserved_SOR3));
                std::memcpy(reserved_SOR3_.data(), reserved_SOR3, length);
                for(size_t i = length; i < StringLengthsEnum::RESERVED_SOR3; ++i ){ reserved_SOR3_[i] = 0;}
            }

        
            inline const int32_t& getVersionNumber() const noexcept {return versionNumber_;}
            inline int32_t& getVersionNumberRef() noexcept {return versionNumber_;}
            inline int32_t getVersionNumberCopy() const noexcept {return versionNumber_;}
            inline void setVersionNumber(int32_t versionNumber) noexcept { versionNumber_ = versionNumber;}

        
            inline const std::array<char, StringLengthsEnum::RESERVED_SOR4>& getReserved_SOR4() const noexcept { return reserved_SOR4_; }
            inline std::array<char, StringLengthsEnum::RESERVED_SOR4>& getReserved_SOR4Ref() noexcept { return reserved_SOR4_; }
            inline std::array<char, StringLengthsEnum::RESERVED_SOR4> getReserved_SOR4Copy() const noexcept { return reserved_SOR4_; }
            inline void setReserved_SOR4(const char* reserved_SOR4) noexcept {
                
                std::size_t length = std::min<std::size_t>(StringLengthsEnum::RESERVED_SOR4, std::strlen(reserved_SOR4));
                std::memcpy(reserved_SOR4_.data(), reserved_SOR4, length);
                for(size_t i = length; i < StringLengthsEnum::RESERVED_SOR4; ++i ){ reserved_SOR4_[i] = 0;}
            }

        
            inline const std::array<char, StringLengthsEnum::WSCLASSNAME>& getWsClassName() const noexcept { return wsClassName_; }
            inline std::array<char, StringLengthsEnum::WSCLASSNAME>& getWsClassNameRef() noexcept { return wsClassName_; }
            inline std::array<char, StringLengthsEnum::WSCLASSNAME> getWsClassNameCopy() const noexcept { return wsClassName_; }
            inline void setWsClassName(const char* wsClassName) noexcept {
                
                std::size_t length = std::min<std::size_t>(StringLengthsEnum::WSCLASSNAME, std::strlen(wsClassName));
                std::memcpy(wsClassName_.data(), wsClassName, length);
                for(size_t i = length; i < StringLengthsEnum::WSCLASSNAME; ++i ){ wsClassName_[i] = 0;}
            }

        
            inline const std::array<char, StringLengthsEnum::RESERVED_SOR5>& getReserved_SOR5() const noexcept { return reserved_SOR5_; }
            inline std::array<char, StringLengthsEnum::RESERVED_SOR5>& getReserved_SOR5Ref() noexcept { return reserved_SOR5_; }
            inline std::array<char, StringLengthsEnum::RESERVED_SOR5> getReserved_SOR5Copy() const noexcept { return reserved_SOR5_; }
            inline void setReserved_SOR5(const char* reserved_SOR5) noexcept {
                
                std::size_t length = std::min<std::size_t>(StringLengthsEnum::RESERVED_SOR5, std::strlen(reserved_SOR5));
                std::memcpy(reserved_SOR5_.data(), reserved_SOR5, length);
                for(size_t i = length; i < StringLengthsEnum::RESERVED_SOR5; ++i ){ reserved_SOR5_[i] = 0;}
            }

        
            inline const std::array<char, StringLengthsEnum::BROKERNAME>& getBrokerName() const noexcept { return brokerName_; }
            inline std::array<char, StringLengthsEnum::BROKERNAME>& getBrokerNameRef() noexcept { return brokerName_; }
            inline std::array<char, StringLengthsEnum::BROKERNAME> getBrokerNameCopy() const noexcept { return brokerName_; }
            inline void setBrokerName(const char* brokerName) noexcept {
                
                std::size_t length = std::min<std::size_t>(StringLengthsEnum::BROKERNAME, std::strlen(brokerName));
                std::memcpy(brokerName_.data(), brokerName, length);
                for(size_t i = length; i < StringLengthsEnum::BROKERNAME; ++i ){ brokerName_[i] = 0;}
            }

        
            inline const std::array<char, StringLengthsEnum::RESERVEDEND_SOR1>& getReservedEnd_SOR1() const noexcept { return reservedEnd_SOR1_; }
            inline std::array<char, StringLengthsEnum::RESERVEDEND_SOR1>& getReservedEnd_SOR1Ref() noexcept { return reservedEnd_SOR1_; }
            inline std::array<char, StringLengthsEnum::RESERVEDEND_SOR1> getReservedEnd_SOR1Copy() const noexcept { return reservedEnd_SOR1_; }
            inline void setReservedEnd_SOR1(const char* reservedEnd_SOR1) noexcept {
                
                std::size_t length = std::min<std::size_t>(StringLengthsEnum::RESERVEDEND_SOR1, std::strlen(reservedEnd_SOR1));
                std::memcpy(reservedEnd_SOR1_.data(), reservedEnd_SOR1, length);
                for(size_t i = length; i < StringLengthsEnum::RESERVEDEND_SOR1; ++i ){ reservedEnd_SOR1_[i] = 0;}
            }

        
            inline const std::array<char, StringLengthsEnum::RESERVEDEND_SOR2>& getReservedEnd_SOR2() const noexcept { return reservedEnd_SOR2_; }
            inline std::array<char, StringLengthsEnum::RESERVEDEND_SOR2>& getReservedEnd_SOR2Ref() noexcept { return reservedEnd_SOR2_; }
            inline std::array<char, StringLengthsEnum::RESERVEDEND_SOR2> getReservedEnd_SOR2Copy() const noexcept { return reservedEnd_SOR2_; }
            inline void setReservedEnd_SOR2(const char* reservedEnd_SOR2) noexcept {
                
                std::size_t length = std::min<std::size_t>(StringLengthsEnum::RESERVEDEND_SOR2, std::strlen(reservedEnd_SOR2));
                std::memcpy(reservedEnd_SOR2_.data(), reservedEnd_SOR2, length);
                for(size_t i = length; i < StringLengthsEnum::RESERVEDEND_SOR2; ++i ){ reservedEnd_SOR2_[i] = 0;}
            }

        
            inline const std::array<char, StringLengthsEnum::RESERVEDEND_SOR3>& getReservedEnd_SOR3() const noexcept { return reservedEnd_SOR3_; }
            inline std::array<char, StringLengthsEnum::RESERVEDEND_SOR3>& getReservedEnd_SOR3Ref() noexcept { return reservedEnd_SOR3_; }
            inline std::array<char, StringLengthsEnum::RESERVEDEND_SOR3> getReservedEnd_SOR3Copy() const noexcept { return reservedEnd_SOR3_; }
            inline void setReservedEnd_SOR3(const char* reservedEnd_SOR3) noexcept {
                
                std::size_t length = std::min<std::size_t>(StringLengthsEnum::RESERVEDEND_SOR3, std::strlen(reservedEnd_SOR3));
                std::memcpy(reservedEnd_SOR3_.data(), reservedEnd_SOR3, length);
                for(size_t i = length; i < StringLengthsEnum::RESERVEDEND_SOR3; ++i ){ reservedEnd_SOR3_[i] = 0;}
            }
        }; 
        class OrderEntryRequest {
            
                static constexpr  int16_t transactionCode_= TranscodesEnum::MS_OE_REQUEST;int32_t logTime_;std::array<char,StringLengthsEnum::ALPHACHAR>  alphaChar_;int32_t userId_;int16_t errorCode_;int64_t timestamp_;int64_t timeStamp1_;int64_t timeStamp2_;int16_t messageLength_;std::array<char,StringLengthsEnum::PARTICIPANTTYPE>  participantType_;std::array<char,StringLengthsEnum::RESERVED_OER1>  reserved_OER1_;int32_t tokenNo_;std::array<char,StringLengthsEnum::INSTRUMENTNAME>  instrumentName_;std::array<char,StringLengthsEnum::SYMBOL>  symbol_;int32_t expiryDate_;int32_t strikePrice_;std::array<char,StringLengthsEnum::OPTIONTYPE>  optionType_;int16_t cALevel_;std::array<char,StringLengthsEnum::RESERVED_OER2>  reserved_OER2_;int16_t orderType_;int64_t orderNumber_;std::array<char,StringLengthsEnum::ACCOUNTNUMBER>  accountNumber_;int16_t bookType_;int16_t buy_SellIndicator_;int32_t disclosedVolume_;std::array<char,StringLengthsEnum::RESERVED_OER3>  reserved_OER3_;int32_t volume_;std::array<char,StringLengthsEnum::RESERVED_OER4>  reserved_OER4_;int32_t price_;int32_t triggerPrice_;int32_t goodTillDate_;std::array<char,StringLengthsEnum::RESERVED_OER5>  reserved_OER5_;std::array<char,StringLengthsEnum::OPEN_CLOSE>  open_Close_;std::array<char,StringLengthsEnum::SETTLOR>  settlor_;int16_t pro_ClientIndicator_;int16_t settlementPeriod_;std::array<char,StringLengthsEnum::RESERVED_OER6>  reserved_OER6_;std::array<char,StringLengthsEnum::PAN>  pAN_;std::array<char,StringLengthsEnum::RESERVED_OER7>  reserved_OER7_;
        public:
            OrderEntryRequest(): logTime_(0), alphaChar_{}, userId_(0), errorCode_(0), timestamp_(0), timeStamp1_(0), timeStamp2_(0), messageLength_(0), participantType_{}, reserved_OER1_{}, tokenNo_(0), instrumentName_{}, symbol_{}, expiryDate_(0), strikePrice_(0), optionType_{}, cALevel_(0), reserved_OER2_{}, orderType_(0), orderNumber_(0), accountNumber_{}, bookType_(0), buy_SellIndicator_(0), disclosedVolume_(0), reserved_OER3_{}, volume_(0), reserved_OER4_{}, price_(0), triggerPrice_(0), goodTillDate_(0), reserved_OER5_{}, open_Close_{}, settlor_{}, pro_ClientIndicator_(0), settlementPeriod_(0), reserved_OER6_{}, pAN_{}, reserved_OER7_{}{
        
    }
    OrderEntryRequest(int32_t logTime, const char* alphaChar, int32_t userId, int16_t errorCode, int64_t timestamp, int64_t timeStamp1, int64_t timeStamp2, int16_t messageLength, const char* participantType, const char* reserved_OER1, int32_t tokenNo, const char* instrumentName, const char* symbol, int32_t expiryDate, int32_t strikePrice, const char* optionType, int16_t cALevel, const char* reserved_OER2, int16_t orderType, int64_t orderNumber, const char* accountNumber, int16_t bookType, int16_t buy_SellIndicator, int32_t disclosedVolume, const char* reserved_OER3, int32_t volume, const char* reserved_OER4, int32_t price, int32_t triggerPrice, int32_t goodTillDate, const char* reserved_OER5, const char* open_Close, const char* settlor, int16_t pro_ClientIndicator, int16_t settlementPeriod, const char* reserved_OER6, const char* pAN, const char* reserved_OER7):logTime_(logTime), alphaChar_(), userId_(userId), errorCode_(errorCode), timestamp_(timestamp), timeStamp1_(timeStamp1), timeStamp2_(timeStamp2), messageLength_(messageLength), participantType_(), reserved_OER1_(), tokenNo_(tokenNo), instrumentName_(), symbol_(), expiryDate_(expiryDate), strikePrice_(strikePrice), optionType_(), cALevel_(cALevel), reserved_OER2_(), orderType_(orderType), orderNumber_(orderNumber), accountNumber_(), bookType_(bookType), buy_SellIndicator_(buy_SellIndicator), disclosedVolume_(disclosedVolume), reserved_OER3_(), volume_(volume), reserved_OER4_(), price_(price), triggerPrice_(triggerPrice), goodTillDate_(goodTillDate), reserved_OER5_(), open_Close_(), settlor_(), pro_ClientIndicator_(pro_ClientIndicator), settlementPeriod_(settlementPeriod), reserved_OER6_(), pAN_(), reserved_OER7_() {
        std::memcpy(alphaChar_.data(), alphaChar, StringLengthsEnum::ALPHACHAR);std::memcpy(participantType_.data(), participantType, StringLengthsEnum::PARTICIPANTTYPE);std::memcpy(reserved_OER1_.data(), reserved_OER1, StringLengthsEnum::RESERVED_OER1);std::memcpy(instrumentName_.data(), instrumentName, StringLengthsEnum::INSTRUMENTNAME);std::memcpy(symbol_.data(), symbol, StringLengthsEnum::SYMBOL);std::memcpy(optionType_.data(), optionType, StringLengthsEnum::OPTIONTYPE);std::memcpy(reserved_OER2_.data(), reserved_OER2, StringLengthsEnum::RESERVED_OER2);std::memcpy(accountNumber_.data(), accountNumber, StringLengthsEnum::ACCOUNTNUMBER);std::memcpy(reserved_OER3_.data(), reserved_OER3, StringLengthsEnum::RESERVED_OER3);std::memcpy(reserved_OER4_.data(), reserved_OER4, StringLengthsEnum::RESERVED_OER4);std::memcpy(reserved_OER5_.data(), reserved_OER5, StringLengthsEnum::RESERVED_OER5);std::memcpy(open_Close_.data(), open_Close, StringLengthsEnum::OPEN_CLOSE);std::memcpy(settlor_.data(), settlor, StringLengthsEnum::SETTLOR);std::memcpy(reserved_OER6_.data(), reserved_OER6, StringLengthsEnum::RESERVED_OER6);std::memcpy(pAN_.data(), pAN, StringLengthsEnum::PAN);std::memcpy(reserved_OER7_.data(), reserved_OER7, StringLengthsEnum::RESERVED_OER7);}
            
    void reset(){logTime_ = 0;alphaChar_.fill('0');userId_ = 0;errorCode_ = 0;timestamp_ = 0;timeStamp1_ = 0;timeStamp2_ = 0;messageLength_ = 0;participantType_.fill('0');reserved_OER1_.fill('0');tokenNo_ = 0;instrumentName_.fill('0');symbol_.fill('0');expiryDate_ = 0;strikePrice_ = 0;optionType_.fill('0');cALevel_ = 0;reserved_OER2_.fill('0');orderType_ = 0;orderNumber_ = 0;accountNumber_.fill('0');bookType_ = 0;buy_SellIndicator_ = 0;disclosedVolume_ = 0;reserved_OER3_.fill('0');volume_ = 0;reserved_OER4_.fill('0');price_ = 0;triggerPrice_ = 0;goodTillDate_ = 0;reserved_OER5_.fill('0');open_Close_.fill('0');settlor_.fill('0');pro_ClientIndicator_ = 0;settlementPeriod_ = 0;reserved_OER6_.fill('0');pAN_.fill('0');reserved_OER7_.fill('0');}
            

        
            inline const int16_t getTransactionCode() const noexcept {return transactionCode_;}
            inline int16_t getTransactionCodeCopy() const noexcept {return transactionCode_;}

        
            inline const int32_t& getLogTime() const noexcept {return logTime_;}
            inline int32_t& getLogTimeRef() noexcept {return logTime_;}
            inline int32_t getLogTimeCopy() const noexcept {return logTime_;}
            inline void setLogTime(int32_t logTime) noexcept { logTime_ = logTime;}

        
            inline const std::array<char, StringLengthsEnum::ALPHACHAR>& getAlphaChar() const noexcept { return alphaChar_; }
            inline std::array<char, StringLengthsEnum::ALPHACHAR>& getAlphaCharRef() noexcept { return alphaChar_; }
            inline std::array<char, StringLengthsEnum::ALPHACHAR> getAlphaCharCopy() const noexcept { return alphaChar_; }
            inline void setAlphaChar(const char* alphaChar) noexcept {
                
                std::size_t length = std::min<std::size_t>(StringLengthsEnum::ALPHACHAR, std::strlen(alphaChar));
                std::memcpy(alphaChar_.data(), alphaChar, length);
                for(size_t i = length; i < StringLengthsEnum::ALPHACHAR; ++i ){ alphaChar_[i] = 0;}
            }

        
            inline const int32_t& getUserId() const noexcept {return userId_;}
            inline int32_t& getUserIdRef() noexcept {return userId_;}
            inline int32_t getUserIdCopy() const noexcept {return userId_;}
            inline void setUserId(int32_t userId) noexcept { userId_ = userId;}

        
            inline const int16_t& getErrorCode() const noexcept {return errorCode_;}
            inline int16_t& getErrorCodeRef() noexcept {return errorCode_;}
            inline int16_t getErrorCodeCopy() const noexcept {return errorCode_;}
            inline void setErrorCode(int16_t errorCode) noexcept { errorCode_ = errorCode;}

        
            inline const int64_t& getTimestamp() const noexcept {return timestamp_;}
            inline int64_t& getTimestampRef() noexcept {return timestamp_;}
            inline int64_t getTimestampCopy() const noexcept {return timestamp_;}
            inline void setTimestamp(int64_t timestamp) noexcept { timestamp_ = timestamp;}

        
            inline const int64_t& getTimeStamp1() const noexcept {return timeStamp1_;}
            inline int64_t& getTimeStamp1Ref() noexcept {return timeStamp1_;}
            inline int64_t getTimeStamp1Copy() const noexcept {return timeStamp1_;}
            inline void setTimeStamp1(int64_t timeStamp1) noexcept { timeStamp1_ = timeStamp1;}

        
            inline const int64_t& getTimeStamp2() const noexcept {return timeStamp2_;}
            inline int64_t& getTimeStamp2Ref() noexcept {return timeStamp2_;}
            inline int64_t getTimeStamp2Copy() const noexcept {return timeStamp2_;}
            inline void setTimeStamp2(int64_t timeStamp2) noexcept { timeStamp2_ = timeStamp2;}

        
            inline const int16_t& getMessageLength() const noexcept {return messageLength_;}
            inline int16_t& getMessageLengthRef() noexcept {return messageLength_;}
            inline int16_t getMessageLengthCopy() const noexcept {return messageLength_;}
            inline void setMessageLength(int16_t messageLength) noexcept { messageLength_ = messageLength;}

        
            inline const std::array<char, StringLengthsEnum::PARTICIPANTTYPE>& getParticipantType() const noexcept { return participantType_; }
            inline std::array<char, StringLengthsEnum::PARTICIPANTTYPE>& getParticipantTypeRef() noexcept { return participantType_; }
            inline std::array<char, StringLengthsEnum::PARTICIPANTTYPE> getParticipantTypeCopy() const noexcept { return participantType_; }
            inline void setParticipantType(const char* participantType) noexcept {
                
                std::size_t length = std::min<std::size_t>(StringLengthsEnum::PARTICIPANTTYPE, std::strlen(participantType));
                std::memcpy(participantType_.data(), participantType, length);
                for(size_t i = length; i < StringLengthsEnum::PARTICIPANTTYPE; ++i ){ participantType_[i] = 0;}
            }

        
            inline const std::array<char, StringLengthsEnum::RESERVED_OER1>& getReserved_OER1() const noexcept { return reserved_OER1_; }
            inline std::array<char, StringLengthsEnum::RESERVED_OER1>& getReserved_OER1Ref() noexcept { return reserved_OER1_; }
            inline std::array<char, StringLengthsEnum::RESERVED_OER1> getReserved_OER1Copy() const noexcept { return reserved_OER1_; }
            inline void setReserved_OER1(const char* reserved_OER1) noexcept {
                
                std::size_t length = std::min<std::size_t>(StringLengthsEnum::RESERVED_OER1, std::strlen(reserved_OER1));
                std::memcpy(reserved_OER1_.data(), reserved_OER1, length);
                for(size_t i = length; i < StringLengthsEnum::RESERVED_OER1; ++i ){ reserved_OER1_[i] = 0;}
            }

        
            inline const int32_t& getTokenNo() const noexcept {return tokenNo_;}
            inline int32_t& getTokenNoRef() noexcept {return tokenNo_;}
            inline int32_t getTokenNoCopy() const noexcept {return tokenNo_;}
            inline void setTokenNo(int32_t tokenNo) noexcept { tokenNo_ = tokenNo;}

        
            inline const std::array<char, StringLengthsEnum::INSTRUMENTNAME>& getInstrumentName() const noexcept { return instrumentName_; }
            inline std::array<char, StringLengthsEnum::INSTRUMENTNAME>& getInstrumentNameRef() noexcept { return instrumentName_; }
            inline std::array<char, StringLengthsEnum::INSTRUMENTNAME> getInstrumentNameCopy() const noexcept { return instrumentName_; }
            inline void setInstrumentName(const char* instrumentName) noexcept {
                
                std::size_t length = std::min<std::size_t>(StringLengthsEnum::INSTRUMENTNAME, std::strlen(instrumentName));
                std::memcpy(instrumentName_.data(), instrumentName, length);
                for(size_t i = length; i < StringLengthsEnum::INSTRUMENTNAME; ++i ){ instrumentName_[i] = 0;}
            }

        
            inline const std::array<char, StringLengthsEnum::SYMBOL>& getSymbol() const noexcept { return symbol_; }
            inline std::array<char, StringLengthsEnum::SYMBOL>& getSymbolRef() noexcept { return symbol_; }
            inline std::array<char, StringLengthsEnum::SYMBOL> getSymbolCopy() const noexcept { return symbol_; }
            inline void setSymbol(const char* symbol) noexcept {
                
                std::size_t length = std::min<std::size_t>(StringLengthsEnum::SYMBOL, std::strlen(symbol));
                std::memcpy(symbol_.data(), symbol, length);
                for(size_t i = length; i < StringLengthsEnum::SYMBOL; ++i ){ symbol_[i] = 0;}
            }

        
            inline const int32_t& getExpiryDate() const noexcept {return expiryDate_;}
            inline int32_t& getExpiryDateRef() noexcept {return expiryDate_;}
            inline int32_t getExpiryDateCopy() const noexcept {return expiryDate_;}
            inline void setExpiryDate(int32_t expiryDate) noexcept { expiryDate_ = expiryDate;}

        
            inline const int32_t& getStrikePrice() const noexcept {return strikePrice_;}
            inline int32_t& getStrikePriceRef() noexcept {return strikePrice_;}
            inline int32_t getStrikePriceCopy() const noexcept {return strikePrice_;}
            inline void setStrikePrice(int32_t strikePrice) noexcept { strikePrice_ = strikePrice;}

        
            inline const std::array<char, StringLengthsEnum::OPTIONTYPE>& getOptionType() const noexcept { return optionType_; }
            inline std::array<char, StringLengthsEnum::OPTIONTYPE>& getOptionTypeRef() noexcept { return optionType_; }
            inline std::array<char, StringLengthsEnum::OPTIONTYPE> getOptionTypeCopy() const noexcept { return optionType_; }
            inline void setOptionType(const char* optionType) noexcept {
                
                std::size_t length = std::min<std::size_t>(StringLengthsEnum::OPTIONTYPE, std::strlen(optionType));
                std::memcpy(optionType_.data(), optionType, length);
                for(size_t i = length; i < StringLengthsEnum::OPTIONTYPE; ++i ){ optionType_[i] = 0;}
            }

        
            inline const int16_t& getCALevel() const noexcept {return cALevel_;}
            inline int16_t& getCALevelRef() noexcept {return cALevel_;}
            inline int16_t getCALevelCopy() const noexcept {return cALevel_;}
            inline void setCALevel(int16_t cALevel) noexcept { cALevel_ = cALevel;}

        
            inline const std::array<char, StringLengthsEnum::RESERVED_OER2>& getReserved_OER2() const noexcept { return reserved_OER2_; }
            inline std::array<char, StringLengthsEnum::RESERVED_OER2>& getReserved_OER2Ref() noexcept { return reserved_OER2_; }
            inline std::array<char, StringLengthsEnum::RESERVED_OER2> getReserved_OER2Copy() const noexcept { return reserved_OER2_; }
            inline void setReserved_OER2(const char* reserved_OER2) noexcept {
                
                std::size_t length = std::min<std::size_t>(StringLengthsEnum::RESERVED_OER2, std::strlen(reserved_OER2));
                std::memcpy(reserved_OER2_.data(), reserved_OER2, length);
                for(size_t i = length; i < StringLengthsEnum::RESERVED_OER2; ++i ){ reserved_OER2_[i] = 0;}
            }

        
            inline const int16_t& getOrderType() const noexcept {return orderType_;}
            inline int16_t& getOrderTypeRef() noexcept {return orderType_;}
            inline int16_t getOrderTypeCopy() const noexcept {return orderType_;}
            inline void setOrderType(int16_t orderType) noexcept { orderType_ = orderType;}

        
            inline const int64_t& getOrderNumber() const noexcept {return orderNumber_;}
            inline int64_t& getOrderNumberRef() noexcept {return orderNumber_;}
            inline int64_t getOrderNumberCopy() const noexcept {return orderNumber_;}
            inline void setOrderNumber(int64_t orderNumber) noexcept { orderNumber_ = orderNumber;}

        
            inline const std::array<char, StringLengthsEnum::ACCOUNTNUMBER>& getAccountNumber() const noexcept { return accountNumber_; }
            inline std::array<char, StringLengthsEnum::ACCOUNTNUMBER>& getAccountNumberRef() noexcept { return accountNumber_; }
            inline std::array<char, StringLengthsEnum::ACCOUNTNUMBER> getAccountNumberCopy() const noexcept { return accountNumber_; }
            inline void setAccountNumber(const char* accountNumber) noexcept {
                
                std::size_t length = std::min<std::size_t>(StringLengthsEnum::ACCOUNTNUMBER, std::strlen(accountNumber));
                std::memcpy(accountNumber_.data(), accountNumber, length);
                for(size_t i = length; i < StringLengthsEnum::ACCOUNTNUMBER; ++i ){ accountNumber_[i] = 0;}
            }

        
            inline const int16_t& getBookType() const noexcept {return bookType_;}
            inline int16_t& getBookTypeRef() noexcept {return bookType_;}
            inline int16_t getBookTypeCopy() const noexcept {return bookType_;}
            inline void setBookType(int16_t bookType) noexcept { bookType_ = bookType;}

        
            inline const int16_t& getBuy_SellIndicator() const noexcept {return buy_SellIndicator_;}
            inline int16_t& getBuy_SellIndicatorRef() noexcept {return buy_SellIndicator_;}
            inline int16_t getBuy_SellIndicatorCopy() const noexcept {return buy_SellIndicator_;}
            inline void setBuy_SellIndicator(int16_t buy_SellIndicator) noexcept { buy_SellIndicator_ = buy_SellIndicator;}

        
            inline const int32_t& getDisclosedVolume() const noexcept {return disclosedVolume_;}
            inline int32_t& getDisclosedVolumeRef() noexcept {return disclosedVolume_;}
            inline int32_t getDisclosedVolumeCopy() const noexcept {return disclosedVolume_;}
            inline void setDisclosedVolume(int32_t disclosedVolume) noexcept { disclosedVolume_ = disclosedVolume;}

        
            inline const std::array<char, StringLengthsEnum::RESERVED_OER3>& getReserved_OER3() const noexcept { return reserved_OER3_; }
            inline std::array<char, StringLengthsEnum::RESERVED_OER3>& getReserved_OER3Ref() noexcept { return reserved_OER3_; }
            inline std::array<char, StringLengthsEnum::RESERVED_OER3> getReserved_OER3Copy() const noexcept { return reserved_OER3_; }
            inline void setReserved_OER3(const char* reserved_OER3) noexcept {
                
                std::size_t length = std::min<std::size_t>(StringLengthsEnum::RESERVED_OER3, std::strlen(reserved_OER3));
                std::memcpy(reserved_OER3_.data(), reserved_OER3, length);
                for(size_t i = length; i < StringLengthsEnum::RESERVED_OER3; ++i ){ reserved_OER3_[i] = 0;}
            }

        
            inline const int32_t& getVolume() const noexcept {return volume_;}
            inline int32_t& getVolumeRef() noexcept {return volume_;}
            inline int32_t getVolumeCopy() const noexcept {return volume_;}
            inline void setVolume(int32_t volume) noexcept { volume_ = volume;}

        
            inline const std::array<char, StringLengthsEnum::RESERVED_OER4>& getReserved_OER4() const noexcept { return reserved_OER4_; }
            inline std::array<char, StringLengthsEnum::RESERVED_OER4>& getReserved_OER4Ref() noexcept { return reserved_OER4_; }
            inline std::array<char, StringLengthsEnum::RESERVED_OER4> getReserved_OER4Copy() const noexcept { return reserved_OER4_; }
            inline void setReserved_OER4(const char* reserved_OER4) noexcept {
                
                std::size_t length = std::min<std::size_t>(StringLengthsEnum::RESERVED_OER4, std::strlen(reserved_OER4));
                std::memcpy(reserved_OER4_.data(), reserved_OER4, length);
                for(size_t i = length; i < StringLengthsEnum::RESERVED_OER4; ++i ){ reserved_OER4_[i] = 0;}
            }

        
            inline const int32_t& getPrice() const noexcept {return price_;}
            inline int32_t& getPriceRef() noexcept {return price_;}
            inline int32_t getPriceCopy() const noexcept {return price_;}
            inline void setPrice(int32_t price) noexcept { price_ = price;}

        
            inline const int32_t& getTriggerPrice() const noexcept {return triggerPrice_;}
            inline int32_t& getTriggerPriceRef() noexcept {return triggerPrice_;}
            inline int32_t getTriggerPriceCopy() const noexcept {return triggerPrice_;}
            inline void setTriggerPrice(int32_t triggerPrice) noexcept { triggerPrice_ = triggerPrice;}

        
            inline const int32_t& getGoodTillDate() const noexcept {return goodTillDate_;}
            inline int32_t& getGoodTillDateRef() noexcept {return goodTillDate_;}
            inline int32_t getGoodTillDateCopy() const noexcept {return goodTillDate_;}
            inline void setGoodTillDate(int32_t goodTillDate) noexcept { goodTillDate_ = goodTillDate;}

        
            inline const std::array<char, StringLengthsEnum::RESERVED_OER5>& getReserved_OER5() const noexcept { return reserved_OER5_; }
            inline std::array<char, StringLengthsEnum::RESERVED_OER5>& getReserved_OER5Ref() noexcept { return reserved_OER5_; }
            inline std::array<char, StringLengthsEnum::RESERVED_OER5> getReserved_OER5Copy() const noexcept { return reserved_OER5_; }
            inline void setReserved_OER5(const char* reserved_OER5) noexcept {
                
                std::size_t length = std::min<std::size_t>(StringLengthsEnum::RESERVED_OER5, std::strlen(reserved_OER5));
                std::memcpy(reserved_OER5_.data(), reserved_OER5, length);
                for(size_t i = length; i < StringLengthsEnum::RESERVED_OER5; ++i ){ reserved_OER5_[i] = 0;}
            }

        
            inline const std::array<char, StringLengthsEnum::OPEN_CLOSE>& getOpen_Close() const noexcept { return open_Close_; }
            inline std::array<char, StringLengthsEnum::OPEN_CLOSE>& getOpen_CloseRef() noexcept { return open_Close_; }
            inline std::array<char, StringLengthsEnum::OPEN_CLOSE> getOpen_CloseCopy() const noexcept { return open_Close_; }
            inline void setOpen_Close(const char* open_Close) noexcept {
                
                std::size_t length = std::min<std::size_t>(StringLengthsEnum::OPEN_CLOSE, std::strlen(open_Close));
                std::memcpy(open_Close_.data(), open_Close, length);
                for(size_t i = length; i < StringLengthsEnum::OPEN_CLOSE; ++i ){ open_Close_[i] = 0;}
            }

        
            inline const std::array<char, StringLengthsEnum::SETTLOR>& getSettlor() const noexcept { return settlor_; }
            inline std::array<char, StringLengthsEnum::SETTLOR>& getSettlorRef() noexcept { return settlor_; }
            inline std::array<char, StringLengthsEnum::SETTLOR> getSettlorCopy() const noexcept { return settlor_; }
            inline void setSettlor(const char* settlor) noexcept {
                
                std::size_t length = std::min<std::size_t>(StringLengthsEnum::SETTLOR, std::strlen(settlor));
                std::memcpy(settlor_.data(), settlor, length);
                for(size_t i = length; i < StringLengthsEnum::SETTLOR; ++i ){ settlor_[i] = 0;}
            }

        
            inline const int16_t& getPro_ClientIndicator() const noexcept {return pro_ClientIndicator_;}
            inline int16_t& getPro_ClientIndicatorRef() noexcept {return pro_ClientIndicator_;}
            inline int16_t getPro_ClientIndicatorCopy() const noexcept {return pro_ClientIndicator_;}
            inline void setPro_ClientIndicator(int16_t pro_ClientIndicator) noexcept { pro_ClientIndicator_ = pro_ClientIndicator;}

        
            inline const int16_t& getSettlementPeriod() const noexcept {return settlementPeriod_;}
            inline int16_t& getSettlementPeriodRef() noexcept {return settlementPeriod_;}
            inline int16_t getSettlementPeriodCopy() const noexcept {return settlementPeriod_;}
            inline void setSettlementPeriod(int16_t settlementPeriod) noexcept { settlementPeriod_ = settlementPeriod;}

        
            inline const std::array<char, StringLengthsEnum::RESERVED_OER6>& getReserved_OER6() const noexcept { return reserved_OER6_; }
            inline std::array<char, StringLengthsEnum::RESERVED_OER6>& getReserved_OER6Ref() noexcept { return reserved_OER6_; }
            inline std::array<char, StringLengthsEnum::RESERVED_OER6> getReserved_OER6Copy() const noexcept { return reserved_OER6_; }
            inline void setReserved_OER6(const char* reserved_OER6) noexcept {
                
                std::size_t length = std::min<std::size_t>(StringLengthsEnum::RESERVED_OER6, std::strlen(reserved_OER6));
                std::memcpy(reserved_OER6_.data(), reserved_OER6, length);
                for(size_t i = length; i < StringLengthsEnum::RESERVED_OER6; ++i ){ reserved_OER6_[i] = 0;}
            }

        
            inline const std::array<char, StringLengthsEnum::PAN>& getPAN() const noexcept { return pAN_; }
            inline std::array<char, StringLengthsEnum::PAN>& getPANRef() noexcept { return pAN_; }
            inline std::array<char, StringLengthsEnum::PAN> getPANCopy() const noexcept { return pAN_; }
            inline void setPAN(const char* pAN) noexcept {
                
                std::size_t length = std::min<std::size_t>(StringLengthsEnum::PAN, std::strlen(pAN));
                std::memcpy(pAN_.data(), pAN, length);
                for(size_t i = length; i < StringLengthsEnum::PAN; ++i ){ pAN_[i] = 0;}
            }

        
            inline const std::array<char, StringLengthsEnum::RESERVED_OER7>& getReserved_OER7() const noexcept { return reserved_OER7_; }
            inline std::array<char, StringLengthsEnum::RESERVED_OER7>& getReserved_OER7Ref() noexcept { return reserved_OER7_; }
            inline std::array<char, StringLengthsEnum::RESERVED_OER7> getReserved_OER7Copy() const noexcept { return reserved_OER7_; }
            inline void setReserved_OER7(const char* reserved_OER7) noexcept {
                
                std::size_t length = std::min<std::size_t>(StringLengthsEnum::RESERVED_OER7, std::strlen(reserved_OER7));
                std::memcpy(reserved_OER7_.data(), reserved_OER7, length);
                for(size_t i = length; i < StringLengthsEnum::RESERVED_OER7; ++i ){ reserved_OER7_[i] = 0;}
            }
        }; 
        