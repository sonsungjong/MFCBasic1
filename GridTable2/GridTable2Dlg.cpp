#include "pch.h"
#include "framework.h"
#include "GridTable2.h"
#include "GridTable2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CGridTable2Dlg::CGridTable2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GRIDTABLE2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	mp_edit_data = NULL;
	m_h_count = 0;
	m_v_count = 0;

	m_select_x = 0;
	m_select_y = 0;
	mp_modify_edit = NULL;
}

void CGridTable2Dlg::AllocStringData(int a_h_count, int a_v_count)
{
	if (m_h_count != a_h_count || m_v_count != a_v_count) {
		if (mp_edit_data != NULL) { FreeStringData(); }
		m_h_count = a_h_count;
		m_v_count = a_v_count;
		mp_edit_data = new TCHAR * *[m_v_count];
		for (unsigned int y = 0; y < m_v_count; y++) {
			*(mp_edit_data + y) = new TCHAR * [a_h_count];
			for (unsigned int x = 0; x < m_h_count; x++) { *(*(mp_edit_data + y) + x) = NULL; }
		}
	}
}

void CGridTable2Dlg::FreeStringData()
{
	for (unsigned int y = 0; y < m_v_count; y++) {
		for (unsigned int x = 0; x < m_h_count; x++) {
			if (*(*(mp_edit_data + y) + x) != NULL) { delete[] *(*(mp_edit_data + y) + x); }
		}
		delete[] *(mp_edit_data + y);
	}
	delete[] mp_edit_data;
	mp_edit_data = NULL;
}

char CGridTable2Dlg::GetEditObject(int* ap_select_x, int* ap_select_y, CPoint* ap_point)
{
	if (ap_point->x >= GRID_X_POSITION && ap_point->y >= GRID_Y_POSITION) {
		unsigned int x = (ap_point->x - GRID_X_POSITION) / GRID_WIDTH;
		unsigned int y = (ap_point->y - GRID_Y_POSITION) / GRID_HEIGHT;
		if (x < m_h_count && y < m_v_count) {
			*ap_select_x = x;
			*ap_select_y = y;
			return 1;
		}
	}
	return 0;
}

// ����Ʈ ��Ʈ���� ����
void CGridTable2Dlg::CreateEdit(CRect* ap_rect)
{
	mp_modify_edit = new CEdit();
	mp_modify_edit->CreateEx(WS_EX_STATICEDGE, _T("EDIT"), _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, *ap_rect, this, 21000);
	mp_modify_edit->SetFont(&m_font);
	mp_modify_edit->SetFocus();
}

void CGridTable2Dlg::DeleteEdit()
{
	if (mp_modify_edit != NULL) {
		CString str;
		mp_modify_edit->GetWindowText(str);
		int len = str.GetLength();

		if (len > 0) {					// �Էµ� ���ڿ��� ������
			// ���� �����Ͱ� ������
			if (mp_edit_data[m_select_y][m_select_x] != NULL) {
				// �������� ���
				if (str != mp_edit_data[m_select_y][m_select_x]) {
					// ���� ���� ����
					delete[] mp_edit_data[m_select_y][m_select_x];

					mp_edit_data[m_select_y][m_select_x] = new TCHAR[++len];
					memcpy(mp_edit_data[m_select_y][m_select_x], (const TCHAR*)str, len *2);
				}
			}
			else {
				// ������ �����Ͱ� �������� �ٷ� �޸��Ҵ�
				mp_edit_data[m_select_y][m_select_x] = new TCHAR[++len];
				memcpy(mp_edit_data[m_select_y][m_select_x], (const TCHAR*)str, len * 2);
			}
		}
		else {
			// �Էµ� ���ڿ��� ������
			// ���� �����Ͱ� ���� ���
			if (mp_edit_data[m_select_y][m_select_x] != NULL) {
				// ����
				delete[] mp_edit_data[m_select_y][m_select_x];
				mp_edit_data[m_select_y][m_select_x] = NULL;
			}
		}
		mp_modify_edit->DestroyWindow();
		delete mp_modify_edit;
		mp_modify_edit = NULL;
	}
}

