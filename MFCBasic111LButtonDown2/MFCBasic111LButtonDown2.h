
// MFCBasic111LButtonDown2.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCBasic111LButtonDown2App:
// See MFCBasic111LButtonDown2.cpp for the implementation of this class
//

class CMFCBasic111LButtonDown2App : public CWinApp
{
public:
	CMFCBasic111LButtonDown2App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCBasic111LButtonDown2App theApp;
