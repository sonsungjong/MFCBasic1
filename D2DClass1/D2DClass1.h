
// D2DClass1.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CD2DClass1App:
// See D2DClass1.cpp for the implementation of this class
//

class CD2DClass1App : public CWinApp
{
public:
	CD2DClass1App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CD2DClass1App theApp;
