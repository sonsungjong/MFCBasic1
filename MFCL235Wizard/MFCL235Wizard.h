
// MFCL235Wizard.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCL235WizardApp:
// See MFCL235Wizard.cpp for the implementation of this class
//

class CMFCL235WizardApp : public CWinApp
{
public:
	CMFCL235WizardApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCL235WizardApp theApp;
