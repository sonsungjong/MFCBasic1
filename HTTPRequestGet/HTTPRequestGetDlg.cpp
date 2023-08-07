
// HTTPRequestGetDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "HTTPRequestGet.h"
#include <winhttp.h>
#include "HTTPRequestGetDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#pragma comment(lib, "winhttp.lib")



CHTTPRequestGetDlg::CHTTPRequestGetDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_HTTPREQUESTGET_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHTTPRequestGetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CHTTPRequestGetDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CHTTPRequestGetDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CHTTPRequestGetDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_WEBCAM, &CHTTPRequestGetDlg::OnBnClickedWebcam)
	ON_BN_CLICKED(IDC_MOBILE_PUSH1, &CHTTPRequestGetDlg::OnBnClickedMobilePush1)
	ON_BN_CLICKED(IDC_MOBILE_PUSH2, &CHTTPRequestGetDlg::OnBnClickedMobilePush2)
	ON_BN_CLICKED(IDC_MOBILE_QR1, &CHTTPRequestGetDlg::OnBnClickedMobileQr1)
	ON_BN_CLICKED(IDC_MOBILE_QR2, &CHTTPRequestGetDlg::OnBnClickedMobileQr2)
	ON_BN_CLICKED(IDC_OTP, &CHTTPRequestGetDlg::OnBnClickedOtp)
	ON_BN_CLICKED(IDC_LOGIN_LOG, &CHTTPRequestGetDlg::OnBnClickedLoginLog)
END_MESSAGE_MAP()


// CHTTPRequestGetDlg message handlers

BOOL CHTTPRequestGetDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	SetDlgItemText(IDC_USERID, _T("9875587"));

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CHTTPRequestGetDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CHTTPRequestGetDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CHTTPRequestGetDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CHTTPRequestGetDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void CHTTPRequestGetDlg::OnBnClickedWebcam()
{
	wchar_t user_id[512] = { 0, };
	::GetDlgItemText(m_hWnd, IDC_USERID, user_id, 512);

	wchar_t user_pw[512] = { 0, };
	::GetDlgItemText(m_hWnd, IDC_USERPW, user_pw, 512);

	WebcamFace(user_id, user_pw);
}

void CHTTPRequestGetDlg::OnBnClickedMobilePush1()
{
	wchar_t user_id[512] = { 0, };
	::GetDlgItemText(m_hWnd, IDC_USERID, user_id, 512);

	MobileAuthPush(user_id);
}


void CHTTPRequestGetDlg::OnBnClickedMobilePush2()
{
	wchar_t user_id[512] = { 0, };
	::GetDlgItemText(m_hWnd, IDC_USERID, user_id, 512);
	wchar_t* request_id = L"9KZ2A84EEV6NKWDT";

	MobileAuthResult(user_id, request_id);
}


void CHTTPRequestGetDlg::OnBnClickedMobileQr1()
{
	wchar_t user_id[512] = { 0, };
	::GetDlgItemText(m_hWnd, IDC_USERID, user_id, 512);

	MobileQrGenerate(user_id);
}


void CHTTPRequestGetDlg::OnBnClickedMobileQr2()
{
	wchar_t user_id[512] = { 0, };
	::GetDlgItemText(m_hWnd, IDC_USERID, user_id, 512);

	MobileQrAuthResult(user_id);
}


void CHTTPRequestGetDlg::OnBnClickedOtp()
{
	wchar_t user_id[512] = { 0, };
	::GetDlgItemText(m_hWnd, IDC_USERID, user_id, 512);
	wchar_t* otp_number = L"123123";

	MobileOtpSignin(user_id, otp_number);
}

void CHTTPRequestGetDlg::OnBnClickedLoginLog()
{
	wchar_t user_id[512] = { 0, };
	::GetDlgItemText(m_hWnd, IDC_USERID, user_id, 512);

	LoginLog();
}

// 얼굴(웹캠)
void CHTTPRequestGetDlg::WebcamFace(wchar_t* _user_id, wchar_t* _user_pw)
{

}

