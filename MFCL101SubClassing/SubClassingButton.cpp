// SubClassingButton.cpp : implementation file
//

#include "pch.h"
#include "MFCL101SubClassing.h"
#include "SubClassingButton.h"


// SubClassingButton
// ��ư�� ������ �־ Ŭ���� �����ϰ� �۵��� �� �ֵ��� ��� �߰�
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
	SetTimer(1, 500, NULL);							// 1��Ÿ�̸�

	CButton::OnLButtonDown(nFlags, point);
}


void SubClassingButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	KillTimer(1);									// 1��Ÿ�̸� ����
	KillTimer(2);									// 2��Ÿ�̸� ����

	CButton::OnLButtonUp(nFlags, point);
}


void SubClassingButton::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	switch (nIDEvent)
	{
		case 1:
			KillTimer(1);					// 0.5���Ŀ� ����
			SetTimer(2, 100, NULL);
			break;
		case 2:
			GetParent()->SendMessage(WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), 44000), (LPARAM)m_hWnd);
			break;
			// 24:00
	}

	CButton::OnTimer(nIDEvent);
}
