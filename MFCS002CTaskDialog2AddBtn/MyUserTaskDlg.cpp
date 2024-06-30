#include "pch.h"
#include "MyUserTaskDlg.h"

MyUserTaskDlg::MyUserTaskDlg()
	: CTaskDialog(L"CTaskDialog에 사용자 정의 버튼을 추가하는 방법", L"[손성종] 버튼을 추가했습니다.", L"사용자 정의 버튼 예제", TDCBF_OK_BUTTON, TDF_ALLOW_DIALOG_CANCELLATION | TDF_USE_COMMAND_LINKS)
{
	AddCommandControl(100, L"손성종");				// 100번으로 사용자 정의 버튼 추가
	AddCommandControl(101, L"&제목\n글내용입니다");				// 101번으로 사용자 정의 버튼 추가
	AddCommandControl(102, L"&음수\n음수를 리턴하면 창이 닫힙니다");				// 102번으로 사용자 정의 버튼 추가
}

HRESULT MyUserTaskDlg::OnCommandControlClick(_In_ int nCommandControlID)
{
	if (100 == nCommandControlID) 
	{
		// 손성종 버튼이 눌릴 때 양수를 리턴해서 창이 닫히지 않게 할 수 있다
		::MessageBox(GetActiveWindow(), L"손성종 버튼 눌림", L"제목", MB_OK);						// GetActiveWindow() 를 사용해서 부모윈도우에 종속되게 메시지박스를 띄운다
		return 100;
	}
	else if (101 == nCommandControlID) {
		SetMainInstruction(L"상단 문구를 변경합니다");

		return 101;
	}
	else if (102 == nCommandControlID) {

		return -1;
	}

	return CTaskDialog::OnCommandControlClick(nCommandControlID);				// 생성자에 TDF_USE_COMMAND_LINKS 를 추가하면 일반버튼이 영역버튼 스타일로 바뀐다
}
