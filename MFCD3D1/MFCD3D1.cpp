#include "pch.h"
#include "framework.h"
#include "MFCD3D1.h"
#include "MFCD3D1Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCD3D1App

BEGIN_MESSAGE_MAP(CMFCD3D1App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMFCD3D1App construction

CMFCD3D1App::CMFCD3D1App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CMFCD3D1App object

CMFCD3D1App theApp;


// CMFCD3D1App initialization

BOOL CMFCD3D1App::InitInstance()
{
	CWinApp::InitInstance();
	CMFCD3D1Dlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	
	return FALSE;
}

