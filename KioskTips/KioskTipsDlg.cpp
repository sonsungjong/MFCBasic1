#include "pch.h"
#include "framework.h"
#include "KioskTips.h"
#include "KioskTipsDlg.h"
#include "afxdialogex.h"
#include "AddItemDlg.h"
#include <vector>
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CKioskTipsDlg dialog



CKioskTipsDlg::CKioskTipsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_KIOSKTIPS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}



// ����Ʈ �ڽ��� ������ ���
void CKioskTipsDlg::DrawListItemBkImage(HDC ah_dc, RECT* ap_rect, UINT a_state, COLORREF a_fill_color, COLORREF a_border_color, COLORREF a_select_color)
{
	// �귯�û� ����
	::SelectObject(ah_dc, ::GetStockObject(DC_BRUSH));
	::SetDCBrushColor(ah_dc, a_fill_color);

	// ��� ����
	::SelectObject(ah_dc, ::GetStockObject(DC_PEN));
	if (a_state & ODS_SELECTED) {
		::SetDCPenColor(ah_dc, a_select_color);				// ���� �Ǿ��� �� ���ڻ� (���)
	}
	else {
		::SetDCPenColor(ah_dc, a_border_color);				// ���� �ȵǾ��� �� ���ڻ� (���)
	}

	// �簢�� ���
	::Rectangle(ah_dc, ap_rect->left, ap_rect->top, ap_rect->right, ap_rect->bottom);
}

// ����Ʈ �ڽ��� �߰��� �׸� �׸���
void CKioskTipsDlg::DrawShopItemList(HDC ah_dc, RECT* ap_rect, KID* ap_data)
{
	// �Ǹ� �������� �̹����� �о��� ���¶�� ����Ѵ�
	if (ap_data->p_image && !ap_data->p_image->IsNull()) {
		ap_data->p_image->Draw(ah_dc, ap_rect->left + 3, ap_rect->top - 5, 180, 180);
	}

	::SelectObject(ah_dc, mh_list_font);				// ����Ʈ�ڽ� �۲�
	::SetBkMode(ah_dc, TRANSPARENT);				// ���׵θ� ����
	::SetTextColor(ah_dc, RGB(0, 0, 0));				// �ۻ���

	// �Ǹ� �׸��� �̸�
	ap_rect->top = ap_rect->bottom - 70;				// ��ġ
	ap_rect->bottom = ap_rect->bottom - 50;
	::DrawText(ah_dc, ap_data->name_kor, _tcslen(ap_data->name_kor), ap_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);				// ���

	// ���� �̸�
	::SetTextColor(ah_dc, RGB(64, 98, 98));				// ���� ����
	ap_rect->top += 20;							// ��ġ ����
	ap_rect->bottom += 20;
	::DrawText(ah_dc, ap_data->name_eng, _tcslen(ap_data->name_eng), ap_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);			// ���

	// �Ǹ� �׸� ����
	TCHAR str[128];
	_stprintf_s(str, 128, _T("%d"), ap_data->price);				// ������ ���ڿ���
	::SetTextColor(ah_dc, RGB(200, 100, 100));					// �ǸŰ��� ����
	ap_rect->top += 20;
	ap_rect->bottom += 20;				// ��ġ
	::DrawText(ah_dc, str, _tcslen(str), ap_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);				// ���
}

