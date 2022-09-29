
// MFCL213ImageRate.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCL213ImageRateApp:
// See MFCL213ImageRate.cpp for the implementation of this class
//

class CMFCL213ImageRateApp : public CWinApp
{
public:
	CMFCL213ImageRateApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCL213ImageRateApp theApp;
