
// Resize_Move_Wnd.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CResizeMoveWndApp:
// See Resize_Move_Wnd.cpp for the implementation of this class
//

class CResizeMoveWndApp : public CWinApp
{
public:
	CResizeMoveWndApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CResizeMoveWndApp theApp;
