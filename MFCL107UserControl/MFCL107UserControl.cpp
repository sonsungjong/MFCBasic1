
// MFCL107UserControl.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "MFCL107UserControl.h"
#include "MFCL107UserControlDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCL107UserControlApp

BEGIN_MESSAGE_MAP(CMFCL107UserControlApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMFCL107UserControlApp construction

CMFCL107UserControlApp::CMFCL107UserControlApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CMFCL107UserControlApp object

CMFCL107UserControlApp theApp;


// CMFCL107UserControlApp initialization

BOOL CMFCL107UserControlApp::InitInstance()
{
	CWinApp::InitInstance();

	CMFCL107UserControlDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	
	return FALSE;
}