// 모바일(인증요청)
void CHTTPRequestGetDlg::MobileAuthPush(wchar_t* _user_id)
{
	wchar_t* api_info = L"/api/v1/auth/face-pattern/auth-push";
	wchar_t* headers = L"Content-Type: application/json\r\nclient_computer_type: pc\r\n";
	wchar_t body[512];
	swprintf_s(body, sizeof(body) / sizeof(wchar_t), L"{\"userId\":\"%s\"}", _user_id);

	HttpPostRequest(api_info, headers, body);
}

// 모바일(인증결과확인요청)
void CHTTPRequestGetDlg::MobileAuthResult(wchar_t* _user_id, wchar_t* _request_id)
{
	wchar_t* api_info = L"/api/v1/auth/face-pattern/auth-result";
	wchar_t* headers = L"Content-Type: application/json\r\nclient_computer_type: pc\r\n";
	wchar_t body[512];
	swprintf(body, sizeof(body) / sizeof(wchar_t), L"{\n  \"userId\": \"%s\",\n  \"requestId\": \"%s\"\n}", _user_id, _request_id);

	HttpPostRequest(api_info, headers, body);
}

// 모바일(QR요청)
void CHTTPRequestGetDlg::MobileQrGenerate(wchar_t* _user_id)
{
	wchar_t* api_info = L"/api/v1/auth/qr/_generate";
	wchar_t* headers = L"Content-Type: application/json\r\nclient_computer_type: pc\r\n";
	wchar_t body[512];
	swprintf_s(body, sizeof(body) / sizeof(wchar_t), L"{\"userId\":\"%s\"}", _user_id);

	HttpPostRequest(api_info, headers, body);
}

// 전달받은 QR 생성 (화면에 QR 이미지 출력)
void CHTTPRequestGetDlg::MobileQrImageDraw()
{

}

// 모바일(QR인증 결과확인요청)
void CHTTPRequestGetDlg::MobileQrAuthResult(wchar_t* _user_id)
{
	wchar_t* api_info = L"/api/v1/auth/qr/_auth-result";
	wchar_t* headers = L"Content-Type: application/json\r\nclient_computer_type: pc\r\n";
	wchar_t body[512];
	swprintf_s(body, sizeof(body) / sizeof(wchar_t), L"{\"userId\":\"%s\"}", _user_id);

	HttpPostRequest(api_info, headers, body);
}

// 모바일(OTP인증요청)
void CHTTPRequestGetDlg::MobileOtpSignin(wchar_t* _user_id, wchar_t* _otp_number)
{
	wchar_t* api_info = L"/api/v1/auth/otp/_signin";
	wchar_t* headers = L"Content-Type: application/json\r\nclient_computer_type: pc\r\n";
	wchar_t body[512];
	swprintf(body, sizeof(body) / sizeof(wchar_t), L"{\"userId\":\"%s\",\"otpNumber\":\"%s\"}", _user_id, _otp_number);

	HttpPostRequest(api_info, headers, body);
}


// 인증 토큰 호출 (인증 완료 시 응답 받은 인증 Token 정보를 호출하는 함수 필요)
// 특정 레지스트리에 저장 가능
void CHTTPRequestGetDlg::CallToken()
{
	
}

// 내부서버로 인증로그전송
void CHTTPRequestGetDlg::LoginLog()
{
	wchar_t* api_info = L"/api/loginLog";
	wchar_t* headers = L"Content-Type: application/json";
	wchar_t* body = LR"(
{
  "agentId": "AuthOCX",
  "clientDt": "2023.07.12 08:45:30",
  "clientIp": "192.168.30.241",
  "clientVer": "1.0",
  "loginType": "FaceSensor",
  "osType": "Windows 10 x64",
  "serialNo": "",
  "status": "Authenfication",
  "usedSso": true,
  "userLogin": "9875587",
  "userName": "김대건"
}
)";

	HttpPostRequest(api_info, headers, body);
}

