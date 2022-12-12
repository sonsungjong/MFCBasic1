
// MFCL228KakaoDlg.h : header file
//

#pragma once
struct ChatRoomData
{
	HWND h_room_wnd;				// ����Ʈ�ڽ� �ڵ�
	HWND h_edit_wnd;				// ���� ��Ʈ�� �ڵ�
};

// CMFCL228KakaoDlg dialog
class CMFCL228KakaoDlg : public CDialogEx
{
// Construction
public:
	CMFCL228KakaoDlg(CWnd* pParent = nullptr);	// standard constructor
	void ResetChatRoomData();



// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCL228KAKAO_DIALOG };
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
	CListBox m_room_list;
	afx_msg void OnBnClickedFindRoomBtn();
	afx_msg void OnBnClickedSendBtn();
	afx_msg void OnDestroy();
};
