#include "pch.h"
#include "ServerApiException.h"

const std::wstring ServerApiException::DefaultExceptionMessage = L"서버 통신에 실패하였습니다.";

ServerApiException::ServerApiException(const std::wstring& message)
	: std::exception(ConvertWideToMultibyte(ModifyMessage(message)).c_str()) {}

ServerApiException::ServerApiException(ServerApiError serverApiError)
	: std::exception(ConvertWideToMultibyte(GetMessage(serverApiError)).c_str()) {}

ServerApiException::ServerApiException(ServerApiError serverApiError, const std::wstring& detail)
	: std::exception(ConvertWideToMultibyte(GetMessage(serverApiError, detail)).c_str()) {}

std::wstring ServerApiException::ModifyMessage(const std::wstring& message)
{
	if (message.empty())
		return DefaultExceptionMessage;

	return message;
}

std::wstring ServerApiException::GetMessage(ServerApiError serverApiError, const std::wstring& detail)
{
	std::wstring msg;
	switch (serverApiError) {
	case ServerApiError::NetworkCommunicationFailed:
	default:
		msg = DefaultExceptionMessage;
		break;
	}
	return msg + L" " + detail;
}

std::string ServerApiException::ConvertWideToMultibyte(const std::wstring& wideString)
{
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, wideString.c_str(), -1, NULL, 0, NULL, NULL);
	std::string narrowString(size_needed, 0);
	WideCharToMultiByte(CP_UTF8, 0, wideString.c_str(), -1, &narrowString[0], size_needed, NULL, NULL);
	return narrowString;
}