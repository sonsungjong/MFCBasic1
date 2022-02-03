
// MFCL112PriceCalculation.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "MFCL112PriceCalculation.h"
#include "MFCL112PriceCalculationDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCL112PriceCalculationApp

BEGIN_MESSAGE_MAP(CMFCL112PriceCalculationApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMFCL112PriceCalculationApp construction

CMFCL112PriceCalculationApp::CMFCL112PriceCalculationApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CMFCL112PriceCalculationApp object

CMFCL112PriceCalculationApp theApp;


// CMFCL112PriceCalculationApp initialization

BOOL CMFCL112PriceCalculationApp::InitInstance()
{
	CWinApp::InitInstance();

	CMFCL112PriceCalculationDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	return FALSE;
}

