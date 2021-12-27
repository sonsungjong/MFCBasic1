#pragma once


// UserWnd

class UserWnd : public CWnd
{
	DECLARE_DYNAMIC(UserWnd)

public:
	UserWnd();
	virtual ~UserWnd();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};


