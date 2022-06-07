#include "pch.h"
#include "framework.h"
#include "PalaDog3.h"
#include "PalaDog3Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CPalaDog3Dlg::CPalaDog3Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PALADOG3_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPalaDog3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPalaDog3Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CPalaDog3Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CPalaDog3Dlg::OnBnClickedCancel)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

BOOL CPalaDog3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	// MakeClipImageWait();
	// MakeClipImageWalk();
	// MakeClipImageWeapon();
	
	//const int img_num = 5;
	//int position[img_num][2][2] = {
	//	{{348, 87},{57,46}},
	//	{{218,166},{58,42}},
	//	{{277,166},{59,42}},
	//	{{406,87},{60,46}},
	//	{{179,87},{60,50}}
	//};
	//MakeClipImage(img_num, position, _T("..\\img\\m01_1"), _T("..\\img\\effect_b_weapons"));

	LoadGameImage();

	// ��ȭ���� ���� ��ǥ ����
	CRect r;
	GetClientRect(r);
	m_cx = r.Width();
	m_cy = r.Height();

	// �̹��� ����
	m_mem_image.Create(m_cx, m_cy, 32);
	m_hdc = m_mem_image.GetDC();
	::SelectObject(m_hdc, GetStockObject(DC_PEN));
	::SetDCPenColor(m_hdc, RGB(255, 255, 255));
	MakeGameImage();

	SetTimer(1, 50, nullptr);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPalaDog3Dlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	if (IsIconic())
	{
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		// ����ȭ�� ���
		m_mem_image.Draw(dc, 0, 0);
		//CDialogEx::OnPaint();
	}
}

HCURSOR CPalaDog3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CPalaDog3Dlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}

void CPalaDog3Dlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnCancel();
}

void CPalaDog3Dlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	//::PostQuitMessage(0);
	DestroyWindow();

	CDialogEx::OnClose();
}

void CPalaDog3Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	KillTimer(1);

	m_mem_image.ReleaseDC();
	m_mem_image.Destroy();

	for (int i = 0; i < MAX_WALK_COUNT; i++) {
		m_walk_image[i].Destroy();
	}
	for (int i = 0; i < MAX_WAIT_COUNT; i++) {
		m_wait_image[i].Destroy();
	}
	for (int i = 0; i < 4; i++) {
		m_move_key_image[i].Destroy();
	}
	m_stage_bk_image.Destroy();
	m_main_panel_image.Destroy();
	m_tool_cover_image.Destroy();
}

void CPalaDog3Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 1) {
		if (!m_left_key_flag) {					// ���� Ű�� ���������� ��
			if (m_hero_x >= 100) {					
				m_hero_x--;						// �ڷ� �̵�
			}
		}
		if (!m_right_key_flag) {					// ������ Ű�� ���������� ��
			if (m_hero_x <= (m_cx - 200)) {
				m_hero_x++;				// ������ �̵�
			}
		}

		// ����ȭ�� �׸���
		MakeGameImage();

		if (m_walk_flag == 0 && m_walk_index == 0) {				// ��� ����
			m_wait_index = (m_wait_index + 1) % MAX_WAIT_COUNT;
		}
		else {				// �̵� ����
			m_walk_index = (m_walk_index + 1) % MAX_WALK_COUNT;
		}

		// ���� �������� DC�� �� ȭ�� ���
		CClientDC dc(this);
		m_mem_image.Draw(dc, 0, 0);
	}
	else{
		CDialogEx::OnTimer(nIDEvent);
	}
}

void CPalaDog3Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (CRect(32, 268, 32 + 74, 268 + 44).PtInRect(point)) {
		HeroMoving();
		m_left_key_flag = 0;
		SetCapture();
	}
	else if (CRect(126, 268, 126 + 74, 268 + 44).PtInRect(point)) {
		HeroMoving();
		m_right_key_flag = 0;
		SetCapture();
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}

void CPalaDog3Dlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (!m_left_key_flag || !m_right_key_flag) {
		m_left_key_flag = 1;
		m_right_key_flag = 1;
		m_walk_flag = 0;
		ReleaseCapture();
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}

