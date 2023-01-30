#pragma once

// Picture Control 속성
// Visible : False, 

// 툴바에 사용가능한 최대 버튼 수
#define MAX_BUTTON_COUNT				24

// 툴바 버튼 구조체
struct TipsCommandData {
	TCHAR* p_name;			// 이름
	int name_len;				// 이름 길이 (NULL 길이 제외)
	int command_id;			// WM_COMMAND의 wParam 값
	int x;					// 시작 좌표
	int width;			// 버튼 가로크기
	int bmp_up_id;				// 버튼 이미지
	int bmp_down_id;			// 버튼 이미지
	CBitmap* p_up_bitmap;				// 리소스에 추가한 비트맵을 읽기
	CBitmap* p_down_bitmap;			// 리소스에 추가한 비트맵을 읽기
};

class TW_ToolBar : public CWnd
{
	DECLARE_DYNAMIC(TW_ToolBar)
private:
	CRect m_rect;				// 툴바가 그려질 영역
	CFont m_tool_font;				// 툴바 글꼴
	TipsCommandData m_btn_list[MAX_BUTTON_COUNT];				// 버튼 정보들 (구조체 배열)
	int m_btn_count = 0;					// 현재 버튼 갯수
	int m_select_index = -1;				// 선택한 버튼의 번호
	char m_clicked_flag = 0;				// 0:클릭X, 1:클릭, 2:클릭되었지만 버튼영역 밖에 있음
	CRect m_select_rect;				// 클릭된 버튼의 영역 정보
	CDC m_mem_dc;						// CBitmap을 화면출력
	COLORREF m_bk_color;				// 툴바 배경색
	COLORREF m_border_color;				// 툴바 테두리색
	COLORREF m_in_border_color;				// 툴바 내부테두리 색
	COLORREF m_push_btn_color;				// 눌린 버튼 색상
	COLORREF m_text_color;					// 버튼 제목 색상

public:
	TW_ToolBar();
	virtual ~TW_ToolBar();
	// 툴바 생성
	void CreateToolBar(int a_rect_id, CWnd* ap_parent, int a_ctrl_id);
	// 툴바에 버튼 사전등록 (CreateToolBar 함수 호출 전에 사용해야함)
	void AddButton(const TCHAR* ap_name, int a_command_id, int a_bmp_up_id = 0, int a_bmp_down_id = 0);
	// 버튼 위치 구성
	void UpdateButtonInfo();
	// 마우스가 위치한 곳에 버튼을 표시
	void CheckButtonInToolBar(CPoint point);
	// 버튼이 눌러진 상태를 출력
	void DrawPushButton(TipsCommandData* ap_btn);
	// 버튼이 눌렸다가 해제된 상태를 출력
	void DrawPopButton(TipsCommandData* ap_btn);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};


