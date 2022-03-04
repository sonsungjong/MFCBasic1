
// MFCL116Pen.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCL116PenApp:
// See MFCL116Pen.cpp for the implementation of this class
//

class CMFCL116PenApp : public CWinApp
{
public:
	CMFCL116PenApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCL116PenApp theApp;
