#pragma once
// MFC Ŭ���� �߰�

#define IMG_WIDTH				3072
#define IMG_HEIGHT				3072

class XRayView : public CWnd
{
	DECLARE_DYNAMIC(XRayView)
private:
	CDC m_mem_dc;							// ȭ�� ����� ���� DC
	CBitmap m_mem_bmp;					// Raw������ ��Ʈ�� �̹����� �����ϱ� ���� ��Ʈ��

	// 16��Ʈ �̹��������� ������ �޸� �ּ��� ������
	unsigned short* mp_16bit_data;
	// ȭ�� ��¿� 32��Ʈ �̹��� ������ ������ �޸� �ּ��� ������
	unsigned char* mp_image_pattern;
	// �̹����� �����ϴ� ���� �� ����
	int m_pixel_count;
	// �̹����� �����ϴ� ������ �ִ� ��ġ�� �ּ� ��ġ, ������ ������ ����
	unsigned short int m_min = 0xFFFF;
	unsigned short int m_max = 0x0000;
	unsigned short int m_range;
	// ������ ������ ���� ������ ����� ����
	int m_color_table[256];

public:
	XRayView();
	virtual ~XRayView();

	// X-Ray �̹����� �о� mp_16bit_data�� ����Ű�� �޸𸮿� ����
	int ReadImageDataFromFile(const TCHAR* ap_image_path);
	// X-Ray �̹����� �о� ��ȯ�� ��� ����
	int LoadXRayImage(const TCHAR* ap_image_path);
	// ����Ʈ �ڽ��� ���� ������ ä��� �Լ�
	void SetColorDataToListBox(CListBox* ap_list_box);
	// ��ȿ���� ����
	void UpdateRange(unsigned char a_enable_colors[]);
	// �̹��� ���� �����
	void MakeNormalPattern(unsigned char a_enable_colors[]);
	// �̹����� ȭ�鿡 ���
	void UpdateImage(unsigned char a_enable_colors[]);
	// ����� ǥ��
	void ChangeSelectColorImage(unsigned char a_enable_colors[], int a_color_index, int a_color_count);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
};


