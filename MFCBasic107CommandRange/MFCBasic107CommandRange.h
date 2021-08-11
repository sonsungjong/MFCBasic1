
// MFCBasic107CommandRange.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCBasic107CommandRangeApp:
// See MFCBasic107CommandRange.cpp for the implementation of this class
//

class CMFCBasic107CommandRangeApp : public CWinApp
{
public:
	CMFCBasic107CommandRangeApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCBasic107CommandRangeApp theApp;
