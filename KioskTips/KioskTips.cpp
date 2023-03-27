
// KioskTips.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "KioskTips.h"
#include "KioskTipsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CKioskTipsApp

BEGIN_MESSAGE_MAP(CKioskTipsApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CKioskTipsApp construction

CKioskTipsApp::CKioskTipsApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CKioskTipsApp object

CKioskTipsApp theApp;


// CKioskTipsApp initialization

BOOL CKioskTipsApp::InitInstance()
{
	CWinApp::InitInstance();
	CKioskTipsDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	
	return FALSE;
}

