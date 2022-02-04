
// MFCL112PriceCalculationDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCL112PriceCalculation.h"
#include "MFCL112PriceCalculationDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCL112PriceCalculationDlg dialog



CMFCL112PriceCalculationDlg::CMFCL112PriceCalculationDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCL112PRICECALCULATION_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCL112PriceCalculationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COUNT_SPIN, m_count_spin);
}

BEGIN_MESSAGE_MAP(CMFCL112PriceCalculationDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_LBN_SELCHANGE(IDC_ITEM_LIST, &CMFCL112PriceCalculationDlg::OnLbnSelchangeItemList)
	ON_NOTIFY(UDN_DELTAPOS, IDC_COUNT_SPIN, &CMFCL112PriceCalculationDlg::OnDeltaposCountSpin)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CMFCL112PriceCalculationDlg message handlers

BOOL CMFCL112PriceCalculationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_count_spin.GetWindowRect(&m_spin_rect);
	ScreenToClient(&m_spin_rect);							// ��ǥ������ Ŭ���̾�Ʈ�� ����

	TCHAR* p_item_name[MAX_COUNT] = {
		_T("�Ƹ޸�ī��            1900��"),
		_T("ī���              2500��"),
		_T("ī���ī              2800��"),
		_T("ī��Ḷ���ƶ�        3200��"),
		_T("����������            1800��"),
		_T("�ٴҶ��            3500��"),
		_T("īǪġ��              3300��"),
		_T("�񿣳�                3500��"),
	};

	int price[MAX_COUNT] = {
		1900, 2500, 2800, 3200, 1800, 3500, 3300, 3500
	};
	m_item_list.SubclassDlgItem(IDC_ITEM_LIST, this);

	m_font.CreatePointFont(96, _T("����ü"));
	m_item_list.SetFont(&m_font);

	m_item_list.SetItemHeight(0, 24);				// ����� ����

	ItemInfo* p;

	for (int i = 0; i < MAX_COUNT; i++) {
		m_item_list.InsertString(i, p_item_name[i]);
		p = new ItemInfo;
		p->price = price[i];
		p->count = 0;
		m_item_list.SetItemDataPtr(i, p);
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCL112PriceCalculationDlg::OnPaint()
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
HCURSOR CMFCL112PriceCalculationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCL112PriceCalculationDlg::CalcTotalPrice()
{
	int total_price = 0;
	int count = m_item_list.GetCount();
	ItemInfo* p;

	for (int i = 0; i < count; i++) {
		if (m_item_list.GetCheck(i)) {
			p = (ItemInfo*)m_item_list.GetItemDataPtr(i);
			total_price += p->price * p->count;
		}
	}
	::SetDlgItemInt(m_hWnd, IDC_TOTAL_PRICE_EDIT, total_price, FALSE);
}

//void CMFCL112PriceCalculationDlg::ChangeText(CListBox* ap_list_box, int a_index, const TCHAR* ap_string)
//{
//	ap_list_box->DeleteString(a_index);
//	ap_list_box->InsertString(a_index, ap_string);
//	ap_list_box->SetCurSel(a_index);
//}

void CMFCL112PriceCalculationDlg::OnLbnSelchangeItemList()
{
	// TODO: Add your control notification handler code here
	int index = m_item_list.GetCurSel();
	ItemInfo* p = (ItemInfo*)m_item_list.GetItemDataPtr(index);

	if (m_item_list.GetCheck(index)) {					// �׸� ���ý�
		if (p->count == 0) { p->count = 1; }
	} else {															// ���� ������
		if (p->count != 0) { p->count = 0; }
	}
	m_item_list.SetCurSel(index);

	// ������Ʈ�� �ϳ��� ������ ����ٴϰ���
	m_count_spin.SetWindowPos(nullptr, m_spin_rect.left, m_spin_rect.top + index * 24, 0, 0, SWP_NOSIZE);
	CalcTotalPrice();
}

// ������Ʈ�� ������ �����ϴ� �̺�Ʈ�ڵ鷯
void CMFCL112PriceCalculationDlg::OnDeltaposCountSpin(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	int index = m_item_list.GetCurSel();
	if (LB_ERR != index && m_item_list.GetCheck(index)) {
		ItemInfo* p = (ItemInfo*)m_item_list.GetItemDataPtr(index);
		if (pNMUpDown->iDelta > 0) {
			if (p->count > 1) { p->count--; }
		}else{
			if (p->count < 100) { p->count++; }
		}
		m_item_list.SetCurSel(index);
		CalcTotalPrice();						// ������Ʈ���� �����ص� ����ƾ ���
	}
}


void CMFCL112PriceCalculationDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	int count = m_item_list.GetCount();
	ItemInfo* p;
	for (int i = 0; i < count; i++) {
		p = (ItemInfo*)m_item_list.GetItemDataPtr(i);
		delete p;
	}
	m_item_list.ResetContent();
}
