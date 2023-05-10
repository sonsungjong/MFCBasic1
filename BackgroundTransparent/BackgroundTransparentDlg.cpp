#include "pch.h"
#include "framework.h"
#include "BackgroundTransparent.h"
#include "BackgroundTransparentDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CBackgroundTransparentDlg::CBackgroundTransparentDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BACKGROUNDTRANSPARENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBackgroundTransparentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBackgroundTransparentDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CBackgroundTransparentDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CBackgroundTransparentDlg::OnBnClickedCancel)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CBackgroundTransparentDlg message handlers

BOOL CBackgroundTransparentDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	// ���� ��ǥ�� ��´�
	GetDlgItem(IDC_IMAGE_RECT)->GetWindowRect(m_rect);
	ScreenToClient(m_rect);				// ����

	// ������ ������ ũ���� �̹����� ����
	m_draw_image.Create(m_rect.Width(), m_rect.Height(), 32);

	// �׸��� �׸� DC ����
	mh_draw_dc = m_draw_image.GetDC();
	::SelectObject(mh_draw_dc, ::GetStockObject(DC_BRUSH));
	::SelectObject(mh_draw_dc, ::GetStockObject(DC_PEN));

	// �׽�Ʈ�� �Ͼ�� �簢��
	::SetDCBrushColor(mh_draw_dc, RGB(255, 255, 255));
	::SetDCPenColor(mh_draw_dc, RGB(0, 0, 128));
	::Rectangle(mh_draw_dc, 10, 10, 100, 100);

	// �׽�Ʈ�� ��Ȳ�� �簢��
	::SetDCBrushColor(mh_draw_dc, RGB(255, 100, 0));
	::SetDCPenColor(mh_draw_dc, RGB(128, 0, 0));
	::Rectangle(mh_draw_dc, 110, 110, 200, 200);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBackgroundTransparentDlg::OnPaint()
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
		m_draw_image.Draw(dc, m_rect.left, m_rect.top);			// �׷��� �̹��� ���
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBackgroundTransparentDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CBackgroundTransparentDlg::OnBnClickedOk()
{
	// Alpha ���� ����ϵ��� ����
	m_draw_image.SetHasAlphaChannel(1);

	// ����� CImage�� ���� ������ ��´�
	BITMAP bmp_info;
	GetObject((HBITMAP)m_draw_image, sizeof(BITMAP), &bmp_info);

	// CImage�� ��Ʈ ������ ����� �ּҸ� ��´�(�� �ּҴ� ������ ���� ���� ��ġ�� ����Ŵ)
	// �̹��� ���� ����Ʈ ������ B, G, R, A�̰� int�� ǥ���ϸ� 0xAARRGGBB
	unsigned char* p_image = (unsigned char*)m_draw_image.GetBits();
	// �ּҸ� �̹��� ������ ������ġ�� �ű��
	// ������ ���� ������ ������ ���� ���̸� ����
	p_image -= (bmp_info.bmHeight - 1) * bmp_info.bmWidthBytes;

	// ũ�⸦ ���� �̹��� ������ ���� �ּҿ� �� �ּҸ� p_pos �� p_limit �� �����Ѵ�
	int cx = m_draw_image.GetWidth();
	int cy = m_draw_image.GetHeight();
	unsigned char* p_pos = p_image;
	unsigned char* p_limit = p_image + (cx * cy * 4);

	// Alpha�� ����Ǹ� A�� 0�� ������ ��µ��� �ʾ� (�⺻������ 0 ����)
	// �Ͼ���� �ƴ� ������� Alpha�� 255�� ����
	while (p_pos < p_limit)
	{
		// �̹����� ���� B(+0), G(+1), R(+2), A(+3)
		// �Ͼ���� �ƴϸ� Alpha���� 255�� �����Ͽ� ����ȭ ���� �ʰ� ó��
		if ((*(UINT32*)p_pos) != 16777215)				// 0xFFFFFF
		{
			*(p_pos + 3) = 0xFF;				// A = 255
		}
		p_pos += 4;				// ���� �������� �̵�
	}

	// CImage �׸��� .png�� ����
	m_draw_image.Save(_T("myimg.png"), Gdiplus::ImageFormatPNG);

	// Alpha ����
	m_draw_image.SetHasAlphaChannel(0);

	// �Ϸ� �޽��� ���
	MessageBox(_T("����ó�� �Ǿ����ϴ�!"), _T("�Ϸ�"), MB_OK);
}


void CBackgroundTransparentDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void CBackgroundTransparentDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	// CImage ����
	m_draw_image.ReleaseDC();
	m_draw_image.Destroy();
}
