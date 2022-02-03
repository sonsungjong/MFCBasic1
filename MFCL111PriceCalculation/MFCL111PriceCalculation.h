
// MFCL111PriceCalculation.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCL111PriceCalculationApp:
// See MFCL111PriceCalculation.cpp for the implementation of this class
//

class CMFCL111PriceCalculationApp : public CWinApp
{
public:
	CMFCL111PriceCalculationApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCL111PriceCalculationApp theApp;
