
// MFCBasic226CSocketClient.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "MFCBasic226CSocketClient.h"
#include "MFCBasic226CSocketClientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBasic226CSocketClientApp

BEGIN_MESSAGE_MAP(CMFCBasic226CSocketClientApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMFCBasic226CSocketClientApp construction

CMFCBasic226CSocketClientApp::CMFCBasic226CSocketClientApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CMFCBasic226CSocketClientApp object

CMFCBasic226CSocketClientApp theApp;


// CMFCBasic226CSocketClientApp initialization

BOOL CMFCBasic226CSocketClientApp::InitInstance()
{
	CWinApp::InitInstance();

	// 윈도우 소켓 기능 활성화
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}


	CMFCBasic226CSocketClientDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	
	return FALSE;
}

