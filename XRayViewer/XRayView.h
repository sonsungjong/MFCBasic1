#pragma once
// MFC 클래스 추가

// X-Ray 이미지에 사용된 색상 사용 갯수와 화면출력 유무를 관리하는 자료형
struct ColorInfo
{
	char is_enable;				// 0: 사용안함, 1: 사용
	int count;						// 사용된 색상 갯수
};

class XRayView : public CWnd
{
	DECLARE_DYNAMIC(XRayView)
private:
	CDC m_mem_dc;							// 화면 출력을 위한 DC
	CBitmap m_mem_bmp;					// Raw파일을 비트맵 이미지로 변경하기 위한 비트맵

	// 확대축소 깜빡임을 제거
	CImage m_draw_image;
	CDC m_draw_dc;

	CRect m_client_rect;
	unsigned char m_zoom_level;
	int m_x, m_y, m_cx, m_cy;					// 시작점과 폭과 높이
	int m_image_width;
	int m_image_height;

	unsigned char m_is_clicked;
	CPoint m_clicked_pos;

	// 16비트 이미지패턴을 저장할 메모리 주소의 포인터
	unsigned short* mp_16bit_data;
	// 화면 출력용 32비트 이미지 패턴을 저장할 메모리 주소의 포인터
	unsigned char* mp_image_pattern;
	// 이미지를 구성하는 점의 총 갯수
	int m_pixel_count;
	// 이미지를 구성하는 색상의 최대 수치와 최소 수치, 범위를 저장할 변수
	unsigned short int m_min = 0xFFFF;
	unsigned short int m_max = 0x0000;
	unsigned short int m_range;
	// 색상이 실제로 사용된 갯수를 기억할 변수
	ColorInfo m_color_table[256];

public:
	XRayView();
	virtual ~XRayView();
	
	// 이미지 색상 정보의 주소
	ColorInfo* GetColorData() { return m_color_table; }
	// X-Ray 이미지를 읽어 mp_16bit_data가 가리키는 메모리에 저장
	int ReadImageDataFromFile(const TCHAR* ap_image_path);
	// X-Ray 이미지를 읽어 변환과 출력 설정
	int LoadXRayImage(const TCHAR* ap_image_path);
	 void SetColorDataToListBox(CListBox* ap_list_box);			// 기본 리스트박스에 색상정보를 추가하는 함수
	// 유효범위 갱신
	void UpdateRange();
	// 이미지 패턴 만들기
	void MakeNormalPattern();
	// 이미지를 화면에 출력
	void UpdateImage();
	// 노란색 표시
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


