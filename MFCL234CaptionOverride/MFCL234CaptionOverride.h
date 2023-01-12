
// MFCL234CaptionOverride.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCL234CaptionOverrideApp:
// See MFCL234CaptionOverride.cpp for the implementation of this class
//

class CMFCL234CaptionOverrideApp : public CWinApp
{
public:
	CMFCL234CaptionOverrideApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCL234CaptionOverrideApp theApp;
