
// PalaDog1Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "PalaDog1.h"
#include "PalaDog1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPalaDog1Dlg dialog



CPalaDog1Dlg::CPalaDog1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PALADOG1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPalaDog1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPalaDog1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CPalaDog1Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CPalaDog1Dlg::OnBnClickedCancel)
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CPalaDog1Dlg message handlers

BOOL CPalaDog1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	// MakeClipImage();								// �̹��� �߶󳻱� �Լ�
	CString file_name;
	// �̵� �̹��� ������ �о� m_work_image�� ����
	for (int i = 0; i < MAX_WALK_COUNT; i++) {
		file_name.Format(_T(".\\image\\walk_%02d.png"), i);
		m_walk_image[i].Load(file_name);
	}

	CRect r;
	GetClientRect(r);
	m_cx = r.Width();
	m_cy = r.Height();

	m_mem_image.Create(m_cx, m_cy, 32);
	m_hdc = m_mem_image.GetDC();
	::SelectObject(m_hdc, GetStockObject(DC_PEN));
	::SetDCPenColor(m_hdc, RGB(255, 255, 255));

	// �⺻ ���� ȭ���� �׸���
	MakeGameImage();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPalaDog1Dlg::OnPaint()
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

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPalaDog1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPalaDog1Dlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CPalaDog1Dlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnCancel();
}



void CPalaDog1Dlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	::PostQuitMessage(0);

	CDialogEx::OnClose();
}

// ���� �̹������� ���ϴ� ������ �߶� PNG ���Ϸ� ����� �Լ�
void CPalaDog1Dlg::MakeClipImage()
{
	// 12���� �̹����� {{����x, ����y}, {����ũ��, ����ũ��}} �迭�� ��ġ ����
	int position[12][2][2] = {
		{ {606, 98}, { 106,92 } }, { {96, 360}, { 106,94 } }, { {98, 266}, { 106,94 } },
		{ {98, 172}, { 106,94 } }, { {0, 748}, { 106,96 } }, { {0, 652}, { 106,96 } },
		{ {0, 556}, { 106,96 } }, { {0, 460}, { 106,96 } }, { {0, 844}, { 106,94 } },
		{ {110, 930}, { 106,92 } }, { {296, 296}, { 106,90 } }, { {296, 206}, { 106,90 } }
	};

	// ���� �̹����� Clip �̹����� ������ ������ ����
	CImage src_image, dest_image;
	// ���� �̸�
	CString file_name;
	// ���� �̹��� ������ ����
	src_image.Load(_T("u_01_1.png"));

	HDC hdc;
	// ������ ������ �귯��(������) �����
	HBRUSH h_bk_brush = ::CreateSolidBrush(RGB(255, 1, 1));
	RECT r = { 0, };

	// 12�ܰ踦 �������� �߶󳻰� ����
	for (int i = 0; i < 12; ++i)
	{
		r.right = position[i][1][0];
		r.bottom = position[i][1][1];

		// �̹��� ũ�⸸ŭ ����
		dest_image.Create(r.right, r.bottom, 32);
		hdc = dest_image.GetDC();
		::FillRect(hdc, &r, h_bk_brush);
		// ���� �̹������� �ش� ��ġ�� ����
		src_image.Draw(hdc, 0, 0, r.right, r.bottom, position[i][0][0], position[i][0][1], r.right, r.bottom);
		file_name.Format(_T(".\\image\\walk_%02d.png"), i);
		dest_image.Save(file_name, Gdiplus::ImageFormatPNG);

		// �׸��⿡ ����� DC �ݳ�
		dest_image.ReleaseDC();
		dest_image.Destroy();
	}
	::DeleteObject(h_bk_brush);
	src_image.Destroy();
}



void CPalaDog1Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 1) {
		// ȭ�鿡 ĳ���͸� �׸�
		MakeGameImage();
		// ���� ��ġ�� ���
		m_cur_index = (m_cur_index + 1) % MAX_WALK_COUNT;
		if (m_cur_index == 0 && m_walk_flag == 0) {
			KillTimer(1);
		}
		CClientDC dc(this);
		// ȭ�� ���
		m_mem_image.Draw(dc, 0, 0);
	}else{
		CDialogEx::OnTimer(nIDEvent);
	}
}


void CPalaDog1Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	KillTimer(1);

	m_mem_image.ReleaseDC();
	m_mem_image.Destroy();

	// ĳ���� �̹��� ��� ����!
	for (int i = 0; i < MAX_WALK_COUNT; i++) {
		m_walk_image[i].Destroy();
	}
}


BOOL CPalaDog1Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN) {
		if (pMsg->wParam == VK_LEFT) {
			if (m_hero_x >= 100) {
				// �ڷ��̵�
				m_hero_x--;
			}
			HeroMoving();
			return 1;
		}
		else if (pMsg->wParam == VK_RIGHT) {
			if (m_hero_x <= (m_cx - 200)) {
				// ������ �̵�
				m_hero_x++;
			}
			HeroMoving();
			return 1;
		}
	}
	else if (pMsg->message == WM_KEYUP) {
		if (pMsg->wParam == VK_LEFT || pMsg->wParam == VK_RIGHT) {
			m_walk_flag = 0;				// ���� ���·� ����
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CPalaDog1Dlg::MakeGameImage()
{
	// ����� ���ó��
	::Rectangle(m_hdc, 0, 0, m_cx, m_cy);
	// ĳ������ ���� ��ġ�� ����(255,1,1)�� ����ó���ϸ鼭 �̵� �̹����� ����Ѵ�.
	m_walk_image[m_cur_index].TransparentBlt(m_hdc, m_hero_x, 50, m_walk_image[m_cur_index].GetWidth(), m_walk_image[m_cur_index].GetHeight(), RGB(255, 1, 1));
}

void CPalaDog1Dlg::HeroMoving()
{
	if (!m_walk_flag) {					// ���� ���� �϶�
		m_walk_flag = 1;				// �̵� ����
		m_cur_index = 0;				// �ִϸ��̼� ù�ܰ�
		SetTimer(1, 50, nullptr);					// �ִϸ��̼��� ���� Ÿ�̸� ����
	}
}

