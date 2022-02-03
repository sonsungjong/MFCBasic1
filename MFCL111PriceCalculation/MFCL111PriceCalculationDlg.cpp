
// MFCL111PriceCalculationDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCL111PriceCalculation.h"
#include "MFCL111PriceCalculationDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCL111PriceCalculationDlg dialog



CMFCL111PriceCalculationDlg::CMFCL111PriceCalculationDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCL111PRICECALCULATION_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCL111PriceCalculationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COUNT_LIST, m_count_list);
	DDX_Control(pDX, IDC_COUNT_SPIN, m_count_spin);
}

BEGIN_MESSAGE_MAP(CMFCL111PriceCalculationDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_LBN_SELCHANGE(IDC_ITEM_LIST, &CMFCL111PriceCalculationDlg::OnLbnSelchangeItemList)
	ON_NOTIFY(UDN_DELTAPOS, IDC_COUNT_SPIN, &CMFCL111PriceCalculationDlg::OnDeltaposCountSpin)
END_MESSAGE_MAP()


// CMFCL111PriceCalculationDlg message handlers

BOOL CMFCL111PriceCalculationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_count_spin.GetWindowRect(&m_spin_rect);
	ScreenToClient(&m_spin_rect);							// 좌표기준을 클라이언트로

	TCHAR* p_item_name[8] = {
		_T("아메리카노    1900원"),
		_T("카페라떼    2500원"),
		_T("카페모카    2800원"),
		_T("카라멜마끼아또    3200원"),
		_T("에스프레소    1800원"),
		_T("바닐라라떼    3500원"),
		_T("카푸치노    3300원"),
		_T("비엔나    3500원"),
	};

	int price[8] = {
		1900, 2500, 2800, 3200, 1800, 3500, 3300, 3500
	};

	m_item_list.SubclassDlgItem(IDC_ITEM_LIST, this);
	m_item_list.SetItemHeight(0, 24);
	m_count_list.SetItemHeight(0, 24);

	for (int i = 0; i < 8; i++)
	{
		m_item_list.InsertString(i, p_item_name[i]);
		m_item_list.SetItemData(i, price[i]);
		m_count_list.InsertString(i, _T("0"));
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCL111PriceCalculationDlg::OnPaint()
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
HCURSOR CMFCL111PriceCalculationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCL111PriceCalculationDlg::CalcTotalPrice()
{
	int total_price = 0;
	int count = m_item_list.GetCount();
	CString str;

	for (int i = 0; i < count; i++)
	{
		if (m_item_list.GetCheck(i)) { 
			m_count_list.GetText(i, str);
			total_price += m_item_list.GetItemData(i) * _ttoi(str);
		}
	}
	//SetDlgItemInt(IDC_TOTAL_PRICE_EDIT, total_price);
	::SetDlgItemInt(m_hWnd, IDC_TOTAL_PRICE_EDIT, total_price, FALSE);
}

void CMFCL111PriceCalculationDlg::ChangeText(CListBox* ap_list_box, int a_index, const TCHAR* ap_string)
{
	ap_list_box->DeleteString(a_index);
	ap_list_box->InsertString(a_index, ap_string);
	ap_list_box->SetCurSel(a_index);
}
void CMFCL111PriceCalculationDlg::OnLbnSelchangeItemList()
{
	// TODO: Add your control notification handler code here
	int index = m_item_list.GetCurSel();
	CString str;
	m_count_list.GetText(index, str);
	int item_count = _ttoi(str);
	// 항목 선택시
	if (m_item_list.GetCheck(index)) {
		if (item_count == 0) { ChangeText(&m_count_list, index, _T("1")); }
	}
	else {
		if (item_count != 0) { ChangeText(&m_count_list, index, _T("0")); }
	}
	
	m_count_list.SetCurSel(index);
	// 스핀컨트롤 하나로 따라다니게함
	m_count_spin.SetWindowPos(nullptr, m_spin_rect.left, m_spin_rect.top + index * 24, 0, 0, SWP_NOSIZE);
	CalcTotalPrice();
}

// 스핀컨트롤 누르면 반응하는 이벤트핸들러
void CMFCL111PriceCalculationDlg::OnDeltaposCountSpin(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	int index = m_count_list.GetCurSel();
	if(LB_ERR != index && m_item_list.GetCheck(index)){
		CString str;
		m_count_list.GetText(index, str);
		int item_count = _ttoi(str);							// _T("0") -> 0

		if (pNMUpDown->iDelta > 0) {
			if (item_count > 1) { item_count--; }
		} else {
			if (item_count < 100) { item_count++; }
		}
		str.Format(_T("%d"), item_count);					// 1 -> _T("1")
		ChangeText(&m_count_list, index, str);

		CalcTotalPrice();							// 가격 계산하는 루틴
	}
}
