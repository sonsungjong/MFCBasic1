#include "pch.h"
#include "framework.h"
#include "BinaryWork.h"
#include "BinaryWorkDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBinaryWorkApp

BEGIN_MESSAGE_MAP(CBinaryWorkApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CBinaryWorkApp construction

CBinaryWorkApp::CBinaryWorkApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CBinaryWorkApp object

CBinaryWorkApp theApp;


// CBinaryWorkApp initialization

BOOL CBinaryWorkApp::InitInstance()
{
	CWinApp::InitInstance();

	CBinaryWorkDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	
	return FALSE;
}