// ����Ʈ �ڽ��� �߰��� �����׸� �׸���
void CKioskTipsDlg::DrawOrderItemList(HDC ah_dc, RECT* ap_rect, KOD* ap_data)
{
	// �ֹ� ������ ��´�
	KID* p_item = ap_data->p_item;
	// �̹����� ������ ����Ѵ�
	if (p_item->p_image && !p_item->p_image->IsNull()) {
		p_item->p_image->Draw(ah_dc, ap_rect->left + 10, ap_rect->top, 64, 64);
	}

	// ����Ʈ�ڽ� �ٹ̱�
	::SelectObject(ah_dc, mh_list_font);				// ����Ʈ�ڽ� �۲�
	::SetBkMode(ah_dc, TRANSPARENT);				// ���׵θ� ����
	::SetTextColor(ah_dc, RGB(0, 0, 0));				// �� ����
	::TextOut(ah_dc, ap_rect->left + 80, ap_rect->top + 8, p_item->name_kor, _tcslen(p_item->name_kor));					// ���

	::SetTextColor(ah_dc, RGB(64, 98, 98));				// ������ ����
	::TextOut(ah_dc, ap_rect->left + 80, ap_rect->top + 24, p_item->name_eng, _tcslen(p_item->name_eng));					// ���

	// �ֹ� ����
	TCHAR str[128];
	_stprintf_s(str, 128, _T("%d�� * %d�� = %d��"), p_item->price, ap_data->count, p_item->price * ap_data->count);				// �ֹ������� ���ڿ���
	::SetTextColor(ah_dc, RGB(200, 100, 100));				// �ֹ����� ����
	::TextOut(ah_dc, ap_rect->left + 80, ap_rect->top + 43, str, _tcslen(str));				// ���
}

void CKioskTipsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ITEM_LIST, m_item_list);
	DDX_Control(pDX, IDC_ORDER_LIST, m_order_list);
}

BEGIN_MESSAGE_MAP(CKioskTipsDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
	ON_WM_LBUTTONUP()
	ON_WM_DRAWITEM()
	ON_WM_MEASUREITEM()
	ON_BN_CLICKED(IDOK, &CKioskTipsDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CKioskTipsDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_ADD_ORDER_BTN, &CKioskTipsDlg::OnBnClickedAddOrderBtn)
	ON_BN_CLICKED(IDC_ADD_ITEM_BTN, &CKioskTipsDlg::OnBnClickedAddItemBtn)
	ON_BN_CLICKED(IDC_MODIFY_ITEM_BTN, &CKioskTipsDlg::OnBnClickedModifyItemBtn)
	ON_BN_CLICKED(IDC_DEL_ITEM_BTN, &CKioskTipsDlg::OnBnClickedDelItemBtn)
	ON_LBN_DBLCLK(IDC_ITEM_LIST, &CKioskTipsDlg::OnLbnDblclkItemList)
	ON_LBN_DBLCLK(IDC_ORDER_LIST, &CKioskTipsDlg::OnLbnDblclkOrderList)
END_MESSAGE_MAP()


// CKioskTipsDlg message handlers

BOOL CKioskTipsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	// �̹����� �о� ���ȭ������ ����
	m_bk_image.Load(_T(".\\image\\bk.png"));
	SetBackgroundImage(m_bk_image);

	// ����Ʈ �ڽ� �ٹ̱�
	mh_list_bk_brush = ::CreateSolidBrush(RGB(254, 242, 220));				// ����
	mh_list_font = ::CreateFont(18, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("����ü"));

	// ��ü ���� �۲�
	m_price_font.CreateFont(32, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("����ü"));
	LoadDataFromFile(_T("item.kid"));

	// ȭ�� ũ�� ���� (Full HD)
	SetWindowPos(NULL, 0, 0, 1920, 1080, 0);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CKioskTipsDlg::OnPaint()
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
		//dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//CDialogEx::OnPaint();
		TCHAR str[128];
		_stprintf_s(str, 128, _T("��ü �ֹ� �ݾ� : %d ��"), m_total_price);				// ��ü�ݾ� ���ڿ�
		dc.SetBkMode(TRANSPARENT);						// ���ڿ� ����� �����ϰ�
		dc.SetTextColor(RGB(255, 255, 0));					// ���ڿ� ����
		dc.SelectObject(&m_price_font);						// ���ڿ� ��Ʈ
		dc.DrawText(str, CRect(993, 953, 1557, 1019), DT_CENTER | DT_VCENTER | DT_SINGLELINE);				// ���ڿ� ���
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CKioskTipsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CKioskTipsDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	//SaveDataToFile(_T("item.kid"));

	// �Ǹ� �׸��� ���� ��´�
	int count = m_item_list.GetCount();
	KID* p_data;

	for (int i = 0; i < count; ++i) {
		p_data = (KID*)m_item_list.GetItemDataPtr(i);			// �Ǹ� �׸��� �ּҸ� ����
		if (!p_data->p_image->IsNull()) { p_data->p_image->Destroy(); }			// ���� �ε�� �̹��� ����
		delete p_data->p_image;			// �̹��� ��ü ����
		delete p_data;				// �Ǹ��׸� ��������
	}
	m_item_list.ResetContent();			// ����Ʈ�ڽ� ��ü ����

	// �ֹ� �׸��� ���� ��´�
	count = m_order_list.GetCount();
	KOD* p_order;
	for (int i = 0; i < count; ++i) {
		p_order = (KOD*)m_order_list.GetItemDataPtr(i);			// �ֹ����� �ּ� ����
		delete p_order;				// ����
	}
	m_order_list.ResetContent();				// ����Ʈ�ڽ� ��ü ����

	// ����Ʈ�ڽ� �۲ð� �귯�� ����
	::DeleteObject(mh_list_font);
	::DeleteObject(mh_list_bk_brush);
}


