
// MFCL202PopupMenu.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCL202PopupMenuApp:
// See MFCL202PopupMenu.cpp for the implementation of this class
//

class CMFCL202PopupMenuApp : public CWinApp
{
public:
	CMFCL202PopupMenuApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCL202PopupMenuApp theApp;
