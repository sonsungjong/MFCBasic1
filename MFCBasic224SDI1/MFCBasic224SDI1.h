
// MFCBasic224SDI1.h : main header file for the MFCBasic224SDI1 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMFCBasic224SDI1App:
// See MFCBasic224SDI1.cpp for the implementation of this class
//

class CMFCBasic224SDI1App : public CWinAppEx
{
public:
	CMFCBasic224SDI1App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCBasic224SDI1App theApp;
