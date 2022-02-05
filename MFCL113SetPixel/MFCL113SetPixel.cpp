
// MFCL113SetPixel.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "MFCL113SetPixel.h"
#include "MFCL113SetPixelDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCL113SetPixelApp

BEGIN_MESSAGE_MAP(CMFCL113SetPixelApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMFCL113SetPixelApp construction

CMFCL113SetPixelApp::CMFCL113SetPixelApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CMFCL113SetPixelApp object

CMFCL113SetPixelApp theApp;


// CMFCL113SetPixelApp initialization

BOOL CMFCL113SetPixelApp::InitInstance()
{
	CWinApp::InitInstance();

	CMFCL113SetPixelDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	
	return FALSE;
}

