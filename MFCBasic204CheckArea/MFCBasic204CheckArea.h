
// MFCBasic204CheckArea.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCBasic204CheckAreaApp:
// See MFCBasic204CheckArea.cpp for the implementation of this class
//

class CMFCBasic204CheckAreaApp : public CWinApp
{
public:
	CMFCBasic204CheckAreaApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCBasic204CheckAreaApp theApp;
