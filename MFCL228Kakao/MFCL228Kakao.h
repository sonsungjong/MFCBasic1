
// MFCL228Kakao.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCL228KakaoApp:
// See MFCL228Kakao.cpp for the implementation of this class
//

class CMFCL228KakaoApp : public CWinApp
{
public:
	CMFCL228KakaoApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCL228KakaoApp theApp;
