
// MFCReal001.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "MFCReal001.h"
#include "MFCReal001Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCReal001App

BEGIN_MESSAGE_MAP(CMFCReal001App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMFCReal001App construction

CMFCReal001App::CMFCReal001App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CMFCReal001App object
// WinMain 전에 생성자를 통해 작업할 클래스의 객체화
CMFCReal001App theApp;


// CMFCReal001App initialization

BOOL CMFCReal001App::InitInstance()
{

	CWinApp::InitInstance();

	CMFCReal001Dlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	
	return FALSE;
}

