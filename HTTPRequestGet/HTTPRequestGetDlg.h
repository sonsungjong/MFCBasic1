
// HTTPRequestGetDlg.h : header file
//

#pragma once


// CHTTPRequestGetDlg dialog
class CHTTPRequestGetDlg : public CDialogEx
{
private:
	wchar_t m_response[8192];
	const wchar_t* m_ip = L"118.33.113.122";
	unsigned short m_port = 9443;

// Construction
public:
	CHTTPRequestGetDlg(CWnd* pParent = nullptr);				// ������

	void WebcamFace(wchar_t* _user_id, wchar_t* _user_pw);

	void MobileAuthPush(wchar_t* _user_id);						//  ����� ������û
	void MobileAuthResult(wchar_t* _user_id, wchar_t* _request_id);				// ����� ���������û

	void MobileQrGenerate(wchar_t* _user_id);				// ����� QR��û
	void MobileQrImageDraw();										// ���޹��� QR �̹��� ���
	void MobileQrAuthResult(wchar_t* _user_id);			// QR ������� Ȯ�ο�û

	void MobileOtpSignin(wchar_t* _user_id, wchar_t* _otp_number);				// OTP ������û

	void CallToken();				// ���� �Ϸ�� ������� ���� Token ������ ȣ���ϴ� �Լ� (Ư�� ������Ʈ���� ���� ����)
	void LoginLog();					// ���� �α� ����

	void HttpPostRequest(wchar_t* api_info, wchar_t* headers, wchar_t* body);
	void HttpGetRequest(wchar_t* api_info, wchar_t* headers);

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HTTPREQUESTGET_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedWebcam();
	afx_msg void OnBnClickedMobilePush1();
	afx_msg void OnBnClickedMobilePush2();
	afx_msg void OnBnClickedMobileQr1();
	afx_msg void OnBnClickedMobileQr2();
	afx_msg void OnBnClickedOtp();
	afx_msg void OnBnClickedLoginLog();
};
