
// MFCBasic224SDI2.h : main header file for the MFCBasic224SDI2 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMFCBasic224SDI2App:
// See MFCBasic224SDI2.cpp for the implementation of this class
//

class CMFCBasic224SDI2App : public CWinApp
{
public:
	CMFCBasic224SDI2App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCBasic224SDI2App theApp;
