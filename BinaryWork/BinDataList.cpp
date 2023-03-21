#include "pch.h"
#include "BinDataList.h"

// ����Ʈ �ڽ��� ������ �� ȣ��Ǵ� �Լ�
void BinDataListBox::CreateUserObject()
{
	// �� �� ����
	m_focus_pen_color = m_select_pen_color = RGB(112, 127, 154);

	// ��Ʈ ���� (�߿�!!)
	mh_font = ::CreateFont(16, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("consolas"));
	SetItemHeight(0, 19);				// ����Ʈ�ڽ� �׸��� ���̸� ���� (�߿�!!)
}

// ����Ʈ �ڽ��� ��ϵ� ���̳ʸ� ������ ������ ��� ����
void BinDataListBox::ResetBinData()
{
	BDF* p_data;
	int count = GetCount();				// ��ϵ� �׸� ���� ��´�
	for (int i = 0; i < count; i++) {
		p_data = (BDF*)GetItemDataPtr(i);				// i ��° �׸��� �޸� �ּҸ� ��´�
		delete p_data;				// �����Ѵ�
	}
	ResetContent();				// �׸� ��� ����
}

// ����Ʈ �ڽ��� ���ŵ� �� ȣ��Ǵ� �Լ�
void BinDataListBox::DeleteUserObject()
{
	ResetBinData();					// �׸� ��� ����
	if (mh_font != NULL) { ::DeleteObject(mh_font); }				// ��¿� GDI Object ����
}

// ��� ������ �׸��� �Լ�
void BinDataListBox::UserDraw(HDC ah_dc, RECT* ap_rect, void* ap_data)
{
	// ������ �۲� ����
	::SelectObject(ah_dc, mh_font);
	// ���� ���
	::SetTextColor(ah_dc, RGB(200, 228, 255));
	// ���� ���� ����
	::SetBkMode(ah_dc, TRANSPARENT);

	BDF* p_data = (BDF*)ap_data;
	::TextOut(ah_dc, ap_rect->left + 6, ap_rect->top + 1, p_data->str, p_data->str_len);
}

// ����� �׸� �Լ�
void BinDataListBox::BaseDraw(HDC ah_dc, RECT* ap_rect)
{
	// ��ü ����, ��Ŀ�� ����, ���� ����
	if (mp_last_lpds->itemAction & 0x07)				// 0x07 == ODA_DRAWENTIRE|ODA_FOCUS|ODA_SELECT
	{
		::SelectObject(ah_dc, ::GetStockObject(DC_BRUSH));
		::SelectObject(ah_dc, ::GetStockObject(DC_PEN));
		// ���õ� �������� üũ
		if (mp_last_lpds->itemState & ODS_SELECTED)
		{
			// ���û��� ������ ����
			::SetDCPenColor(ah_dc, m_select_pen_color);
		}
		else {
			// ���õ� ���°� �ƴϸ� ������ ������ ���
			::SetDCPenColor(ah_dc, m_bk_pen_color);
		}
		::SetDCBrushColor(ah_dc, m_bk_brush_color);
		// ���׸���
		::Rectangle(ah_dc, ap_rect->left, ap_rect->top, ap_rect->right, ap_rect->bottom);
	}
}

// �� �� �߰�
void BinDataListBox::AddBinaryData(BDF* ap_line_data)
{
	int index = InsertString(-1, _T(""));
	SetItemDataPtr(index, ap_line_data);
}
