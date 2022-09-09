
// MFCL206EditCtrl2.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCL206EditCtrl2App:
// See MFCL206EditCtrl2.cpp for the implementation of this class
//

class CMFCL206EditCtrl2App : public CWinApp
{
public:
	CMFCL206EditCtrl2App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCL206EditCtrl2App theApp;
