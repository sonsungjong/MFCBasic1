
// HTTPRequestGetDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "HTTPRequestGet.h"

#include <string>
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

void CHTTPRequestGetDlg::WebcamFace(wchar_t* _user_id, wchar_t* _user_pw)
{
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




//// Get��û �׽�Ʈ https://jsonplaceholder.typicode.com/guide/
//// 'https://jsonplaceholder.typicode.com/posts/1'
//void CHTTPRequestGetDlg::OnBnClickedTest()
//{
//	TCHAR response_text[1024] = { 0, };				// ����� ũ��� ����
//	int response_index = 0;
//
//	HINTERNET hSession = WinHttpOpen(L"User Agent/1.0",
//		WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
//
//	if (hSession) {
//		HINTERNET hConnect = WinHttpConnect(hSession, L"jsonplaceholder.typicode.com", INTERNET_DEFAULT_HTTPS_PORT, 0);
//
//		if (hConnect) {
//			HINTERNET hRequest = WinHttpOpenRequest(hConnect, L"GET", L"/posts/1",
//				NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);
//
//			if (hRequest) {
//				BOOL bResults = WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0,
//					WINHTTP_NO_REQUEST_DATA, 0, 0, 0);
//
//				if (bResults) {
//					bResults = WinHttpReceiveResponse(hRequest, NULL);
//
//					if (bResults) {
//						DWORD dwSize = 0;
//						DWORD dwDownloaded = 0;
//
//						do {
//							dwSize = 0;
//							WinHttpQueryDataAvailable(hRequest, &dwSize);
//							BYTE* pszOutBuffer = new BYTE[dwSize + 1];
//							ZeroMemory(pszOutBuffer, dwSize + 1);
//
//							if (WinHttpReadData(hRequest, (LPVOID)pszOutBuffer, dwSize, &dwDownloaded)) {
//								TCHAR tempBuffer[1024];
//								MultiByteToWideChar(CP_UTF8, 0, (char*)pszOutBuffer, -1, tempBuffer, sizeof(tempBuffer) / sizeof(tempBuffer[0]));
//								// ��� ûũ�� �ϳ��� ���ڿ��� �����Ѵ�.
//								_tcscat_s(response_text, sizeof(response_text) / sizeof(response_text[0]), tempBuffer);
//							}
//
//							delete[] pszOutBuffer;
//						} while (dwSize > 0);
//
//						::MessageBox(m_hWnd, response_text, _T("Response"), MB_OK);
//
//					}
//				}
//
//				WinHttpCloseHandle(hRequest);
//			}
//
//			WinHttpCloseHandle(hConnect);
//		}
//
//		WinHttpCloseHandle(hSession);
//	}
//}


void CHTTPRequestGetDlg::OnBnClickedWebcam()
{
	
}


void CHTTPRequestGetDlg::OnBnClickedMobilePush1()
{
	TCHAR user_id[20] = { 0, };
	::GetDlgItemText(m_hWnd, IDC_USERID, user_id, 20);
	MobileAuthPush(user_id);
}


void CHTTPRequestGetDlg::OnBnClickedMobilePush2()
{
	
}


void CHTTPRequestGetDlg::OnBnClickedMobileQr1()
{
	
}


void CHTTPRequestGetDlg::OnBnClickedMobileQr2()
{
	
}


void CHTTPRequestGetDlg::OnBnClickedOtp()
{
	
}

void CHTTPRequestGetDlg::OnBnClickedLoginLog()
{
	TCHAR user_id[20] = { 0, };
	::GetDlgItemText(m_hWnd, IDC_USERID, user_id, 20);

	LoginLog();
}




void CHTTPRequestGetDlg::MobileAuthPush(wchar_t* _user_id)
{
	// ���� �� ���� �ڵ� �ʱ�ȭ
	HINTERNET hSession = WinHttpOpen(L"User Agent", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);

	if (hSession) {
		HINTERNET hConnect = WinHttpConnect(hSession, L"118.33.113.122", 9443, 0);					// ���� IP (URL) �� ��Ʈ

		if (hConnect) {
			// POST ��û ����
			HINTERNET hRequest = WinHttpOpenRequest(hConnect, L"POST", L"/api/v1/auth/face-pattern/auth-push", NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);				// POST�������� ��û URL����

			if (hRequest) {
				// ��� ����
				WinHttpAddRequestHeaders(hRequest, L"Content-Type: application/json", -1L, WINHTTP_ADDREQ_FLAG_ADD);				// JSON ��û
				WinHttpAddRequestHeaders(hRequest, L"client_computer_type: pc", -1L, WINHTTP_ADDREQ_FLAG_ADD);				// PC Ÿ�� ��� �߰�
				WinHttpAddRequestHeaders(hRequest, L"accept: application/json", -1L, WINHTTP_ADDREQ_FLAG_ADD); // accept ��� �߰�

				// ��û �ٵ� ����
				std::wstring body = LR"(
{
  "userId": "9875587",
}
)";

				// �۽ſ� �޽��� UTF8�� ��ȯ
				int utf8_length = WideCharToMultiByte(CP_UTF8, 0, body.c_str(), -1, NULL, 0, NULL, NULL);
				char* utf8body = new char[utf8_length];
				WideCharToMultiByte(CP_UTF8, 0, body.c_str(), -1, utf8body, utf8_length, NULL, NULL);

				// ������ ���� ����
				DWORD dwFlags = SECURITY_FLAG_IGNORE_UNKNOWN_CA |
					SECURITY_FLAG_IGNORE_CERT_WRONG_USAGE |
					SECURITY_FLAG_IGNORE_CERT_CN_INVALID |
					SECURITY_FLAG_IGNORE_CERT_DATE_INVALID;
				WinHttpSetOption(hRequest, WINHTTP_OPTION_SECURITY_FLAGS, &dwFlags, sizeof(dwFlags));


				// ��û�޽��� http����
				BOOL b_send_result = WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, (LPVOID)utf8body, utf8_length, utf8_length, 0);
				if (b_send_result) {

					// http���� ����
					BOOL b_recv_result = WinHttpReceiveResponse(hRequest, NULL);

					if (b_recv_result) {
						DWORD dwStatusCode = 0;				// ���� �����ڵ�
						DWORD dwSize = sizeof(dwStatusCode);							// ����޽��� ������

						BOOL query_result = 0;
						query_result = WinHttpQueryHeaders(hRequest, WINHTTP_QUERY_STATUS_CODE | WINHTTP_QUERY_FLAG_NUMBER, NULL, &dwStatusCode, &dwSize, NULL);

						// ���¸޽��� ���ڿ� ����
						TCHAR status_msg[20];
						_stprintf_s(status_msg, 20, _T("%d"), dwStatusCode);

						if (dwStatusCode != 200) {
							// ���� ó��
							::MessageBox(m_hWnd, L"ũ�� ���� �� ����", status_msg, MB_OK);
						}
						else {
							// ���� ũ�� Ȯ��
							BOOL data_result = WinHttpQueryDataAvailable(hRequest, &dwSize);

							char* pszOutBuffer = new char[dwSize + 1];				// UTF8 ����
							DWORD dwDownloaded = 0;

							BOOL read_result = WinHttpReadData(hRequest, (LPVOID)pszOutBuffer, dwSize, &dwDownloaded);

							// ���� �б�
							if (read_result) {
								pszOutBuffer[dwDownloaded] = 0;

								// UTF-8 ���ڿ��� �����ڵ�� ��ȯ
								int wSize = MultiByteToWideChar(CP_UTF8, 0, pszOutBuffer, -1, NULL, 0);
								if (wSize > 0) {
									wchar_t* pwszBuffer = new wchar_t[wSize];
									if (MultiByteToWideChar(CP_UTF8, 0, pszOutBuffer, -1, pwszBuffer, wSize)) {
										::MessageBox(m_hWnd, pwszBuffer, status_msg, MB_OK);
									}
									delete[] pwszBuffer;
								}
							}

							delete[] pszOutBuffer;
						}
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
					::MessageBox(m_hWnd, (LPCWSTR)lpMsgBuf, L"����", MB_OK);
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

void CHTTPRequestGetDlg::MobileAuthResult(wchar_t* _user_id, wchar_t* _request_id)
{
}

void CHTTPRequestGetDlg::MobileQrGenerate(wchar_t* _user_id)
{
}

void CHTTPRequestGetDlg::MobileQrImageDraw()
{
}

void CHTTPRequestGetDlg::MobileQrAuthResult(wchar_t* _user_id)
{
}

void CHTTPRequestGetDlg::MobileOtpSignin(wchar_t* _user_id, wchar_t* _otp_number)
{
}

void CHTTPRequestGetDlg::CallToken()
{
}

/*
POST�޽���

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
  "userName": "����"
}
*/
void CHTTPRequestGetDlg::LoginLog()
{
	// ���� �� ���� �ڵ� �ʱ�ȭ
	HINTERNET hSession = WinHttpOpen(L"User Agent", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);

	if (hSession) {
		HINTERNET hConnect = WinHttpConnect(hSession, L"118.33.113.122", 9443, 0);					// ���� IP (URL) �� ��Ʈ

		if (hConnect) {
			// POST ��û ����
			HINTERNET hRequest = WinHttpOpenRequest(hConnect, L"POST", L"/api/loginLog", NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);				// POST�������� ��û URL����

			if (hRequest) {
				// ��� ����
				WinHttpAddRequestHeaders(hRequest, L"Content-Type: application/json", -1L, WINHTTP_ADDREQ_FLAG_ADD);				// JSON ��û

				// ��û �ٵ� ����
				std::wstring body = LR"(
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
  "userName": "����"
}
)";
				
				// �۽ſ� �޽��� UTF8�� ��ȯ
				int utf8_length = WideCharToMultiByte(CP_UTF8, 0, body.c_str(), -1, NULL, 0, NULL, NULL);
				char* utf8body = new char[utf8_length];
				WideCharToMultiByte(CP_UTF8, 0, body.c_str(), -1, utf8body, utf8_length, NULL, NULL);

				// ������ ���� ����
				DWORD dwFlags = SECURITY_FLAG_IGNORE_UNKNOWN_CA |
					SECURITY_FLAG_IGNORE_CERT_WRONG_USAGE |
					SECURITY_FLAG_IGNORE_CERT_CN_INVALID |
					SECURITY_FLAG_IGNORE_CERT_DATE_INVALID;
				WinHttpSetOption(hRequest, WINHTTP_OPTION_SECURITY_FLAGS, &dwFlags, sizeof(dwFlags));


				// ��û�޽��� http����
				BOOL b_send_result = WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, (LPVOID)utf8body, utf8_length, utf8_length, 0);
				if (b_send_result) {

					// http���� ����
					BOOL b_recv_result = WinHttpReceiveResponse(hRequest, NULL);

					if (b_recv_result) {
						DWORD dwStatusCode = 0;				// ���� �����ڵ�
						DWORD dwSize = sizeof(dwStatusCode);							// ����޽��� ������

						BOOL query_result = 0;
						query_result = WinHttpQueryHeaders(hRequest, WINHTTP_QUERY_STATUS_CODE | WINHTTP_QUERY_FLAG_NUMBER, NULL, &dwStatusCode, &dwSize, NULL);

						// ���¸޽��� ���ڿ� ����
						TCHAR status_msg[20];
						_stprintf_s(status_msg, 20, _T("%d"), dwStatusCode);

						if (dwStatusCode != 200) {
							// ���� ó��
							::MessageBox(m_hWnd, L"ũ�� ���� �� ����", status_msg, MB_OK);
						}
						else {
							// ���� ũ�� Ȯ��
							BOOL data_result = WinHttpQueryDataAvailable(hRequest, &dwSize);
							
							char* pszOutBuffer = new char[dwSize + 1];				// UTF8 ����
							DWORD dwDownloaded = 0;

							BOOL read_result = WinHttpReadData(hRequest, (LPVOID)pszOutBuffer, dwSize, &dwDownloaded);

							// ���� �б�
							if (read_result) {
								pszOutBuffer[dwDownloaded] = 0;

								// UTF-8 ���ڿ��� �����ڵ�� ��ȯ
								int wSize = MultiByteToWideChar(CP_UTF8, 0, pszOutBuffer, -1, NULL, 0);
								if (wSize > 0) {
									wchar_t* pwszBuffer = new wchar_t[wSize];
									if (MultiByteToWideChar(CP_UTF8, 0, pszOutBuffer, -1, pwszBuffer, wSize)) {
										::MessageBox(m_hWnd, pwszBuffer, status_msg, MB_OK);
									}
									delete[] pwszBuffer;
								}
							}

							delete[] pszOutBuffer;
						}
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
					::MessageBox(m_hWnd, (LPCWSTR)lpMsgBuf, L"����", MB_OK);
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