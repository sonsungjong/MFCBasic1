#include "pch.h"
#include "global_struct.h"			// ��������
#include "Common.h"
#include <winhttp.h>				// ��������
#include <json/json.h>			// ��������
#include "PolicyApi.h"

PolicyApi::PolicyApi(RequestInfo a_requestInfo)
	: requestInfo(a_requestInfo)
{
}

bool PolicyApi::GetAuthenticationList(const std::wstring& agentId, const std::wstring& userId, AuthListResponse& a_response)
{
	int retryCount = this->requestInfo.RetryCount();
	std::wstring computerType;
	UrlDefinition url_definition;
	int method_success = 0;

	do
	{
		computerType = L"pc";
		//if (LocalMachineRegistry.IsVmModel())
		//{
		//	computerType = L"vm";
		//}

		std::wstring api_info = requestInfo.Host() + L":" + requestInfo.Port() + url_definition.GetAuthenticationList + L"?agentId=" + agentId + L"&login=" + userId;
		std::wstring headers = L"client_computer_type:"+ computerType;

		// ���� �� ���� �ڵ� �ʱ�ȭ
		HINTERNET hSession = WinHttpOpen(L"User Agent", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);

		if (hSession) {
			HINTERNET hConnect = WinHttpConnect(hSession, this->requestInfo.Host().c_str(), std::stoi(this->requestInfo.Port()), 0); // ���� IP (URL) �� ��Ʈ

			if (hConnect) {
				// GET ��û ����
				HINTERNET hRequest = WinHttpOpenRequest(hConnect, L"GET", api_info.c_str(), NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);

				if (hRequest) {
					// ��� ����
					WinHttpAddRequestHeaders(hRequest, headers.c_str(), -1L, WINHTTP_ADDREQ_FLAG_ADD); // JSON ��û

					// ������ ���� ����
					DWORD dwFlags = SECURITY_FLAG_IGNORE_UNKNOWN_CA |
						SECURITY_FLAG_IGNORE_CERT_WRONG_USAGE |
						SECURITY_FLAG_IGNORE_CERT_CN_INVALID |
						SECURITY_FLAG_IGNORE_CERT_DATE_INVALID;
					WinHttpSetOption(hRequest, WINHTTP_OPTION_SECURITY_FLAGS, &dwFlags, sizeof(dwFlags));

					// http����
					BOOL b_send_result = WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0);
					if (b_send_result) {
						// http���� ����
						BOOL b_recv_result = WinHttpReceiveResponse(hRequest, NULL);

						// ���� ���� ���� �� (200 ~ 500)
						if (b_recv_result) {
							DWORD dwStatusCode = 0; // ���� �����ڵ�
							DWORD dwSize = sizeof(dwStatusCode); // ����޽��� ������

							BOOL query_result = 0;
							query_result = WinHttpQueryHeaders(hRequest, WINHTTP_QUERY_STATUS_CODE | WINHTTP_QUERY_FLAG_NUMBER, NULL, &dwStatusCode, &dwSize, NULL);

							// ���¸޽��� ���ڿ� ����
							wchar_t status_msg[20];
							swprintf_s(status_msg, 20, L"%d", dwStatusCode);

							BOOL data_result = WinHttpQueryDataAvailable(hRequest, &dwSize);
							char* pszOutBuffer = new char[dwSize + 1]; // UTF8 ����
							// ���� ũ�� Ȯ��
							DWORD dwDownloaded = 0;
							BOOL read_result = WinHttpReadData(hRequest, (LPVOID)pszOutBuffer, dwSize, &dwDownloaded);
							pszOutBuffer[dwDownloaded] = 0;

							Json::CharReaderBuilder readerBuilder;
							std::unique_ptr<Json::CharReader> reader(readerBuilder.newCharReader());
							Json::Value json_string;
							std::string errs;
							if (dwStatusCode == 200)			// OK
							{
								AuthListResponseDto authListResponseDto;

								// Deserialize JSON using JsonCpp
								if (reader->parse(pszOutBuffer, pszOutBuffer + dwDownloaded, &json_string, &errs))
								{
									// BaseDto
									authListResponseDto.resultCode = Utf8ToUnicode(json_string["resultCode"].asString());
									authListResponseDto.resultMessage = Utf8ToUnicode(json_string["resultMessage"].asString());
									
									// Apc
									authListResponseDto.pac.apcToken = Utf8ToUnicode(json_string["pac"]["apcToken"].asString());
									authListResponseDto.pac.passedAll = json_string["pac"]["passedAll"].asBool();
									authListResponseDto.pac.sso = json_string["pac"]["sso"].asBool();
									authListResponseDto.pac.tgt = Utf8ToUnicode(json_string["pac"]["tgt"].asString());
									authListResponseDto.pac.validUntilDate = Utf8ToUnicode(json_string["pac"]["validUntilDate"].asString());

									// Policy
									authListResponseDto.policy.priority = Utf8ToUnicode(json_string["policy"]["priority"].asString());
									for (const auto& factorListArray : json_string["policy"]["factorList"]) {
										std::vector<AuthListResponseDto::FactorList> factorListVector;
										for (const auto& factor : factorListArray) {
											factorListVector.push_back({ Utf8ToUnicode(factor["type"].asString()) });
										}
										authListResponseDto.policy.factorList.push_back(factorListVector);
									}

									// a_response�� �� �Ҵ�
									a_response.resultCode = authListResponseDto.resultCode;
									a_response.resultMessage = authListResponseDto.resultMessage;
									a_response.apcToken = authListResponseDto.pac.apcToken;

									a_response.factorList.clear();
									for (const auto& factorListVector : authListResponseDto.policy.factorList) {
										for (const auto& factor : factorListVector) {
											AuthListResponse::FactorList factorList;
											factorList.type = factor.type;
											a_response.factorList.push_back(factorList);
										}
									}
								}
								
							}
							else
							{
								// �� �� ���� �ڵ�
								if (reader->parse(pszOutBuffer, pszOutBuffer + dwDownloaded, &json_string, &errs)) {
									// Process the deserialized JSON
									a_response.resultMessage = Utf8ToUnicode(json_string["resultMessage"].asString());
									a_response.resultCode = Utf8ToUnicode(json_string["resultCode"].asString());
								}
							}
							delete[] pszOutBuffer;
							method_success = 1;
						}
					}
					else {
						// ��û ����
						DWORD dwErr = GetLastError();
						LPVOID lpMsgBuf;
						FormatMessage(
							FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
							NULL,
							dwErr,
							0,
							(LPWSTR)&lpMsgBuf,
							0,
							NULL
						);
						::MessageBox(NULL, (LPCWSTR)lpMsgBuf, L"����", MB_OK);
						LocalFree(lpMsgBuf);
					}

					WinHttpCloseHandle(hRequest);
				}

				WinHttpCloseHandle(hConnect);
			}
			WinHttpCloseHandle(hSession);
			if (method_success == 1) {
				return true;
			}
		}

	} while (retryCount-- > 0);

	return false;
}


std::wstring PolicyApi::Utf8ToUnicode(const std::string& utf8_string)
{
	if (utf8_string.empty()) {
		return std::wstring();
	}

	int wideCharLength = MultiByteToWideChar(CP_UTF8, 0, utf8_string.c_str(), -1, NULL, 0);
	if (wideCharLength == 0) {
		return std::wstring();
	}

	wchar_t* wideBuffer = new wchar_t[wideCharLength];
	if (MultiByteToWideChar(CP_UTF8, 0, utf8_string.c_str(), -1, wideBuffer, wideCharLength) == 0) {
		delete[] wideBuffer;
		return std::wstring();
	}

	std::wstring result(wideBuffer);
	delete[] wideBuffer;

	return result; // Null ���� ���� ����
}