HBRUSH CKioskTipsDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	// ����Ʈ�ڽ� ���� �귯�� ��ȯ
	if (pWnd && (pWnd->m_hWnd == m_item_list.m_hWnd || pWnd->m_hWnd == m_order_list.m_hWnd)) {
		return mh_list_bk_brush;
	}

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}


void CKioskTipsDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (point.x >= 358 && point.y >= 953 && point.x <= 924 && point.y <= 1019) {
		OnBnClickedAddOrderBtn();			// �ֹ� ���� �߰�
	}
	else if (CRect(1842, 24, 1894, 76).PtInRect(point)) {
		CMenu menu;
		menu.CreatePopupMenu();				// �˾��޴� ����

		// ������ ����� �˾��޴��� �߰�
		menu.AppendMenu(MF_STRING, 23000, _T("�� �׸� �߰�"));
		menu.AppendMenu(MF_STRING, 23001, _T("���� �׸� ����"));
		menu.AppendMenu(MF_STRING, 23002, _T("���� �׸� ����"));
		menu.AppendMenu(MF_SEPARATOR, 0, _T(""));				// ���м�
		menu.AppendMenu(MF_STRING, 23003, _T("���α׷� ����"));

		CPoint pos;
		GetCursorPos(&pos);				// ȭ����� ���콺 ��ǥ�� ��´�
		menu.TrackPopupMenu(TPM_LEFTALIGN, pos.x, pos.y, this);			// �˾�����
		menu.DestroyMenu();				// �˾� �޴� ����
	}
	//CDialogEx::OnLButtonUp(nFlags, point);
}


void CKioskTipsDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpds)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDCtl == IDC_ITEM_LIST)					// �Ǹ��׸�
	{
		if (lpds->itemID <= (UINT)m_item_list.GetCount()) 
		{
			DrawListItemBkImage(lpds->hDC, &lpds->rcItem, lpds->itemState, RGB(254, 242, 220), RGB(254, 242, 220), RGB(0, 168, 228));				// �Ǹ��׸� ��� �׸���
			DrawShopItemList(lpds->hDC, &lpds->rcItem, (KID*)lpds->itemData);				// �Ǹ��׸� ���� �׸���
		}
	} else if (nIDCtl == IDC_ORDER_LIST)				// �ֹ� �׸�
	{
		if (lpds->itemID <= (UINT)m_order_list.GetCount())
		{
			DrawListItemBkImage(lpds->hDC, &lpds->rcItem, lpds->itemState, RGB(254, 242, 220), RGB(254, 242, 220), RGB(0, 168, 228));				// �ֹ��׸� ���
			DrawOrderItemList(lpds->hDC, &lpds->rcItem, (KOD*)lpds->itemData);				// �ֹ��׸� ���� �׸���
		}
	} else { CDialogEx::OnDrawItem(nIDCtl, lpds); }
}


