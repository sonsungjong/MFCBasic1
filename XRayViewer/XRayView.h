#pragma once
// MFC Ŭ���� �߰�

// X-Ray �̹����� ���� ���� ��� ������ ȭ����� ������ �����ϴ� �ڷ���
struct ColorInfo
{
	char is_enable;				// 0: ������, 1: ���
	int count;						// ���� ���� ����
};

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
	int m_x, m_y, m_cx, m_cy;					// �������� ���� ����
	int m_image_width;
	int m_image_height;

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
	ColorInfo m_color_table[256];

public:
	XRayView();
	virtual ~XRayView();
	
	// �̹��� ���� ������ �ּ�
	ColorInfo* GetColorData() { return m_color_table; }
	// X-Ray �̹����� �о� mp_16bit_data�� ����Ű�� �޸𸮿� ����
	int ReadImageDataFromFile(const TCHAR* ap_image_path);
	// X-Ray �̹����� �о� ��ȯ�� ��� ����
	int LoadXRayImage(const TCHAR* ap_image_path);
	 void SetColorDataToListBox(CListBox* ap_list_box);			// �⺻ ����Ʈ�ڽ��� ���������� �߰��ϴ� �Լ�
	// ��ȿ���� ����
	void UpdateRange();
	// �̹��� ���� �����
	void MakeNormalPattern();
	// �̹����� ȭ�鿡 ���
	void UpdateImage();
	// ����� ǥ��
	void ChangeSelectColorImage(int a_color_index);

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


