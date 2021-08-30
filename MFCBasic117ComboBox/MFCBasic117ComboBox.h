
// MFCBasic117ComboBox.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCBasic117ComboBoxApp:
// See MFCBasic117ComboBox.cpp for the implementation of this class
//

class CMFCBasic117ComboBoxApp : public CWinApp
{
public:
	CMFCBasic117ComboBoxApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCBasic117ComboBoxApp theApp;
