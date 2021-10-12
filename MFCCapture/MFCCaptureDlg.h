
// MFCCaptureDlg.h : header file
//

#pragma once


// CMFCCaptureDlg dialog
class CMFCCaptureDlg : public CDialogEx
{
private:
	HWND mh_next_chain = NULL;
	CImage m_image;
	HDC mh_mem_dc;
	CRect m_image_rect;
	
// Construction
public:
	CMFCCaptureDlg(CWnd* pParent = nullptr);	// standard constructor

	void AddEventString(const wchar_t* ap_string);

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCCAPTURE_DIALOG };
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
	CListBox m_event_list;
	afx_msg void OnChangeCbChain(HWND hWndRemove, HWND hWndAfter);
	afx_msg void OnDestroy();
	afx_msg void OnDrawClipboard();
	afx_msg void OnBnClickedSaveBtn();
	CButton m_auto_save_check;
	afx_msg void OnBnClickedOpenPathBtn();
};
