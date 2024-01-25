#include "pch.h"
#include "MVCMFC.h"
#include "LoginController.h"

LoginController::LoginController(CWinApp* app)
{
	m_pApp = app;
	m_pLoginModel = new LoginModel;
	m_pLoginDlg = new LoginView;

	// DoModal �ϱ� ���� DB�����̳� ���ѷ��� ������ �̸� �ɾ���� ��

	m_dlgResponse = m_pLoginDlg->DoModal();
	if (m_dlgResponse == IDOK) {
		createMainDlg();
	}
}



LoginController::~LoginController()
{
	delete m_pLoginDlg;
	delete m_pLoginModel;
}

void LoginController::createMainDlg()
{
	((CMVCMFCApp*)m_pApp)->num = 1;
	CMVCMFCApp::flag = 1;
}
