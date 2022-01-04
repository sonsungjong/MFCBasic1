
// MFCL108ProgressCtrl.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCL108ProgressCtrlApp:
// See MFCL108ProgressCtrl.cpp for the implementation of this class
//

class CMFCL108ProgressCtrlApp : public CWinApp
{
public:
	CMFCL108ProgressCtrlApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCL108ProgressCtrlApp theApp;
