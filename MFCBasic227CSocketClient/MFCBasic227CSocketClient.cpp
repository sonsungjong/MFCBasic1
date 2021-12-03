
// MFCBasic227CSocketClient.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "MFCBasic227CSocketClient.h"
#include "MFCBasic227CSocketClientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBasic227CSocketClientApp

BEGIN_MESSAGE_MAP(CMFCBasic227CSocketClientApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMFCBasic227CSocketClientApp construction

CMFCBasic227CSocketClientApp::CMFCBasic227CSocketClientApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CMFCBasic227CSocketClientApp object

CMFCBasic227CSocketClientApp theApp;


// CMFCBasic227CSocketClientApp initialization

BOOL CMFCBasic227CSocketClientApp::InitInstance()
{
	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}


	CMFCBasic227CSocketClientDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	
	return FALSE;
}

