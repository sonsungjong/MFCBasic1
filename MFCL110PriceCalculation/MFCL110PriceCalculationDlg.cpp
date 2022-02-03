
// MFCL110PriceCalculationDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCL110PriceCalculation.h"
#include "MFCL110PriceCalculationDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCL110PriceCalculationDlg dialog



CMFCL110PriceCalculationDlg::CMFCL110PriceCalculationDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCL110PRICECALCULATION_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCL110PriceCalculationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCL110PriceCalculationDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_LBN_SELCHANGE(IDC_ITEM_LIST, &CMFCL110PriceCalculationDlg::OnLbnSelchangeItemList)
END_MESSAGE_MAP()


// CMFCL110PriceCalculationDlg message handlers

BOOL CMFCL110PriceCalculationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	TCHAR* p_item_name[MAX_ITEM_COUNT] = {
		_T("아메리카노    1900원"),
		_T("카페라떼    2500원"),
		_T("카페모카    2800원"),
		_T("카라멜마끼아또    3200원"),
		_T("에스프레소    1800원"),
		_T("바닐라라떼    3500원"),
		_T("카푸치노    3300원"),
		_T("비엔나    3500원"),
	};

	int price[MAX_ITEM_COUNT] = {1900, 2500, 2800, 3200, 1800, 3500, 3300, 3500};

	m_item_list.SubclassDlgItem(IDC_ITEM_LIST, this);
	m_item_list.SetItemHeight(0, 24);
	for (int i = 0; i < MAX_ITEM_COUNT; i++)
	{
		m_item_list.InsertString(i, p_item_name[i]);
		m_item_list.SetItemData(i, price[i]);
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCL110PriceCalculationDlg::OnPaint()
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
HCURSOR CMFCL110PriceCalculationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// 리스트박스 LBN셀체인지
void CMFCL110PriceCalculationDlg::OnLbnSelchangeItemList()
{
	// TODO: Add your control notification handler code here
	int count = m_item_list.GetCount();
	int total_price = 0;
	for (int i = 0; i < count; i++)
	{
		if (m_item_list.GetCheck(i) != 0)
		{
			total_price += m_item_list.GetItemData(i);
		}
	}
	SetDlgItemInt(IDC_TOTAL_PRICE_EDIT, total_price);
}
