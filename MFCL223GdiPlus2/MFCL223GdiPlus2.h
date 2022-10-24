
// MFCL223GdiPlus2.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCL223GdiPlus2App:
// See MFCL223GdiPlus2.cpp for the implementation of this class
//

class CMFCL223GdiPlus2App : public CWinApp
{
public:
	CMFCL223GdiPlus2App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCL223GdiPlus2App theApp;
