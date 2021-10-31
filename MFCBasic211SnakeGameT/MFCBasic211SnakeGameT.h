
// MFCBasic211SnakeGameT.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCBasic211SnakeGameTApp:
// See MFCBasic211SnakeGameT.cpp for the implementation of this class
//

class CMFCBasic211SnakeGameTApp : public CWinApp
{
public:
	CMFCBasic211SnakeGameTApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCBasic211SnakeGameTApp theApp;
