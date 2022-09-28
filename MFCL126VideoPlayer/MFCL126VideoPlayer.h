
// MFCL126VideoPlayer.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCL126VideoPlayerApp:
// See MFCL126VideoPlayer.cpp for the implementation of this class
//

class CMFCL126VideoPlayerApp : public CWinApp
{
public:
	CMFCL126VideoPlayerApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCL126VideoPlayerApp theApp;
