
// TableCtrlDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "TableCtrl.h"
#include "TableCtrlDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTableCtrlDlg dialog



CTableCtrlDlg::CTableCtrlDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TABLECTRL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	// 각 그리드 항목이 사용할 정보를 NULL로 초기화
	mp_edit_data = NULL;
	m_h_count = m_v_count = 0;

	m_select_x = m_select_y = 0;
	mp_modify_edit = NULL;
}



void CTableCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTableCtrlDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CTableCtrlDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CTableCtrlDlg::OnBnClickedCancel)
	ON_WM_DESTROY()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_MESSAGE(21000, &CTableCtrlDlg::OnDeleteEdit)
	ON_BN_CLICKED(IDC_APPLY_BTN, &CTableCtrlDlg::OnBnClickedApplyBtn)
END_MESSAGE_MAP()


// CTableCtrlDlg message handlers

BOOL CTableCtrlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	// 에디트 컨트롤이 사용할 폰트 객체 생성
	m_font.CreateFont(12, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("굴림"));

	SetDlgItemInt(IDC_H_COUNT_EDIT, 5);
	SetDlgItemInt(IDC_V_COUNT_EDIT, 3);

	AllocStringData(5, 3);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTableCtrlDlg::OnPaint()
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
		int old_mode = dc.SetBkMode(TRANSPARENT);

		CRect r;
		for (int y = 0; y < m_v_count; y++) {
			for (int x = 0; x < m_h_count; x++) {
				r.SetRect(GRID_X_POS + x * GRID_WIDTH, GRID_Y_POS + y * GRID_HEIGHT,
					GRID_X_POS + (x + 1) * GRID_WIDTH + 1, GRID_Y_POS + (y + 1) * GRID_HEIGHT + 1);
				dc.Rectangle(r);

				if (mp_edit_data[y][x] != NULL) {
					r.left += 2;
					r.top += 2;
					dc.DrawText(mp_edit_data[y][x], r, DT_SINGLELINE | DT_LEFT);
				}
			}
		}

		dc.SelectObject(p_old_font);				// 기본 폰트로 복구
		dc.SetBkMode(old_mode);					// 기본 문자열 배경 속성으로 복구
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTableCtrlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTableCtrlDlg::OnBnClickedOk()
{
	//CDialogEx::OnOK();
	DeleteEdit();
}


void CTableCtrlDlg::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}


void CTableCtrlDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	DeleteEdit();

	if (mp_edit_data != NULL) {
		FreeStringData();
	}
	m_font.DeleteObject();
}


void CTableCtrlDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (GetEditObject(&m_select_x, &m_select_y, &point)) {
		CRect r(GRID_X_POS + m_select_x * GRID_WIDTH + 1, GRID_Y_POS + m_select_y * GRID_HEIGHT + 1,
			GRID_X_POS + (m_select_x + 1) * GRID_WIDTH, GRID_Y_POS + (m_select_y + 1) * GRID_HEIGHT);
		CreateEdit(&r);
		if (mp_edit_data[m_select_y][m_select_x] != NULL) {
			mp_modify_edit->SetWindowTextW(mp_edit_data[m_select_y][m_select_x]);
			mp_modify_edit->SetSel(0, -1);
		}
	}
	CDialogEx::OnLButtonDblClk(nFlags, point);
}


void CTableCtrlDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	DeleteEdit();

	CDialogEx::OnLButtonDown(nFlags, point);
}

char CTableCtrlDlg::GetEditObject(int* ap_select_x, int* ap_select_y, CPoint* ap_point)
{
	if (ap_point->x >= GRID_X_POS && ap_point->y >= GRID_Y_POS) {
		int x = (ap_point->x - GRID_X_POS) / GRID_WIDTH;
		int y = (ap_point->y - GRID_Y_POS) / GRID_HEIGHT;
		if (x < m_h_count && y < m_v_count) {
			*ap_select_x = x;
			*ap_select_y = y;
			return 1;
		}
	}
	return 0;
}

