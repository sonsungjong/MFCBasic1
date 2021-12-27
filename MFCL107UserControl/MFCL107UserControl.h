
// MFCL107UserControl.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCL107UserControlApp:
// See MFCL107UserControl.cpp for the implementation of this class
//

class CMFCL107UserControlApp : public CWinApp
{
public:
	CMFCL107UserControlApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCL107UserControlApp theApp;
