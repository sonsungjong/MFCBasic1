#pragma once

#include "LoginView.h"
#include "LoginModel.h"

class LoginController
{
public:
	LoginController(CWinApp* app);
	~LoginController();

	void createMainDlg();

	LoginView* m_pLoginDlg;
	LoginModel* m_pLoginModel;
	INT_PTR m_dlgResponse;

private:
	CWinApp* m_pApp;
};

