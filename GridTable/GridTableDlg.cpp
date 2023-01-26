#include "pch.h"
#include "framework.h"
#include "GridTable.h"
#include "GridTableDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CGridTableDlg::CGridTableDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GRIDTABLE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	// �� �׸��� �׸��� ����� ������ NULL�� �ʱ�ȭ
	for (int y = 0; y < MAX_GRID_Y_COUNT; y++) {
		for (int x = 0; x < MAX_GRID_X_COUNT; x++) {
			mp_edit_data[y][x] = NULL;
		}
	}

	m_select_x = 0;
	m_select_y = 0;
	mp_modify_edit = NULL;
}

void CGridTableDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGridTableDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CGridTableDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CGridTableDlg::OnBnClickedCancel)
	ON_WM_DESTROY()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_EN_KILLFOCUS(21000, &CGridTableDlg::OnDeleteEdit)
END_MESSAGE_MAP()


// CGridTableDlg message handlers

BOOL CGridTableDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	// ����Ʈ ��Ʈ���� ����� ��Ʈ ����
	m_font.CreateFont(12, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("����ü"));

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGridTableDlg::OnPaint()
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
		// ��Ʈ ����
		CFont* p_old_font = dc.SelectObject(&m_font);
		// ��µ� ���ڿ��� ����� ����ó��
		int old_mode = dc.SetBkMode(TRANSPARENT);

		CRect r;
		// �� ���� �簢���� �׷� ǥ��
		for (int y = 0; y < MAX_GRID_Y_COUNT; y++) {
			for (int x = 0; x < MAX_GRID_X_COUNT; x++) {
				// ��ġ ���
				r.SetRect(GRID_X_POSITION + x * GRID_WIDTH, GRID_Y_POSITION + y * GRID_HEIGHT, GRID_X_POSITION + (x + 1) * GRID_WIDTH + 1, GRID_Y_POSITION + (y + 1) * GRID_HEIGHT + 1);
				// �簢��
				dc.Rectangle(r);

				// ���ڿ��� ������ ���
				if (mp_edit_data[y][x] != NULL) {
					r.left += 2;
					r.top += 2;
					dc.DrawText(mp_edit_data[y][x], r, DT_SINGLELINE | DT_LEFT);
				}
			}
		}
		// �⺻���� ����
		dc.SelectObject(p_old_font);
		dc.SetBkMode(old_mode);
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGridTableDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CGridTableDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	// ����Ű�� ������ �Է��� �����ϰ� ����Ʈ ��Ʈ���� ����
	DeleteEdit();

	//CDialogEx::OnOK();
}


void CGridTableDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void CGridTableDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	DeleteEdit();

	// �� ���� ���ڿ� ������ ����
	for (int y = 0; y < MAX_GRID_Y_COUNT; y++) {
		for (int x = 0; x < MAX_GRID_X_COUNT; x++) {
			if (mp_edit_data[y][x] != NULL) { delete[] mp_edit_data[y][x]; }
		}
	}
	m_font.DeleteObject();
}

char CGridTableDlg::GetEditObject(int* ap_select_x, int* ap_select_y, CPoint* ap_point)
{
	// ������ ����� �ش� ������ ���콺�� Ŭ���Ǿ����� ��
	/*
	CRect r;
	for (int y = 0; y < MAX_GRID_Y_COUNT; y++) {
		for (int x = 0; x < MAX_GRID_X_COUNT; x++) {
			r.SetRect(GRID_X_POSITION + x * GRID_WIDTH, GRID_Y_POSITION + y * GRID_HEIGHT, GRID_X_POSITION + (x + 1) * GRID_WIDTH, GRID_Y_POSITION + (y + 1) * GRID_HEIGHT);
			if (r.PtInRect(*ap_point)) {
				*ap_select_x = x;
				*ap_select_y = y;
				return 1;
			}
		}
	}
	*/

	// ������ ������ ���� �� ȿ������ �ڵ�
	if (ap_point->x >= GRID_X_POSITION && ap_point->y >= GRID_Y_POSITION) {
		unsigned int x = (ap_point->x - GRID_X_POSITION) / GRID_WIDTH;
		unsigned int y = (ap_point->y - GRID_Y_POSITION) / GRID_HEIGHT;
		if (x < MAX_GRID_X_COUNT && y < MAX_GRID_Y_COUNT) {
			*ap_select_x = x;
			*ap_select_y = y;
			return 1;
		}
	}
	return 0;
}

