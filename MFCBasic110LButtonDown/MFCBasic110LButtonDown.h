
// MFCBasic110LButtonDown.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCBasic110LButtonDownApp:
// See MFCBasic110LButtonDown.cpp for the implementation of this class
//

class CMFCBasic110LButtonDownApp : public CWinApp
{
public:
	CMFCBasic110LButtonDownApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCBasic110LButtonDownApp theApp;
