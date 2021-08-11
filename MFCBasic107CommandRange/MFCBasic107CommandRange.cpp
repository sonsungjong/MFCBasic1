
// MFCBasic107CommandRange.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "MFCBasic107CommandRange.h"
#include "MFCBasic107CommandRangeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBasic107CommandRangeApp

BEGIN_MESSAGE_MAP(CMFCBasic107CommandRangeApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMFCBasic107CommandRangeApp construction

CMFCBasic107CommandRangeApp::CMFCBasic107CommandRangeApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CMFCBasic107CommandRangeApp object

CMFCBasic107CommandRangeApp theApp;


// CMFCBasic107CommandRangeApp initialization

BOOL CMFCBasic107CommandRangeApp::InitInstance()
{
	CWinApp::InitInstance();

	CMFCBasic107CommandRangeDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	
	return FALSE;
}

