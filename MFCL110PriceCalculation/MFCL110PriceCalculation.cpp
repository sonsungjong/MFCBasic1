
// MFCL110PriceCalculation.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "MFCL110PriceCalculation.h"
#include "MFCL110PriceCalculationDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCL110PriceCalculationApp

BEGIN_MESSAGE_MAP(CMFCL110PriceCalculationApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMFCL110PriceCalculationApp construction

CMFCL110PriceCalculationApp::CMFCL110PriceCalculationApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CMFCL110PriceCalculationApp object

CMFCL110PriceCalculationApp theApp;


// CMFCL110PriceCalculationApp initialization

BOOL CMFCL110PriceCalculationApp::InitInstance()
{
	CWinApp::InitInstance();

	CMFCL110PriceCalculationDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	
	return FALSE;
}

