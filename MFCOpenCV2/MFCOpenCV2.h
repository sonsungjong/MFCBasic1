
// MFCOpenCV2.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCOpenCV2App:
// See MFCOpenCV2.cpp for the implementation of this class
//

class CMFCOpenCV2App : public CWinApp
{
public:
	CMFCOpenCV2App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCOpenCV2App theApp;
