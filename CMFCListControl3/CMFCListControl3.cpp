
// CMFCListControl3.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "CMFCListControl3.h"
#include "CMFCListControl3Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCMFCListControl3App

BEGIN_MESSAGE_MAP(CCMFCListControl3App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CCMFCListControl3App construction

CCMFCListControl3App::CCMFCListControl3App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CCMFCListControl3App object

CCMFCListControl3App theApp;


// CCMFCListControl3App initialization

BOOL CCMFCListControl3App::InitInstance()
{
	CWinApp::InitInstance();

	CCMFCListControl3Dlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	
	return FALSE;
}

