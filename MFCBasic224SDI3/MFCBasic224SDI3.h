
// MFCBasic224SDI3.h : main header file for the MFCBasic224SDI3 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMFCBasic224SDI3App:
// See MFCBasic224SDI3.cpp for the implementation of this class
//

class CMFCBasic224SDI3App : public CWinAppEx
{
public:
	CMFCBasic224SDI3App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCBasic224SDI3App theApp;
