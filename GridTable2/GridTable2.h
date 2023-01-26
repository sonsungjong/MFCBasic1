
// GridTable2.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CGridTable2App:
// See GridTable2.cpp for the implementation of this class
//

class CGridTable2App : public CWinApp
{
public:
	CGridTable2App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CGridTable2App theApp;
