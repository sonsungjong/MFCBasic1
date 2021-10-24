
// MFCBasic209SaveRecentDataDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCBasic209SaveRecentData.h"
#include "MFCBasic209SaveRecentDataDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBasic209SaveRecentDataDlg dialog



CMFCBasic209SaveRecentDataDlg::CMFCBasic209SaveRecentDataDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCBASIC209SAVERECENTDATA_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCBasic209SaveRecentDataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCBasic209SaveRecentDataDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CMFCBasic209SaveRecentDataDlg message handlers

BOOL CMFCBasic209SaveRecentDataDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	// 64��Ʈ�� time�Լ��� srand���� ����ϱ� ���� 32��Ʈ�� �ٲٱ����� unsigned int�� ����ȯ�� ��
	srand((unsigned int)time(NULL));
	SetTimer(1, 800, NULL);				// WM_TIMER

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCBasic209SaveRecentDataDlg::OnPaint()
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
		//CDialogEx::OnPaint();
		CRect r;
		CString str;
		POSITION pos = m_data_list.GetHeadPosition();

		// ����ֱ�
		dc.SelectStockObject(DC_BRUSH);
		dc.SetDCBrushColor(RGB(0, 0, 128));
		dc.SetBkColor(RGB(0, 0, 128));
		dc.SetTextColor(RGB(0, 255, 255));

		for (int i = 0; pos != NULL;i++) {
			str.Format(_T("%d"), *(int*)m_data_list.GetNext(pos));
			r.SetRect(10 + i * 65, 10, 70 + i * 65, 40);
			dc.Rectangle(r);
			dc.DrawText(str, r, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
		}

		for (int i = 0; i<m_data_count; i++) {
			str.Format(_T("%d"), m_move_data[i]);
			r.SetRect(10 + i * 65, 50, 70 + i * 65, 80);
			dc.Rectangle(r);
			dc.DrawText(str, r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}

		for (int i = 0; i < m_data_count; i++) {
			str.Format(_T("%d"), m_index_data[ (i+m_index)%10 ]);
			r.SetRect(10 + i * 65, 90, 70 + i * 65, 120);
			dc.Rectangle(r);
			dc.DrawText(str, r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCBasic209SaveRecentDataDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCBasic209SaveRecentDataDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	KillTimer(1);

	POSITION pos = m_data_list.GetHeadPosition();
	while (pos != NULL) {
		delete (int*)m_data_list.GetNext(pos);
	}
}


void CMFCBasic209SaveRecentDataDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 1) {			// 0.8��
		int temp = rand() % 100;			// 0~99

		int* p = new int;			// �����޸𸮴� Heap�� �Ҵ�Ǿ� �Լ��� ������ ������ ������� ����
		*p = temp;
		m_data_list.AddTail(p);

		if (m_data_list.GetCount() > 10) {
			p = (int*)m_data_list.GetHead();
			delete p;
			m_data_list.RemoveHead();
		}

		if (m_data_count < 10) {
			m_move_data[m_data_count] = temp;
			m_index_data[m_data_count] = temp;
			m_data_count++;
		}
		else {
			for (int i = 0; i < 9; i++) m_move_data[i] = m_move_data[i + 1];
			//memcpy(m_move_data, m_move_data+1, sizeof(int)*9);
			m_move_data[9] = temp;

			// �����͸� �̵���Ű���ʰ� ������ġ�� �ٲ�
			m_index_data[m_index] = temp;
			m_index = (m_index+1)%10;
		}

		Invalidate(FALSE);
	}
	else {
		CDialogEx::OnTimer(nIDEvent);
	}

}
