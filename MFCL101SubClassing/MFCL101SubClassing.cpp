
// MFCL101SubClassing.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "MFCL101SubClassing.h"
#include "MFCL101SubClassingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCL101SubClassingApp

BEGIN_MESSAGE_MAP(CMFCL101SubClassingApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMFCL101SubClassingApp construction

CMFCL101SubClassingApp::CMFCL101SubClassingApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CMFCL101SubClassingApp object

CMFCL101SubClassingApp theApp;


// CMFCL101SubClassingApp initialization

BOOL CMFCL101SubClassingApp::InitInstance()
{
	CWinApp::InitInstance();									//1
	
	CMFCL101SubClassingDlg dlg;								//2
	m_pMainWnd = &dlg;											//3
	dlg.DoModal();													//4
	
	return FALSE;														//5
}

