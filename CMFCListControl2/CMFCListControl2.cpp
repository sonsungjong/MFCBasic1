
// CMFCListControl2.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "CMFCListControl2.h"
#include "CMFCListControl2Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCMFCListControl2App

BEGIN_MESSAGE_MAP(CCMFCListControl2App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CCMFCListControl2App construction

CCMFCListControl2App::CCMFCListControl2App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CCMFCListControl2App object

CCMFCListControl2App theApp;


// CCMFCListControl2App initialization

BOOL CCMFCListControl2App::InitInstance()
{
	CWinApp::InitInstance();

	CCMFCListControl2Dlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	return FALSE;
}

