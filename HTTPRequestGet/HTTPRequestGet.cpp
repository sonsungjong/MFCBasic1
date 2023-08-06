
// HTTPRequestGet.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "HTTPRequestGet.h"
#include "HTTPRequestGetDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHTTPRequestGetApp

BEGIN_MESSAGE_MAP(CHTTPRequestGetApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CHTTPRequestGetApp construction

CHTTPRequestGetApp::CHTTPRequestGetApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CHTTPRequestGetApp object

CHTTPRequestGetApp theApp;


// CHTTPRequestGetApp initialization

BOOL CHTTPRequestGetApp::InitInstance()
{
	CWinApp::InitInstance();

	CHTTPRequestGetDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	return FALSE;
}

