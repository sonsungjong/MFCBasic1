
// MFC_MoveWnd.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCMoveWndApp:
// See MFC_MoveWnd.cpp for the implementation of this class
//

class CMFCMoveWndApp : public CWinApp
{
public:
	CMFCMoveWndApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCMoveWndApp theApp;
