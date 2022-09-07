
// MFCL203Popup.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCL203PopupApp:
// See MFCL203Popup.cpp for the implementation of this class
//

class CMFCL203PopupApp : public CWinApp
{
public:
	CMFCL203PopupApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCL203PopupApp theApp;
