#include "pch.h"
#include "MyUserTaskDlg.h"

MyUserTaskDlg::MyUserTaskDlg()
	: CTaskDialog(L"CTaskDialog�� ����� ���� ��ư�� �߰��ϴ� ���", L"[�ռ���] ��ư�� �߰��߽��ϴ�.", L"����� ���� ��ư ����", TDCBF_OK_BUTTON, TDF_ALLOW_DIALOG_CANCELLATION | TDF_USE_COMMAND_LINKS)
{
	AddCommandControl(100, L"�ռ���");				// 100������ ����� ���� ��ư �߰�
	AddCommandControl(101, L"&����\n�۳����Դϴ�");				// 101������ ����� ���� ��ư �߰�
	AddCommandControl(102, L"&����\n������ �����ϸ� â�� �����ϴ�");				// 102������ ����� ���� ��ư �߰�
}

HRESULT MyUserTaskDlg::OnCommandControlClick(_In_ int nCommandControlID)
{
	if (100 == nCommandControlID) 
	{
		// �ռ��� ��ư�� ���� �� ����� �����ؼ� â�� ������ �ʰ� �� �� �ִ�
		::MessageBox(GetActiveWindow(), L"�ռ��� ��ư ����", L"����", MB_OK);						// GetActiveWindow() �� ����ؼ� �θ������쿡 ���ӵǰ� �޽����ڽ��� ����
		return 100;
	}
	else if (101 == nCommandControlID) {
		SetMainInstruction(L"��� ������ �����մϴ�");

		return 101;
	}
	else if (102 == nCommandControlID) {

		return -1;
	}

	return CTaskDialog::OnCommandControlClick(nCommandControlID);				// �����ڿ� TDF_USE_COMMAND_LINKS �� �߰��ϸ� �Ϲݹ�ư�� ������ư ��Ÿ�Ϸ� �ٲ��
}
