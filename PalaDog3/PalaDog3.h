
// PalaDog3.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CPalaDog3App:
// See PalaDog3.cpp for the implementation of this class
//

class CPalaDog3App : public CWinApp
{
public:
	CPalaDog3App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CPalaDog3App theApp;
