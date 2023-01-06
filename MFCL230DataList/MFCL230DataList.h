
// MFCL230DataList.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCL230DataListApp:
// See MFCL230DataList.cpp for the implementation of this class
//

class CMFCL230DataListApp : public CWinApp
{
public:
	CMFCL230DataListApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCL230DataListApp theApp;
