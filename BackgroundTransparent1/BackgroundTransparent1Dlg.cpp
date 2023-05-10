
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

	// 영역 얻기
	GetDlgItem(IDC_IMAGE_RECT)->GetWindowRect(m_rect);
	ScreenToClient(m_rect);

	// 파일을 읽는다 (고정이름)
	m_load_image.Load(_T("test.png"));

	// 같은 크기의 이미지 생성하고 이미지 패턴을 복사한다
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
		// 편집된 이미지를 화면에 출력
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
	// m_load_image의 이미지 패턴을 m_edit_image에 복사
	CopyImagePattern(&m_edit_image, &m_load_image);

	// WM_PAINT 실행
	Invalidate(0);
}


void CBackgroundTransparent1Dlg::OnBnClickedSaveBtn()
{
	// Alpha값 활성화
	m_edit_image.SetHasAlphaChannel(1);

	// CImage 에 저장된 이미지 정보를 얻는다 (m_edit_image)
	BITMAP bmp_info;
	GetObject((HBITMAP)m_edit_image, sizeof(BITMAP), &bmp_info);

	// CImage의 비트 패턴이 저장된 주소 얻기
	// 비트 위치를 얻어서 마지막 줄을 제외한 나머지 줄의 길이를 빼면
	// 이미지 패턴의 시작 위치로 포인터가 이동함
	unsigned char* p_image = (unsigned char*)m_edit_image.GetBits();
	p_image -= (bmp_info.bmHeight - 1) * bmp_info.bmWidthBytes;
	unsigned char* p_pos = p_image;
	unsigned char* p_limit = p_image + bmp_info.bmHeight * bmp_info.bmWidthBytes;

	// Alpha 값이 적용되면 0인 색상은 출력되지 않아
	// 검은색을 제외한 다른 색상들은 Alpha에 255를 대입한다
	while (p_pos < p_limit)
	{
		// 검은색이 아니면 A = 255; 하여 투명화되지 않게 한다
		if ((*(UINT32*)p_pos) != 0) {
			*(p_pos + 3) = 0xFF;					// Alpha = 255
		}
		p_pos += 4;			// 다음 색상을 이동
	}

	// CImage의 그림을 png파일로 저장한다.
	m_edit_image.Save(_T("test_result.png"), Gdiplus::ImageFormatPNG);
	MessageBox(_T("투명처리 하였습니다!"), _T("test_result.png"), MB_OK);

	// Alpha 사용 해제
	m_edit_image.SetHasAlphaChannel(0);
}


void CBackgroundTransparent1Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	// CImage 해제
	m_load_image.Destroy();
	m_edit_image.Destroy();
}

void CBackgroundTransparent1Dlg::CopyImagePattern(CImage* ap_dest, CImage* ap_src)
{
	// 이미지를 붙여넣을 CImage에 저장된 기본 정보를 얻음
	BITMAP bmp_info;
	GetObject((HBITMAP)*ap_dest, sizeof(BITMAP), &bmp_info);

	// 이미지 비트 패턴이 저장된 주소를 얻는다 (마지막 줄의 시작 위치)
	// 이미지 값은 바이트 단위로 B, G, R, A 이고, int로 표시하면 0xAARRGGBB
	unsigned char* p_src_image = (unsigned char*)ap_src->GetBits();
	unsigned char* p_dest_image = (unsigned char*)ap_dest->GetBits();

	// CImage에 저장된 주소를 이미지 패턴의 시작 위치로 옮기려면
	// 마지막 줄을 제외한 나머지 줄의 길이를 빼야한다
	p_src_image -= (bmp_info.bmHeight - 1) * bmp_info.bmWidthBytes;
	p_dest_image -= (bmp_info.bmHeight - 1) * bmp_info.bmWidthBytes;

	// p_src_image 이미지 패턴을 p_dest_image에 복사하여 붙여넣는다
	memcpy(p_dest_image, p_src_image, bmp_info.bmHeight * bmp_info.bmWidthBytes);
}

