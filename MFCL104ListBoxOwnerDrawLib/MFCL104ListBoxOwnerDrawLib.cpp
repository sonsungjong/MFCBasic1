
// MFCL104ListBoxOwnerDrawLib.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "MFCL104ListBoxOwnerDrawLib.h"
#include "MFCL104ListBoxOwnerDrawLibDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCL104ListBoxOwnerDrawLibApp

BEGIN_MESSAGE_MAP(CMFCL104ListBoxOwnerDrawLibApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMFCL104ListBoxOwnerDrawLibApp construction

CMFCL104ListBoxOwnerDrawLibApp::CMFCL104ListBoxOwnerDrawLibApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CMFCL104ListBoxOwnerDrawLibApp object

CMFCL104ListBoxOwnerDrawLibApp theApp;


// CMFCL104ListBoxOwnerDrawLibApp initialization

BOOL CMFCL104ListBoxOwnerDrawLibApp::InitInstance()
{
	CWinApp::InitInstance();

	CMFCL104ListBoxOwnerDrawLibDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	
	return FALSE;
}

