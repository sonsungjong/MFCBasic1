
// MFCRepeat110.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCRepeat110App:
// See MFCRepeat110.cpp for the implementation of this class
//

class CMFCRepeat110App : public CWinApp
{
public:
	CMFCRepeat110App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCRepeat110App theApp;
