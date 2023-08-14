#include "pch.h"
#include "global_struct.h"			// 삭제예정
#include "Common.h"
#include <winhttp.h>				// 삭제예정
#include <json/json.h>			// 삭제예정
#include "UserApi.h"

UserApi::UserApi(RequestInfo a_requestInfo)
	: requestInfo(a_requestInfo)
{
}

bool UserApi::GetUserInfo(const std::wstring& userId, const std::wstring& apcToken, UserInfoResponse& a_response)
{
	int retryCount = this->requestInfo.RetryCount();
	UrlDefinition url_definition;
    int method_success = 0;

	do
	{
		std::wstring api_info = requestInfo.Host() + L":" + requestInfo.Port() + url_definition.GetUserInfo + L"?userId=" + userId;
		
        HINTERNET hSession = WinHttpOpen(L"User Agent", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
        if (hSession) {
            HINTERNET hConnect = WinHttpConnect(hSession, this->requestInfo.Host().c_str(), std::stoi(this->requestInfo.Port()), 0); // 서버 IP (URL) 와 포트
            if (hConnect) {
                // GET 요청 설정
                HINTERNET hRequest = WinHttpOpenRequest(hConnect, L"GET", api_info.c_str(), NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);
                if (hRequest) {
                    // 헤더 설정
                    WinHttpAddRequestHeaders(hRequest, L"Content-Type: application/json", -1L, WINHTTP_ADDREQ_FLAG_ADD);
                    std::wstring apcTokenHeader = L"ApcToken: " + apcToken;
                    WinHttpAddRequestHeaders(hRequest, apcTokenHeader.c_str(), -1L, WINHTTP_ADDREQ_FLAG_ADD);

                    // api_info 를 로그찍기
                    // 헤더를 로그찍기

                    // 인증서 무시
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
                            if (dwStatusCode == 200)
                            {
                                UserInfoResponseDto userInfoResponseDto;
                                // 파싱하여 대입
                                if (reader->parse(pszOutBuffer, pszOutBuffer + dwDownloaded, &json_string, &errs))
                                {
                                    // BaseDto
                                    userInfoResponseDto.resultCode = Utf8ToUnicode(json_string["resultCode"].asString());
                                    userInfoResponseDto.resultMessage = Utf8ToUnicode(json_string["resultMessage"].asString());

                                    // Apc
                                    userInfoResponseDto.apc.apcToken = Utf8ToUnicode(json_string["apc"]["apcToken"].asString());
                                    userInfoResponseDto.apc.passedAll = json_string["apc"]["passedAll"].asBool();
                                    userInfoResponseDto.apc.redirectUrl = Utf8ToUnicode(json_string["apc"]["redirectUrl"].asString());
                                    userInfoResponseDto.apc.sso = json_string["apc"]["sso"].asBool();
                                    userInfoResponseDto.apc.tgt = Utf8ToUnicode(json_string["apc"]["tgt"].asString());
                                    userInfoResponseDto.apc.validUntilDate = Utf8ToUnicode(json_string["apc"]["validUntilDate"].asString());

                                    // User
                                    userInfoResponseDto.user.deviceUuid = Utf8ToUnicode(json_string["user"]["deviceUuid"].asString());
                                    userInfoResponseDto.user.empNo = Utf8ToUnicode(json_string["user"]["empNo"].asString());
                                    userInfoResponseDto.user.groupKey = json_string["user"]["groupKey"].asInt();
                                    userInfoResponseDto.user.name = Utf8ToUnicode(json_string["user"]["name"].asString());
                                    userInfoResponseDto.user.postCode = Utf8ToUnicode(json_string["user"]["postCode"].asString());
                                    userInfoResponseDto.user.pwValue = json_string["user"]["pwValue"].asBool();
                                    userInfoResponseDto.user.rankCode = Utf8ToUnicode(json_string["user"]["rankCode"].asString());
                                    userInfoResponseDto.user.registeredFace = json_string["user"]["registeredFace"].asBool();
                                    userInfoResponseDto.user.registeredOtp = json_string["user"]["registeredOtp"].asBool();
                                    userInfoResponseDto.user.registeredPattern = json_string["user"]["registeredPattern"].asBool();
                                    userInfoResponseDto.user.registeredQr = json_string["user"]["registeredQr"].asBool();
                                    userInfoResponseDto.user.userId = Utf8ToUnicode(json_string["user"]["userId"].asString());

                                    a_response.resultMessage = userInfoResponseDto.resultMessage;
                                    a_response.resultCode = userInfoResponseDto.resultCode;
                                    a_response.registeredQr = userInfoResponseDto.user.registeredQr;
                                    a_response.registeredPattern = userInfoResponseDto.user.registeredPattern;
                                    a_response.registeredFace = userInfoResponseDto.user.registeredFace;
                                    a_response.registeredOtp = userInfoResponseDto.user.registeredOtp;
                                    a_response.pwValue = userInfoResponseDto.user.pwValue;
                                }
                            }
                            else {
                                if (reader->parse(pszOutBuffer, pszOutBuffer + dwDownloaded, &json_string, &errs))
                                {
                                    a_response.resultMessage = Utf8ToUnicode(json_string["resultMessage"].asString());
                                    a_response.resultCode = Utf8ToUnicode(json_string["resultCode"].asString());
                                }
                            }
                            delete[] pszOutBuffer;
                            method_success = 1;
                        }
                    }

                }
                WinHttpCloseHandle(hRequest);
            }
            WinHttpCloseHandle(hConnect);
        }
        WinHttpCloseHandle(hSession);
        if (method_success == 1) {
            return true;
        }

	} while (retryCount-- > 0);

	return false;
}

std::wstring UserApi::Utf8ToUnicode(const std::string& utf8_string)
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
