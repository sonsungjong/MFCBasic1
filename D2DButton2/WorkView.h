#ifndef _WORK_VIEW_H_
#define _WORK_VIEW_H_
#include "TW_Direct2D.h"

class WorkView : public TWD_View
{
public:
	WorkView();

	// �� ��ư�� ��ǥ�� ���� �� ����ϴ� �Լ�
	D2D1_RECT_F* GetBtnRect(int a_index);

	// ��ư�� ���¸� �����ϴ� �Լ�
	void SetBtnState(int a_index, unsigned char a_state);
	// ��ư ���¸� �����ϴ� �Լ�
	unsigned char GetBtnState(int a_index);

	// ���õ� ��ư�� �ε����� �����ϴ� �Լ�
	void SetSelectedBtn(unsigned char a_btn_index);
	// ���õ� ��ư�� �ε����� ��� �Լ�
	unsigned char GetSelectedBtn();

	// View �׸��� �۾��� ������ �Լ�
	virtual void OnDraw();

protected:
	// ��ư�� �ؽ�Ʈ ���� ( 0: �ȴ���, 1: ����)
	D2D1_COLOR_F m_text_color[2] = {  
		{0.35f, 0.85f, 1.0f, 1.0f},
		{0.75f, 0.95f, 1.0f, 1.0f}
	};				// RGBA

	// ��ư�� �׵θ� ���� ( 0:�ȴ���, 1: ����)
	D2D1_COLOR_F m_btn_border_color[2] = {
		{0.2f, 0.7f, 0.9f, 1.0f},
		{0.6f, 0.9f, 0.95f, 1.0f}
	};

	// �� ���� ��ư ��ġ ����
	D2D1_RECT_F m_btn_rect[3] = {
		{30.0f, 30.0f, 180.0f, 75.0f},
		{210.0f, 30.0f, 360.0f, 75.0f},
		{390.0f, 30.0f, 540.0f, 75.0f}
	};

	// ��ư�� ������ ���¿� ���� ���õ� ��ư�� �ε��� ��
	unsigned char m_btn_state[3] = { 0,0,0 }, m_selected_btn = 0xFF;

};

#endif