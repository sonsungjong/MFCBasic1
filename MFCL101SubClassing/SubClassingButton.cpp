// SubClassingButton.cpp : implementation file
//

#include "pch.h"
#include "MFCL101SubClassing.h"
#include "SubClassingButton.h"


// SubClassingButton
// 버튼을 누르고 있어도 클릭과 동일하게 작동할 수 있도록 기능 추가
IMPLEMENT_DYNAMIC(SubClassingButton, CButton)

SubClassingButton::SubClassingButton()
{

}

SubClassingButton::~SubClassingButton()
{
}


BEGIN_MESSAGE_MAP(SubClassingButton, CButton)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
END_MESSAGE_MAP()



// SubClassingButton message handlers

void SubClassingButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	SetTimer(1, 500, NULL);							// 1번타이머, 눌려있으며 0.5초 지나면 시작 (기능확장)

	CButton::OnLButtonDown(nFlags, point);
}


void SubClassingButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	KillTimer(1);									// 1번타이머 해제
	KillTimer(2);									// 2번타이머 해제

	CButton::OnLButtonUp(nFlags, point);
}


void SubClassingButton::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	switch (nIDEvent)
	{
		case 1:											// 1번타이머
			KillTimer(1);								// 0.5초후에 대기 후 제거하고
			SetTimer(2, 100, NULL);				// 0.1초짜리 새로운 타이머 생성
			break;
		case 2:											// 2번타이머
			GetParent()->SendMessage(WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), 44000), (LPARAM)m_hWnd);
			break;
	}

	CButton::OnTimer(nIDEvent);
}