// ����Ʈ ��Ʈ���� ����
void CGridTableDlg::CreateEdit(CRect* ap_rect)
{
	mp_modify_edit = new CEdit();
	mp_modify_edit->CreateEx(WS_EX_STATICEDGE, _T("EDIT"), _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, *ap_rect, this, 21000);
	// ��Ʈ ����
	mp_modify_edit->SetFont(&m_font);
	// Ű���� �Է��� �����ϵ��� ��Ŀ�� ����
	mp_modify_edit->SetFocus();
}


void CGridTableDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (GetEditObject(&m_select_x, &m_select_y, &point)) {
		// Ư�� ���� ����Ŭ���ߴٸ� ����Ʈ ��Ʈ���� �����Ѵ�
		CRect r(GRID_X_POSITION + m_select_x * GRID_WIDTH + 1, GRID_Y_POSITION + m_select_y * GRID_HEIGHT + 1, GRID_X_POSITION + (m_select_x + 1) * GRID_WIDTH, GRID_Y_POSITION + (m_select_y + 1) * GRID_HEIGHT);
		CreateEdit(&r);

		// �̹� ���ڿ��� ������ �����ϵ���
		if (mp_edit_data[m_select_y][m_select_x] != NULL) {
			mp_modify_edit->SetWindowText(mp_edit_data[m_select_y][m_select_x]);
			mp_modify_edit->SetSel(0, -1);
		}
	}

	CDialogEx::OnLButtonDblClk(nFlags, point);
}

// ����Ʈ ��Ʈ�� ����
void CGridTableDlg::DeleteEdit()
{
	if (mp_modify_edit != NULL) {
		CString str;
		mp_modify_edit->GetWindowText(str);
		int len = str.GetLength();

		// �Էµ� ���ڿ��� �ִٸ�
		if (len > 0) {
			// �������� ������ �־�����
			if (mp_edit_data[m_select_y][m_select_x] != NULL) {
				// ������ �ִ� ���ڿ��� ������ �޶�������
				if (str != mp_edit_data[m_select_y][m_select_x]) {
					//���� ���� ����
					delete[] mp_edit_data[m_select_y][m_select_x];

					// ���� ������ ���� �޸� �Ҵ�
					mp_edit_data[m_select_y][m_select_x] = new TCHAR[++len];
					memcpy(mp_edit_data[m_select_y][m_select_x], (const TCHAR*)str, len * 2);
				}
			}
			else {
				// ���� ������ ���� �޸� �Ҵ�
				mp_edit_data[m_select_y][m_select_x] = new TCHAR[++len];
				memcpy(mp_edit_data[m_select_y][m_select_x], (const TCHAR*)str, len * 2);
			}
		}
		else {				// �Է� �׸��� ������
			// ���� ������ �־�����
			if (mp_edit_data[m_select_y][m_select_x] != NULL) {
				// �ԷµǾ��ִ� ���� ���� ���̴� �����͸� �����Ѵ�
				delete[] mp_edit_data[m_select_y][m_select_x];
				mp_edit_data[m_select_y][m_select_x] = NULL;
			}
		}

		mp_modify_edit->DestroyWindow();
		delete mp_modify_edit;
		mp_modify_edit = NULL;
	}
}

// ��Ŀ���� ������ ����Ʈ��Ʈ�� ����
void CGridTableDlg::OnDeleteEdit()
{
	DeleteEdit();
}

// ����Ʈ ��Ʈ�� ���� �� �ٸ� ���� Ŭ���ϸ� ����Ʈ ��Ʈ�� ����
void CGridTableDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	DeleteEdit();

	CDialogEx::OnLButtonDown(nFlags, point);
}