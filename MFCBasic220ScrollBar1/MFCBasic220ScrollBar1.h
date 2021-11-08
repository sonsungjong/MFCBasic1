
// MFCBasic220ScrollBar1.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCBasic220ScrollBar1App:
// See MFCBasic220ScrollBar1.cpp for the implementation of this class
//

class CMFCBasic220ScrollBar1App : public CWinApp
{
public:
	CMFCBasic220ScrollBar1App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCBasic220ScrollBar1App theApp;
