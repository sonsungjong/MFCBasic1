#include "pch.h"
#include "SensorDataList.h"

// 리스트 박스가 생성될 때 호출되는 함수
void SensorDataListBox::CreateUserObject()
{
	// 펜 색 설정
	m_focus_pen_color = m_select_pen_color = RGB(112, 127, 154);

	// 폰트 생성 (중요!!)
	mh_font = ::CreateFont(16, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("consolas"));
	SetItemHeight(0, 19);				// 리스트박스 항목의 높이를 설정 (중요!!)
}

// 리스트 박스에 등록된 바이너리 데이터 정보를 모두 제거
void SensorDataListBox::ResetSensorData()
{
	SDF* p_data;
	int count = GetCount();				// 등록된 항목 수를 얻는다
	for (int i = 0; i < count; i++) {
		p_data = (SDF*)GetItemDataPtr(i);				// i 번째 항목의 메모리 주소를 얻는다
		delete p_data;				// 해제한다
	}
	ResetContent();				// 항목 모두 제거
}

// 리스트 박스가 제거될 때 호출되는 함수
void SensorDataListBox::DeleteUserObject()
{
	ResetSensorData();					// 항목 모두 제거
	if (mh_font != NULL) { ::DeleteObject(mh_font); }				// 출력용 GDI Object 제거
}

// 출력 정보를 그리는 함수
void SensorDataListBox::UserDraw(HDC ah_dc, RECT* ap_rect, void* ap_data)
{
	// 생성한 글꼴 적용
	::SelectObject(ah_dc, mh_font);
	// 글자 흰색
	::SetTextColor(ah_dc, RGB(200, 228, 255));
	// 글자 배경색 투명
	::SetBkMode(ah_dc, TRANSPARENT);

	SDF* p_data = (SDF*)ap_data;
	::TextOut(ah_dc, ap_rect->left + 6, ap_rect->top + 1, p_data->str_date, p_data->str_date_len);
	wchar_t str[128];
	int len = swprintf_s(str, 128, L"%.1f, %d%%, %.1f, %.1f, %.1f", p_data->temp, p_data->humi, p_data->acc, p_data->lat, p_data->lon);
	::TextOut(ah_dc, ap_rect->left + 140, ap_rect->top + 1, str, len);

}

// 배경을 그릴 함수
void SensorDataListBox::BaseDraw(HDC ah_dc, RECT* ap_rect)
{
	// 전체 갱신, 포커스 갱신, 선택 갱신
	if (mp_last_lpds->itemAction & 0x07)				// 0x07 == ODA_DRAWENTIRE|ODA_FOCUS|ODA_SELECT
	{
		::SelectObject(ah_dc, ::GetStockObject(DC_BRUSH));
		::SelectObject(ah_dc, ::GetStockObject(DC_PEN));
		// 선택된 상태인지 체크
		if (mp_last_lpds->itemState & ODS_SELECTED)
		{
			// 선택상태 펜으로 변경
			::SetDCPenColor(ah_dc, m_select_pen_color);
		}
		else {
			// 선택된 상태가 아니면 배경색과 동일한 펜색
			::SetDCPenColor(ah_dc, m_bk_pen_color);
		}
		::SetDCBrushColor(ah_dc, m_bk_brush_color);
		// 배경그리기
		::Rectangle(ah_dc, ap_rect->left, ap_rect->top, ap_rect->right, ap_rect->bottom);
	}
}

// 한 줄 추가
void SensorDataListBox::AddSensorData(char* ap_data, unsigned short a_data_size)
{
	FILE* p_file = NULL;

	if (0 == fopen_s(&p_file, ".\\data\\cbm.dat", "a+b")) {  
		

		fwrite(ap_data, 1, a_data_size, p_file);          // 할당된 메모리에 파일 내용을 복사한다.
		fclose(p_file);  // 파일을 닫는다!
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
		// 서비스 시작 일을 날짜 형식으로 값을 얻는다.
		localtime_s(&tm_time, &p->date);

		p->str_date_len = swprintf_s(p->str_date, 20, L"%04d-%02d-%02d %02d:%02d", tm_time.tm_year + 1900, tm_time.tm_mon + 1,
			tm_time.tm_mday, tm_time.tm_hour, tm_time.tm_min);

		index = InsertString(-1, _T(""));
		SetItemDataPtr(index, p);
		mp_graph->AddData(p->temp, (float)p->humi);
	}
	SetCurSel(index);
}
