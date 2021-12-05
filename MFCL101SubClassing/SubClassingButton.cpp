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
	SetTimer(1, 500, NULL);							// 1��Ÿ�̸�, ���������� 0.5�� ������ ���� (���Ȯ��)

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
		case 1:											// 1��Ÿ�̸�
			KillTimer(1);								// 0.5���Ŀ� ��� �� �����ϰ�
			SetTimer(2, 100, NULL);				// 0.1��¥�� ���ο� Ÿ�̸� ����
			break;
		case 2:											// 2��Ÿ�̸�
			GetParent()->SendMessage(WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), 44000), (LPARAM)m_hWnd);
			break;
	}

	CButton::OnTimer(nIDEvent);
}
