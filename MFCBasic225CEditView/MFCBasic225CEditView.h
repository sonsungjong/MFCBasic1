
// MFCBasic225CEditView.h : main header file for the MFCBasic225CEditView application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMFCBasic225CEditViewApp:
// See MFCBasic225CEditView.cpp for the implementation of this class
//

class CMFCBasic225CEditViewApp : public CWinAppEx
{
public:
	CMFCBasic225CEditViewApp() noexcept;


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

extern CMFCBasic225CEditViewApp theApp;