// POST요청 후 멤버변수에 응답 저장
void CHTTPRequestGetDlg::HttpPostRequest(wchar_t* api_info, wchar_t* headers, wchar_t* body)
{
	// 세션 및 연결 핸들 초기화
	HINTERNET hSession = WinHttpOpen(L"User Agent", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);

	if (hSession) {
		HINTERNET hConnect = WinHttpConnect(hSession, L"118.33.113.122", 9443, 0);					// 서버 IP (URL) 와 포트

		if (hConnect) {
			// POST 요청 설정
			HINTERNET hRequest = WinHttpOpenRequest(hConnect, L"POST", api_info, NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);				// POST형식으로 요청 URL정보

			if (hRequest) {
				// 헤더 설정
				WinHttpAddRequestHeaders(hRequest, headers, -1L, WINHTTP_ADDREQ_FLAG_ADD);				// JSON 요청

				// 송신용 메시지 UTF8로 변환
				int utf8_length = WideCharToMultiByte(CP_UTF8, 0, body, -1, NULL, 0, NULL, NULL);
				char* utf8body = new char[utf8_length];
				WideCharToMultiByte(CP_UTF8, 0, body, -1, utf8body, utf8_length, NULL, NULL);

				// 인증서 검증 무시
				DWORD dwFlags = SECURITY_FLAG_IGNORE_UNKNOWN_CA |
					SECURITY_FLAG_IGNORE_CERT_WRONG_USAGE |
					SECURITY_FLAG_IGNORE_CERT_CN_INVALID |
					SECURITY_FLAG_IGNORE_CERT_DATE_INVALID;
				WinHttpSetOption(hRequest, WINHTTP_OPTION_SECURITY_FLAGS, &dwFlags, sizeof(dwFlags));


				// 요청메시지 http전송
				BOOL b_send_result = WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, (LPVOID)utf8body, utf8_length, utf8_length, 0);
				if (b_send_result) {

					// http응답 수신
					BOOL b_recv_result = WinHttpReceiveResponse(hRequest, NULL);

					if (b_recv_result) {
						DWORD dwStatusCode = 0;				// 응답 상태코드
						DWORD dwSize = sizeof(dwStatusCode);							// 응답메시지 사이즈

						BOOL query_result = 0;
						query_result = WinHttpQueryHeaders(hRequest, WINHTTP_QUERY_STATUS_CODE | WINHTTP_QUERY_FLAG_NUMBER, NULL, &dwStatusCode, &dwSize, NULL);

						// 상태메시지 문자열 저장
						wchar_t status_msg[20];
						swprintf_s(status_msg, 20, _T("%d"), dwStatusCode);

						// 응답 크기 확인
						BOOL data_result = WinHttpQueryDataAvailable(hRequest, &dwSize);

						char* pszOutBuffer = new char[dwSize + 1];				// UTF8 응답
						DWORD dwDownloaded = 0;

						BOOL read_result = WinHttpReadData(hRequest, (LPVOID)pszOutBuffer, dwSize, &dwDownloaded);

						// 응답 읽기
						if (read_result) {
							pszOutBuffer[dwDownloaded] = 0;

							// UTF-8 문자열을 유니코드로 변환
							int wSize = MultiByteToWideChar(CP_UTF8, 0, pszOutBuffer, -1, NULL, 0);
							if (wSize > 0 && wSize < sizeof(m_response)/sizeof(wchar_t)) {
								if (MultiByteToWideChar(CP_UTF8, 0, pszOutBuffer, -1, m_response, sizeof(m_response)/sizeof(wchar_t)))
								{
									::MessageBox(m_hWnd, m_response, status_msg, MB_OK);
								}
							}
						}
						delete[] pszOutBuffer;
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
					::MessageBox(m_hWnd, (LPCWSTR)lpMsgBuf, L"에러", MB_OK);
					LocalFree(lpMsgBuf);
				}
				delete[] utf8body;
			}

			WinHttpCloseHandle(hRequest);
		}
		WinHttpCloseHandle(hConnect);
	}
	WinHttpCloseHandle(hSession);
}
