#ifndef _TW_CODE_EDIT_H_
#define _TW_CODE_EDIT_H_
// TW_CodeEdit

class TW_CodeEdit : public CWnd
{
	DECLARE_DYNAMIC(TW_CodeEdit)
protected:
	CImage m_mem_image;
	HDC mh_mem_dc;

	BYTE m_key_state[256];				// 키입력 매칭
	HFONT mh_font;				// 글꼴
	CString m_str;

public:
	TW_CodeEdit();
	virtual ~TW_CodeEdit();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};


#endif