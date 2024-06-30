#include "pch.h"
#include "TaskDialogProgressBar.h"

TaskDialogProgressBar::TaskDialogProgressBar()
	: CTaskDialog(L"CTaskDialog ���� ���� Ȯ��", L"�۾� ���� �� �Դϴ�...", L"TaskDialog ���� ���� Ȯ��", NULL, TDF_ALLOW_DIALOG_CANCELLATION | TDF_SHOW_PROGRESS_BAR | TDF_CALLBACK_TIMER)
{
	AddCommandControl(100, L"�����");					// ����� ���� ��ư 100��
	AddCommandControl(101, L"����");					// ����� ���� ��ư 101��
	AddCommandControl(102, L"���� �߻�");					// ����� ���� ��ư 102��

	SetProgressBarRange(0, 100);				// ���� 0~100
	SetProgressBarPosition(m_step);			// ����� ���� ��ġ
}

HRESULT TaskDialogProgressBar::OnCommandControlClick(_In_ int nCommandControlID)
{
	if (100 == nCommandControlID) 
	{
		// ��õ� ��ư
		m_is_paused = 0;
		SetProgressBarState(PBST_NORMAL);				// �ʷϻ�
		SetMainInstruction(L"����� �մϴ�");
		return 1;
	}
	else if (101 == nCommandControlID) {
		// ���� ��ư
		m_is_paused = 1;
		SetProgressBarState(PBST_PAUSED);				// �����
		SetMainInstruction(L"���� �մϴ�");
		return 1;
	}
	else if (102 == nCommandControlID) {
		// �����߻� ��ư
		m_is_paused = 1;
		SetProgressBarState(PBST_ERROR);				// ������
		SetMainInstruction(L"���� �߻�");
		return 1;
	}
	return CTaskDialog::OnCommandControlClick(nCommandControlID);
}

HRESULT TaskDialogProgressBar::OnTimer(long a_time)
{
	if (m_is_paused == 0) 
	{
		m_step = (m_step + 1) % 101;			// 1�� ����
		SetProgressBarPosition(m_step);			// ���൵ �� �ݿ�
	}

	return S_OK;
}
