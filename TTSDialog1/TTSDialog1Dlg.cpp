
// TTSDialog1Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "TTSDialog1.h"
#include "TTSDialog1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTTSDialog1Dlg dialog



CTTSDialog1Dlg::CTTSDialog1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TTSDIALOG1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTTSDialog1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTTSDialog1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CTTSDialog1Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CTTSDialog1Dlg::OnBnClickedCancel)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON1, &CTTSDialog1Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CTTSDialog1Dlg message handlers

BOOL CTTSDialog1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	CoInitialize(NULL);

	HRESULT hr = mp_voice_engine.CoCreateInstance(CLSID_SpVoice);
	if (SUCCEEDED(hr)) {
		m_engine_flag = 1;
		SetDlgItemText(IDC_EDIT1, _T("승객 여러분! 지금 내리실 역은 성수역, 성수역입니다!"));
	}
	else {
		SetDlgItemText(IDC_EDIT1, _T("TTS 엔진을 사용할 수 없습니다."));
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTTSDialog1Dlg::OnPaint()
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
HCURSOR CTTSDialog1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTTSDialog1Dlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	// 
	//CDialogEx::OnOK();
}


void CTTSDialog1Dlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnCancel();
}



void CTTSDialog1Dlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	DestroyWindow();

	CDialogEx::OnClose();
}


void CTTSDialog1Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	if (m_engine_flag == 1) {
		mp_voice_engine.Release();
	}
	CoUninitialize();
}


void CTTSDialog1Dlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	if (m_engine_flag == 1) {
		CString str;
		GetDlgItemText(IDC_EDIT1, str);

		HRESULT hr = mp_voice_engine->Speak((TCHAR*)(const TCHAR*)str, SPF_ASYNC | SPF_IS_NOT_XML, 0);
		if (FAILED(hr)) {
			MessageBox(_T("TTS COM Engine 오류 - 말을 할 수 없습니다."), _T("엔진 오류"), MB_ICONSTOP);
		}
	}
}
