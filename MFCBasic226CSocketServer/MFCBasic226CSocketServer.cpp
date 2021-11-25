
// MFCBasic226CSocketServer.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "MFCBasic226CSocketServer.h"
#include "MFCBasic226CSocketServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBasic226CSocketServerApp

BEGIN_MESSAGE_MAP(CMFCBasic226CSocketServerApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMFCBasic226CSocketServerApp construction

CMFCBasic226CSocketServerApp::CMFCBasic226CSocketServerApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CMFCBasic226CSocketServerApp object

CMFCBasic226CSocketServerApp theApp;


// CMFCBasic226CSocketServerApp initialization

BOOL CMFCBasic226CSocketServerApp::InitInstance()
{
	CWinApp::InitInstance();

	// 소켓기능 함수
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}
	
	CMFCBasic226CSocketServerDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	
	return FALSE;
}

