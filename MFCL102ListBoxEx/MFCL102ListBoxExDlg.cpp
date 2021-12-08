
// MFCL102ListBoxExDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCL102ListBoxEx.h"
#include "MFCL102ListBoxExDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCL102ListBoxExDlg dialog



CMFCL102ListBoxExDlg::CMFCL102ListBoxExDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCL102LISTBOXEX_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCL102ListBoxExDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATA_LIST, m_data_list);
}

BEGIN_MESSAGE_MAP(CMFCL102ListBoxExDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ADD_BTN, &CMFCL102ListBoxExDlg::OnBnClickedAddBtn)
	ON_LBN_SELCHANGE(IDC_DATA_LIST, &CMFCL102ListBoxExDlg::OnLbnSelchangeDataList)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CMFCL102ListBoxExDlg message handlers

BOOL CMFCL102ListBoxExDlg::OnInitDialog()
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

void CMFCL102ListBoxExDlg::OnPaint()
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
HCURSOR CMFCL102ListBoxExDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCL102ListBoxExDlg::OnBnClickedAddBtn()
{
	// TODO: Add your control notification handler code here
	CString str, name_str, phone_str;
	PersonData* p = new PersonData;										// 구조체로 리스트박스 성능을 향상
	GetDlgItemText(IDC_NAME_EDIT, name_str);
	GetDlgItemText(IDC_PHONE_EDIT, phone_str);
	int age = GetDlgItemInt(IDC_AGE_EDIT);
	
	_tcscpy_s(p->name, 32, name_str);
	_tcscpy_s(p->phone, 32, phone_str);
	p->age = age;

	str.Format(_T("%s (%d / %s)"), name_str, age, phone_str);

	int index = m_data_list.AddString(str);
	m_data_list.SetItemDataPtr(index, p);					// 동적할당된 p의 주소를 관리
	m_data_list.SetCurSel(index);				// 커서위치 설정
}


void CMFCL102ListBoxExDlg::OnLbnSelchangeDataList()
{
	// TODO: Add your control notification handler code here
	int index = m_data_list.GetCurSel();
	if (LB_ERR != index) {
		PersonData* p = (PersonData*)m_data_list.GetItemDataPtr(index);
		
		SetDlgItemText(IDC_NAME_EDIT, p->name);
		SetDlgItemText(IDC_PHONE_EDIT, p->phone);
		SetDlgItemInt(IDC_AGE_EDIT, p->age);
	}
}


void CMFCL102ListBoxExDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	int count = m_data_list.GetCount();
	PersonData* p;
	for (int i = 0; i < count; i++) {
		p = (PersonData*)m_data_list.GetItemDataPtr(i);
		delete p;
	}
	m_data_list.ResetContent();
}
