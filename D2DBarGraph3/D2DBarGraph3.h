
// D2DBarGraph3.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CD2DBarGraph3App:
// See D2DBarGraph3.cpp for the implementation of this class
//

class CD2DBarGraph3App : public CWinApp
{
public:
	CD2DBarGraph3App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CD2DBarGraph3App theApp;
