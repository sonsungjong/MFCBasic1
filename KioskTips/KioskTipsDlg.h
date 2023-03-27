#pragma once

// PNG������ ���ҽ��� �߰��ϸ� ���� �̹����� �������ϰ� ���� ÷���Ͽ� ��θ� ������ �ʿ����
// ������ �� �������� ��ü�� ���Եǰ� �ȴ�. (���, �������� �뷮�� Ŀ��)
// ���ҽ��信�� rc������ ���ҽ� �߰��� �Ѵ��� png������ �����ϸ� �ȴ�
// FindResource() �Լ��� ���ؼ� rc�� �߰��� png������ ����Ѵ�

// Ű����ũ �Ǹ� �׸��� ����
typedef struct KioskItemData
{
	TCHAR name_kor[64];
	TCHAR name_eng[64];
	TCHAR image_path[MAX_PATH];
	CImage* p_image;				// ������ �̹����� �о ����� ��ü
	int price;
} KID;

// �ֹ��� ������ �׸��� ����
typedef struct KioskOrderData
{
	int count;					// �ش� ����
	KID* p_item;				// ���� �׸�
} KOD;

// CKioskTipsDlg dialog (TitleBar=False )
class CKioskTipsDlg : public CDialogEx
{
private:
	CImage m_bk_image;				// ����̹���
	HFONT mh_list_font;				// ����Ʈ�ڽ� �۲�
	HBRUSH mh_list_bk_brush;				// ����Ʈ�ڽ� ����
	HRSRC mh_png_pos = NULL;				// PNG���ҽ� �ڵ�

	int m_total_price = 0;					// ��ü ����
	CFont m_price_font;					// ��ü ���� �۲�

// Construction
public:
	CKioskTipsDlg(CWnd* pParent = nullptr);	// standard constructor

	// Ű����ũ ������ ���������Ͽ� �����ϴ� �Լ�
	void SaveDataToFile(const TCHAR* ap_path_name);
	// ������ ��ηκ��� ������ ������ �о Ű����ũ ������ �������� �Լ�
	void LoadDataFromFile(const TCHAR* ap_path_name);

	// ����Ʈ�ڽ� �����۹�� �׸���
	void DrawListItemBkImage(HDC ah_dc, RECT* ap_rect, UINT a_state, COLORREF a_fill_color, COLORREF a_border_color, COLORREF a_select_color);
	// ����Ʈ�ڽ��� �߰��� �Ǹ� �׸� �׸���
	void DrawShopItemList(HDC ah_dc, RECT* ap_rect, KID* ap_data);
	// ����Ʈ�ڽ��� �߰��� �����׸� �׸���
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
	CListBox m_item_list;				// ���ʵ�ο�Fixed, ��Ƽ�÷�, Border=False, HasString, ��Ʈ�Ѻ��� �߰�, (�̺�Ʈ�ڵ鷯=DBLCLK, )
	CListBox m_order_list;			// ���ʵ�ο�Fixed, Border=False, HasString, ��Ʈ�Ѻ��� �߰�, (�̺�Ʈ�ڵ鷯=DBLCLK, )
public:
	// ���ʵ�ο�, Visible=False
	afx_msg void OnBnClickedAddOrderBtn();
	afx_msg void OnBnClickedAddItemBtn();
	afx_msg void OnBnClickedModifyItemBtn();
	afx_msg void OnBnClickedDelItemBtn();
	afx_msg void OnLbnDblclkItemList();
	afx_msg void OnLbnDblclkOrderList();
};
