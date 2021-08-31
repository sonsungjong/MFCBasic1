
// MFCBasic1.cpp: 애플리케이션에 대한 클래스 동작을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "MFCBasic1.h"
#include "MFCBasic1Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBasic1App

BEGIN_MESSAGE_MAP(CMFCBasic1App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMFCBasic1App 생성

CMFCBasic1App::CMFCBasic1App()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CMFCBasic1App 개체입니다.

CMFCBasic1App theApp;


// CMFCBasic1App 초기화

BOOL CMFCBasic1App::InitInstance()
{


	CWinApp::InitInstance();

	CMFCBasic1Dlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	
	return FALSE;
}

