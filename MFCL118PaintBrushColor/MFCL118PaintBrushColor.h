
// MFCL118PaintBrushColor.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCL118PaintBrushColorApp:
// See MFCL118PaintBrushColor.cpp for the implementation of this class
//

class CMFCL118PaintBrushColorApp : public CWinApp
{
public:
	CMFCL118PaintBrushColorApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCL118PaintBrushColorApp theApp;