void CBackgroundTransparent1Dlg::ModifyBlue()
{
	// CImage 에 저장된 정보를 얻는다
	BITMAP bmp_info;
	GetObject((HBITMAP)m_edit_image, sizeof(BITMAP), &bmp_info);

	// CImage의 비트 패턴이 저장된 주소를 얻는다
	// 마지막 줄을 제외한 나머지 길이만큼 빼서
	// 이미지 패턴이 시작하는 위치로 포인터를 옮긴다
	unsigned char* p_image = (unsigned char*)m_edit_image.GetBits();
	p_image -= (bmp_info.bmHeight - 1) * bmp_info.bmWidthBytes;

	// 이미지 패턴의 시작주소와 끝주소를 p_pos 와 p_limit 에 저장
	unsigned char* p_pos = p_image;
	unsigned char* p_limit = p_image + bmp_info.bmHeight * bmp_info.bmWidthBytes;

	// 정확도 값을 얻는다
	int r, g, b, depth = GetDlgItemInt(IDC_DEPTH_EDIT);

	// 이미지값 나열 순서
	// B(+0), G(+1), R(+2), A(+3)
	while (p_pos < p_limit)
	{
		b = *p_pos;				// blue 값을 얻는다
		g = *(p_pos + 1) + depth;			// green 값에 depth를 더한 값을 얻는다
		r = *(p_pos + 2) + depth;			// red값에 depth를 더한 값을 얻는다

		// blue의 값이 가중치를 더한 green 또는 red 보다 작다면
		// 검은색으로 변경
		if (b < r || b < g) { *(UINT32*)p_pos = 0; }
		p_pos += 4;
	}

	// WM_PAINT
	Invalidate(0);
}

void CBackgroundTransparent1Dlg::ModifyGreen()
{
	// CImage 에 저장된 정보를 얻는다
	BITMAP bmp_info;
	GetObject((HBITMAP)m_edit_image, sizeof(BITMAP), &bmp_info);

	// CImage의 비트 패턴이 저장된 주소를 얻는다
	// 마지막 줄을 제외한 나머지 길이만큼 빼서
	// 이미지 패턴이 시작하는 위치로 포인터를 옮긴다
	unsigned char* p_image = (unsigned char*)m_edit_image.GetBits();
	p_image -= (bmp_info.bmHeight - 1) * bmp_info.bmWidthBytes;

	// 이미지 패턴의 시작 주소와 끝 주소를 p_pos와 p_limit 변수에 저장한다.
	unsigned char* p_pos = p_image;
	unsigned char* p_limit = p_image + bmp_info.bmHeight * bmp_info.bmWidthBytes;

	// 정확도 값을 얻는다.
	int r, g, b, depth = GetDlgItemInt(IDC_DEPTH_EDIT);

	// 이미지 값의 나열 순서    B(+0), G(+1), R(+2), A(+3)
	while (p_pos < p_limit) {
		b = *p_pos + depth;  // blue 값에 depth을 더한 값을 얻는다.
		g = *(p_pos + 1);  // green 값을 얻는다.
		r = *(p_pos + 2) + depth;  // red 값에 depth을 더한 값을 얻는다.

		// green의 값이 가중치를 더한 blue 또는 red 보다 작다면
		// 검은색으로 변경
		if (g < b || g < r) { *(UINT32*)p_pos = 0; }
		p_pos += 4;						// 다음 색상으로 이동
	}

	// WM_PAINT
	Invalidate(0);
}

void CBackgroundTransparent1Dlg::ModifyRed()
{
	// CImage 에 저장된 정보를 얻는다
	BITMAP bmp_info;
	GetObject((HBITMAP)m_edit_image, sizeof(BITMAP), &bmp_info);

	// CImage의 비트 패턴이 저장된 주소를 얻는다
	// 마지막 줄을 제외한 나머지 길이만큼 빼서 이미지 패턴이 시작하는 위치로 포인터를 옮긴다
	unsigned char* p_image = (unsigned char*)m_edit_image.GetBits();
	p_image -= (bmp_info.bmHeight - 1) * bmp_info.bmWidthBytes;

	// 이미지 패턴의 시작 주소와 끝 주소를 p_pos와 p_limit 변수에 저장한다.
	unsigned char* p_pos = p_image;
	unsigned char* p_limit = p_image + bmp_info.bmHeight * bmp_info.bmWidthBytes;

	// 정확도 값을 얻는다.
	int r, g, b, depth = GetDlgItemInt(IDC_DEPTH_EDIT);

	// 이미지 값의 나열 B(+0), G(+1), R(+2), A(+3) 순서
	while (p_pos < p_limit) {
		b = *p_pos + depth;  // blue 값에 depth을 더한 값을 얻는다.
		g = *(p_pos + 1) + depth;  // green 값에 depth을 더한 값을 얻는다.
		r = *(p_pos + 2);  // red 값을 얻는다.

		// red의 값이 blue(+가중치) 또는 green(+가중치) 보다 작다면
		// 검은색으로 변경한다.
		if (r < b || r < g) { *(UINT32*)p_pos = 0; }
		p_pos += 4;					// 다음 색상으로 이동
	}

	// WM_PAINT
	Invalidate(0);
}
