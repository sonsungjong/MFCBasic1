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

	// WM_CREATE �ð� �ƴϰ� ����Ʈ�ڽ� �����ÿ� �۾��� ������ �߰��ϱ� ���� �Լ�
	virtual void CreateUserObject();
	// WM_DESTROY�� ������� �ʰ� ����Ʈ�ڽ��� ���ŵ� �� �۾��� ������ �߰��ϱ� ���� �Լ�
	virtual void DeleteUserObject();
	// �� �׸� ��µ� ������ �׸��� �Լ�
	virtual void UserDraw(HDC ah_dc, RECT* ap_rect, void* ap_data);
	// �׸��� ����Ŭ�������� ȣ��Ǵ� �Լ�
	virtual void ProcessDoubleClicked(int a_index);
	// ��� ��Ʈ�ѿ��� �����ϴ� �޽����� ó���� �Լ� (�޽����߰�On44001)
	virtual void SetBuddyMessage(int a_count, void* ap_data);

	// ���¸޽����� �߰��ϴ� �Լ�
	void AddState(const TCHAR* ap_str, int a_state = 0);
};

#endif