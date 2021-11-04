
// MFCBasic217Circle.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCBasic217CircleApp:
// See MFCBasic217Circle.cpp for the implementation of this class
//

class CMFCBasic217CircleApp : public CWinApp
{
public:
	CMFCBasic217CircleApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCBasic217CircleApp theApp;
