
// MFCBasic102BasicClass.cpp: 애플리케이션에 대한 클래스 동작을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "MFCBasic102BasicClass.h"
#include "MFCBasic102BasicClassDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBasic102BasicClassApp

BEGIN_MESSAGE_MAP(CMFCBasic102BasicClassApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMFCBasic102BasicClassApp 생성

CMFCBasic102BasicClassApp::CMFCBasic102BasicClassApp()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CMFCBasic102BasicClassApp 개체입니다.

CMFCBasic102BasicClassApp theApp;


BOOL CMFCBasic102BasicClassApp::InitInstance()
{
	CWinApp::InitInstance();
	CMFCBasic102BasicClassDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();

	return FALSE;
}

