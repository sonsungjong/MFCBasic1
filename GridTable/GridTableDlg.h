#pragma once

// ǥ�� ������ġ�� ���Ѵ�
#define GRID_X_POSITION						10
#define GRID_Y_POSITION						36

// �� ���� ���� ����
#define GRID_WIDTH							100
#define GRID_HEIGHT						26

// �׸����� ������ ���Ѵ�
#define MAX_GRID_X_COUNT					5
#define MAX_GRID_Y_COUNT					3

// CGridTableDlg dialog
class CGridTableDlg : public CDialogEx
{
private:
	// �׸��� ������ ������ ����
	TCHAR* mp_edit_data[MAX_GRID_Y_COUNT][MAX_GRID_X_COUNT];

	// Edit ��Ʈ���� �������� �� ����� ��Ʈ
	CFont m_font;
	// ���� Ŭ������ ������ ����Ʈ ��Ʈ���� �ּҸ� ����� ����
	CEdit* mp_modify_edit;
	// ���� ���õ� �׸��� �׸��� ��ġ���� ������ ����
	int m_select_x;
	int m_select_y;

// Construction
public:
	CGridTableDlg(CWnd* pParent = nullptr);	// standard constructor

	// Ŭ���� ��ġ�� �ִ� ���� ������ ����
	char GetEditObject(int* ap_select_x, int* ap_select_y, CPoint* ap_point);
	// ����Ʈ ��Ʈ�� ���� �Լ�
	void CreateEdit(CRect* ap_rect);
	// ����Ʈ ��Ʈ���� �����ϴ� �Լ�
	void DeleteEdit();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GRIDTABLE_DIALOG };
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
};
