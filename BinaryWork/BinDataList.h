#ifndef BIN_DATA_LIST_BOX_H_
#define BIN_DATA_LIST_BOX_H_

#include "TW_ListBox.h"

#define BIN_COUNT		40
#define BIN_STR_SIZE		(3*BIN_COUNT+6+1)			// ���ٿ� ��µ� ���ڿ� ����

typedef struct BinaryDataFormat
{
	UINT8* p_bin;
	UINT8 bin_data_size;
	UINT8 str_len;
	TCHAR str[BIN_STR_SIZE];
} BDF;

class BinDataListBox : public TW_ListBox
{
protected:
	// �۲�
	HFONT mh_font;

public:
	BinDataListBox() { mh_font = NULL; }
	virtual void CreateUserObject();			// ������ ���
	virtual void DeleteUserObject();			// ���Ž� ���
	virtual void UserDraw(HDC ah_dc, RECT* ap_rect, void* ap_data);
	virtual void BaseDraw(HDC ah_dc, RECT* ap_rect);

	void ResetBinData();
	void AddBinaryData(BDF* ap_line_data);
};

#endif