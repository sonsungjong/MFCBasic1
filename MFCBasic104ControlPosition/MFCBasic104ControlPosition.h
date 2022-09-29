
// MFCBasic104ControlPosition.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCBasic104ControlPositionApp:
// See MFCBasic104ControlPosition.cpp for the implementation of this class
//

class CMFCBasic104ControlPositionApp : public CWinApp
{
public:
	CMFCBasic104ControlPositionApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCBasic104ControlPositionApp theApp;
