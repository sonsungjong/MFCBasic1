
// PalaDog3.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "PalaDog3.h"
#include "PalaDog3Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPalaDog3App

BEGIN_MESSAGE_MAP(CPalaDog3App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CPalaDog3App construction

CPalaDog3App::CPalaDog3App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CPalaDog3App object

CPalaDog3App theApp;


// CPalaDog3App initialization

BOOL CPalaDog3App::InitInstance()
{
	CWinApp::InitInstance();

	CPalaDog3Dlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	
	return FALSE;
}