// ��ȭ���ڿ��� Ű���� �ν��� ���� �����Լ�
BOOL CPalaDog3Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN) {
		if (pMsg->wParam == VK_LEFT) {
			m_left_key_flag = 0;
			HeroMoving();
			return 1;
		}
		else if (pMsg->wParam == VK_RIGHT) {
			m_right_key_flag = 0;
			HeroMoving();
			return 1;
		}
	}
	else if (pMsg->message == WM_KEYUP) {
		if (pMsg->wParam == VK_LEFT) {
			m_left_key_flag = 1;
			m_walk_flag = 0;
			return 1;
		}
		else if (pMsg->wParam == VK_RIGHT) {
			m_right_key_flag = 1;
			m_walk_flag = 0;
			return 1;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CPalaDog3Dlg::MakeGameImage()
{
	// ��� �����
	// ::Rectangle(m_hdc, 0, 0, m_cx, m_cy);
	// DC�� �̹��� ��� ������
	m_stage_bk_image.Draw(m_hdc, 0, 0);
	// ���� ������
	m_main_panel_image.TransparentBlt(m_hdc, 0, 190, m_main_panel_image.GetWidth(), m_main_panel_image.GetHeight(), RGB(255, 1, 1));
	// ���� Ŀ��
	m_tool_cover_image.TransparentBlt(m_hdc, 238, 280, m_tool_cover_image.GetWidth(), m_tool_cover_image.GetHeight(), RGB(255, 1, 1));
	// ���� Ű
	m_move_key_image[m_left_key_flag].Draw(m_hdc, 10, 267);
	// ������ Ű
	m_move_key_image[m_right_key_flag + 2].Draw(m_hdc, 124, 267);

	CImage* p_image;
	// �̵��� ��ġ�� ������ ���ְ� �̹����� ���
	if (m_walk_flag == 0 && m_walk_index == 0)
	{
		p_image = m_wait_image + m_wait_index;
	}
	else {
		p_image = m_walk_image + m_walk_index;
	}
	p_image->TransparentBlt(m_hdc, m_hero_x, 70, p_image->GetWidth(), p_image->GetHeight(), RGB(255, 1, 1));
}

// �̹����� �����Ͽ� �̵��ϴ� �ִϸ��̼� ����
void CPalaDog3Dlg::HeroMoving()
{
	if (!m_walk_flag) {						// ��� �����̸�
		m_walk_flag = 1;				// �̵� ����
		m_walk_index = 0;				// ó�� �̹���
	}
}

// ���ӿ� ����� �̹����� �д� �Լ�
void CPalaDog3Dlg::LoadGameImage()
{
	CString file_name;
	// �̵� �̹����� ���Ͽ��� �о� m_walk_image �迭�� ����
	for (int i = 0; i < MAX_WALK_COUNT; i++)
	{
		file_name.Format(_T("..\\img\\walk_%02d.png"), i);
		m_walk_image[i].Load(file_name);
	}
	// ��� �̹����� ���Ͽ��� �о� m_wait_image �迭�� ����
	for (int i = 0; i < MAX_WAIT_COUNT; i++)
	{
		file_name.Format(_T("..\\img\\wait_%02d.png"), i);
		m_wait_image[i].Load(file_name);
	}

	// ���� ��� �̹����� �����´�
	m_stage_bk_image.Load(_T("..\\img\\stage_01.png"));
	// ���� ���� �г��� �̹����� �����´�
	m_main_panel_image.Load(_T("..\\img\\main_panel.png"));
	// ���� ���� Ŀ�� �̹����� �����´�
	m_tool_cover_image.Load(_T("..\\img\\tool_cover.png"));
	// ���� �Ǵ� ������ Ű ���� �̹����� �����´�
	m_move_key_image[0].Load(_T("..\\img\\left_down.png"));
	m_move_key_image[1].Load(_T("..\\img\\left_up.png"));
	m_move_key_image[2].Load(_T("..\\img\\right_down.png"));
	m_move_key_image[3].Load(_T("..\\img\\right_up.png"));
}

void CPalaDog3Dlg::MakeClipImageWait()
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
	src_image.Load(_T("..\\img\\u_01_1.png"));

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

// �̹��� ���� �Ϻθ� �߶� PNG�� ����� �Լ�
void CPalaDog3Dlg::MakeClipImageWalk()
{
	// [12���̹���][������ġx,y][��������]
	int position[12][2][2] = {
		{{204,264},{92,92}}, {{590,360},{90,92}}, {{860,384},{90,90}},
		{{770,474},{90,90}}, {{770,384},{90,90}}, {{680,474},{90,90}},
		{{680,384},{90,90}}, {{590,452},{90,90}}, {{500,452},{90,90}}, 
		{{500,360},{90,92}}, {{204,172},{92,92}}, {{106,766},{92,92}}
	};

	CImage src_image, dest_image;
	CString file_name;
	src_image.Load(_T("..\\img\\u_01_1.png"));

	HDC hdc;
	HBRUSH h_bk_brush = ::CreateSolidBrush(RGB(255, 1, 1));
	RECT r = { 0, };

	for (int i = 0; i < 12; i++) {
		// ���� �ܰ��� �̹��� ���� ���� ����
		r.right = position[i][1][0];
		r.bottom = position[i][1][1];

		dest_image.Create(r.right, r.bottom, 32);
		hdc = dest_image.GetDC();
		::FillRect(hdc, &r, h_bk_brush);
		src_image.Draw(hdc, 0, 0, r.right, r.bottom, position[i][0][0], position[i][0][1], r.right, r.bottom);
		file_name.Format(_T("..\\img\\wait_%02d.png"), i);
		dest_image.Save(file_name, Gdiplus::ImageFormatPNG);

		// ���ҽ� �ݳ�
		dest_image.ReleaseDC();
		dest_image.Destroy();
	}
	::DeleteObject(h_bk_brush);
	src_image.Destroy();
}

void CPalaDog3Dlg::MakeClipImageWeapon()
{
	const int image_count = 5;

	// [5���̹���][������ġx,y][��������]
	int position[image_count][2][2] = {
		{{348, 87},{57,46}},
		{{218,166},{58,42}}, 
		{{277,166},{59,42}}, 
		{{406,87},{60,46}}, 
		{{179,87},{60,50}}
	};

	CImage src_image, dest_image;
	CString file_name;
	src_image.Load(_T("..\\img\\m01_1.png"));

	HDC hdc;
	// ����ȭ ó���� ���� RGB(255,1,1)
	HBRUSH h_bk_brush = ::CreateSolidBrush(RGB(255, 1, 1));
	RECT r = { 0, };

	for (int i = 0; i < image_count; i++) {
		// ���� �ܰ��� �̹��� ���� ���� ����
		r.right = position[i][1][0];
		r.bottom = position[i][1][1];

		dest_image.Create(r.right, r.bottom, 32);
		hdc = dest_image.GetDC();
		::FillRect(hdc, &r, h_bk_brush);
		src_image.Draw(hdc, 0, 0, r.right, r.bottom, position[i][0][0], position[i][0][1], r.right, r.bottom);
		file_name.Format(_T("..\\img\\effect_b_weapons_%02d.png"), i);
		dest_image.Save(file_name, Gdiplus::ImageFormatPNG);

		// ���ҽ� �ݳ�
		dest_image.ReleaseDC();
		dest_image.Destroy();
	}
	::DeleteObject(h_bk_brush);
	src_image.Destroy();
}

// Ȯ���� ���� �Ķ���� ���� ��
void CPalaDog3Dlg::MakeClipImage(const int img_num, const int (*a_position)[2][2], TCHAR* a_origin_path, TCHAR* a_crop_path = _T(".\\"))
{
	CImage src_image, dest_image;
	CString file_name;
	TCHAR add_extension[512];
	_tcscpy_s(add_extension, sizeof(add_extension) / sizeof(add_extension[0]), a_origin_path);
	_tcscat_s(add_extension, sizeof(add_extension)/sizeof(add_extension[0]), _T(".png"));
	src_image.Load(add_extension);

	HDC hdc;
	// ����ȭ ó���� ���� RGB(255,1,1)
	HBRUSH h_bk_brush = ::CreateSolidBrush(RGB(255, 1, 1));
	RECT r = { 0, };

	for (int i = 0; i < img_num; i++) {
		// ���� �ܰ��� �̹��� ���� ���� ����
		r.right = a_position[i][1][0];
		r.bottom = a_position[i][1][1];

		dest_image.Create(r.right, r.bottom, 32);
		hdc = dest_image.GetDC();
		::FillRect(hdc, &r, h_bk_brush);

		src_image.Draw(hdc, 0, 0, r.right, r.bottom, a_position[i][0][0], a_position[i][0][1], r.right, r.bottom);
		file_name.Format(_T("%s_%02d.png"), a_crop_path, i);
		dest_image.Save(file_name, Gdiplus::ImageFormatPNG);

		// ���ҽ� �ݳ�
		dest_image.ReleaseDC();
		dest_image.Destroy();
	}
	::DeleteObject(h_bk_brush);
	src_image.Destroy();
}