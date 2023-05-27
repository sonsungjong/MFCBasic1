
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
CEF3 ���̺귯���� ����Ͽ� ũ�� ��ȭ���� MFC ���̾�α׿� ����
1. CMake 3.19 �̻��� ������ ��ġ�Ѵ�
2. Python 2.7.x ������ ��ġ�Ѵ� (���̽� ȯ�� ���� ���������ϰ� �ٸ� ������ �ӽ� ����)
3. git bash�� ��ġ�Ѵ�.
4. git bash�� ������ �������� �����ϰ� python --version �� �Է��Ͽ� 2.7.x ������ �⺻���� �����ִ��� Ȯ���Ѵ�.
5. Visual Studio 2019 �̻�, 64bit ��� ����
6. git clone https://bitbucket.org/chromiumembedded/cef-project.git �ҽ� �ڵ� ����

7. ������ �������� git bash�� �����ϰ� cef-project �ȿ� �� build ������ �����ϰ� ����
cd cef-project
mkdir build
cd build

8. �Ʒ� ��ɾ ���� CMake�� .sln ������ �����Ѵ�.
cmake -G "Visual Studio 17 2022" -A x64 ..
cmake --build . --config Release
cmake --build . --config Debug

9. ����� ������Ʈ�� ���Խ�Ų��
<��� ���>
C:\cef-project\third_party\cef\cef_binary_106.0.26+ge105400+chromium-106.0.5249.91_windows64
<���̺귯�� ���>
C:\cef-project\third_party\cef\cef_binary_106.0.26+ge105400+chromium-106.0.5249.91_windows64\Release
<���� ���̺귯��>
libcef.lib

<���� dll (Environment) >
PAHT=C:\cef-project\third_party\cef\cef_binary_106.0.26+ge105400+chromium-106.0.5249.91_windows64\Release;
%PATH%;

����, 64��Ʈ�� �����ϰ� 32��Ʈ�� �����ϰ��� �ϸ� ���� ���� ���ϰ� CMake ĳ�ø� �����ؾ��Ѵ�.
cd cef-project/build
rm -rf CMakeCache.txt CMakeFiles/
cmake -G "Visual Studio 17 2022" -A Win32 ..

���� �ڼ��� ������ readme.md ������ �д´�
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
