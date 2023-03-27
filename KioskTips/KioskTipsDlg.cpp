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



// 리스트 박스의 아이템 배경
void CKioskTipsDlg::DrawListItemBkImage(HDC ah_dc, RECT* ap_rect, UINT a_state, COLORREF a_fill_color, COLORREF a_border_color, COLORREF a_select_color)
{
	// 브러시색 변경
	::SelectObject(ah_dc, ::GetStockObject(DC_BRUSH));
	::SetDCBrushColor(ah_dc, a_fill_color);

	// 펜색 변경
	::SelectObject(ah_dc, ::GetStockObject(DC_PEN));
	if (a_state & ODS_SELECTED) {
		::SetDCPenColor(ah_dc, a_select_color);				// 선택 되었을 때 글자색 (펜색)
	}
	else {
		::SetDCPenColor(ah_dc, a_border_color);				// 선택 안되었을 때 글자색 (펜색)
	}

	// 사각형 출력
	::Rectangle(ah_dc, ap_rect->left, ap_rect->top, ap_rect->right, ap_rect->bottom);
}

// 리스트 박스에 추가된 항목 그리기
void CKioskTipsDlg::DrawShopItemList(HDC ah_dc, RECT* ap_rect, KID* ap_data)
{
	// 판매 아이템의 이미지가 읽어진 상태라면 출력한다
	if (ap_data->p_image && !ap_data->p_image->IsNull()) {
		ap_data->p_image->Draw(ah_dc, ap_rect->left + 3, ap_rect->top - 5, 180, 180);
	}

	::SelectObject(ah_dc, mh_list_font);				// 리스트박스 글꼴
	::SetBkMode(ah_dc, TRANSPARENT);				// 글테두리 투명
	::SetTextColor(ah_dc, RGB(0, 0, 0));				// 글색상

	// 판매 항목의 이름
	ap_rect->top = ap_rect->bottom - 70;				// 위치
	ap_rect->bottom = ap_rect->bottom - 50;
	::DrawText(ah_dc, ap_data->name_kor, _tcslen(ap_data->name_kor), ap_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);				// 출력

	// 영문 이름
	::SetTextColor(ah_dc, RGB(64, 98, 98));				// 색상 지정
	ap_rect->top += 20;							// 위치 지정
	ap_rect->bottom += 20;
	::DrawText(ah_dc, ap_data->name_eng, _tcslen(ap_data->name_eng), ap_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);			// 출력

	// 판매 항목 가격
	TCHAR str[128];
	_stprintf_s(str, 128, _T("%d"), ap_data->price);				// 가격을 문자열로
	::SetTextColor(ah_dc, RGB(200, 100, 100));					// 판매가격 색상
	ap_rect->top += 20;
	ap_rect->bottom += 20;				// 위치
	::DrawText(ah_dc, str, _tcslen(str), ap_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);				// 출력
}

