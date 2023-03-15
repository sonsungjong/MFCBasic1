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

// 에디트 컨트롤을 생성
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

		if (len > 0) {					// 입력된 문자열이 있으면
			// 기존 데이터가 있으면
			if (mp_edit_data[m_select_y][m_select_x] != NULL) {
				// 수정됬을 경우
				if (str != mp_edit_data[m_select_y][m_select_x]) {
					// 기존 정보 제거
					delete[] mp_edit_data[m_select_y][m_select_x];

					mp_edit_data[m_select_y][m_select_x] = new TCHAR[++len];
					memcpy(mp_edit_data[m_select_y][m_select_x], (const TCHAR*)str, len *2);
				}
			}
			else {
				// 기존에 데이터가 없었으면 바로 메모리할당
				mp_edit_data[m_select_y][m_select_x] = new TCHAR[++len];
				memcpy(mp_edit_data[m_select_y][m_select_x], (const TCHAR*)str, len * 2);
			}
		}
		else {
			// 입력된 문자열이 없으면
			// 기존 데이터가 있을 경우
			if (mp_edit_data[m_select_y][m_select_x] != NULL) {
				// 제거
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
	// 에디트 컨트롤의 폰트를 설정
	m_font.CreateFont(12, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("굴림체"));

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
		int old_mode = dc.SetBkMode(TRANSPARENT);				// 출력 문자열 배경을 투명하게

		CRect r;
		for (unsigned int y = 0; y < m_v_count; y++) {
			for (unsigned int x = 0; x < m_h_count; x++) {
				// 그리드 위치에 사각형을 그린다
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

	// 문자열 제거
	if (mp_edit_data != NULL) { FreeStringData(); }
	// 폰트 제거
	m_font.DeleteObject();
}


void CGridTable2Dlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (GetEditObject(&m_select_x, &m_select_y, &point)) {
		// 더블클릭시 에디트 컨트롤 생성
		CRect r(GRID_X_POSITION + m_select_x * GRID_WIDTH + 1, GRID_Y_POSITION + m_select_y * GRID_HEIGHT + 1, GRID_X_POSITION + (m_select_x + 1) * GRID_WIDTH, GRID_Y_POSITION + (m_select_y + 1) * GRID_HEIGHT);
		CreateEdit(&r);

		// 문자열이 이미 있다면 편집
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
	// 에디트 컨트롤 사용 중 다른 영역을 클릭하면 제거
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
			MessageBox(_T("세로 항목의 개수는 1개 이상 8개 이하만 설정 가능합니다."), _T("항목 수 오류"), MB_ICONSTOP);
		}
	}
	else {
		MessageBox(_T("가로 항목의 개수는 1개 이상 6개 이하만 설정 가능합니다."), _T("항목 수 오류"), MB_ICONSTOP);
	}
}

void CGridTable2Dlg::OnDeleteEdit()
{
	DeleteEdit();
}