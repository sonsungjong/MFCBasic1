#ifndef _WORK_VIEW_H_
#define _WORK_VIEW_H_
#include "TW_Direct2D.h"

class WorkView : public TWD_View
{
public:
	WorkView();

	// 각 버튼의 좌표를 얻을 때 사용하는 함수
	D2D1_RECT_F* GetBtnRect(int a_index);

	// 버튼의 상태를 설정하는 함수
	void SetBtnState(int a_index, unsigned char a_state);
	// 버튼 상태를 설정하는 함수
	unsigned char GetBtnState(int a_index);

	// 선택된 버튼의 인덱스를 설정하는 함수
	void SetSelectedBtn(unsigned char a_btn_index);
	// 선택된 버튼의 인덱스를 얻는 함수
	unsigned char GetSelectedBtn();

	// View 그리기 작업을 전담할 함수
	virtual void OnDraw();

protected:
	// 버튼의 텍스트 색상 ( 0: 안눌림, 1: 눌림)
	D2D1_COLOR_F m_text_color[2] = {  
		{0.35f, 0.85f, 1.0f, 1.0f},
		{0.75f, 0.95f, 1.0f, 1.0f}
	};				// RGBA

	// 버튼의 테두리 색상 ( 0:안눌림, 1: 눌림)
	D2D1_COLOR_F m_btn_border_color[2] = {
		{0.2f, 0.7f, 0.9f, 1.0f},
		{0.6f, 0.9f, 0.95f, 1.0f}
	};

	// 세 개의 버튼 위치 정보
	D2D1_RECT_F m_btn_rect[3] = {
		{30.0f, 30.0f, 180.0f, 75.0f},
		{210.0f, 30.0f, 360.0f, 75.0f},
		{390.0f, 30.0f, 540.0f, 75.0f}
	};

	// 버튼의 눌러짐 상태와 현재 선택된 버튼의 인덱스 값
	unsigned char m_btn_state[3] = { 0,0,0 }, m_selected_btn = 0xFF;

};

#endif