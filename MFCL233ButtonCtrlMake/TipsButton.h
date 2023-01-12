#pragma once

// 직접 만들어쓰는 버튼

// 버튼이 클릭되었을 때 발생하는 메시지 (LM_BTN_CLICKED == 28001)
#define LM_BTN_CLICKED				28001

// MFC클래스
class TipsButton : public CWnd
{
	DECLARE_DYNAMIC(TipsButton)
protected:
	HDC mh_mem_dc;					// 버튼 출력시 사용할 메모리DC
	HBITMAP mh_mem_bmp;				// 메모리 DC가 그릴 비트맵
	HFONT mh_font;						// 메모리 DC가 사용할 폰트
	CRect m_rect;							// 버튼의 영역
	CString m_title_str;						// 버튼이 사용할 문자열

	// 포커스된 버튼색, 포커스된 테두리색, 일반 버튼색, 일반 테두리색
	COLORREF m_focus_btn_color;
	COLORREF m_focus_border_color;
	COLORREF m_btn_color;
	COLORREF m_border_color;

	// 버튼 내부 테두리색, 버튼 텍스트 색상
	COLORREF m_in_border_color;
	COLORREF m_text_color;

	// 버튼의 눌러짐 상태를 기억할 변수와 마우스 클릭 상태를 기억할 변수
	char m_push_flag;
	char m_is_clicked;

public:
	TipsButton();
	virtual ~TipsButton();

	// 가이드 컨트롤을 사용해서 버튼 생성
	int CreateButton(CWnd* ap_parent, const TCHAR* ap_title, int a_ctrl_id, int a_guide_rect);
	// 직접 좌표를 지정해서 버튼 생성
	int CreateButton(CWnd* ap_parent, const TCHAR* ap_title, int a_ctrl_id, CRect a_rect);
	// 버튼을 메모리DC에 그림
	void DrawButtonImage(char a_push_flag = 0);
	void ChangeColor(COLORREF a_focus_btn_color, COLORREF a_focus_border_color, COLORREF a_btn_color, COLORREF a_border_color, COLORREF a_in_border_color, COLORREF a_text_color);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
};


