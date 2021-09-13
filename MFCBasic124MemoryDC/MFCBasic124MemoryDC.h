
// MFCBasic124MemoryDC.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCBasic124MemoryDCApp:
// See MFCBasic124MemoryDC.cpp for the implementation of this class
//

class CMFCBasic124MemoryDCApp : public CWinApp
{
public:
	CMFCBasic124MemoryDCApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCBasic124MemoryDCApp theApp;
