
// SimpleLineGraph1.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CSimpleLineGraph1App:
// See SimpleLineGraph1.cpp for the implementation of this class
//

class CSimpleLineGraph1App : public CWinApp
{
public:
	CSimpleLineGraph1App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CSimpleLineGraph1App theApp;
