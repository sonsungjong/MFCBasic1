
// MFCL106ListBoxOwnerDraw2.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCL106ListBoxOwnerDraw2App:
// See MFCL106ListBoxOwnerDraw2.cpp for the implementation of this class
//

class CMFCL106ListBoxOwnerDraw2App : public CWinApp
{
public:
	CMFCL106ListBoxOwnerDraw2App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCL106ListBoxOwnerDraw2App theApp;
