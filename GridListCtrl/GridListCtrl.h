
// GridListCtrl.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CGridListCtrlApp:
// See GridListCtrl.cpp for the implementation of this class
//

class CGridListCtrlApp : public CWinApp
{
public:
	CGridListCtrlApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CGridListCtrlApp theApp;
