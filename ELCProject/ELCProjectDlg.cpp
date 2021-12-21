
// ELCProjectDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "ELCProject.h"
#include "ELCProjectDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void TWAPI_MakeGateImage(TW_DCP* ap_dcp);
void TWAPI_DrawGateImage(TW_DCP* ap_dcp, int a_x, int a_y, TW_DCP* ap_gate_dcp, int a_gate_id, int a_mode);

// CELCProjectDlg dialog
CELCProjectDlg::CELCProjectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ELCPROJECT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CELCProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CELCProjectDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CELCProjectDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CELCProjectDlg::OnBnClickedCancel)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_ADD_OR_BTN, IDC_ADD_NOT_BTN, &CELCProjectDlg::OnBnClickedAddGateBtn)
END_MESSAGE_MAP()


// CELCProjectDlg message handlers

BOOL CELCProjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	GetDlgItem(IDC_DRAW_RECT)->GetWindowRect(m_rect);
	ScreenToClient(m_rect);
	//GDI+ : 회로
	m_dcp.CreateDCP(m_rect.Width(), m_rect.Height());
	//GDI+ : 게이트 이미지
	m_gate_dcp.CreateDCP(700, 280);

	// 어두운 회색
	m_dcp.Clear(RGB24(18, 21, 29));

	TWAPI_MakeGateImage(&m_gate_dcp);

	DrawBoard();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CELCProjectDlg::DrawBoard()
{
	m_dcp.Clear(RGB24(18, 21, 29));
	int y_step = m_rect.Height() / GRID_INTERVAL;
	int x_step = m_rect.Width() / GRID_INTERVAL;
	int x, y;

	m_dcp.SetDCPenColor(Gdiplus::DashStyleSolid, 1, RGB32(32, 128, 128, 128));
	for (y = 0; y < y_step; y++)
	{
		m_dcp.DrawLine(0, y * GRID_INTERVAL, m_rect.right, y * GRID_INTERVAL);
	}
	for (x = 0; x < x_step; x++)
	{
		m_dcp.DrawLine(x * GRID_INTERVAL, 0, x * GRID_INTERVAL, m_rect.bottom);
	}
}

void CELCProjectDlg::OnPaint()
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
		m_dcp.Draw(dc, m_rect.left, m_rect.top);
		//CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CELCProjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CELCProjectDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CELCProjectDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}

void CELCProjectDlg::OnBnClickedAddGateBtn(UINT a_ctrl_id)
{
	UINT gate_id = a_ctrl_id - IDC_ADD_OR_BTN;

	DrawBoard();
	TWAPI_DrawGateImage(&m_dcp, 28, 28, &m_gate_dcp, gate_id, 0);

	InvalidateRect(m_rect, 0);
}