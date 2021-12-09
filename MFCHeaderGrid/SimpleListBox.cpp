#include "pch.h"
#include "SimpleListBox.h"
#include "HeaderGrid.h"

SimpleListBox::SimpleListBox(){}

void SimpleListBox::CreateUserObject()
{
	mh_font = ::CreateFont(16, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS, _T("����"));

	// ����Ʈ�ڽ� �� �Ѹ��� ���̿� ��
	SetItemHeight(0, 18);
}

void SimpleListBox::DeleteUserObject()
{
	// ��� �׸� ����
	ResetContent();
	// �۲� ����
	::DeleteObject(mh_font);
}

void SimpleListBox::UserDraw(HDC ah_dc, RECT* ap_rect, void* ap_data)
{
	// ���� �׷����� �׸��� ��ġ
	int index = mp_last_lpds->itemID;

	// �۲� ����
	::SelectObject(ah_dc, mh_font);
	// ���ڿ� ����� ����ó��
	::SetBkMode(ah_dc, TRANSPARENT);

	// ��ɾ� �̸� ��¿� ����� ���� ����
	::SetTextColor(ah_dc, RGB(255,255,255));
	// ��ɾ� �̸� ���
	const TCHAR* p_str_table[3] = {_T("myid"), _T("�ռ���"), _T("���￡�� �������")};
	RECT r;
	// top�� bottom�� ����
	r.top = ap_rect->top;
	r.bottom = ap_rect->bottom;
	// left�� right�� 3���� ���� ���
	for (int i = 0; i < 3; i++) {
		r.left = ap_rect->left + m_position[i];
		r.right = ap_rect->left + m_position[i+1];
		::DrawText(ah_dc, p_str_table[i], _tcslen(p_str_table[i]), &r, DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);
	}
}

void SimpleListBox::ProcessDoubleClicked(int a_index)
{
	
}

void SimpleListBox::AddState(const TCHAR* ap_str, int a_state)
{
	// ���� ������ �ִ� 2000�� ������
	while (GetCount() > 2000) { DeleteString(0); }

	int index = InsertString(-1, ap_str);					// ���� �޽��� �߰�
	SetItemData(index, a_state);								// ���� �޽��� ���� ����
	SetCurSel(index);												// �߰��� �޽����� ����
}

void SimpleListBox::SetBuddyMessage(int a_count, void* ap_data)
{
	HID* p = (HID*)ap_data;
	int i, position = 0;
	for (i = 0; i < a_count; i++) {
		m_position[i] = position;
		position += p->width;
		p++;
	}
	m_position[i] = position;
	Invalidate();
}