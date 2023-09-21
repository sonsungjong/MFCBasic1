#pragma once


// SystemBar

class SystemBar : public CWnd
{
	DECLARE_DYNAMIC(SystemBar)

public:
	SystemBar();
	virtual ~SystemBar();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


