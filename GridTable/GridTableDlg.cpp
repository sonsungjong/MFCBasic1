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

	// 각 그리드 항목이 사용할 정보를 NULL로 초기화
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
	// 에디트 컨트롤이 사용할 폰트 설정
	m_font.CreateFont(12, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("굴림체"));

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
		// 폰트 설정
		CFont* p_old_font = dc.SelectObject(&m_font);
		// 출력될 문자열의 배경을 투명처리
		int old_mode = dc.SetBkMode(TRANSPARENT);

		CRect r;
		// 각 셀을 사각형을 그려 표시
		for (int y = 0; y < MAX_GRID_Y_COUNT; y++) {
			for (int x = 0; x < MAX_GRID_X_COUNT; x++) {
				// 위치 계산
				r.SetRect(GRID_X_POSITION + x * GRID_WIDTH, GRID_Y_POSITION + y * GRID_HEIGHT, GRID_X_POSITION + (x + 1) * GRID_WIDTH + 1, GRID_Y_POSITION + (y + 1) * GRID_HEIGHT + 1);
				// 사각형
				dc.Rectangle(r);

				// 문자열이 있으면 출력
				if (mp_edit_data[y][x] != NULL) {
					r.left += 2;
					r.top += 2;
					dc.DrawText(mp_edit_data[y][x], r, DT_SINGLELINE | DT_LEFT);
				}
			}
		}
		// 기본설정 복구
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
	// 엔터키를 누르면 입력을 종료하고 에디트 컨트롤을 삭제
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

	// 각 셀의 문자열 정보를 삭제
	for (int y = 0; y < MAX_GRID_Y_COUNT; y++) {
		for (int x = 0; x < MAX_GRID_X_COUNT; x++) {
			if (mp_edit_data[y][x] != NULL) { delete[] mp_edit_data[y][x]; }
		}
	}
	m_font.DeleteObject();
}

char CGridTableDlg::GetEditObject(int* ap_select_x, int* ap_select_y, CPoint* ap_point)
{
	// 영역을 만들고 해당 영역에 마우스가 클릭되었는지 비교
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

	// 포인터 연산을 통한 더 효율적인 코드
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

// 에디트 컨트롤을 생성
void CGridTableDlg::CreateEdit(CRect* ap_rect)
{
	mp_modify_edit = new CEdit();
	mp_modify_edit->CreateEx(WS_EX_STATICEDGE, _T("EDIT"), _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, *ap_rect, this, 21000);
	// 폰트 설정
	mp_modify_edit->SetFont(&m_font);
	// 키보드 입력이 가능하도록 포커스 설정
	mp_modify_edit->SetFocus();
}


void CGridTableDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (GetEditObject(&m_select_x, &m_select_y, &point)) {
		// 특정 셀을 더블클릭했다면 에디트 컨트롤을 생성한다
		CRect r(GRID_X_POSITION + m_select_x * GRID_WIDTH + 1, GRID_Y_POSITION + m_select_y * GRID_HEIGHT + 1, GRID_X_POSITION + (m_select_x + 1) * GRID_WIDTH, GRID_Y_POSITION + (m_select_y + 1) * GRID_HEIGHT);
		CreateEdit(&r);

		// 이미 문자열이 있으면 편집하도록
		if (mp_edit_data[m_select_y][m_select_x] != NULL) {
			mp_modify_edit->SetWindowText(mp_edit_data[m_select_y][m_select_x]);
			mp_modify_edit->SetSel(0, -1);
		}
	}

	CDialogEx::OnLButtonDblClk(nFlags, point);
}

// 에디트 컨트롤 삭제
void CGridTableDlg::DeleteEdit()
{
	if (mp_modify_edit != NULL) {
		CString str;
		mp_modify_edit->GetWindowText(str);
		int len = str.GetLength();

		// 입력된 문자열이 있다면
		if (len > 0) {
			// 기존에도 정보가 있었으면
			if (mp_edit_data[m_select_y][m_select_x] != NULL) {
				// 기존에 있던 문자열과 내용이 달라졌으면
				if (str != mp_edit_data[m_select_y][m_select_x]) {
					//기존 정보 제거
					delete[] mp_edit_data[m_select_y][m_select_x];

					// 변경 정보를 위해 메모리 할당
					mp_edit_data[m_select_y][m_select_x] = new TCHAR[++len];
					memcpy(mp_edit_data[m_select_y][m_select_x], (const TCHAR*)str, len * 2);
				}
			}
			else {
				// 정보 저장을 위해 메모리 할당
				mp_edit_data[m_select_y][m_select_x] = new TCHAR[++len];
				memcpy(mp_edit_data[m_select_y][m_select_x], (const TCHAR*)str, len * 2);
			}
		}
		else {				// 입력 항목이 없으면
			// 기존 정보는 있었으면
			if (mp_edit_data[m_select_y][m_select_x] != NULL) {
				// 입력되어있던 값을 지운 것이니 데이터를 제거한다
				delete[] mp_edit_data[m_select_y][m_select_x];
				mp_edit_data[m_select_y][m_select_x] = NULL;
			}
		}

		mp_modify_edit->DestroyWindow();
		delete mp_modify_edit;
		mp_modify_edit = NULL;
	}
}

// 포커스를 잃으면 에디트컨트롤 제거
void CGridTableDlg::OnDeleteEdit()
{
	DeleteEdit();
}

// 에디트 컨트롤 편집 중 다른 곳을 클릭하면 에디트 컨트롤 제거
void CGridTableDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	DeleteEdit();

	CDialogEx::OnLButtonDown(nFlags, point);
}