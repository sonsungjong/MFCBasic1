#pragma once


// SubClassingButton

class SubClassingButton : public CButton
{
	DECLARE_DYNAMIC(SubClassingButton)

public:
	SubClassingButton();
	virtual ~SubClassingButton();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};


