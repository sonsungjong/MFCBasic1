
// MFCL117PaintBrush.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "MFCL117PaintBrush.h"
#include "MFCL117PaintBrushDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCL117PaintBrushApp

BEGIN_MESSAGE_MAP(CMFCL117PaintBrushApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMFCL117PaintBrushApp construction

CMFCL117PaintBrushApp::CMFCL117PaintBrushApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CMFCL117PaintBrushApp object

CMFCL117PaintBrushApp theApp;


// CMFCL117PaintBrushApp initialization

BOOL CMFCL117PaintBrushApp::InitInstance()
{
	
	CWinApp::InitInstance();

	CMFCL117PaintBrushDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	
	return FALSE;
}

