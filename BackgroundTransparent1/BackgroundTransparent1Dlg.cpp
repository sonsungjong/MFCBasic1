
// BackgroundTransparent1Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "BackgroundTransparent1.h"
#include "BackgroundTransparent1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBackgroundTransparent1Dlg dialog



CBackgroundTransparent1Dlg::CBackgroundTransparent1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BACKGROUNDTRANSPARENT1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBackgroundTransparent1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBackgroundTransparent1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CBackgroundTransparent1Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CBackgroundTransparent1Dlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_MODIFY_BTN, &CBackgroundTransparent1Dlg::OnBnClickedModifyBtn)
	ON_BN_CLICKED(IDC_RESTORE_BTN, &CBackgroundTransparent1Dlg::OnBnClickedRestoreBtn)
	ON_BN_CLICKED(IDC_SAVE_BTN, &CBackgroundTransparent1Dlg::OnBnClickedSaveBtn)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CBackgroundTransparent1Dlg message handlers

BOOL CBackgroundTransparent1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	SetDlgItemInt(IDC_DEPTH_EDIT, 100);

	// ���� ���
	GetDlgItem(IDC_IMAGE_RECT)->GetWindowRect(m_rect);
	ScreenToClient(m_rect);

	// ������ �д´� (�����̸�)
	m_load_image.Load(_T("test.png"));

	// ���� ũ���� �̹��� �����ϰ� �̹��� ������ �����Ѵ�
	m_edit_image.Create(m_load_image.GetWidth(), m_load_image.GetHeight(), 32);
	CopyImagePattern(&m_edit_image, &m_load_image);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBackgroundTransparent1Dlg::OnPaint()
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
		// ������ �̹����� ȭ�鿡 ���
		m_edit_image.Draw(dc, m_rect.left, m_rect.top);
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBackgroundTransparent1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CBackgroundTransparent1Dlg::OnBnClickedOk(){}


void CBackgroundTransparent1Dlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void CBackgroundTransparent1Dlg::OnBnClickedModifyBtn()
{
	ModifyRed();
	//ModifyGreen();
	// ModifyBlue();
}


void CBackgroundTransparent1Dlg::OnBnClickedRestoreBtn()
{
	// m_load_image�� �̹��� ������ m_edit_image�� ����
	CopyImagePattern(&m_edit_image, &m_load_image);

	// WM_PAINT ����
	Invalidate(0);
}


void CBackgroundTransparent1Dlg::OnBnClickedSaveBtn()
{
	// Alpha�� Ȱ��ȭ
	m_edit_image.SetHasAlphaChannel(1);

	// CImage �� ����� �̹��� ������ ��´� (m_edit_image)
	BITMAP bmp_info;
	GetObject((HBITMAP)m_edit_image, sizeof(BITMAP), &bmp_info);

	// CImage�� ��Ʈ ������ ����� �ּ� ���
	// ��Ʈ ��ġ�� �� ������ ���� ������ ������ ���� ���̸� ����
	// �̹��� ������ ���� ��ġ�� �����Ͱ� �̵���
	unsigned char* p_image = (unsigned char*)m_edit_image.GetBits();
	p_image -= (bmp_info.bmHeight - 1) * bmp_info.bmWidthBytes;
	unsigned char* p_pos = p_image;
	unsigned char* p_limit = p_image + bmp_info.bmHeight * bmp_info.bmWidthBytes;

	// Alpha ���� ����Ǹ� 0�� ������ ��µ��� �ʾ�
	// �������� ������ �ٸ� ������� Alpha�� 255�� �����Ѵ�
	while (p_pos < p_limit)
	{
		// �������� �ƴϸ� A = 255; �Ͽ� ����ȭ���� �ʰ� �Ѵ�
		if ((*(UINT32*)p_pos) != 0) {
			*(p_pos + 3) = 0xFF;					// Alpha = 255
		}
		p_pos += 4;			// ���� ������ �̵�
	}

	// CImage�� �׸��� png���Ϸ� �����Ѵ�.
	m_edit_image.Save(_T("test_result.png"), Gdiplus::ImageFormatPNG);
	MessageBox(_T("����ó�� �Ͽ����ϴ�!"), _T("test_result.png"), MB_OK);

	// Alpha ��� ����
	m_edit_image.SetHasAlphaChannel(0);
}


void CBackgroundTransparent1Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	// CImage ����
	m_load_image.Destroy();
	m_edit_image.Destroy();
}

void CBackgroundTransparent1Dlg::CopyImagePattern(CImage* ap_dest, CImage* ap_src)
{
	// �̹����� �ٿ����� CImage�� ����� �⺻ ������ ����
	BITMAP bmp_info;
	GetObject((HBITMAP)*ap_dest, sizeof(BITMAP), &bmp_info);

	// �̹��� ��Ʈ ������ ����� �ּҸ� ��´� (������ ���� ���� ��ġ)
	// �̹��� ���� ����Ʈ ������ B, G, R, A �̰�, int�� ǥ���ϸ� 0xAARRGGBB
	unsigned char* p_src_image = (unsigned char*)ap_src->GetBits();
	unsigned char* p_dest_image = (unsigned char*)ap_dest->GetBits();

	// CImage�� ����� �ּҸ� �̹��� ������ ���� ��ġ�� �ű����
	// ������ ���� ������ ������ ���� ���̸� �����Ѵ�
	p_src_image -= (bmp_info.bmHeight - 1) * bmp_info.bmWidthBytes;
	p_dest_image -= (bmp_info.bmHeight - 1) * bmp_info.bmWidthBytes;

	// p_src_image �̹��� ������ p_dest_image�� �����Ͽ� �ٿ��ִ´�
	memcpy(p_dest_image, p_src_image, bmp_info.bmHeight * bmp_info.bmWidthBytes);
}

