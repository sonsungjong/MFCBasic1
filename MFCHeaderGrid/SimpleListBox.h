#ifndef _SIMPLE_LISTBOX_H_
#define _SIMPLE_LISTBOX_H_

#include "User_ListBox.h"

class SimpleListBox : public User_ListBox
{
protected:
	HFONT mh_font;
	//TCHAR m_temp_str[256];
	int m_position[4] = { 0, 70, 120, 200 };
	
public:
	SimpleListBox();

	// WM_CREATE 시가 아니고 리스트박스 생성시에 작업할 내용을 추가하기 위한 함수
	virtual void CreateUserObject();
	// WM_DESTROY를 사용하지 않고 리스트박스가 제거될 때 작업할 내용을 추가하기 위한 함수
	virtual void DeleteUserObject();
	// 각 항목에 출력될 정보를 그리는 함수
	virtual void UserDraw(HDC ah_dc, RECT* ap_rect, void* ap_data);
	// 항목을 더블클릭했을때 호출되는 함수
	virtual void ProcessDoubleClicked(int a_index);
	// 헤더 컨트롤에서 전송하는 메시지를 처리할 함수 (메시지추가On44001)
	virtual void SetBuddyMessage(int a_count, void* ap_data);

	// 상태메시지를 추가하는 함수
	void AddState(const TCHAR* ap_str, int a_state = 0);
};

#endif