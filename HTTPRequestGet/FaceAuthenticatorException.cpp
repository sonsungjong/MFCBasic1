#include "pch.h"
#include "FaceAuthenticatorException.h"

const std::wstring FaceAuthenticatorException::DefaultExceptionMessage = L"얼굴 인증에 실패하였습니다.";

FaceAuthenticatorException::FaceAuthenticatorException(const std::wstring& message)
    : std::exception(ConvertWideToMultibyte(ModifyMessage(message)).c_str()) {}

FaceAuthenticatorException::FaceAuthenticatorException(FaceAuthError faceAuthError)
    : std::exception(ConvertWideToMultibyte(GetMessage(faceAuthError)).c_str()) {}

FaceAuthenticatorException::FaceAuthenticatorException(FaceAuthError faceAuthError, const std::wstring& detail)
    : std::exception(ConvertWideToMultibyte(GetMessage(faceAuthError, detail)).c_str()) {}

const char* FaceAuthenticatorException::what() const noexcept {
    return std::exception::what();
}

std::wstring FaceAuthenticatorException::ModifyMessage(const std::wstring& message) {
    return message.empty() ? DefaultExceptionMessage : message;
}

std::wstring FaceAuthenticatorException::GetMessage(FaceAuthError faceAuthError, const std::wstring& detail) {
    std::wstring msg;
    switch (faceAuthError) {
        case FaceAuthError::InitDeviceFailed:
            msg = L"얼굴 인식 장치 초기화에 실패 하였습니다.";
            break;
        case FaceAuthError::CaptureFailed:
            msg = L"얼굴 캡처에 실패하였습니다.";
            break;
        case FaceAuthError::StartCaptureFailed:
        default:
            msg = DefaultExceptionMessage;
            break;
    }
    return msg + L" " + detail;
}

std::string FaceAuthenticatorException::ConvertWideToMultibyte(const std::wstring& wideString) {
    int size_needed = WideCharToMultiByte(CP_UTF8, 0, wideString.c_str(), -1, NULL, 0, NULL, NULL);
    std::string narrowString(size_needed, 0);
    WideCharToMultiByte(CP_UTF8, 0, wideString.c_str(), -1, &narrowString[0], size_needed, NULL, NULL);
    return narrowString;
}