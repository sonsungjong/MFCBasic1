
// MFCBasic115DoModal.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCBasic115DoModalApp:
// See MFCBasic115DoModal.cpp for the implementation of this class
//

class CMFCBasic115DoModalApp : public CWinApp
{
public:
	CMFCBasic115DoModalApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCBasic115DoModalApp theApp;
