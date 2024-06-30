#include "pch.h"
#include "TaskDialogProgressBar.h"

TaskDialogProgressBar::TaskDialogProgressBar()
	: CTaskDialog(L"CTaskDialog 진행 상태 확인", L"작업 진행 중 입니다...", L"TaskDialog 진행 상태 확인", NULL, TDF_ALLOW_DIALOG_CANCELLATION | TDF_SHOW_PROGRESS_BAR | TDF_CALLBACK_TIMER)
{
	AddCommandControl(100, L"재시작");					// 사용자 정의 버튼 100번
	AddCommandControl(101, L"중지");					// 사용자 정의 버튼 101번
	AddCommandControl(102, L"오류 발생");					// 사용자 정의 버튼 102번

	SetProgressBarRange(0, 100);				// 범위 0~100
	SetProgressBarPosition(m_step);			// 진행바 현재 위치
}

HRESULT TaskDialogProgressBar::OnCommandControlClick(_In_ int nCommandControlID)
{
	if (100 == nCommandControlID) 
	{
		// 재시도 버튼
		m_is_paused = 0;
		SetProgressBarState(PBST_NORMAL);				// 초록색
		SetMainInstruction(L"재시작 합니다");
		return 1;
	}
	else if (101 == nCommandControlID) {
		// 중지 버튼
		m_is_paused = 1;
		SetProgressBarState(PBST_PAUSED);				// 노란색
		SetMainInstruction(L"중지 합니다");
		return 1;
	}
	else if (102 == nCommandControlID) {
		// 오류발생 버튼
		m_is_paused = 1;
		SetProgressBarState(PBST_ERROR);				// 빨간색
		SetMainInstruction(L"오류 발생");
		return 1;
	}
	return CTaskDialog::OnCommandControlClick(nCommandControlID);
}

HRESULT TaskDialogProgressBar::OnTimer(long a_time)
{
	if (m_is_paused == 0) 
	{
		m_step = (m_step + 1) % 101;			// 1씩 증가
		SetProgressBarPosition(m_step);			// 진행도 값 반영
	}

	return S_OK;
}
