
// MFCBasic116Modaless.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCBasic116ModalessApp:
// See MFCBasic116Modaless.cpp for the implementation of this class
//

class CMFCBasic116ModalessApp : public CWinApp
{
public:
	CMFCBasic116ModalessApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCBasic116ModalessApp theApp;
