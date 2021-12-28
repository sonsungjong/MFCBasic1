
// DirectX02.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CDirectX02App:
// See DirectX02.cpp for the implementation of this class
//

class CDirectX02App : public CWinApp
{
public:
	CDirectX02App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CDirectX02App theApp;
