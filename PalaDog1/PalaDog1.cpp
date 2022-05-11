
// PalaDog1.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "PalaDog1.h"
#include "PalaDog1Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPalaDog1App

BEGIN_MESSAGE_MAP(CPalaDog1App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CPalaDog1App construction

CPalaDog1App::CPalaDog1App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CPalaDog1App object

CPalaDog1App theApp;


// CPalaDog1App initialization

BOOL CPalaDog1App::InitInstance()
{
	CWinApp::InitInstance();

	CPalaDog1Dlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	
	return FALSE;
}

