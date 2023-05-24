#ifndef SENSOR_DATA_LIST_BOX_H_
#define SENSOR_DATA_LIST_BOX_H_

#include "TW_ListBox.h"
#include "LineGraphWnd.h"
/*

�Ͻ� 8byte
�µ� float 4byte
���� char 1byte
��ݰ��ӵ� float 4byte
���� float 4byte
�浵 float 4byte
*/

typedef struct SensorDataFormat
{
	time_t date;
	float temp;
	char humi;
	float acc;
	float lat;
	float lon;
	UINT8 str_date_len;			// ��¿�(ȿ��)
	wchar_t str_date[20];
} SDF;

class SensorDataListBox : public TW_ListBox
{
protected:
	// �۲�
	HFONT mh_font;
	LineGraphWnd* mp_graph;
public:
	SensorDataListBox() { mh_font = NULL; }
	virtual void CreateUserObject();			// ������ ���
	virtual void DeleteUserObject();			// ���Ž� ���
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