void CKioskTipsDlg::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpms)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDCtl == IDC_ITEM_LIST)				// �Ǹ��׸�
	{
		// �Ǹ� �׸��� ��Ƽ�÷��� ����ϱ� ������ ���� ���̸� ����������Ѵ�
		lpms->itemWidth = 180;
		lpms->itemHeight = 250;
	}
	else if (nIDCtl == IDC_ORDER_LIST)		// �ֹ��׸�
	{
		lpms->itemHeight = 64;
	}
	else {
		CDialogEx::OnMeasureItem(nIDCtl, lpms);
	}
}


BOOL CKioskTipsDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class
	// ������ ���� ���Ǵ� ����� ó��
	if (wParam == 23000) { OnBnClickedAddItemBtn(); }			// �׸� �߰�
	else if (wParam == 23001) { OnBnClickedModifyItemBtn(); }		// �׸� ����
	else if (wParam == 23002) { OnBnClickedDelItemBtn(); }			// �׸� ����
	else if (wParam == 23003) { OnBnClickedCancel(); }					// ��ȭ���ڴݱ�

	return CDialogEx::OnCommand(wParam, lParam);
}


void CKioskTipsDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CKioskTipsDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	int result = MessageBox(_T("���α׷��� �����Ͻðڽ��ϱ�?"), _T("����"), MB_OKCANCEL|MB_ICONQUESTION);
	if (result == IDOK) {
		CDialogEx::OnCancel();
	}
}


void CKioskTipsDlg::OnBnClickedAddOrderBtn()
{
	// TODO: Add your control notification handler code here
	int index = m_item_list.GetCurSel();
	if (index != LB_ERR)
	{
		// ����ڰ� ������ �׸� ����� �Ǹ� �׸��� �ּ�
		KID* p_item = (KID*)m_item_list.GetItemDataPtr(index);
		KOD* p_check;
		
		// ������ �׸��� �ִ��� üũ�ϱ� ���ؼ� �׸���� ��´�
		int count = m_order_list.GetCount(), i;
		for (i = 0; i < count; i++) {
			// i��° �ֹ� ������ ��´�
			p_check = (KOD*)m_order_list.GetItemDataPtr(i);
			if (p_check->p_item == p_item)
			{
				p_check->count++;
				m_order_list.SetCurSel(i);
				break;
			}
		}
		// ���� �׸��� ���� ���
		if (i == count)
		{
			p_check = new KOD;
			p_check->count = 1;
			p_check->p_item = p_item;
			index = m_order_list.InsertString(-1, _T(""));
			m_order_list.SetItemDataPtr(index, p_check);
			m_order_list.SetCurSel(index);
		}

		// ��ü ���� 0�� �ʱ�ȭ
		m_total_price = 0;
		count = m_order_list.GetCount();				// �ֹ� ��� ���� ��´�
		for (int i = 0; i < count; i++) {
			p_check = (KOD*)m_order_list.GetItemDataPtr(i);
			m_total_price += p_check->count * p_check->p_item->price;
		}
		// ��ü �ֹ� ������ ȭ�鿡 ����!
		InvalidateRect(CRect(993, 953, 1557, 1019));
	}
}


void CKioskTipsDlg::OnBnClickedAddItemBtn()
{
	// TODO: Add your control notification handler code here
	AddItemDlg ins_dlg;

	if (IDOK == ins_dlg.DoModal()) {
		// �Ǹ� �׸� ���� ������ ������ �޸� �Ҵ�
		KID* p_data = new KID;
		// ���� ����
		_tcscpy_s(p_data->name_kor, 64, ins_dlg.GetNameKor());
		_tcscpy_s(p_data->name_eng, 64, ins_dlg.GetNameEng());
		_tcscpy_s(p_data->image_path, MAX_PATH, ins_dlg.GetImagePath());
		p_data->price = ins_dlg.GetPrice();

		p_data->p_image = new CImage;			// �̹��� ��ü�� �Ҵ�
		p_data->p_image->Load(p_data->image_path);		// �̹��� ��ü�� �д´�

		// ����Ʈ �ڽ��� �׸� �߰�
		int index = m_item_list.InsertString(-1, _T(""));
		m_item_list.SetItemDataPtr(index, p_data);
		m_item_list.SetCurSel(index);
	}
}


