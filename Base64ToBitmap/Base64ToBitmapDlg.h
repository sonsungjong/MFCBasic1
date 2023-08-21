
// Base64ToBitmapDlg.h : header file
//

#pragma once
#include <string>
#include <wincrypt.h>
#include <vector>

// CBase64ToBitmapDlg dialog
class CBase64ToBitmapDlg : public CDialogEx
{
private:
	std::string base64Image = "Qk1iAAAAAAAAAD4AAAAoAAAACAAAAAgAAAABABgAAAAAAEAAAAAAAAAAAAAAAAAAAAAA////AAEAAQABAADAAwADAAEAAQABAADAAwADAAEAAQABAADAAwADAAEAAQABAADAAwADAAEAAQABAADAAwADAAEAAQABAADAAwADAAEAAQABAADAAwADAAEAAQABAADAAwADAAEAAQABAADAAwADAAEAAQABAADAAwADAAEAAQABAADAAwADAAEAAQABAADAAwADAAEAAQABAADAAwADAAEAAQABAADAAwADAAEAAQABAADAAwADAAEAAQABAADAAwADAAEAAQABAADAAwADAAEAAQABAADAAwADAAEAAQABAADAAwADAAEAAQABAADAAwADAAEAAQABAADAAwADAAEAAQABAADAAwADAAEAAQABAADAAwADAAEAAQABAADAAwADAAEAAQABAADAAwADAAEAAQABAADAAwADAAEAAQABAADAAwAD";

	ULONG_PTR m_token;				// 나중에 GDI+ 해제를 하기위한 변수

// Construction
public:
	CBase64ToBitmapDlg(CWnd* pParent = nullptr);	// standard constructor
	//BYTE* DecodeBase64(std::string& base64String, DWORD& dwSize);
	std::vector<BYTE> DecodeBase64(const std::string& base64);
	void DisplayImage(HWND hwnd, const std::string& base64Image);
	HBITMAP CreateBitmapFromBuffer(BYTE* buffer);

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BASE64TOBITMAP_DIALOG };
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
};
