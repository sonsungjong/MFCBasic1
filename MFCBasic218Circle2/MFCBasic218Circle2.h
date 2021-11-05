
// MFCBasic218Circle2.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCBasic218Circle2App:
// See MFCBasic218Circle2.cpp for the implementation of this class
//

class CMFCBasic218Circle2App : public CWinApp
{
public:
	CMFCBasic218Circle2App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCBasic218Circle2App theApp;
