
// MFCCapture.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCCaptureApp:
// See MFCCapture.cpp for the implementation of this class
//

class CMFCCaptureApp : public CWinApp
{
public:
	CMFCCaptureApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCCaptureApp theApp;
