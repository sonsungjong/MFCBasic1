
// MFCL117PaintBrush.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCL117PaintBrushApp:
// See MFCL117PaintBrush.cpp for the implementation of this class
//

class CMFCL117PaintBrushApp : public CWinApp
{
public:
	CMFCL117PaintBrushApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCL117PaintBrushApp theApp;
