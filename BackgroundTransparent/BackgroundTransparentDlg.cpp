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
	// 영역 좌표를 얻는다
	GetDlgItem(IDC_IMAGE_RECT)->GetWindowRect(m_rect);
	ScreenToClient(m_rect);				// 보정

	// 영역과 동일한 크기의 이미지를 생성
	m_draw_image.Create(m_rect.Width(), m_rect.Height(), 32);

	// 그림을 그릴 DC 셋팅
	mh_draw_dc = m_draw_image.GetDC();
	::SelectObject(mh_draw_dc, ::GetStockObject(DC_BRUSH));
	::SelectObject(mh_draw_dc, ::GetStockObject(DC_PEN));

	// 테스트용 하얀색 사각형
	::SetDCBrushColor(mh_draw_dc, RGB(255, 255, 255));
	::SetDCPenColor(mh_draw_dc, RGB(0, 0, 128));
	::Rectangle(mh_draw_dc, 10, 10, 100, 100);

	// 테스트용 주황색 사각형
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
		m_draw_image.Draw(dc, m_rect.left, m_rect.top);			// 그려진 이미지 출력
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
	// Alpha 값을 사용하도록 설정
	m_draw_image.SetHasAlphaChannel(1);

	// 저장된 CImage에 대한 정보를 얻는다
	BITMAP bmp_info;
	GetObject((HBITMAP)m_draw_image, sizeof(BITMAP), &bmp_info);

	// CImage의 비트 패턴이 저장된 주소를 얻는다(이 주소는 마지막 줄의 시작 위치를 가리킴)
	// 이미지 값은 바이트 단위로 B, G, R, A이고 int로 표시하면 0xAARRGGBB
	unsigned char* p_image = (unsigned char*)m_draw_image.GetBits();
	// 주소를 이미지 패턴의 시작위치로 옮기기
	// 마지막 줄을 제외한 나머지 줄의 길이를 뺀다
	p_image -= (bmp_info.bmHeight - 1) * bmp_info.bmWidthBytes;

	// 크기를 구해 이미지 패턴의 시작 주소와 끝 주소를 p_pos 와 p_limit 에 저장한다
	int cx = m_draw_image.GetWidth();
	int cy = m_draw_image.GetHeight();
	unsigned char* p_pos = p_image;
	unsigned char* p_limit = p_image + (cx * cy * 4);

	// Alpha가 적용되면 A가 0인 색상은 출력되지 않아 (기본값으로 0 보유)
	// 하얀색이 아닌 색상들은 Alpha에 255를 대입
	while (p_pos < p_limit)
	{
		// 이미지값 나열 B(+0), G(+1), R(+2), A(+3)
		// 하얀색이 아니면 Alpha값을 255로 설정하여 투명화 되지 않게 처리
		if ((*(UINT32*)p_pos) != 16777215)				// 0xFFFFFF
		{
			*(p_pos + 3) = 0xFF;				// A = 255
		}
		p_pos += 4;				// 다음 색상으로 이동
	}

	// CImage 그림을 .png로 저장
	m_draw_image.Save(_T("myimg.png"), Gdiplus::ImageFormatPNG);

	// Alpha 해제
	m_draw_image.SetHasAlphaChannel(0);

	// 완료 메시지 출력
	MessageBox(_T("투명처리 되었습니다!"), _T("완료"), MB_OK);
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
	// CImage 해제
	m_draw_image.ReleaseDC();
	m_draw_image.Destroy();
}
