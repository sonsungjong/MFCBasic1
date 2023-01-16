
// XRayViewer.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CXRayViewerApp:
// See XRayViewer.cpp for the implementation of this class
//

class CXRayViewerApp : public CWinApp
{
public:
	CXRayViewerApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CXRayViewerApp theApp;