void CKioskTipsDlg::OnBnClickedModifyItemBtn()
{
	// TODO: Add your control notification handler code here
	// ���õǾ��ִ� �Ǹ��׸��� ��ġ�� ��´�
	int index = m_item_list.GetCurSel();
	if (index != LB_ERR)
	{
		// �ش� ��ġ�� �ּҸ� ��´�
		KID* p = (KID*)m_item_list.GetItemDataPtr(index);
		AddItemDlg ins_dlg;
		// ��ȭ���� ��� ���� ���� ��ǰ ������ ����
		ins_dlg.SetKidData(p->name_kor, p->name_eng, p->image_path, p->price);
		// ��ȭ���� ���
		INT_PTR nRes = ins_dlg.DoModal();
		if (IDOK == nRes) {
			// ���� ������ ���� �޸𸮿� ����
			_tcscpy_s(p->name_kor, 64, ins_dlg.GetNameKor());
			_tcscpy_s(p->name_eng, 64, ins_dlg.GetNameEng());
			p->price = ins_dlg.GetPrice();

			// �̹����� ����Ȱ��
			if (_tcscmp(p->image_path, ins_dlg.GetImagePath())) {
				_tcscpy_s(p->image_path, MAX_PATH, ins_dlg.GetImagePath());	// �̹��� ��� ������Ʈ

				if (p->p_image) {
					// ���� �ε�� �̹����� ����
					if (!p->p_image->IsNull()) { p->p_image->Destroy(); }
				}
				else { p->p_image = new CImage; }
				p->p_image->Load(p->image_path);
			}
			// ���� ���� �ݿ��� ���� ����� �׸��� ���� �׸����� ����
			m_item_list.SetCurSel(index);
		}
	}
}


void CKioskTipsDlg::OnBnClickedDelItemBtn()
{
	// TODO: Add your control notification handler code here
	int index = m_item_list.GetCurSel();
	if (index != LB_ERR) {
		// ������ �׸��� �ּҸ� ��´�
		KID* p_data = (KID*)m_item_list.GetItemDataPtr(index);
		int res = MessageBox(p_data->name_kor, _T("�Ʒ��� ��ǰ ������ �����Ͻðڽ��ϱ�?"), MB_OKCANCEL|MB_ICONQUESTION);
		if (IDOK == res) {
			delete p_data;				// ���� ����
			m_item_list.DeleteString(index);				// �׸� ����

			// ���� �� ���� �׸� ����
			m_item_list.SetCurSel(index - (m_item_list.GetCount() == index));
		}
	}
}


void CKioskTipsDlg::OnLbnDblclkItemList()
{
	// TODO: Add your control notification handler code here
	OnBnClickedAddOrderBtn();				// �ֹ����� �߰�
}


void CKioskTipsDlg::OnLbnDblclkOrderList()
{
	// TODO: Add your control notification handler code here
	int index = m_order_list.GetCurSel();
	if (index != LB_ERR) {
		// ���õ� �ֹ������� �ּҸ� ��´�
		KOD* p_order = (KOD*)m_order_list.GetItemDataPtr(index);
		m_total_price -= p_order->p_item->price;			// �ѱݾ� ����
		p_order->count--;

		if (!p_order->count) {
			// 0���� �Ǹ� �ֹ� ���� ����
			delete p_order;
			m_order_list.DeleteString(index);
		}
		else {
			// 0���� �ƴϸ� Ŀ�� �缳��
			m_order_list.SetCurSel(index);
		}
		InvalidateRect(CRect(993, 953, 1557, 1019));
	}
}

