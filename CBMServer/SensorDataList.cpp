#include "pch.h"
#include "SensorDataList.h"

// ����Ʈ �ڽ��� ������ �� ȣ��Ǵ� �Լ�
void SensorDataListBox::CreateUserObject()
{
	// �� �� ����
	m_focus_pen_color = m_select_pen_color = RGB(112, 127, 154);

	// ��Ʈ ���� (�߿�!!)
	mh_font = ::CreateFont(16, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("consolas"));
	SetItemHeight(0, 19);				// ����Ʈ�ڽ� �׸��� ���̸� ���� (�߿�!!)
}

// ����Ʈ �ڽ��� ��ϵ� ���̳ʸ� ������ ������ ��� ����
void SensorDataListBox::ResetSensorData()
{
	SDF* p_data;
	int count = GetCount();				// ��ϵ� �׸� ���� ��´�
	for (int i = 0; i < count; i++) {
		p_data = (SDF*)GetItemDataPtr(i);				// i ��° �׸��� �޸� �ּҸ� ��´�
		delete p_data;				// �����Ѵ�
	}
	ResetContent();				// �׸� ��� ����
}

// ����Ʈ �ڽ��� ���ŵ� �� ȣ��Ǵ� �Լ�
void SensorDataListBox::DeleteUserObject()
{
	ResetSensorData();					// �׸� ��� ����
	if (mh_font != NULL) { ::DeleteObject(mh_font); }				// ��¿� GDI Object ����
}

// ��� ������ �׸��� �Լ�
void SensorDataListBox::UserDraw(HDC ah_dc, RECT* ap_rect, void* ap_data)
{
	// ������ �۲� ����
	::SelectObject(ah_dc, mh_font);
	// ���� ���
	::SetTextColor(ah_dc, RGB(200, 228, 255));
	// ���� ���� ����
	::SetBkMode(ah_dc, TRANSPARENT);

	SDF* p_data = (SDF*)ap_data;
	::TextOut(ah_dc, ap_rect->left + 6, ap_rect->top + 1, p_data->str_date, p_data->str_date_len);
	wchar_t str[128];
	int len = swprintf_s(str, 128, L"%.1f, %d%%, %.1f, %.1f, %.1f", p_data->temp, p_data->humi, p_data->acc, p_data->lat, p_data->lon);
	::TextOut(ah_dc, ap_rect->left + 140, ap_rect->top + 1, str, len);

}

// ����� �׸� �Լ�
void SensorDataListBox::BaseDraw(HDC ah_dc, RECT* ap_rect)
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
void SensorDataListBox::AddSensorData(char* ap_data, unsigned short a_data_size)
{
	FILE* p_file = NULL;

	if (0 == fopen_s(&p_file, ".\\data\\cbm.dat", "a+b")) {  
		

		fwrite(ap_data, 1, a_data_size, p_file);          // �Ҵ�� �޸𸮿� ���� ������ �����Ѵ�.
		fclose(p_file);  // ������ �ݴ´�!
	}
	int count = *ap_data++;
	int index = 0;
	for (int i = 0; i < count; i++) {
		SDF* p = new SDF;
		p->date = *(time_t*)ap_data;
		ap_data += sizeof(time_t);

		p->temp = *(float*)ap_data;
		ap_data += sizeof(float);

		p->humi = *ap_data++;

		p->acc = *(float*)ap_data;
		ap_data += sizeof(float);

		p->lat = *(float*)ap_data;
		ap_data += sizeof(float);

		p->lon = *(float*)ap_data;
		ap_data += sizeof(float);

		tm tm_time;
		// ���� ���� ���� ��¥ �������� ���� ��´�.
		localtime_s(&tm_time, &p->date);

		p->str_date_len = swprintf_s(p->str_date, 20, L"%04d-%02d-%02d %02d:%02d", tm_time.tm_year + 1900, tm_time.tm_mon + 1,
			tm_time.tm_mday, tm_time.tm_hour, tm_time.tm_min);

		index = InsertString(-1, _T(""));
		SetItemDataPtr(index, p);
		mp_graph->AddData(p->temp, (float)p->humi);
	}
	SetCurSel(index);
}
