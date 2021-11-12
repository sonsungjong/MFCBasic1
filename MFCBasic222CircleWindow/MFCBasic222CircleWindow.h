
// MFCBasic222CircleWindow.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCBasic222CircleWindowApp:
// See MFCBasic222CircleWindow.cpp for the implementation of this class
//

class CMFCBasic222CircleWindowApp : public CWinApp
{
public:
	CMFCBasic222CircleWindowApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCBasic222CircleWindowApp theApp;
