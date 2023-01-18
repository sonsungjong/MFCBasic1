#pragma once
// MFC 클래스 추가

#define IMG_WIDTH				3072
#define IMG_HEIGHT				3072

class XRayView : public CWnd
{
	DECLARE_DYNAMIC(XRayView)
private:
	CDC m_mem_dc;							// 화면 출력을 위한 DC
	CBitmap m_mem_bmp;					// Raw파일을 비트맵 이미지로 변경하기 위한 비트맵

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
	int m_color_table[256];

public:
	XRayView();
	virtual ~XRayView();

	// X-Ray 이미지를 읽어 mp_16bit_data가 가리키는 메모리에 저장
	int ReadImageDataFromFile(const TCHAR* ap_image_path);
	// X-Ray 이미지를 읽어 변환과 출력 설정
	int LoadXRayImage(const TCHAR* ap_image_path);
	// 리스트 박스에 색상 정보를 채우는 함수
	void SetColorDataToListBox(CListBox* ap_list_box);
	// 유효범위 갱신
	void UpdateRange(unsigned char a_enable_colors[]);
	// 이미지 패턴 만들기
	void MakeNormalPattern(unsigned char a_enable_colors[]);
	// 이미지를 화면에 출력
	void UpdateImage(unsigned char a_enable_colors[]);
	// 노란색 표시
	void ChangeSelectColorImage(unsigned char a_enable_colors[], int a_color_index, int a_color_count);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
};


