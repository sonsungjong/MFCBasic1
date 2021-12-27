
// MFCL105OwnerDrawBtn.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCL105OwnerDrawBtnApp:
// See MFCL105OwnerDrawBtn.cpp for the implementation of this class
//

class CMFCL105OwnerDrawBtnApp : public CWinApp
{
public:
	CMFCL105OwnerDrawBtnApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCL105OwnerDrawBtnApp theApp;
