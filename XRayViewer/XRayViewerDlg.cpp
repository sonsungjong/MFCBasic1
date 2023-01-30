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
	// Picture Control ��ǥ�� ����
	GetDlgItem(IDC_VIEW_RECT)->GetWindowRect(r);
	// ��ǥ�� ���� ��ȭ���� �������� ��ȯ
	ScreenToClient(r);
	// �̹����� ������ ��ü ����
	m_xray_view.Create(NULL, NULL, WS_CHILD | WS_VISIBLE, r, this, 25001);
	// 'test1.img' ������ ����
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

// '*' ���ڰ� �پ������� ���� ����
// '*' ���ڷ� �����ϴ� ���ڿ��� 0�� �����ϰ� �׷��� ������ 1�� �����Ͽ� ����
void CXRayViewerDlg::MakeEnableColorTable()
{
	CString str;
	// 256���� ������ ��� üũ
	for (int i = 0; i < 256; i++) {
		// ������ ǥ�õ� �������� Ȯ��
		if (m_color_list.GetItemData(i)) {
			// �ؽ�Ʈ�� ����
			m_color_list.GetText(i, str);
			// �̸� �տ� '*' ���ڰ� �ִ��� üũ
			if (str[0] == '*') { m_enable_colors[i] = 0; }				// ��Ȱ��
			else { m_enable_colors[i] = 1; }									// Ȱ��
		}
		else {
			m_enable_colors[i] = 0;						// ��Ȱ��
		}
	}
}



void CXRayViewerDlg::OnBnClickedGetColorBtn()
{
	// TODO: Add your control notification handler code here
	// X-Ray �̹����� ���� ������ ���� ��� ������ ����Ʈ �ڿ��� ���
	m_xray_view.SetColorDataToListBox(&m_color_list);
	// ����Ʈ �ڽ��� ��µ� '*' ���ڸ� �������� ���� ��Ȱ��ȭ
	MakeEnableColorTable();
}

void CXRayViewerDlg::OnBnClickedShowSelectColor()
{
	// TODO: Add your control notification handler code here
	OnLbnSelchangeColorList();
}

// ����Ʈ�ڽ� : �̺�Ʈ �ڵ鷯 �߰�
// ���� �ε��� ���� �ǽð� ����
void CXRayViewerDlg::OnLbnSelchangeColorList()
{
	// TODO: Add your control notification handler code here
	// ������ �ε����� ����
	int index = m_color_list.GetCurSel();
	//if (index != LB_ERR) {
	//	if (m_show_select_color.GetCheck()) {
	//		// ���� ������ ��������� ǥ���ϴ� ���
	//		m_xray_view.ChangeSelectColorImage(m_enable_colors, index, m_color_list.GetItemData(index));
	//	}
	//	else {
	//		// ���� ������ ǥ������ �ʴ� ���
	//		m_xray_view.UpdateImage(m_enable_colors);
	//	}
	//}
}

// ����Ʈ�ڽ� : �̺�Ʈ �ڵ鷯 �߰�
void CXRayViewerDlg::OnLbnDblclkColorList()
{
	// TODO: Add your control notification handler code here
		// ������ ������ ��ġ���� ����
	int index = m_color_list.GetCurSel();
	// ���� �̹����� ���� �������� Ȯ��
	if (index != LB_ERR && m_color_list.GetItemData(index)) {
		CString str;
		m_color_list.GetText(index, str);					// ���� ������ ����

		// '*' ���ڷ� �����ϸ� '*' ���ڸ� ����, '*' ���ڰ� ������ '*' ���� �߰�
		if (str[0] == '*') { str.Delete(0, 1); }
		else { str = '*' + str; }

		// ���� ���� ���� ��� (���->������, ������->���)
		m_enable_colors[index] = !m_enable_colors[index];

		int color_count = m_color_list.GetItemData(index);
		m_color_list.DeleteString(index);				// ���� ����
		m_color_list.InsertString(index, str);						// ���� �߰�
		m_color_list.SetItemData(index, color_count);				// ���� ���� ����
		m_color_list.SetCurSel(index);						// �߰��� �׸��� �����׸����� ����

		m_xray_view.UpdateRange(m_enable_colors);
		OnLbnSelchangeColorList();
	}
}

void CXRayViewerDlg::ChangeListBoxItemString(int a_index, const TCHAR* ap_string)
{
	// �����ϱ� �� ���� ��� ������ ����ϰ�
	// ���� ������ ����
	// ���� ���� �ٽ� �߰�
	// �߰��� ��ġ�� ���� ������ �ٽ� ����
	// �߰��� �׸��� ���� �׸����� �ٽ� ����
	int color_count = m_color_list.GetItemData(a_index);
	m_color_list.DeleteString(a_index);
	m_color_list.InsertString(a_index, ap_string);
	m_color_list.SetItemData(a_index, color_count);
	m_color_list.SetSel(a_index);
}

void CXRayViewerDlg::ImageUpdateAccordingToColorRangeChange()
{
	// ������ �ִ񰪰� �ּڰ��� �ٽ� ����Ͽ� ��ȿ������ ����
	// ���� ��� ���ο� ���� �̹����� ���
	OnLbnSelchangeColorList();
}

void CXRayViewerDlg::OnBnClickedSelectAllBtn()
{
	// 256�� ���� üũ
	for (int i = 0; i < 256; i++) {
		// ���� ��� ������ �ִ� �׸� 1�� ����
		if (m_color_list.GetItemData(i)) {
			m_color_list.SetSel(i, m_color_list.GetItemData(i) != 0);
		}
	}
}


void CXRayViewerDlg::OnBnClickedToggleBtn()
{
	CString str;
	// 256�� ���� ��� üũ
	for (int i = 0; i < 256; i++) {
		// ���õǾ� �ְ� ������ ǥ�õ� �������� Ȯ��
		if (m_color_list.GetSel(i) && m_color_list.GetItemData(i)) {
			// ���� ������ ��´�
			m_color_list.GetText(i, str);
			// '*' �� �����ϸ� '*' ����, '*'�� �������� ������ '*' ���̱�
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
