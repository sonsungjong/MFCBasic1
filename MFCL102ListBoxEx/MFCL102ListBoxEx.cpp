
// MFCL102ListBoxEx.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "MFCL102ListBoxEx.h"
#include "MFCL102ListBoxExDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCL102ListBoxExApp

BEGIN_MESSAGE_MAP(CMFCL102ListBoxExApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMFCL102ListBoxExApp construction

CMFCL102ListBoxExApp::CMFCL102ListBoxExApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CMFCL102ListBoxExApp object

CMFCL102ListBoxExApp theApp;


// CMFCL102ListBoxExApp initialization

BOOL CMFCL102ListBoxExApp::InitInstance()
{
	CWinApp::InitInstance();

	CMFCL102ListBoxExDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	
	return FALSE;
}