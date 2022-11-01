
// MFCL221LineGraph.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCL221LineGraphApp:
// See MFCL221LineGraph.cpp for the implementation of this class
//

class CMFCL221LineGraphApp : public CWinApp
{
public:
	CMFCL221LineGraphApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCL221LineGraphApp theApp;
