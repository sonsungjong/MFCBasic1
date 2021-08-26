
// MFCBasic114CPtrArray.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCBasic114CPtrArrayApp:
// See MFCBasic114CPtrArray.cpp for the implementation of this class
//

class CMFCBasic114CPtrArrayApp : public CWinApp
{
public:
	CMFCBasic114CPtrArrayApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCBasic114CPtrArrayApp theApp;
