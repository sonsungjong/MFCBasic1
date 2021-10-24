
// MFCBasic210SnakeGame.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCBasic210SnakeGameApp:
// See MFCBasic210SnakeGame.cpp for the implementation of this class
//

class CMFCBasic210SnakeGameApp : public CWinApp
{
public:
	CMFCBasic210SnakeGameApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCBasic210SnakeGameApp theApp;
