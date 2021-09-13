
// MFCBasic123Timer2.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCBasic123Timer2App:
// See MFCBasic123Timer2.cpp for the implementation of this class
//

class CMFCBasic123Timer2App : public CWinApp
{
public:
	CMFCBasic123Timer2App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCBasic123Timer2App theApp;
