
// MFCL113SetPixel.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCL113SetPixelApp:
// See MFCL113SetPixel.cpp for the implementation of this class
//

class CMFCL113SetPixelApp : public CWinApp
{
public:
	CMFCL113SetPixelApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCL113SetPixelApp theApp;
