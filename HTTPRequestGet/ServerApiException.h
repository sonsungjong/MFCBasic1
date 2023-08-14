#ifndef SERVER_API_EXCEPTION_H_
#define SERVER_API_EXCEPTION_H_

#include <stdexcept>
#include <string>

enum class ServerApiError
{
	NetworkCommunicationFailed = -1,
	InvalidResponseDataValue = -2,
};

class ServerApiException : public std::exception
{
public:
	static const std::wstring DefaultExceptionMessage;

	ServerApiException(const std::wstring& message);
	ServerApiException(ServerApiError serverApiError);
	ServerApiException(ServerApiError serverApiError, const std::wstring& detail);

private:
	static std::wstring ModifyMessage(const std::wstring& message);
	static std::wstring GetMessage(ServerApiError serverApiError, const std::wstring& detail = L"");
	static std::string ConvertWideToMultibyte(const std::wstring& wideString);
};

#endif