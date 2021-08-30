
// MFCBasic116ModalessInner.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCBasic116ModalessInnerApp:
// See MFCBasic116ModalessInner.cpp for the implementation of this class
//

class CMFCBasic116ModalessInnerApp : public CWinApp
{
public:
	CMFCBasic116ModalessInnerApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCBasic116ModalessInnerApp theApp;
