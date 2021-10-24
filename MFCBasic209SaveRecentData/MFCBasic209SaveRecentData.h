
// MFCBasic209SaveRecentData.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCBasic209SaveRecentDataApp:
// See MFCBasic209SaveRecentData.cpp for the implementation of this class
//

class CMFCBasic209SaveRecentDataApp : public CWinApp
{
public:
	CMFCBasic209SaveRecentDataApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCBasic209SaveRecentDataApp theApp;
