
// MFCL204KeyboardMsg.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCL204KeyboardMsgApp:
// See MFCL204KeyboardMsg.cpp for the implementation of this class
//

class CMFCL204KeyboardMsgApp : public CWinApp
{
public:
	CMFCL204KeyboardMsgApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCL204KeyboardMsgApp theApp;
