
// DirectX02.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "DirectX02.h"
#include "DirectX02Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDirectX02App

BEGIN_MESSAGE_MAP(CDirectX02App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CDirectX02App construction

CDirectX02App::CDirectX02App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CDirectX02App object

CDirectX02App theApp;


// CDirectX02App initialization

BOOL CDirectX02App::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	CDirectX02Dlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	return FALSE;
}

