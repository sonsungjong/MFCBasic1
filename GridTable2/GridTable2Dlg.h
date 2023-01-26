#pragma once

// �׸����� ���� ��ġ
#define GRID_X_POSITION					10
#define GRID_Y_POSITION					82

// �� ���� ���� ����
#define GRID_WIDTH						100
#define GRID_HEIGHT					26

// CGridTable2Dlg dialog
class CGridTable2Dlg : public CDialogEx
{
private:
	// �׸��� �׸��� ������ ������ ����
	unsigned int m_h_count;
	unsigned int m_v_count;

	// �� ���� ������ ������ ����
	TCHAR*** mp_edit_data;

	// ����Ʈ ��Ʈ�� ��Ʈ
	CFont m_font;
	// ����Ŭ���� ���� ����Ʈ��Ʈ�� �ּ�
	CEdit* mp_modify_edit;
	// ���õ� ���� ��ġ��
	int m_select_x;
	int m_select_y;

// Construction
public:
	CGridTable2Dlg(CWnd* pParent = nullptr);	// standard constructor

	// �׸��忡�� ����� �޸� �Ҵ�
	void AllocStringData(int a_h_count, int a_v_count);
	// ���ڿ� ���� ����
	void FreeStringData();

	// Ŭ���� ��ġ�� �ִ� ���� ������ ����
	char GetEditObject(int* ap_select_x, int* ap_select_y, CPoint* ap_point);
	// ����Ʈ ��Ʈ�� ���� �Լ�
	void CreateEdit(CRect* ap_rect);
	// ����Ʈ ��Ʈ�� ���� �Լ�
	void DeleteEdit();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GRIDTABLE2_DIALOG };
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
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDeleteEdit();
	afx_msg void OnBnClickedApplyBtn();
};