void CBackgroundTransparent1Dlg::ModifyBlue()
{
	// CImage �� ����� ������ ��´�
	BITMAP bmp_info;
	GetObject((HBITMAP)m_edit_image, sizeof(BITMAP), &bmp_info);

	// CImage�� ��Ʈ ������ ����� �ּҸ� ��´�
	// ������ ���� ������ ������ ���̸�ŭ ����
	// �̹��� ������ �����ϴ� ��ġ�� �����͸� �ű��
	unsigned char* p_image = (unsigned char*)m_edit_image.GetBits();
	p_image -= (bmp_info.bmHeight - 1) * bmp_info.bmWidthBytes;

	// �̹��� ������ �����ּҿ� ���ּҸ� p_pos �� p_limit �� ����
	unsigned char* p_pos = p_image;
	unsigned char* p_limit = p_image + bmp_info.bmHeight * bmp_info.bmWidthBytes;

	// ��Ȯ�� ���� ��´�
	int r, g, b, depth = GetDlgItemInt(IDC_DEPTH_EDIT);

	// �̹����� ���� ����
	// B(+0), G(+1), R(+2), A(+3)
	while (p_pos < p_limit)
	{
		b = *p_pos;				// blue ���� ��´�
		g = *(p_pos + 1) + depth;			// green ���� depth�� ���� ���� ��´�
		r = *(p_pos + 2) + depth;			// red���� depth�� ���� ���� ��´�

		// blue�� ���� ����ġ�� ���� green �Ǵ� red ���� �۴ٸ�
		// ���������� ����
		if (b < r || b < g) { *(UINT32*)p_pos = 0; }
		p_pos += 4;
	}

	// WM_PAINT
	Invalidate(0);
}

void CBackgroundTransparent1Dlg::ModifyGreen()
{
	// CImage �� ����� ������ ��´�
	BITMAP bmp_info;
	GetObject((HBITMAP)m_edit_image, sizeof(BITMAP), &bmp_info);

	// CImage�� ��Ʈ ������ ����� �ּҸ� ��´�
	// ������ ���� ������ ������ ���̸�ŭ ����
	// �̹��� ������ �����ϴ� ��ġ�� �����͸� �ű��
	unsigned char* p_image = (unsigned char*)m_edit_image.GetBits();
	p_image -= (bmp_info.bmHeight - 1) * bmp_info.bmWidthBytes;

	// �̹��� ������ ���� �ּҿ� �� �ּҸ� p_pos�� p_limit ������ �����Ѵ�.
	unsigned char* p_pos = p_image;
	unsigned char* p_limit = p_image + bmp_info.bmHeight * bmp_info.bmWidthBytes;

	// ��Ȯ�� ���� ��´�.
	int r, g, b, depth = GetDlgItemInt(IDC_DEPTH_EDIT);

	// �̹��� ���� ���� ����    B(+0), G(+1), R(+2), A(+3)
	while (p_pos < p_limit) {
		b = *p_pos + depth;  // blue ���� depth�� ���� ���� ��´�.
		g = *(p_pos + 1);  // green ���� ��´�.
		r = *(p_pos + 2) + depth;  // red ���� depth�� ���� ���� ��´�.

		// green�� ���� ����ġ�� ���� blue �Ǵ� red ���� �۴ٸ�
		// ���������� ����
		if (g < b || g < r) { *(UINT32*)p_pos = 0; }
		p_pos += 4;						// ���� �������� �̵�
	}

	// WM_PAINT
	Invalidate(0);
}

void CBackgroundTransparent1Dlg::ModifyRed()
{
	// CImage �� ����� ������ ��´�
	BITMAP bmp_info;
	GetObject((HBITMAP)m_edit_image, sizeof(BITMAP), &bmp_info);

	// CImage�� ��Ʈ ������ ����� �ּҸ� ��´�
	// ������ ���� ������ ������ ���̸�ŭ ���� �̹��� ������ �����ϴ� ��ġ�� �����͸� �ű��
	unsigned char* p_image = (unsigned char*)m_edit_image.GetBits();
	p_image -= (bmp_info.bmHeight - 1) * bmp_info.bmWidthBytes;

	// �̹��� ������ ���� �ּҿ� �� �ּҸ� p_pos�� p_limit ������ �����Ѵ�.
	unsigned char* p_pos = p_image;
	unsigned char* p_limit = p_image + bmp_info.bmHeight * bmp_info.bmWidthBytes;

	// ��Ȯ�� ���� ��´�.
	int r, g, b, depth = GetDlgItemInt(IDC_DEPTH_EDIT);

	// �̹��� ���� ���� B(+0), G(+1), R(+2), A(+3) ����
	while (p_pos < p_limit) {
		b = *p_pos + depth;  // blue ���� depth�� ���� ���� ��´�.
		g = *(p_pos + 1) + depth;  // green ���� depth�� ���� ���� ��´�.
		r = *(p_pos + 2);  // red ���� ��´�.

		// red�� ���� blue(+����ġ) �Ǵ� green(+����ġ) ���� �۴ٸ�
		// ���������� �����Ѵ�.
		if (r < b || r < g) { *(UINT32*)p_pos = 0; }
		p_pos += 4;					// ���� �������� �̵�
	}

	// WM_PAINT
	Invalidate(0);
}
