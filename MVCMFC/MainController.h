#pragma once

#include "MainView.h"
#include "MainModel.h"

class MainController
{
public:
	MainController(CWinApp* app);

	~MainController();

	MainView* m_pMainDlg;
	MainModel* m_pMainModel;
	INT_PTR m_dlgResponse;

private:
	CWinApp* m_pApp;
};

