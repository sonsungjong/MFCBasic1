
// D2DUserControl1.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CD2DUserControl1App:
// See D2DUserControl1.cpp for the implementation of this class
//

class CD2DUserControl1App : public CWinApp
{
public:
	CD2DUserControl1App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CD2DUserControl1App theApp;
