#ifndef GLOBAL_STRUCT_H_
#define GLOBAL_STURCT_H_

#include <string>
#include <vector>

struct RequestInfo
{
    std::wstring host;
    std::wstring port;
    int retryCount;

    std::wstring Host() { return host; }
    std::wstring Port() { return port; }
    int RetryCount() { return retryCount; }

    RequestInfo(const std::wstring& url, const std::wstring& port, int retryCount = 0)
    {
        this->host = url;
        this->port = port;
        this->retryCount = retryCount;
    }
};

struct AuthListResponse
{
    std::wstring resultCode;
    std::wstring resultMessage;

    std::wstring apcToken;

    struct FactorList
    {
        int id;
        std::wstring type;
        std::wstring name;
        std::wstring config;
    };
    std::vector<FactorList> factorList;
};

struct UserInfoResponse
{
    std::wstring resultCode;
    std::wstring resultMessage;

    bool registeredFace;
    bool registeredOtp;
    bool registeredPattern;
    bool registeredQr;
    bool passwordRegister;
    bool pwValue;
};

struct FaceAuthRequestDto
{
    std::wstring userId;
    std::wstring data;
};

struct FaceGetStatusResponse
{
    std::wstring resultCode;
    std::wstring resultMessage;

    bool isRegistered;
    std::wstring code;
    std::wstring msg;
};

struct FaceGetStatusRequestDto
{
    std::wstring userId;
    std::wstring data;
};

struct FaceRegisterRequestDto
{
    std::wstring userId;
    std::wstring password;
    std::wstring data;
};

struct FaceAuthResponse
{
    std::wstring resultCode;
    std::wstring resultMessage;

    std::wstring validUntilDate;
    bool requireRegistration;
    std::wstring code;
    std::wstring msg;
    std::wstring password;
    std::wstring secureToken;
};

struct UserInfoResponseDto
{
    // BaseDto
    std::wstring resultCode;
    std::wstring resultMessage;

    struct Apc
    {
        std::wstring apcToken;
        bool passedAll;
        std::wstring redirectUrl;
        bool sso;
        std::wstring tgt;
        std::wstring validUntilDate;
    };
    struct User
    {
        std::wstring deviceUuid;
        std::wstring empNo;
        int groupKey;
        std::wstring name;
        std::wstring postCode;
        bool pwValue;
        std::wstring rankCode;
        bool registeredFace;
        bool registeredOtp;
        bool registeredPattern;
        bool registeredQr;
        std::wstring userId;
    };

    Apc apc;
    User user;
};

struct MotpAuthResponse
{
    std::wstring resultCode;
    std::wstring resultMessage;

    std::wstring validUntilDate;
    std::wstring secureToken;
    std::wstring password;
};

struct MotpAuthRequestDto
{
    std::wstring userId;
    std::wstring otpNumber;
};

struct AuthListResponseDto
{
    // BaseDto
    std::wstring resultCode;
    std::wstring resultMessage;

    struct Apc
    {
        std::wstring apcToken;
        bool passedAll;
        bool sso;
        std::wstring tgt;
        std::wstring validUntilDate;
    };
    struct FactorList
    {
        std::wstring type;
    };
    struct Policy
    {
        std::wstring priority;
        std::vector<std::vector<FactorList>> factorList;
    };

    Apc pac;
    Policy policy;
};


// Definition
struct UrlDefinition
{
    const std::wstring CheckServer = L"/api/v1/sso/checkserver";
    const std::wstring GetAuthenticationList = L"/api/v1/policy";
    const std::wstring ValidateToken = L"/api/v1/sso/_validate";
    const std::wstring IdPwLogin = L"/api/v1/auth/form";
    const std::wstring MotpPush = L"/api/v1/auth/otp/_push";
    const std::wstring MotpLogin = L"/api/v1/auth/otp/_signin";
    const std::wstring QrCodeGenerateQrCode = L"/api/v1/auth/qr/_generate";
    const std::wstring QrCodeConfirmAuthResult = L"/api/v1/auth/qr/_auth-result";
    const std::wstring FaceAuthentication = L"/api/v1/auth/face-sensor/auth";
    const std::wstring FacePrepareAuthentication = L"/api/v1/auth/face/_auth-prepare";
    const std::wstring FaceGetStatus = L"/api/v1/auth/face-sensor/status";
    const std::wstring FaceRegistration = L"/api/v1/auth/face-sensor/register";
    const std::wstring EasyPassPush = L"/api/v1/auth/face-pattern/auth-push";
    const std::wstring EasyPassConfirmAuthResult = L"/api/v1/auth/face-pattern/auth-result";
    const std::wstring SendLog = L"/api/loginLog";
    const std::wstring GetUserInfo = L"/api/v1/user";
};

struct JsonValueDefinition
{
    const std::wstring CmdCheckServer = L"checkserver";
    const std::wstring CmdGetEeWinAuthList = L"getEeWinAuthList";
};

struct ResponseCodeDefinition
{
    const std::wstring Success = L"000000";

    const std::wstring ApcStatusOk = L"S200.000";
    const std::wstring ApcSuccess = L"0200.000";
};

struct ApcBusinessDefinition
{
    static const std::wstring EeWinAgentId;
};

const std::wstring ApcBusinessDefinition::EeWinAgentId = L"-1";

#endif				// GLOBAL_STRUCT_H_