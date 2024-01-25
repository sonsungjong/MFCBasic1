#include "pch.h"
#include "MainController.h"

MainController::MainController(CWinApp* app)
{
	m_pApp = app;
	m_pMainModel = new MainModel;
	m_pMainDlg = new MainView;
	m_dlgResponse = m_pMainDlg->DoModal();
}

MainController::~MainController()
{
	delete m_pMainDlg;
	delete m_pMainModel;
}
