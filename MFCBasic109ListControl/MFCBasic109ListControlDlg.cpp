
// MFCBasic109ListControlDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCBasic109ListControl.h"
#include "MFCBasic109ListControlDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBasic109ListControlDlg dialog



CMFCBasic109ListControlDlg::CMFCBasic109ListControlDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCBASIC109LISTCONTROL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCBasic109ListControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATA_LIST, m_data_list);
	DDX_Control(pDX, IDC_NAME_EDIT, m_name_edit_ctrl);
}

BEGIN_MESSAGE_MAP(CMFCBasic109ListControlDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCBasic109ListControlDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_ADD_BTN, &CMFCBasic109ListControlDlg::OnBnClickedAddBtn)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_DATA_LIST, &CMFCBasic109ListControlDlg::OnLvnItemchangedDataList)
	ON_BN_CLICKED(IDC_MODIFY_BTN, &CMFCBasic109ListControlDlg::OnBnClickedModifyBtn)
END_MESSAGE_MAP()


// CMFCBasic109ListControlDlg message handlers

BOOL CMFCBasic109ListControlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// LstCtrl타이틀 : LV_COLUMN구조체 사용
	LV_COLUMN add_column;
	add_column.mask = LVCF_TEXT | LVCF_WIDTH;
	add_column.pszText = L"이름";
	add_column.cx = 128;
	m_data_list.InsertColumn(0, &add_column);			// 타이틀의 0번째 항목에 추가

	add_column.pszText = L"전화번호";
	add_column.cx = 128;
	m_data_list.InsertColumn(1, &add_column);

	add_column.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_FMT;
	add_column.pszText = L"주소";
	add_column.cx = 256;
	add_column.fmt = LVCFMT_CENTER;
	m_data_list.InsertColumn(2, &add_column);

	m_data_list.SetExtendedStyle(LVS_EX_FULLROWSELECT);			// 한번에 한 행을 선택할 수 있게 속성 변경

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCBasic109ListControlDlg::OnPaint()
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
HCURSOR CMFCBasic109ListControlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCBasic109ListControlDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CMFCBasic109ListControlDlg::OnBnClickedAddBtn()
{
	// TODO: Add your control notification handler code here
	CString str;
	int index = m_data_list.GetItemCount();
	// LstCtrl내용물 : LV_ITEM구조체 사용
	LV_ITEM add_item;
	
	GetDlgItemText(IDC_NAME_EDIT, str);
	if (str != L"") {
		add_item.mask = LVIF_TEXT;
		add_item.pszText = (wchar_t*)(const wchar_t*)str;				// CString == const wchar_t*    ->  wchar_t*
		add_item.iItem = index;				// 0번째 행에 추가
		add_item.iSubItem = 0;			// 0번째 열에 추가
		// 항목 생성
		m_data_list.InsertItem(&add_item);

		GetDlgItemText(IDC_PHONE_EDIT, str);
		add_item.pszText = (wchar_t*)(const wchar_t*)str;
		add_item.iSubItem = 1;				// 1번째 열에 추가
		// 항목 추가
		m_data_list.SetItem(&add_item);

		// 항목추가2
		GetDlgItemText(IDC_ADDRESS_EDIT, str);
		m_data_list.SetItemText(index, 2, str);

		SetDlgItemText(IDC_NAME_EDIT, L"");
		SetDlgItemText(IDC_PHONE_EDIT, L"");
		SetDlgItemText(IDC_ADDRESS_EDIT, L"");
		m_name_edit_ctrl.SetFocus();
	}
}

// LstControl 이벤트 핸들러
void CMFCBasic109ListControlDlg::OnLvnItemchangedDataList(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	if (pNMLV->uNewState & LVIS_SELECTED) {
		CString str;
		str = m_data_list.GetItemText(pNMLV->iItem, 0);
		SetDlgItemText(IDC_NAME_EDIT, str);

		str = m_data_list.GetItemText(pNMLV->iItem, 1);
		SetDlgItemText(IDC_PHONE_EDIT, str);

		str = m_data_list.GetItemText(pNMLV->iItem, 2);
		SetDlgItemText(IDC_ADDRESS_EDIT, str);
	}

	*pResult = 0;
}


void CMFCBasic109ListControlDlg::OnBnClickedModifyBtn()
{
	// TODO: Add your control notification handler code here
	POSITION pos = m_data_list.GetFirstSelectedItemPosition();
	if (pos != NULL) {
		int index;
		while (pos != NULL) {
			index = m_data_list.GetNextSelectedItem(pos);
		}
		CString str;
		GetDlgItemText(IDC_NAME_EDIT, str);
		m_data_list.SetItemText(index, 0, str);
		GetDlgItemText(IDC_PHONE_EDIT, str);
		m_data_list.SetItemText(index, 1, str);
		GetDlgItemText(IDC_ADDRESS_EDIT, str);
		m_data_list.SetItemText(index, 2, str);
	}
}
