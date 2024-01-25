
// MVCMFC.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include "LoginController.h"
#include "MainController.h"

// CMVCMFCApp:
// See MVCMFC.cpp for the implementation of this class
//

class CMVCMFCApp : public CWinApp
{
public:
	CMVCMFCApp();
	int num = 0;
	static int flag;

// Overrides
public:
	virtual BOOL InitInstance();
	LoginController* m_pLoginController;
	MainController* m_pMainController;

// Implementation

	DECLARE_MESSAGE_MAP()

	
};

extern CMVCMFCApp theApp;