void CGridTable2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGridTable2Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CGridTable2Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CGridTable2Dlg::OnBnClickedCancel)
	ON_WM_DESTROY()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_EN_KILLFOCUS(21000, &CGridTable2Dlg::OnDeleteEdit)
	ON_BN_CLICKED(IDC_APPLY_BTN, &CGridTable2Dlg::OnBnClickedApplyBtn)
END_MESSAGE_MAP()


// CGridTable2Dlg message handlers

BOOL CGridTable2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	// ����Ʈ ��Ʈ���� ��Ʈ�� ����
	m_font.CreateFont(12, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("����ü"));

	SetDlgItemInt(IDC_H_COUNT_EDIT, 5);
	SetDlgItemInt(IDC_V_COUNT_EDIT, 3);

	AllocStringData(5, 3);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGridTable2Dlg::OnPaint()
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
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//CDialogEx::OnPaint();
		CFont* p_old_font = dc.SelectObject(&m_font);
		int old_mode = dc.SetBkMode(TRANSPARENT);				// ��� ���ڿ� ����� �����ϰ�

		CRect r;
		for (unsigned int y = 0; y < m_v_count; y++) {
			for (unsigned int x = 0; x < m_h_count; x++) {
				// �׸��� ��ġ�� �簢���� �׸���
				r.SetRect(GRID_X_POSITION + x * GRID_WIDTH, GRID_Y_POSITION + y * GRID_HEIGHT, GRID_X_POSITION + (x + 1) * GRID_WIDTH + 1, GRID_Y_POSITION + (y + 1) * GRID_HEIGHT + 1);
				dc.Rectangle(r);

				if (mp_edit_data[y][x] != NULL) {
					r.left += 2;
					r.top += 2;
					dc.DrawText(mp_edit_data[y][x], r, DT_SINGLELINE | DT_LEFT);
				}
			}
		}
		dc.SelectObject(p_old_font);
		dc.SetBkMode(old_mode);
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGridTable2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CGridTable2Dlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	DeleteEdit();
	 
	//CDialogEx::OnOK();
}


void CGridTable2Dlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void CGridTable2Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	DeleteEdit();

	// ���ڿ� ����
	if (mp_edit_data != NULL) { FreeStringData(); }
	// ��Ʈ ����
	m_font.DeleteObject();
}


void CGridTable2Dlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (GetEditObject(&m_select_x, &m_select_y, &point)) {
		// ����Ŭ���� ����Ʈ ��Ʈ�� ����
		CRect r(GRID_X_POSITION + m_select_x * GRID_WIDTH + 1, GRID_Y_POSITION + m_select_y * GRID_HEIGHT + 1, GRID_X_POSITION + (m_select_x + 1) * GRID_WIDTH, GRID_Y_POSITION + (m_select_y + 1) * GRID_HEIGHT);
		CreateEdit(&r);

		// ���ڿ��� �̹� �ִٸ� ����
		if (mp_edit_data[m_select_y][m_select_x] != NULL) {
			mp_modify_edit->SetWindowText(mp_edit_data[m_select_y][m_select_x]);
			mp_modify_edit->SetSel(0, -1);
		}
	}
	CDialogEx::OnLButtonDblClk(nFlags, point);
}


void CGridTable2Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	// ����Ʈ ��Ʈ�� ��� �� �ٸ� ������ Ŭ���ϸ� ����
	DeleteEdit();

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CGridTable2Dlg::OnBnClickedApplyBtn()
{
	int h_count = GetDlgItemInt(IDC_H_COUNT_EDIT);
	int v_count = GetDlgItemInt(IDC_V_COUNT_EDIT);
	if (h_count > 0 && h_count <= 6) {
		if (v_count > 0 && v_count <= 8) {
			AllocStringData(h_count, v_count);
			Invalidate();
		}
		else {
			MessageBox(_T("���� �׸��� ������ 1�� �̻� 8�� ���ϸ� ���� �����մϴ�."), _T("�׸� �� ����"), MB_ICONSTOP);
		}
	}
	else {
		MessageBox(_T("���� �׸��� ������ 1�� �̻� 6�� ���ϸ� ���� �����մϴ�."), _T("�׸� �� ����"), MB_ICONSTOP);
	}
}

void CGridTable2Dlg::OnDeleteEdit()
{
	DeleteEdit();
}