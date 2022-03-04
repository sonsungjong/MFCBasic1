
// MFCL116Pen.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "MFCL116Pen.h"
#include "MFCL116PenDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCL116PenApp

BEGIN_MESSAGE_MAP(CMFCL116PenApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMFCL116PenApp construction

CMFCL116PenApp::CMFCL116PenApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CMFCL116PenApp object

CMFCL116PenApp theApp;


// CMFCL116PenApp initialization

BOOL CMFCL116PenApp::InitInstance()
{
	CWinApp::InitInstance();

	CMFCL116PenDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	
	return FALSE;
}

