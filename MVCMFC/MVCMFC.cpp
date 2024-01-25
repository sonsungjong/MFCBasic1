
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
int CMVCMFCApp::flag = 0;						// static�� �̷��� ���� �ʱ�ȭ

BOOL CMVCMFCApp::InitInstance()
{
	CWinApp::InitInstance();

	// View�� ������� �ʴ� Model ���� ���� (��Ʈ�ѷ����� DoModal �ϱ� ���� �ص� ��)
	// �̱��� Ŭ���� �����ϰ�
	// DB �Ǵ� ��Ʈ��ũ ���� ��... 
	// ��Ʈ��ũ ���ſ� ���� ������ ���� �� ���� �ٲ���� �� ��Ʈ�ѷ��� �˰��ϴ� ���� �����ؾ���

	// ��Ʈ�ѷ� ����
	m_pLoginController = new LoginController(this);
	MessageBox(NULL, L"�α���â ����", L"app", MB_OK);
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

