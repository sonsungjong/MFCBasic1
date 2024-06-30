
// MFCS002CTaskDialog2AddBtn.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCS002CTaskDialog2AddBtnApp:
// See MFCS002CTaskDialog2AddBtn.cpp for the implementation of this class
//

class CMFCS002CTaskDialog2AddBtnApp : public CWinApp
{
public:
	CMFCS002CTaskDialog2AddBtnApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCS002CTaskDialog2AddBtnApp theApp;