// 리스트 박스에 추가된 구매항목 그리기
void CKioskTipsDlg::DrawOrderItemList(HDC ah_dc, RECT* ap_rect, KOD* ap_data)
{
	// 주문 정보를 얻는다
	KID* p_item = ap_data->p_item;
	// 이미지가 있으면 출력한다
	if (p_item->p_image && !p_item->p_image->IsNull()) {
		p_item->p_image->Draw(ah_dc, ap_rect->left + 10, ap_rect->top, 64, 64);
	}

	// 리스트박스 꾸미기
	::SelectObject(ah_dc, mh_list_font);				// 리스트박스 글꼴
	::SetBkMode(ah_dc, TRANSPARENT);				// 글테두리 투명
	::SetTextColor(ah_dc, RGB(0, 0, 0));				// 글 색상
	::TextOut(ah_dc, ap_rect->left + 80, ap_rect->top + 8, p_item->name_kor, _tcslen(p_item->name_kor));					// 출력

	::SetTextColor(ah_dc, RGB(64, 98, 98));				// 영문글 색상
	::TextOut(ah_dc, ap_rect->left + 80, ap_rect->top + 24, p_item->name_eng, _tcslen(p_item->name_eng));					// 출력

	// 주문 가격
	TCHAR str[128];
	_stprintf_s(str, 128, _T("%d원 * %d개 = %d원"), p_item->price, ap_data->count, p_item->price * ap_data->count);				// 주문가격을 문자열로
	::SetTextColor(ah_dc, RGB(200, 100, 100));				// 주문가격 색깔
	::TextOut(ah_dc, ap_rect->left + 80, ap_rect->top + 43, str, _tcslen(str));				// 출력
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
	// 이미지를 읽어 배경화면으로 설정
	m_bk_image.Load(_T(".\\image\\bk.png"));
	SetBackgroundImage(m_bk_image);

	// 리스트 박스 꾸미기
	mh_list_bk_brush = ::CreateSolidBrush(RGB(254, 242, 220));				// 색상
	mh_list_font = ::CreateFont(18, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("굴림체"));

	// 전체 가격 글꼴
	m_price_font.CreateFont(32, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("굴림체"));
	LoadDataFromFile(_T("item.kid"));

	// 화면 크기 조정 (Full HD)
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
		_stprintf_s(str, 128, _T("전체 주문 금액 : %d 원"), m_total_price);				// 전체금액 문자열
		dc.SetBkMode(TRANSPARENT);						// 문자열 배경은 투명하게
		dc.SetTextColor(RGB(255, 255, 0));					// 문자열 색상
		dc.SelectObject(&m_price_font);						// 문자열 폰트
		dc.DrawText(str, CRect(993, 953, 1557, 1019), DT_CENTER | DT_VCENTER | DT_SINGLELINE);				// 문자열 출력
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

	// 판매 항목의 수를 얻는다
	int count = m_item_list.GetCount();
	KID* p_data;

	for (int i = 0; i < count; ++i) {
		p_data = (KID*)m_item_list.GetItemDataPtr(i);			// 판매 항목의 주소를 얻어옴
		if (!p_data->p_image->IsNull()) { p_data->p_image->Destroy(); }			// 기존 로드된 이미지 제거
		delete p_data->p_image;			// 이미지 객체 제거
		delete p_data;				// 판매항목 정보제거
	}
	m_item_list.ResetContent();			// 리스트박스 전체 제거

	// 주문 항목의 수를 얻는다
	count = m_order_list.GetCount();
	KOD* p_order;
	for (int i = 0; i < count; ++i) {
		p_order = (KOD*)m_order_list.GetItemDataPtr(i);			// 주문정보 주소 얻어옴
		delete p_order;				// 제거
	}
	m_order_list.ResetContent();				// 리스트박스 전체 제거

	// 리스트박스 글꼴과 브러시 제거
	::DeleteObject(mh_list_font);
	::DeleteObject(mh_list_bk_brush);
}


HBRUSH CKioskTipsDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	// 리스트박스 배경색 브러시 반환
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
		OnBnClickedAddOrderBtn();			// 주문 정보 추가
	}
	else if (CRect(1842, 24, 1894, 76).PtInRect(point)) {
		CMenu menu;
		menu.CreatePopupMenu();				// 팝업메뉴 생성

		// 관리자 기능을 팝업메뉴에 추가
		menu.AppendMenu(MF_STRING, 23000, _T("새 항목 추가"));
		menu.AppendMenu(MF_STRING, 23001, _T("선택 항목 변경"));
		menu.AppendMenu(MF_STRING, 23002, _T("선택 항목 삭제"));
		menu.AppendMenu(MF_SEPARATOR, 0, _T(""));				// 구분선
		menu.AppendMenu(MF_STRING, 23003, _T("프로그램 종료"));

		CPoint pos;
		GetCursorPos(&pos);				// 화면상의 마우스 좌표를 얻는다
		menu.TrackPopupMenu(TPM_LEFTALIGN, pos.x, pos.y, this);			// 팝업전시
		menu.DestroyMenu();				// 팝업 메뉴 삭제
	}
	//CDialogEx::OnLButtonUp(nFlags, point);
}


void CKioskTipsDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpds)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDCtl == IDC_ITEM_LIST)					// 판매항목
	{
		if (lpds->itemID <= (UINT)m_item_list.GetCount()) 
		{
			DrawListItemBkImage(lpds->hDC, &lpds->rcItem, lpds->itemState, RGB(254, 242, 220), RGB(254, 242, 220), RGB(0, 168, 228));				// 판매항목 배경 그리기
			DrawShopItemList(lpds->hDC, &lpds->rcItem, (KID*)lpds->itemData);				// 판매항목 정보 그리기
		}
	} else if (nIDCtl == IDC_ORDER_LIST)				// 주문 항목
	{
		if (lpds->itemID <= (UINT)m_order_list.GetCount())
		{
			DrawListItemBkImage(lpds->hDC, &lpds->rcItem, lpds->itemState, RGB(254, 242, 220), RGB(254, 242, 220), RGB(0, 168, 228));				// 주문항목 배경
			DrawOrderItemList(lpds->hDC, &lpds->rcItem, (KOD*)lpds->itemData);				// 주문항목 정보 그리기
		}
	} else { CDialogEx::OnDrawItem(nIDCtl, lpds); }
}


void CKioskTipsDlg::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpms)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDCtl == IDC_ITEM_LIST)				// 판매항목
	{
		// 판매 항목은 멀티컬럼을 사용하기 때문에 폭과 높이를 지정해줘야한다
		lpms->itemWidth = 180;
		lpms->itemHeight = 250;
	}
	else if (nIDCtl == IDC_ORDER_LIST)		// 주문항목
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
	// 관리자 모드로 사용되는 기능을 처리
	if (wParam == 23000) { OnBnClickedAddItemBtn(); }			// 항목 추가
	else if (wParam == 23001) { OnBnClickedModifyItemBtn(); }		// 항목 변경
	else if (wParam == 23002) { OnBnClickedDelItemBtn(); }			// 항목 제거
	else if (wParam == 23003) { OnBnClickedCancel(); }					// 대화상자닫기

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
	int result = MessageBox(_T("프로그램을 종료하시겠습니까?"), _T("종료"), MB_OKCANCEL|MB_ICONQUESTION);
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
		// 사용자가 선택한 항목에 저장된 판매 항목의 주소
		KID* p_item = (KID*)m_item_list.GetItemDataPtr(index);
		KOD* p_check;
		
		// 동일한 항목이 있는지 체크하기 위해선 항목수를 얻는다
		int count = m_order_list.GetCount(), i;
		for (i = 0; i < count; i++) {
			// i번째 주문 정보를 얻는다
			p_check = (KOD*)m_order_list.GetItemDataPtr(i);
			if (p_check->p_item == p_item)
			{
				p_check->count++;
				m_order_list.SetCurSel(i);
				break;
			}
		}
		// 동일 항목이 없을 경우
		if (i == count)
		{
			p_check = new KOD;
			p_check->count = 1;
			p_check->p_item = p_item;
			index = m_order_list.InsertString(-1, _T(""));
			m_order_list.SetItemDataPtr(index, p_check);
			m_order_list.SetCurSel(index);
		}

		// 전체 가격 0로 초기화
		m_total_price = 0;
		count = m_order_list.GetCount();				// 주문 목록 수를 얻는다
		for (int i = 0; i < count; i++) {
			p_check = (KOD*)m_order_list.GetItemDataPtr(i);
			m_total_price += p_check->count * p_check->p_item->price;
		}
		// 전체 주문 가격을 화면에 갱신!
		InvalidateRect(CRect(993, 953, 1557, 1019));
	}
}


