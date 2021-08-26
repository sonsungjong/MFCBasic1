
// MFCBasic112Slider.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCBasic112SliderApp:
// See MFCBasic112Slider.cpp for the implementation of this class
//

class CMFCBasic112SliderApp : public CWinApp
{
public:
	CMFCBasic112SliderApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCBasic112SliderApp theApp;
