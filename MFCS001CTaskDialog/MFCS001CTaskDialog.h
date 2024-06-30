
// MFCS001CTaskDialog.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCS001CTaskDialogApp:
// See MFCS001CTaskDialog.cpp for the implementation of this class
//

class CMFCS001CTaskDialogApp : public CWinApp
{
public:
	CMFCS001CTaskDialogApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCS001CTaskDialogApp theApp;
