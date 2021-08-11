
// MFCBasic106ListBox.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "MFCBasic106ListBox.h"
#include "MFCBasic106ListBoxDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBasic106ListBoxApp

BEGIN_MESSAGE_MAP(CMFCBasic106ListBoxApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMFCBasic106ListBoxApp construction

CMFCBasic106ListBoxApp::CMFCBasic106ListBoxApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CMFCBasic106ListBoxApp object

CMFCBasic106ListBoxApp theApp;


// CMFCBasic106ListBoxApp initialization
BOOL CMFCBasic106ListBoxApp::InitInstance()
{

	CWinApp::InitInstance();

	CMFCBasic106ListBoxDlg dlg;

	m_pMainWnd = &dlg;
	dlg.DoModal();
	
	return FALSE;
}

