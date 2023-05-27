
// MFCwithChromeDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCwithChrome.h"
#include "MFCwithChromeDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/*
CEF3 라이브러리를 사용하여 크롬 웹화면을 MFC 다이얼로그에 삽입
1. CMake 3.19 이상의 버전을 설치한다
2. Python 2.7.x 버전을 설치한다 (파이썬 환경 변수 설정까지하고 다른 버전은 임시 제거)
3. git bash를 설치한다.
4. git bash를 관리자 권한으로 실행하고 python --version 을 입력하여 2.7.x 버전이 기본으로 잡혀있는지 확인한다.
5. Visual Studio 2019 이상, 64bit 사용 권장
6. git clone https://bitbucket.org/chromiumembedded/cef-project.git 소스 코드 복제

7. 관리자 권한으로 git bash를 실행하고 cef-project 안에 들어가 build 폴더를 생성하고 들어간다
cd cef-project
mkdir build
cd build

8. 아래 명령어를 통해 CMake로 .sln 파일을 생성한다.
cmake -G "Visual Studio 17 2022" -A x64 ..
cmake --build . --config Release
cmake --build . --config Debug

9. 사용할 프로젝트에 포함시킨다
<헤더 경로>
C:\cef-project\third_party\cef\cef_binary_106.0.26+ge105400+chromium-106.0.5249.91_windows64
<라이브러리 경로>
C:\cef-project\third_party\cef\cef_binary_106.0.26+ge105400+chromium-106.0.5249.91_windows64\Release
<포함 라이브러리>
libcef.lib

<포함 dll (Environment) >
PAHT=C:\cef-project\third_party\cef\cef_binary_106.0.26+ge105400+chromium-106.0.5249.91_windows64\Release;
%PATH%;

만약, 64비트로 빌드하고 32비트도 빌드하고자 하면 이전 빌드 파일과 CMake 캐시를 제거해야한다.
cd cef-project/build
rm -rf CMakeCache.txt CMakeFiles/
cmake -G "Visual Studio 17 2022" -A Win32 ..

좀더 자세한 사항은 readme.md 파일을 읽는다
*/

CMFCwithChromeDlg::CMFCwithChromeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCWITHCHROME_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCwithChromeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCwithChromeDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCwithChromeDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCwithChromeDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CMFCwithChromeDlg message handlers

BOOL CMFCwithChromeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_rect.SetRect(0, 0, 300, 300);
	CefRect cef_rect(m_rect.left, m_rect.top, m_rect.Width(), m_rect.Height());
	
	m_window_info.SetAsChild(GetSafeHwnd(), cef_rect);
	CefBrowserHost::CreateBrowserSync(m_window_info, m_client.get(), _T("https://www.google.com"), m_browser_settings, nullptr, nullptr);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCwithChromeDlg::OnPaint()
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
HCURSOR CMFCwithChromeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCwithChromeDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CMFCwithChromeDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}
