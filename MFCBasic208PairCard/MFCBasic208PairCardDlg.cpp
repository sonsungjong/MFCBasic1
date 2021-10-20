
// MFCBasic208PairCardDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCBasic208PairCard.h"
#include "MFCBasic208PairCardDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBasic208PairCardDlg dialog



CMFCBasic208PairCardDlg::CMFCBasic208PairCardDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCBASIC208PAIRCARD_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCBasic208PairCardDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCBasic208PairCardDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCBasic208PairCardDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCBasic208PairCardDlg::OnBnClickedCancel)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CMFCBasic208PairCardDlg message handlers

BOOL CMFCBasic208PairCardDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	CString str;

	for (int i = 0; i < 19; i++) {
		str.Format(L".\\card_image\\%03d.bmp", i);
		m_card_image[i].Load(str);			// 19장의 카드를 읽음
	}

	for (int i = 0; i < 18; i++) {
		m_table[i] = i+1;			// 카드번호
		m_table[18+i] = i+1;
	}

	srand((unsigned int)time(NULL));
	int first, second, temp;
	for (int i = 0; i < 100; i++) {			// 카드섞기
		first = rand() % 36;
		second = rand() % 36;
		if (first != second) {
			// m_table[first] <-> m_table[second]
			temp = m_table[first];
			m_table[first] = m_table[second];
			m_table[second] = temp;
		}
	}

	SetTimer(1, 3000, NULL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCBasic208PairCardDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	if (IsIconic())
	{

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
		CString str;
		int card_index = 0;
		for (int i = 0; i < 36; i++)
		{
			if (m_view_flag == 1) {
				card_index = m_table[i];
			}
			
			m_card_image[card_index].Draw(dc, (i%6)*36, i/6*56);

			str.Format(L"%d", m_table[i]);
			dc.TextOutW(5 + (i % 6) * 36, 5 + i / 6 * 56, str);
		}
		//CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCBasic208PairCardDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCBasic208PairCardDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CMFCBasic208PairCardDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void CMFCBasic208PairCardDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 1) {
		KillTimer(1);			// 1회용 타이머로 만듦
		m_view_flag = 0;
		Invalidate();
	}
	else {
		CDialogEx::OnTimer(nIDEvent);
	}
}
