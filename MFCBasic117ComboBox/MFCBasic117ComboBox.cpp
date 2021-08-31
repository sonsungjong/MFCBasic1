
// MFCBasic117ComboBox.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "MFCBasic117ComboBox.h"
#include "MFCBasic117ComboBoxDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBasic117ComboBoxApp

BEGIN_MESSAGE_MAP(CMFCBasic117ComboBoxApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMFCBasic117ComboBoxApp construction

CMFCBasic117ComboBoxApp::CMFCBasic117ComboBoxApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CMFCBasic117ComboBoxApp object

CMFCBasic117ComboBoxApp theApp;


// CMFCBasic117ComboBoxApp initialization

BOOL CMFCBasic117ComboBoxApp::InitInstance()
{
	CWinApp::InitInstance();

	CMFCBasic117ComboBoxDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	
	return FALSE;
}

