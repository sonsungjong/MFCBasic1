#ifndef FACE_AUTHENTICATOR_EXCEPTION_H_
#define FACE_AUTHENTICATOR_EXCEPTION_H_

#include <exception>
#include <string>

enum class FaceAuthError {
    InitDeviceFailed = -1,
    StartCaptureFailed = -2,
    CaptureFailed = -3,
};

class FaceAuthenticatorException : public std::exception {
public:
    static const std::wstring DefaultExceptionMessage;

    FaceAuthenticatorException(const std::wstring& message);
    FaceAuthenticatorException(FaceAuthError faceAuthError);
    FaceAuthenticatorException(FaceAuthError faceAuthError, const std::wstring& detail);

    virtual const char* what() const noexcept override;

private:
    static std::wstring ModifyMessage(const std::wstring& message);
    static std::wstring GetMessage(FaceAuthError faceAuthError, const std::wstring& detail = L"");
    static std::string ConvertWideToMultibyte(const std::wstring& wideString);
};

#endif			// FACE_AUTHENTICATOR_EXCEPTION_H_