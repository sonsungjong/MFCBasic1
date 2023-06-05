
// WOL_WakeOnLan.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CWOLWakeOnLanApp:
// See WOL_WakeOnLan.cpp for the implementation of this class
//

class CWOLWakeOnLanApp : public CWinApp
{
public:
	CWOLWakeOnLanApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CWOLWakeOnLanApp theApp;
