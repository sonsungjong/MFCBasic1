
// CMFCListControl1.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "CMFCListControl1.h"
#include "CMFCListControl1Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCMFCListControl1App

BEGIN_MESSAGE_MAP(CCMFCListControl1App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CCMFCListControl1App construction

CCMFCListControl1App::CCMFCListControl1App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CCMFCListControl1App object

CCMFCListControl1App theApp;


// CCMFCListControl1App initialization

BOOL CCMFCListControl1App::InitInstance()
{

	CWinApp::InitInstance();

	// 스타일 변경
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));

	CCMFCListControl1Dlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	return FALSE;
}

