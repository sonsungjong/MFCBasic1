#ifndef POLICY_API_H_
#define POLICY_API_H_

#include <string>

class PolicyApi
{
private:
	RequestInfo requestInfo;

public:
	PolicyApi(RequestInfo a_requestInfo);
	bool GetAuthenticationList(const std::wstring& agentId, const std::wstring& userId, AuthListResponse& response);

	std::wstring Utf8ToUnicode(const std::string& utf8_string);
};

#endif			// POLICY_API_H_