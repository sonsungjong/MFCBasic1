
// MFCS004LineGraph.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCS004LineGraphApp:
// See MFCS004LineGraph.cpp for the implementation of this class
//

class CMFCS004LineGraphApp : public CWinApp
{
public:
	CMFCS004LineGraphApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCS004LineGraphApp theApp;
