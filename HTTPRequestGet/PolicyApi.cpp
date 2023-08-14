#include "pch.h"
#include "global_struct.h"			// 삭제예정
#include "Common.h"
#include <winhttp.h>				// 삭제예정
#include <json/json.h>			// 삭제예정
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

		// 세션 및 연결 핸들 초기화
		HINTERNET hSession = WinHttpOpen(L"User Agent", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);

		if (hSession) {
			HINTERNET hConnect = WinHttpConnect(hSession, this->requestInfo.Host().c_str(), std::stoi(this->requestInfo.Port()), 0); // 서버 IP (URL) 와 포트

			if (hConnect) {
				// GET 요청 설정
				HINTERNET hRequest = WinHttpOpenRequest(hConnect, L"GET", api_info.c_str(), NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);

				if (hRequest) {
					// 헤더 설정
					WinHttpAddRequestHeaders(hRequest, headers.c_str(), -1L, WINHTTP_ADDREQ_FLAG_ADD); // JSON 요청

					// 인증서 검증 무시
					DWORD dwFlags = SECURITY_FLAG_IGNORE_UNKNOWN_CA |
						SECURITY_FLAG_IGNORE_CERT_WRONG_USAGE |
						SECURITY_FLAG_IGNORE_CERT_CN_INVALID |
						SECURITY_FLAG_IGNORE_CERT_DATE_INVALID;
					WinHttpSetOption(hRequest, WINHTTP_OPTION_SECURITY_FLAGS, &dwFlags, sizeof(dwFlags));

					// http전송
					BOOL b_send_result = WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0);
					if (b_send_result) {
						// http응답 수신
						BOOL b_recv_result = WinHttpReceiveResponse(hRequest, NULL);

						// 무언가 수신 성공 시 (200 ~ 500)
						if (b_recv_result) {
							DWORD dwStatusCode = 0; // 응답 상태코드
							DWORD dwSize = sizeof(dwStatusCode); // 응답메시지 사이즈

							BOOL query_result = 0;
							query_result = WinHttpQueryHeaders(hRequest, WINHTTP_QUERY_STATUS_CODE | WINHTTP_QUERY_FLAG_NUMBER, NULL, &dwStatusCode, &dwSize, NULL);

							// 상태메시지 문자열 저장
							wchar_t status_msg[20];
							swprintf_s(status_msg, 20, L"%d", dwStatusCode);

							BOOL data_result = WinHttpQueryDataAvailable(hRequest, &dwSize);
							char* pszOutBuffer = new char[dwSize + 1]; // UTF8 응답
							// 응답 크기 확인
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

									// a_response에 값 할당
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
								// 그 외 상태 코드
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
						// 요청 실패
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
						::MessageBox(NULL, (LPCWSTR)lpMsgBuf, L"에러", MB_OK);
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

	return result; // Null 종료 문자 제거
}
