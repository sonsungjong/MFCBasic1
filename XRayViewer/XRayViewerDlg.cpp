#include "pch.h"
#include "framework.h"
#include "XRayViewer.h"
#include "XRayViewerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CXRayViewerDlg::CXRayViewerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_XRAYVIEWER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	memset(m_enable_colors, 0, sizeof(m_enable_colors));
}

void CXRayViewerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COLOR_LIST, m_color_list);
	//DDX_Control(pDX, IDC_SHOW_SELECT_COLOR, m_show_select_color);
}

BEGIN_MESSAGE_MAP(CXRayViewerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CXRayViewerDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CXRayViewerDlg::OnBnClickedCancel)
	ON_WM_DESTROY()
	ON_LBN_DBLCLK(IDC_COLOR_LIST, &CXRayViewerDlg::OnLbnDblclkColorList)
	ON_LBN_SELCHANGE(IDC_COLOR_LIST, &CXRayViewerDlg::OnLbnSelchangeColorList)
	ON_BN_CLICKED(IDC_SHOW_SELECT_COLOR, &CXRayViewerDlg::OnBnClickedShowSelectColor)
	ON_BN_CLICKED(IDC_SELECT_ALL_BTN, &CXRayViewerDlg::OnBnClickedSelectAllBtn)
	ON_BN_CLICKED(IDC_GET_COLOR_BTN, &CXRayViewerDlg::OnBnClickedGetColorBtn)
	ON_BN_CLICKED(IDC_TOGGLE_BTN, &CXRayViewerDlg::OnBnClickedToggleBtn)
	ON_BN_CLICKED(IDC_COLOR_ENABLE_BTN, &CXRayViewerDlg::OnBnClickedColorEnableBtn)
	ON_BN_CLICKED(IDC_COLOR_DISABLE_BTN, &CXRayViewerDlg::OnBnClickedColorDisableBtn)
END_MESSAGE_MAP()


// CXRayViewerDlg message handlers

BOOL CXRayViewerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	CRect r;
	// Picture Control 좌표를 얻어옴
	GetDlgItem(IDC_VIEW_RECT)->GetWindowRect(r);
	// 좌표를 현재 대화상자 기준으로 변환
	ScreenToClient(r);
	// 이미지를 보여줄 객체 생성
	m_xray_view.Create(NULL, NULL, WS_CHILD | WS_VISIBLE, r, this, 25001);
	// 'test1.img' 파일을 연다
	m_xray_view.LoadXRayImage(_T("test1.img"));

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CXRayViewerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

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
		CDialogEx::OnPaint();
	}
}

HCURSOR CXRayViewerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CXRayViewerDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}

void CXRayViewerDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}

void CXRayViewerDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	
}

// '*' 문자가 붙어있으면 색상 제외
// '*' 문자로 시작하는 문자열은 0을 대입하고 그렇지 않으면 1을 대입하여 구분
void CXRayViewerDlg::MakeEnableColorTable()
{
	CString str;
	// 256개의 색상을 모두 체크
	for (int i = 0; i < 256; i++) {
		// 실제로 표시된 색상인지 확인
		if (m_color_list.GetItemData(i)) {
			// 텍스트를 읽음
			m_color_list.GetText(i, str);
			// 이름 앞에 '*' 문자가 있는지 체크
			if (str[0] == '*') { m_enable_colors[i] = 0; }				// 비활성
			else { m_enable_colors[i] = 1; }									// 활성
		}
		else {
			m_enable_colors[i] = 0;						// 비활성
		}
	}
}



void CXRayViewerDlg::OnBnClickedGetColorBtn()
{
	// TODO: Add your control notification handler code here
	// X-Ray 이미지에 사용된 색상의 실제 사용 갯수를 리스트 박에서 출력
	m_xray_view.SetColorDataToListBox(&m_color_list);
	// 리스트 박스에 출력된 '*' 문자를 기준으로 색상 비활성화
	MakeEnableColorTable();
}

void CXRayViewerDlg::OnBnClickedShowSelectColor()
{
	// TODO: Add your control notification handler code here
	OnLbnSelchangeColorList();
}

// 리스트박스 : 이벤트 핸들러 추가
// 선택 인덱스 색상 실시간 갱신
void CXRayViewerDlg::OnLbnSelchangeColorList()
{
	// TODO: Add your control notification handler code here
	// 선택한 인덱스를 얻음
	int index = m_color_list.GetCurSel();
	//if (index != LB_ERR) {
	//	if (m_show_select_color.GetCheck()) {
	//		// 선택 색상을 노란색으로 표시하는 경우
	//		m_xray_view.ChangeSelectColorImage(m_enable_colors, index, m_color_list.GetItemData(index));
	//	}
	//	else {
	//		// 선택 색상을 표시하지 않는 경우
	//		m_xray_view.UpdateImage(m_enable_colors);
	//	}
	//}
}

