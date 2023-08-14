#ifndef FACE_AUTHENTICATOR_H_
#define FACE_AUTHENTICATOR_H_

#include <string>

class FaceAuthenticator
{
private:
    static const int CaptureWaitingTime = 10000;
    static const std::wstring CameraName;
    static const std::wstring Channel;

    RequestInfo serverInfo;
    std::wstring cachedtAuthCapturedData;
    std::wstring cachedRegisterCapturedData;
    std::wstring cachedPrepareAuthResultData;
    bool isPasswordRegistration = false;
    bool isFaceRegistration = false;

    void PrepareAuthentication(const std::wstring& ssoId);

public:
    bool IsPasswordRegistration() const { return isPasswordRegistration; }
    bool IsFaceRegistration() const { return isFaceRegistration; }

    FaceAuthenticator(RequestInfo serverInfo); // Constructor

    void Authenticate(const std::wstring& ssoId, std::wstring& validUntilDate, std::wstring& secureToken, std::wstring& password);
    void Register(const std::wstring& ssoId, const std::wstring& ssoPw);

    bool CheckRegistered(const std::wstring& ssoId);
    void MotpAuthentication(const std::wstring& ssoId, const std::wstring& otpNumber, std::wstring& encPassword);
    void ClearCachedData();
};

#endif				// FACE_AUTHENTICATOR_H_