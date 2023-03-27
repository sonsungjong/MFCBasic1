#pragma once

// PNG파일을 리소스에 추가하면 따로 이미지를 실행파일과 같이 첨부하여 경로를 맞춰줄 필요없이
// 빌드할 때 실행파일 자체에 포함되게 된다. (대신, 실행파일 용량이 커짐)
// 리소스뷰에서 rc폴더에 리소스 추가를 한다음 png파일을 선택하면 된다
// FindResource() 함수를 통해서 rc에 추가한 png파일을 사용한다

// 키오스크 판매 항목의 정보
typedef struct KioskItemData
{
	TCHAR name_kor[64];
	TCHAR name_eng[64];
	TCHAR image_path[MAX_PATH];
	CImage* p_image;				// 선택한 이미지를 읽어서 사용할 객체
	int price;
} KID;

// 주문을 선택한 항목의 정보
typedef struct KioskOrderData
{
	int count;					// 해당 갯수
	KID* p_item;				// 선택 항목
} KOD;

// CKioskTipsDlg dialog (TitleBar=False )
class CKioskTipsDlg : public CDialogEx
{
private:
	CImage m_bk_image;				// 배경이미지
	HFONT mh_list_font;				// 리스트박스 글꼴
	HBRUSH mh_list_bk_brush;				// 리스트박스 배경색
	HRSRC mh_png_pos = NULL;				// PNG리소스 핸들

	int m_total_price = 0;					// 전체 가격
	CFont m_price_font;					// 전체 가격 글꼴

// Construction
public:
	CKioskTipsDlg(CWnd* pParent = nullptr);	// standard constructor

	// 키오스크 정보를 데이터파일에 저장하는 함수
	void SaveDataToFile(const TCHAR* ap_path_name);
	// 지정된 경로로부터 데이터 파일을 읽어서 키오스크 정보를 가져오는 함수
	void LoadDataFromFile(const TCHAR* ap_path_name);

	// 리스트박스 아이템배경 그리기
	void DrawListItemBkImage(HDC ah_dc, RECT* ap_rect, UINT a_state, COLORREF a_fill_color, COLORREF a_border_color, COLORREF a_select_color);
	// 리스트박스에 추가된 판매 항목 그리기
	void DrawShopItemList(HDC ah_dc, RECT* ap_rect, KID* ap_data);
	// 리스트박스에 추가된 구매항목 그리기
	void DrawOrderItemList(HDC ah_dc, RECT* ap_rect, KOD* ap_data);

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_KIOSKTIPS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpds);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpms);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
protected:
	CListBox m_item_list;				// 오너드로우Fixed, 멀티컬럼, Border=False, HasString, 컨트롤변수 추가, (이벤트핸들러=DBLCLK, )
	CListBox m_order_list;			// 오너드로우Fixed, Border=False, HasString, 컨트롤변수 추가, (이벤트핸들러=DBLCLK, )
public:
	// 오너드로우, Visible=False
	afx_msg void OnBnClickedAddOrderBtn();
	afx_msg void OnBnClickedAddItemBtn();
	afx_msg void OnBnClickedModifyItemBtn();
	afx_msg void OnBnClickedDelItemBtn();
	afx_msg void OnLbnDblclkItemList();
	afx_msg void OnLbnDblclkOrderList();
};
