
// MFCL222GdiPlus1.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCL222GdiPlus1App:
// See MFCL222GdiPlus1.cpp for the implementation of this class
//

class CMFCL222GdiPlus1App : public CWinApp
{
public:
	CMFCL222GdiPlus1App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCL222GdiPlus1App theApp;
