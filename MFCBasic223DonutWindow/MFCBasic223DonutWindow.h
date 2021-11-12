
// MFCBasic223DonutWindow.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCBasic223DonutWindowApp:
// See MFCBasic223DonutWindow.cpp for the implementation of this class
//

class CMFCBasic223DonutWindowApp : public CWinApp
{
public:
	CMFCBasic223DonutWindowApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCBasic223DonutWindowApp theApp;
