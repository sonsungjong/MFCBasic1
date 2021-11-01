
// MFCBasic212FileListView.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCBasic212FileListViewApp:
// See MFCBasic212FileListView.cpp for the implementation of this class
//

class CMFCBasic212FileListViewApp : public CWinApp
{
public:
	CMFCBasic212FileListViewApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCBasic212FileListViewApp theApp;