void CKioskTipsDlg::OnBnClickedAddItemBtn()
{
	// TODO: Add your control notification handler code here
	AddItemDlg ins_dlg;

	if (IDOK == ins_dlg.DoModal()) {
		// 판매 항목에 대한 정보를 저장할 메모리 할당
		KID* p_data = new KID;
		// 정보 저장
		_tcscpy_s(p_data->name_kor, 64, ins_dlg.GetNameKor());
		_tcscpy_s(p_data->name_eng, 64, ins_dlg.GetNameEng());
		_tcscpy_s(p_data->image_path, MAX_PATH, ins_dlg.GetImagePath());
		p_data->price = ins_dlg.GetPrice();

		p_data->p_image = new CImage;			// 이미지 객체를 할당
		p_data->p_image->Load(p_data->image_path);		// 이미지 객체를 읽는다

		// 리스트 박스에 항목 추가
		int index = m_item_list.InsertString(-1, _T(""));
		m_item_list.SetItemDataPtr(index, p_data);
		m_item_list.SetCurSel(index);
	}
}


void CKioskTipsDlg::OnBnClickedModifyItemBtn()
{
	// TODO: Add your control notification handler code here
	// 선택되어있는 판매항목의 위치를 얻는다
	int index = m_item_list.GetCurSel();
	if (index != LB_ERR)
	{
		// 해당 위치의 주소를 얻는다
		KID* p = (KID*)m_item_list.GetItemDataPtr(index);
		AddItemDlg ins_dlg;
		// 대화상자 출력 전에 기존 상품 정보를 전달
		ins_dlg.SetKidData(p->name_kor, p->name_eng, p->image_path, p->price);
		// 대화상자 출력
		INT_PTR nRes = ins_dlg.DoModal();
		if (IDOK == nRes) {
			// 변경 정보를 기존 메모리에 복사
			_tcscpy_s(p->name_kor, 64, ins_dlg.GetNameKor());
			_tcscpy_s(p->name_eng, 64, ins_dlg.GetNameEng());
			p->price = ins_dlg.GetPrice();

			// 이미지가 변경된경우
			if (_tcscmp(p->image_path, ins_dlg.GetImagePath())) {
				_tcscpy_s(p->image_path, MAX_PATH, ins_dlg.GetImagePath());	// 이미지 경로 업데이트

				if (p->p_image) {
					// 기존 로드된 이미지는 제거
					if (!p->p_image->IsNull()) { p->p_image->Destroy(); }
				}
				else { p->p_image = new CImage; }
				p->p_image->Load(p->image_path);
			}
			// 갱신 상태 반영을 위해 변경된 항목을 선택 항목으로 지정
			m_item_list.SetCurSel(index);
		}
	}
}


void CKioskTipsDlg::OnBnClickedDelItemBtn()
{
	// TODO: Add your control notification handler code here
	int index = m_item_list.GetCurSel();
	if (index != LB_ERR) {
		// 선택한 항목의 주소를 얻는다
		KID* p_data = (KID*)m_item_list.GetItemDataPtr(index);
		int res = MessageBox(p_data->name_kor, _T("아래의 상품 정보를 삭제하시겠습니까?"), MB_OKCANCEL|MB_ICONQUESTION);
		if (IDOK == res) {
			delete p_data;				// 정보 제거
			m_item_list.DeleteString(index);				// 항목 제거

			// 제거 후 위쪽 항목 선택
			m_item_list.SetCurSel(index - (m_item_list.GetCount() == index));
		}
	}
}


void CKioskTipsDlg::OnLbnDblclkItemList()
{
	// TODO: Add your control notification handler code here
	OnBnClickedAddOrderBtn();				// 주문정보 추가
}


void CKioskTipsDlg::OnLbnDblclkOrderList()
{
	// TODO: Add your control notification handler code here
	int index = m_order_list.GetCurSel();
	if (index != LB_ERR) {
		// 선택된 주문정보의 주소를 얻는다
		KOD* p_order = (KOD*)m_order_list.GetItemDataPtr(index);
		m_total_price -= p_order->p_item->price;			// 총금액 감소
		p_order->count--;

		if (!p_order->count) {
			// 0개가 되면 주문 정보 제거
			delete p_order;
			m_order_list.DeleteString(index);
		}
		else {
			// 0개가 아니면 커서 재설정
			m_order_list.SetCurSel(index);
		}
		InvalidateRect(CRect(993, 953, 1557, 1019));
	}
}

