
// D2DButton2Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "D2DButton2.h"
#include "D2DButton2Dlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ʈ D2D ��ü�� ���� ������ �����ؼ� �ڵ� �ʱ�ȭ ��Ų��.
TWD_Core g_tw_d2d_core;


// CD2DButton2Dlg dialog
CD2DButton2Dlg::CD2DButton2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_D2DBUTTON2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CD2DButton2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CD2DButton2Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CD2DButton2Dlg::OnBnClickedOk)
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(27000, &CD2DButton2Dlg::On27000)
END_MESSAGE_MAP()


// CD2DButton2Dlg message handlers

BOOL CD2DButton2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	// Ŭ���̾�Ʈ ������ ����
	::RECT r;
	::GetClientRect(m_hWnd, &r);
	// D2D ��� ���� ����
	m_view.Create(m_hWnd, &r);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CD2DButton2Dlg::OnPaint()
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
		//CDialogEx::OnPaint();
		m_view.OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CD2DButton2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CD2DButton2Dlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CD2DButton2Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
}


void CD2DButton2Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	for (int i = 0; i < 3; i++) {
		// ������ ��ư�� üũ�Ѵ�
		if (TW_PtInRectF(m_view.GetBtnRect(i), &point)) {
			// ������ ��ư�� �ε����� ����Ѵ�.
			m_view.SetSelectedBtn(i);
			// ������ ��ư�� ���¸� 1�� �����Ѵ�.
			m_view.SetBtnState(i, 1);
			// ���� ��Ȳ�� �ݿ��ǵ��� ��ư�� �ٽ� �׸���.
			m_view.UpdateView();
		}
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CD2DButton2Dlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	unsigned char index = m_view.GetSelectedBtn();

	// ������ ��ư�� �ִ��� üũ�Ѵ�.
	if (index != 0xFF) {
		// ��ư�� ���°� 1�� ��쿡�� Ŭ�� ���¸� �뺸�Ѵ�.
		// �̹� 0�̶�� ��ư �ۿ� ���콺�� �ִ� ���¶� �ٽ� �׸��� �ʴ´�.
		if (m_view.GetBtnState(index) == 1) {
			if (TW_PtInRectF(m_view.GetBtnRect(index), &point)) {
				PostMessage(27000, index);
			}
			m_view.SetBtnState(index, 0);
			m_view.UpdateView();
		}
		// ��ư ���� ���¸� �ʱ�ȭ�Ѵ�.
		m_view.SetSelectedBtn(0xFF);
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CD2DButton2Dlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	unsigned char index = m_view.GetSelectedBtn();

	// ���õ� ��ư�� �ִ��� üũ�Ѵ�.
	if (index != 0xFF) {
		// ��ư ���ο� ���콺�� �ִ��� üũ�Ѵ�.
		if (TW_PtInRectF(m_view.GetBtnRect(index), &point)) {
			// ���ο� �ִ��ϴ��� �̹� 1�� ���¶�� ���¸� �������� �ʴ´�.
			if (m_view.GetBtnState(index) == 0) {
				m_view.SetBtnState(index, 1);
				m_view.UpdateView();
			}
		}
		else {
			// �ܺο� �ִ��� �̹� 0�� ���¶�� ���¸� �������� �ʴ´�.
			if (m_view.GetBtnState(index) == 1) {
				m_view.SetBtnState(index, 0);
				m_view.UpdateView();
			}
		}
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


afx_msg LRESULT CD2DButton2Dlg::On27000(WPARAM wParam, LPARAM lParam)
{
	const TCHAR* p_msg_list[3] = { _T("�ռ���"), _T("�̰���"), _T("�ױ�����")};
	AfxMessageBox(p_msg_list[wParam]);
	return 0;
}
