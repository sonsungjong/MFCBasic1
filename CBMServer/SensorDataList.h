#ifndef SENSOR_DATA_LIST_BOX_H_
#define SENSOR_DATA_LIST_BOX_H_

#include "TW_ListBox.h"
#include "LineGraphWnd.h"
/*

일시 8byte
온도 float 4byte
습도 char 1byte
충격가속도 float 4byte
위도 float 4byte
경도 float 4byte
*/

typedef struct SensorDataFormat
{
	time_t date;
	float temp;
	char humi;
	float acc;
	float lat;
	float lon;
	UINT8 str_date_len;			// 출력용(효율)
	wchar_t str_date[20];
} SDF;

class SensorDataListBox : public TW_ListBox
{
protected:
	// 글꼴
	HFONT mh_font;
	LineGraphWnd* mp_graph;
public:
	SensorDataListBox() { mh_font = NULL; }
	virtual void CreateUserObject();			// 생성시 사용
	virtual void DeleteUserObject();			// 제거시 사용
	virtual void UserDraw(HDC ah_dc, RECT* ap_rect, void* ap_data);
	virtual void BaseDraw(HDC ah_dc, RECT* ap_rect);

	void ResetSensorData();
	void AddSensorData(char* ap_data, unsigned short a_data_size);
	void SetLineGraph(LineGraphWnd* ap_graph)
	{
		mp_graph = ap_graph;
	}
};

#endif