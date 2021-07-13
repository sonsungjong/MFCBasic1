
// MFCBasic116Dialog2.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCBasic116Dialog2App:
// See MFCBasic116Dialog2.cpp for the implementation of this class
//

class CMFCBasic116Dialog2App : public CWinApp
{
public:
	CMFCBasic116Dialog2App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCBasic116Dialog2App theApp;
