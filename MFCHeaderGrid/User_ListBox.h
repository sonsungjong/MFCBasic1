// 클래스 제작 : 김성엽 (tipsware@naver.com)
// 2021년 4월 11일 일요일
// 서브 클래스시에도 초기화가 잘 진행되도록 PreSubclassWindow 함수 추가

#pragma once
class User_ListBox : public CListBox
{
	DECLARE_DYNAMIC(User_ListBox)
protected:
	// 리스트 박스 배경색으로 사용할 브러시 객체
	HBRUSH mh_list_bk_brush;
	// 상황별 브러시 색상을 기억할 변수들
	COLORREF m_select_brush_color, m_focus_brush_color, m_bk_brush_color;
	// 상황별 펜 색상을 기억할 변수들
	COLORREF m_select_pen_color, m_focus_pen_color, m_bk_pen_color;
	// 현재 처리중인 Owner-Draw 구조체 정보, 매개 변수로 계속 안넘기려고 
	// 구조체 주소를 보관해서 사용. 나중에 사용하면 주소가 유효하지 
	// 않을수 있으니 주의해야 함!
	LPDRAWITEMSTRUCT mp_last_lpds;

	// 리스트 박스의 깜빡임을 잡기 위해 사용할 이미지 객체
	CImage m_draw_image;
	// 이미지 객체에 글미을 그릴때 사용할 DC 객체
	HDC mh_draw_dc;
	// 현재 윈도우를 갱신할 때 사용할 함수(재정의)
	void Invalidate(BOOL bErase =0);
	void CreateMemoryDC();

public:
	User_ListBox();
	virtual ~User_ListBox();

	// WM_CREATE를 사용하지 않고 리스트 박스가 생성될때 함께 작업해야 할
	// 내용을 추가하기 위해서 이 함수를 제공함
	virtual void CreateUserObject() {}
	// WM_DESTROY를 사용하지 않고 리스트 박스가 제거될때 함께 작업해야 할
	// 내용을 추가하기 위해서 이 함수를 제공함
	virtual void DeleteUserObject() {}
	// 각 항목의 배경을 그리기 위해 사용할 함수 (기본 코드 존재)
	virtual void BaseDraw(HDC ah_dc, RECT *ap_rect);
	// 각 항목에 출력될 정보를 그리는 함수
	virtual void UserDraw(HDC ah_dc, RECT *ap_rect, void *ap_data) { }
	// 리스트 박스의 특정 항목 위치만 갱신하는 함수
	void UpdateItemInfo(int a_index, int a_count);
	// 항목을 더블 클릭했을 때 호출되는 함수
	virtual void ProcessDoubleClicked(int a_index) { }
	// 헤더 컨트롤에서 전송하는 메시지를 처리할 함수
	virtual void SetBuddyMessage(int a_count, void* ap_data) {}

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH CtlColor(CDC * /*pDC*/, UINT /*nCtlColor*/);
	afx_msg void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	virtual void PreSubclassWindow();
	afx_msg void OnLbnDblclk();
protected:
	afx_msg LRESULT On44001(WPARAM wParam, LPARAM lParam);
};