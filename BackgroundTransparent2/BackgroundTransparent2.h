
// BackgroundTransparent2.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CBackgroundTransparent2App:
// See BackgroundTransparent2.cpp for the implementation of this class
//

class CBackgroundTransparent2App : public CWinApp
{
public:
	CBackgroundTransparent2App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CBackgroundTransparent2App theApp;
