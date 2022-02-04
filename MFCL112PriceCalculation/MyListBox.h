#pragma once


// MyListBox

class MyListBox : public CCheckListBox
{
	DECLARE_DYNAMIC(MyListBox)

public:
	MyListBox();
	virtual ~MyListBox();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};


