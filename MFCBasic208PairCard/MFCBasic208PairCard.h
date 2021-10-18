
// MFCBasic208PairCard.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCBasic208PairCardApp:
// See MFCBasic208PairCard.cpp for the implementation of this class
//

class CMFCBasic208PairCardApp : public CWinApp
{
public:
	CMFCBasic208PairCardApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCBasic208PairCardApp theApp;
