
// MyEditControl1.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "MyEditControl1.h"
#include "MyEditControl1Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyEditControl1App

BEGIN_MESSAGE_MAP(CMyEditControl1App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMyEditControl1App construction

CMyEditControl1App::CMyEditControl1App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CMyEditControl1App object

CMyEditControl1App theApp;


// CMyEditControl1App initialization

BOOL CMyEditControl1App::InitInstance()
{

	CWinApp::InitInstance();


	CMyEditControl1Dlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	return FALSE;
}



BOOL CMyEditControl1App::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if()

	return CWinApp::PreTranslateMessage(pMsg);
}