// Ű����ũ ������ ������ ������ ���Ͽ� ����
void CKioskTipsDlg::SaveDataToFile(const TCHAR* ap_path_name)
{
	int count = m_item_list.GetCount();			// ����Ʈ�ڽ� �׸� ������ ����
	KID* p_data;
	FILE* p_file = NULL;

	// ������ ������� ����
	if (0 == _tfopen_s(&p_file, ap_path_name, _T("wb")))
	{
		fwrite(&count, sizeof(int), 1, p_file);			// �׸�� ����
		for (int i = 0; i < count; ++i)
		{
			p_data = (KID*)m_item_list.GetItemDataPtr(i);		// i �� �׸� ����� �Ǹ����� �ּҸ� ����
			fwrite(p_data, sizeof(KID), 1, p_file);			// ���Ͽ� ����
		}
		fclose(p_file);			// ���� �ݱ�
	}
}

// ������ ��ο��� ������ ������ �о Ű����ũ ������ ������
void CKioskTipsDlg::LoadDataFromFile(const TCHAR* ap_path_name)
{
	KID* p_data;
	TCHAR menu_kor[9][64] = { _T("���̽� �Ƹ޸�ī��"), _T("���� ��ũƼ"), _T("���� ������"), _T("���̽����� ����"), _T("������ ���� ���̵�"), _T("�ڸ� ���̵�"), _T("�� ������ġ"), _T("ũ�οͻ� ������ġ"), _T("ġŲ ������")};
	TCHAR menu_eng[9][64] = { _T("iced americano"), _T("strawberry milk tea"), _T("strawberry smoothie"), _T("iced choco bledded"), _T("orange lime ade"), _T("grapefruit ade"), _T("ham sandwich"), _T("croissant sandwich"), _T("chicken salad")};
	TCHAR menu_image[9][MAX_PATH] = { _T(".\\image\\004.png"), _T(".\\image\\006.png"), _T(".\\image\\007.png"), _T(".\\image\\005.png"), _T(".\\image\\008.png"), _T(".\\image\\009.png"), _T(".\\image\\003.png"), _T(".\\image\\001.png"), _T(".\\image\\002.png")};
	int menu_price[9] = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000};


	/*
	FILE* p_file = NULL;

	// ������ ������ �б���� ����
	if (0 == _tfopen_s(&p_file, ap_path_name, _T("rb")))
	{
		fread(&count, sizeof(int), 1, p_file);			// ����� �׸��� ���� ����
		for (int i = 0; i < count; ++i) {
			p_data = new KID;				// �Ǹ� ������ ������ �޸� �Ҵ�
			fread(p_data, sizeof(KID), 1, p_file);				// �׸� ������ ����
			p_data->p_image = new CImage;			// �̹��� ��ü ����
			p_data->p_image->Load(p_data->image_path);				// �̹��� �ε�

			m_item_list.InsertString(-1, _T(""));			// ����Ʈ�ڽ� �׸��߰�
			m_item_list.SetItemDataPtr(i, p_data);			// �߰� �׸� ���� ����
		}
		fclose(p_file);				// ���� ����
	}
	*/

	int count = sizeof(menu_price) / sizeof(int);
	p_data = new KID[count];
	
	for (int i = 0; i < count; i++)
	{		
		// p_data�� ���� ����
		KID* pp = p_data+i;
		_tcscpy_s(pp->name_kor, 64, menu_kor[i]);
		_tcscpy_s(pp->name_eng, 64, menu_eng[i]);
		_tcscpy_s(pp->image_path, MAX_PATH, menu_image[i]);
		pp->price = menu_price[i];

		pp->p_image = new CImage;				// �̹��� ��ü ����
		pp->p_image->Load(pp->image_path);				// �̹��� �ε�
	}

	int j = 0;
	for (int i = 0; i < count; ++i)
	{
		if (j >= count) {
			j = j % (count-1);
		}
		m_item_list.InsertString(-1, _T(""));				// ����Ʈ�ڽ��� ���׸� �߰�
		m_item_list.SetItemDataPtr(i, p_data+j);			// ���׸� ���� ����
		j += 3;
	}
}