void CTableCtrlDlg::CreateEdit(CRect* ap_rect)
{
	mp_modify_edit = new CEdit();
	// 에디트컨트롤 생성
	mp_modify_edit->CreateEx(WS_EX_STATICEDGE, _T("EDIT"), _T(""), 
		WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, *ap_rect, this, 21000);
	mp_modify_edit->SetFont(&m_font);					// 폰트설정
	mp_modify_edit->SetFocus();			// 키보드 입력을 할 수 있도록 포커스 설정
}

void CTableCtrlDlg::DeleteEdit()
{
	if (NULL != mp_modify_edit) {
		CString str;
		mp_modify_edit->GetWindowText(str);
		int len = str.GetLength();

		if (len > 0) {
			if (mp_edit_data[m_select_y][m_select_x] != NULL) {
				if (str != mp_edit_data[m_select_y][m_select_x]) {
					delete[] mp_edit_data[m_select_y][m_select_x];

					mp_edit_data[m_select_y][m_select_x] = new TCHAR[++len];
					memcpy(mp_edit_data[m_select_y][m_select_x], (const TCHAR*)str, len *sizeof(TCHAR));
				}
			}
			else {
				mp_edit_data[m_select_y][m_select_x] = new TCHAR[++len];
				memcpy(mp_edit_data[m_select_y][m_select_x], (const TCHAR*)str, len *sizeof(TCHAR));
			}
		}
		else {
			if (mp_edit_data[m_select_y][m_select_x] != NULL) {
				delete[] mp_edit_data[m_select_y][m_select_x];
				mp_edit_data[m_select_y][m_select_x] = NULL;
			}
		}
		mp_modify_edit->DestroyWindow();
		delete mp_modify_edit;
		mp_modify_edit = NULL;
	}
}


afx_msg LRESULT CTableCtrlDlg::OnDeleteEdit(WPARAM wParam, LPARAM lParam)
{
	DeleteEdit();
	return 0;
}

void CTableCtrlDlg::AllocStringData(int a_h_count, int a_v_count)
{
	if (m_h_count != a_h_count || m_v_count != a_v_count) {
		if (mp_edit_data != NULL) {
			FreeStringData();
		}
		m_h_count = a_h_count;
		m_v_count = a_v_count;
		mp_edit_data = new TCHAR * *[m_v_count];
		for (unsigned int y = 0; y < m_v_count; y++) {
			*(mp_edit_data + y) = new TCHAR * [a_h_count];
			for (unsigned int x = 0; x < m_h_count; x++) {
				*(*(mp_edit_data + y) + x) = NULL;
			}
		}
	}
}

void CTableCtrlDlg::FreeStringData()
{
	for (unsigned int y = 0; y < m_v_count; y++) {
		for (unsigned int x = 0; x < m_h_count; x++) {
			if (*(*(mp_edit_data + y) + x) != NULL) {
				delete[] * (*(mp_edit_data + y) + x);
			}
		}
		delete[] * (mp_edit_data + y);
	}
	delete[] mp_edit_data;
	mp_edit_data = NULL;
}



void CTableCtrlDlg::OnBnClickedApplyBtn()
{
	int h_count = GetDlgItemInt(IDC_H_COUNT_EDIT);
	int v_count = GetDlgItemInt(IDC_V_COUNT_EDIT);
	if (h_count > 0 && h_count <= 6) {
		if (v_count > 0 && v_count <= 8) {
			AllocStringData(h_count, v_count);
			Invalidate();
		}
		else {
			MessageBox(_T("세로 항목의 개수는 1개 이상 8개 이하만 설정 가능합니다."), _T("항목 수 오류"), MB_ICONSTOP);
		}
	}
	else {
		MessageBox(_T("가로 항목의 개수는 1개 이상 6개 이하만 설정 가능합니다."), _T("항목 수 오류"), MB_ICONSTOP);
	}
}
