
// MFCBasic115Dialog1.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCBasic115Dialog1App:
// See MFCBasic115Dialog1.cpp for the implementation of this class
//

class CMFCBasic115Dialog1App : public CWinApp
{
public:
	CMFCBasic115Dialog1App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCBasic115Dialog1App theApp;
