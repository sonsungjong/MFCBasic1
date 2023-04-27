
// MemoryDCInnerWnd.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMemoryDCInnerWndApp:
// See MemoryDCInnerWnd.cpp for the implementation of this class
//

class CMemoryDCInnerWndApp : public CWinApp
{
public:
	CMemoryDCInnerWndApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMemoryDCInnerWndApp theApp;
