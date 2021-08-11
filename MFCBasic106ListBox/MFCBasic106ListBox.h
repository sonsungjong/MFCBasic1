
// MFCBasic106ListBox.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCBasic106ListBoxApp:
// See MFCBasic106ListBox.cpp for the implementation of this class
//

class CMFCBasic106ListBoxApp : public CWinApp
{
public:
	CMFCBasic106ListBoxApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCBasic106ListBoxApp theApp;
