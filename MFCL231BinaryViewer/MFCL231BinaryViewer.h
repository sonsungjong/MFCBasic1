
// MFCL231BinaryViewer.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCL231BinaryViewerApp:
// See MFCL231BinaryViewer.cpp for the implementation of this class
//

class CMFCL231BinaryViewerApp : public CWinApp
{
public:
	CMFCL231BinaryViewerApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCL231BinaryViewerApp theApp;
