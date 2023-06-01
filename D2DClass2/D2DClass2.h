
// D2DClass2.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CD2DClass2App:
// See D2DClass2.cpp for the implementation of this class
//

class CD2DClass2App : public CWinApp
{
public:
	CD2DClass2App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CD2DClass2App theApp;
