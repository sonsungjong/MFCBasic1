
// MFCBasic216SineCos.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCBasic216SineCosApp:
// See MFCBasic216SineCos.cpp for the implementation of this class
//

class CMFCBasic216SineCosApp : public CWinApp
{
public:
	CMFCBasic216SineCosApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCBasic216SineCosApp theApp;
