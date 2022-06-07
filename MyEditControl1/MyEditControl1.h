
// MyEditControl1.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMyEditControl1App:
// See MyEditControl1.cpp for the implementation of this class
//

class CMyEditControl1App : public CWinApp
{
public:
	CMyEditControl1App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

extern CMyEditControl1App theApp;
