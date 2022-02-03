
// MFCL112PriceCalculation.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCL112PriceCalculationApp:
// See MFCL112PriceCalculation.cpp for the implementation of this class
//

class CMFCL112PriceCalculationApp : public CWinApp
{
public:
	CMFCL112PriceCalculationApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCL112PriceCalculationApp theApp;
