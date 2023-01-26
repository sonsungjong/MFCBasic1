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

	// Ȯ����� �������� ����
	CImage m_draw_image;
	CDC m_draw_dc;

	CRect m_client_rect;
	unsigned char m_zoom_level;
	int m_x, m_y, m_cx, m_cy;

	unsigned char m_is_clicked;
	CPoint m_clicked_pos;

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

	inline void DpToLp(float a_dx, float a_dy, float* ap_lx, float* ap_ly);
	inline void LpToDp(float a_lx, float a_ly, float* ap_dx, float* ap_dy);

	void MakeDisplayImageFromPattern(unsigned char* ap_pattern);
	void MakeDisplayImage();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};


