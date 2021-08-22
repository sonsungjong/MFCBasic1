
// MFCReal001.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCReal001App:
// See MFCReal001.cpp for the implementation of this class
//

class CMFCReal001App : public CWinApp
{
public:
	CMFCReal001App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCReal001App theApp;
