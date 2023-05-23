
// MFCOpenCV3Dlg.h : header file
//

#pragma once
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

class CMFCOpenCV3Dlg : public CDialogEx
{
public:
	CMFCOpenCV3Dlg(CWnd* pParent = nullptr);	// standard constructor

private:
	CRect m_rect;
	cv::VideoCapture* m_capture;
	cv::Mat m_mat_frame;

	char m_flip = 0;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCOPENCV3_DIALOG };
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
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedFlipBtn();
};
