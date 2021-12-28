
// DirectX01.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CDirectX01App:
// See DirectX01.cpp for the implementation of this class
//

class CDirectX01App : public CWinApp
{
public:
	CDirectX01App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CDirectX01App theApp;
