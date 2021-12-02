
// MFCBasic227CSocketServer.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "MFCBasic227CSocketServer.h"
#include "MFCBasic227CSocketServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBasic227CSocketServerApp

BEGIN_MESSAGE_MAP(CMFCBasic227CSocketServerApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMFCBasic227CSocketServerApp construction

CMFCBasic227CSocketServerApp::CMFCBasic227CSocketServerApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CMFCBasic227CSocketServerApp object

CMFCBasic227CSocketServerApp theApp;


// CMFCBasic227CSocketServerApp initialization

BOOL CMFCBasic227CSocketServerApp::InitInstance()
{
	CWinApp::InitInstance();

	// CSocket È°¼ºÈ­
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	CMFCBasic227CSocketServerDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	
	return FALSE;
}

