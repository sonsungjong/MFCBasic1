
// MFCBasic116Login.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCBasic116LoginApp:
// See MFCBasic116Login.cpp for the implementation of this class
//

class CMFCBasic116LoginApp : public CWinApp
{
public:
	CMFCBasic116LoginApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCBasic116LoginApp theApp;
