
// CMFCListControl1.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CCMFCListControl1App:
// See CMFCListControl1.cpp for the implementation of this class
//

class CCMFCListControl1App : public CWinApp
{
public:
	CCMFCListControl1App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CCMFCListControl1App theApp;
