
// MFCBasic106ListBoxDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCBasic106ListBox.h"
#include "MFCBasic106ListBoxDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBasic106ListBoxDlg dialog



CMFCBasic106ListBoxDlg::CMFCBasic106ListBoxDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCBASIC106LISTBOX_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

// ��Ʈ�Ѱ� ������ ����
void CMFCBasic106ListBoxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	// �������� IDC_CHAT_LIST == m_chat_list
	DDX_Control(pDX, IDC_CHAT_LIST, m_chat_list);
}

BEGIN_MESSAGE_MAP(CMFCBasic106ListBoxDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ADD_BTN, &CMFCBasic106ListBoxDlg::OnBnClickedAddBtn)
END_MESSAGE_MAP()


// CMFCBasic106ListBoxDlg message handlers

BOOL CMFCBasic106ListBoxDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCBasic106ListBoxDlg::OnPaint()
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
HCURSOR CMFCBasic106ListBoxDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCBasic106ListBoxDlg::OnBnClickedAddBtn()
{
	// TODO: Add your control notification handler code here
	CString str;
	GetDlgItemText(IDC_CHAT_EDIT, str);

	//m_chat_list.AddString(str);			// ������������ �����߰� (sort�Ӽ��� false�� �ٲٸ� �������� ����)
	int index = m_chat_list.InsertString(-1, str);		// ���ڿ��Է�(��ġ, ���ڿ�), return �߰�����ġ��

	m_chat_list.SetCurSel(index);			// �ش� index��ġ�� ����
	SetDlgItemText(IDC_CHAT_EDIT, L"");

	// ���ҽ�Dlg���� Format(����) -> Tab Order(�Ǽ���) : 1.EditCTL, 2.AddBTN 3. LstBox
	// Ȯ���� Default Button�� False�� �ٲٰ� AddBTN ��ư�� Default Button�� True�� �ؾ� �⺻ ����Ű ��ư�� �ٲ�
}