// 리스트박스 : 이벤트 핸들러 추가
void CXRayViewerDlg::OnLbnDblclkColorList()
{
	// TODO: Add your control notification handler code here
		// 선택한 색상의 위치값을 얻어옴
	int index = m_color_list.GetCurSel();
	// 실제 이미지에 사용된 색상인지 확인
	if (index != LB_ERR && m_color_list.GetItemData(index)) {
		CString str;
		m_color_list.GetText(index, str);					// 색상 정보를 읽음

		// '*' 문자로 시작하면 '*' 문자를 삭제, '*' 문자가 없으면 '*' 문자 추가
		if (str[0] == '*') { str.Delete(0, 1); }
		else { str = '*' + str; }

		// 색상 포함 여부 토글 (사용->사용안함, 사용안함->사용)
		m_enable_colors[index] = !m_enable_colors[index];

		int color_count = m_color_list.GetItemData(index);
		m_color_list.DeleteString(index);				// 색상 제거
		m_color_list.InsertString(index, str);						// 색상 추가
		m_color_list.SetItemData(index, color_count);				// 색상 갯수 저장
		m_color_list.SetCurSel(index);						// 추가된 항목을 선택항목으로 갱신

		m_xray_view.UpdateRange(m_enable_colors);
		OnLbnSelchangeColorList();
	}
}

void CXRayViewerDlg::ChangeListBoxItemString(int a_index, const TCHAR* ap_string)
{
	// 제거하기 전 색상 사용 갯수를 백업하고
	// 색상 정보를 제거
	// 색상 정보 다시 추가
	// 추가된 위치에 색상 갯수도 다시 저장
	// 추가된 항목을 선택 항목으로 다시 설정
	int color_count = m_color_list.GetItemData(a_index);
	m_color_list.DeleteString(a_index);
	m_color_list.InsertString(a_index, ap_string);
	m_color_list.SetItemData(a_index, color_count);
	m_color_list.SetSel(a_index);
}

void CXRayViewerDlg::ImageUpdateAccordingToColorRangeChange()
{
	// 색상의 최댓값과 최솟값을 다시 계산하여 유효범위를 결정
	// 색상 사용 여부에 따라 이미지를 출력
	OnLbnSelchangeColorList();
}

void CXRayViewerDlg::OnBnClickedSelectAllBtn()
{
	// 256개 색상 체크
	for (int i = 0; i < 256; i++) {
		// 색상 사용 갯수가 있는 항목만 1로 설정
		if (m_color_list.GetItemData(i)) {
			m_color_list.SetSel(i, m_color_list.GetItemData(i) != 0);
		}
	}
}


void CXRayViewerDlg::OnBnClickedToggleBtn()
{
	CString str;
	// 256개 색상 모두 체크
	for (int i = 0; i < 256; i++) {
		// 선택되어 있고 실제로 표시된 색상인지 확인
		if (m_color_list.GetSel(i) && m_color_list.GetItemData(i)) {
			// 색상 정보를 얻는다
			m_color_list.GetText(i, str);
			// '*' 로 시작하면 '*' 삭제, '*'로 시작하지 않으면 '*' 붙이기
			if (str[0] == '*') { str.Delete(0, 1); }
			else { str = '*' + str; }

			m_enable_colors[i] = !m_enable_colors[i];
			ChangeListBoxItemString(i, str);
		}
	}
	ImageUpdateAccordingToColorRangeChange();
}


void CXRayViewerDlg::OnBnClickedColorEnableBtn()
{
	CString str;
	for (int i = 0; i < 256; i++) {
		if (m_color_list.GetSel(i) && m_color_list.GetItemData(i)) {
			m_color_list.GetText(i, str);
			if (str[0] == '*') {
				str.Delete(0, 1);
				m_enable_colors[i] = 1;
			}
			ChangeListBoxItemString(i, str);
		}
	}
	ImageUpdateAccordingToColorRangeChange();
}


void CXRayViewerDlg::OnBnClickedColorDisableBtn()
{
	CString str;
	for (int i = 0; i < 256; i++) {
		if (m_color_list.GetSel(i) && m_color_list.GetItemData(i)) {
			m_color_list.GetText(i, str);
			if (str[0] != '*') {
				str = '*' + str;
				m_enable_colors[i] = 0;
			}
			ChangeListBoxItemString(i, str);
		}
	}
	ImageUpdateAccordingToColorRangeChange();
}
