
// MVCMFC.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "MVCMFC.h"
#include "MainView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMVCMFCApp

BEGIN_MESSAGE_MAP(CMVCMFCApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMVCMFCApp construction


CMVCMFCApp::CMVCMFCApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CMVCMFCApp object

CMVCMFCApp theApp;


// CMVCMFCApp initialization
int CMVCMFCApp::flag = 0;						// static은 이렇게 값을 초기화

BOOL CMVCMFCApp::InitInstance()
{
	CWinApp::InitInstance();

	// View와 연결되지 않는 Model 먼저 생성 (컨트롤러에서 DoModal 하기 전에 해도 됨)
	// 싱글턴 클래스 생성하고
	// DB 또는 네트워크 수신 등... 
	// 네트워크 수신에 대해 관찰자 패턴 등 값이 바뀌었을 때 컨트롤러가 알게하는 것을 구현해야함

	// 컨트롤러 생성
	m_pLoginController = new LoginController(this);
	MessageBox(NULL, L"로그인창 닫힘", L"app", MB_OK);
	if (num == 1 && flag == 1) {
		m_pMainController = new MainController(this);
		delete m_pLoginController;
		m_pLoginController = nullptr;
	}


	//LoginView* pLoginDlg = NULL;
	//pLoginDlg = new LoginView;
	//pLoginDlg->Create(IDD_LOGIN_DLG, nullptr);
	//pLoginDlg->ShowWindow(SW_SHOW);
	//INT_PTR loginRes = pLoginDlg->DoModal();

	//if (loginRes == IDOK)
	//{
	//	MainView* pMainDlg = NULL;
	//	pMainDlg = new MainView;
	//	delete pLoginDlg;
	//	pLoginDlg = NULL;

	//	INT_PTR mainRes = pMainDlg->DoModal();
	//	if (mainRes == IDOK)
	//	{
	//		pLoginDlg = new LoginView;
	//		delete pMainDlg;
	//		pMainDlg = NULL;

	//		loginRes = pLoginDlg->DoModal();
	//	}
	//}
	//else if (loginRes == IDCANCEL)
	//{
	//	
	//}

	return FALSE;
}

