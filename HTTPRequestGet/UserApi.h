#ifndef USER_API_H_
#define USER_API_H_

#include <string>

class UserApi
{
private:
	RequestInfo requestInfo;

public:
	UserApi(RequestInfo a_requestInfo);
	bool GetUserInfo(const std::wstring& userId, const std::wstring& apcToken, UserInfoResponse& a_response);
	std::wstring Utf8ToUnicode(const std::string& utf8_string);
};

#endif			// USER_API_H_