// 키오스크 정보를 지정된 데이터 파일에 저장
void CKioskTipsDlg::SaveDataToFile(const TCHAR* ap_path_name)
{
	int count = m_item_list.GetCount();			// 리스트박스 항목 갯수를 얻음
	KID* p_data;
	FILE* p_file = NULL;

	// 파일을 쓰기모드로 오픈
	if (0 == _tfopen_s(&p_file, ap_path_name, _T("wb")))
	{
		fwrite(&count, sizeof(int), 1, p_file);			// 항목수 저장
		for (int i = 0; i < count; ++i)
		{
			p_data = (KID*)m_item_list.GetItemDataPtr(i);		// i 번 항목에 저장된 판매정보 주소를 얻음
			fwrite(p_data, sizeof(KID), 1, p_file);			// 파일에 저장
		}
		fclose(p_file);			// 파일 닫기
	}
}

// 지정된 경로에서 데이터 파일을 읽어서 키오스크 정보를 가져옴
void CKioskTipsDlg::LoadDataFromFile(const TCHAR* ap_path_name)
{
	KID* p_data;
	TCHAR menu_kor[9][64] = { _T("아이스 아메리카노"), _T("딸기 밀크티"), _T("딸기 스무디"), _T("아이스초코 블랜드"), _T("오렌지 라임 에이드"), _T("자몽 에이드"), _T("햄 샌드위치"), _T("크로와상 샌드위치"), _T("치킨 샐러드")};
	TCHAR menu_eng[9][64] = { _T("iced americano"), _T("strawberry milk tea"), _T("strawberry smoothie"), _T("iced choco bledded"), _T("orange lime ade"), _T("grapefruit ade"), _T("ham sandwich"), _T("croissant sandwich"), _T("chicken salad")};
	TCHAR menu_image[9][MAX_PATH] = { _T(".\\image\\004.png"), _T(".\\image\\006.png"), _T(".\\image\\007.png"), _T(".\\image\\005.png"), _T(".\\image\\008.png"), _T(".\\image\\009.png"), _T(".\\image\\003.png"), _T(".\\image\\001.png"), _T(".\\image\\002.png")};
	int menu_price[9] = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000};


	/*
	FILE* p_file = NULL;

	// 지정된 파일을 읽기모드로 오픈
	if (0 == _tfopen_s(&p_file, ap_path_name, _T("rb")))
	{
		fread(&count, sizeof(int), 1, p_file);			// 저장된 항목의 수를 읽음
		for (int i = 0; i < count; ++i) {
			p_data = new KID;				// 판매 정보를 저장할 메모리 할당
			fread(p_data, sizeof(KID), 1, p_file);				// 항목 정보를 읽음
			p_data->p_image = new CImage;			// 이미지 객체 생성
			p_data->p_image->Load(p_data->image_path);				// 이미지 로드

			m_item_list.InsertString(-1, _T(""));			// 리스트박스 항목추가
			m_item_list.SetItemDataPtr(i, p_data);			// 추가 항목에 정보 전달
		}
		fclose(p_file);				// 파일 종료
	}
	*/

	int count = sizeof(menu_price) / sizeof(int);
	p_data = new KID[count];
	
	for (int i = 0; i < count; i++)
	{		
		// p_data에 정보 전달
		KID* pp = p_data+i;
		_tcscpy_s(pp->name_kor, 64, menu_kor[i]);
		_tcscpy_s(pp->name_eng, 64, menu_eng[i]);
		_tcscpy_s(pp->image_path, MAX_PATH, menu_image[i]);
		pp->price = menu_price[i];

		pp->p_image = new CImage;				// 이미지 객체 생성
		pp->p_image->Load(pp->image_path);				// 이미지 로드
	}

	int j = 0;
	for (int i = 0; i < count; ++i)
	{
		if (j >= count) {
			j = j % (count-1);
		}
		m_item_list.InsertString(-1, _T(""));				// 리스트박스에 빈항목 추가
		m_item_list.SetItemDataPtr(i, p_data+j);			// 빈항목에 정보 적용
		j += 3;
	}
}
