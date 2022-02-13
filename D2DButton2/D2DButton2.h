
// D2DButton2.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CD2DButton2App:
// See D2DButton2.cpp for the implementation of this class
//

class CD2DButton2App : public CWinApp
{
public:
	CD2DButton2App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CD2DButton2App theApp;
