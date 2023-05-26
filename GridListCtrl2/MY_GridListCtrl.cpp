// MY_GridListCtrl.cpp : implementation file
//

#include "pch.h"
#include "GridListCtrl2.h"
#include "MY_GridListCtrl.h"


// MY_GridListCtrl

IMPLEMENT_DYNAMIC(MY_GridListCtrl, CListCtrl)

MY_GridListCtrl::MY_GridListCtrl()
{

}

MY_GridListCtrl::~MY_GridListCtrl()
{
}

void MY_GridListCtrl::SetGridLine()
{
	m_font = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_MODERN, _T("���� ���"));
	SendMessage(WM_SETFONT, (WPARAM)m_font, (LPARAM)TRUE);

	LVITEM item;
	::ZeroMemory(&item, sizeof(item));
	item.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
	item.pszText = _T("TEST ITEM");
	item.iItem = 5;
	item.iImage = 1;
	item.state = LVIS_SELECTED | LVIS_FOCUSED;

	// ���� ��� �߰� �� �÷� �߰�
	SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);							// ���� �߰�
	InsertColumn(0, _T("No"), LVCFMT_CENTER, 40);
	InsertColumn(1, _T("Name"), LVCFMT_CENTER, 100);
	InsertColumn(2, _T("Kor"), LVCFMT_CENTER, 60);
	InsertColumn(3, _T("Eng"), LVCFMT_CENTER, 60);
	InsertColumn(4, _T("Math"), LVCFMT_CENTER, 60);
	InsertColumn(5, _T("Sum"), LVCFMT_CENTER, 100);
	InsertColumn(6, _T("Avg"), LVCFMT_CENTER, 60);
	InsertColumn(7, _T("�� ����"), LVCFMT_CENTER, 100);
	ModifyStyle(LVS_TYPEMASK, LVS_REPORT);

	CString strItem;
	// �׸� ����
	for (int i = 0; i < 30; i++) {
		strItem.Format(_T("%d"), i+1);
		InsertItem(i, strItem);
		SetItem(i, 1, LVIF_TEXT, _T("item"), NULL, NULL, NULL, NULL);
		SetItem(i, 2, LVIF_TEXT, _T("33"), NULL, NULL, NULL, NULL);
		SetItem(i, 3, LVIF_TEXT, _T("44"), NULL, NULL, NULL, NULL);
		SetItem(i, 4, LVIF_TEXT, _T("55"), NULL, NULL, NULL, NULL);
		SetItem(i, 5, LVIF_TEXT, _T("22"), NULL, NULL, NULL, NULL);
		SetItem(i, 6, LVIF_TEXT, _T("10.1"), NULL, NULL, NULL, NULL);
		// SetBtn 7
	}

}

void MY_GridListCtrl::SetGridLine2()
{
	// ����Ʈ��Ʈ�� Font
	m_font = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_MODERN, _T("���� ���"));
	SendMessage(WM_SETFONT, (WPARAM)m_font, (LPARAM)TRUE);

	// ����Ʈ ��Ʈ�� �⺻ ����
	LVITEM item;
	::ZeroMemory(&item, sizeof(item));
	item.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
	item.pszText = _T("LIG");
	item.iItem = 5;
	item.iImage = 1;
	item.state = LVIS_SELECTED | LVIS_FOCUSED;

	// ���� ��� �߰� �� �÷� �߰�
	SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);							// ���� �߰�
	InsertColumn(0, _T("No"), LVCFMT_LEFT, 40);
	InsertColumn(1, _T("�δ��"), LVCFMT_LEFT, 120);
	InsertColumn(2, _T("����ȣ"), LVCFMT_CENTER, 180);
	InsertColumn(3, _T("�Ϸù�ȣ"), LVCFMT_CENTER, 180);
	InsertColumn(4, _T("ź��"), LVCFMT_CENTER, 120);
	InsertColumn(5, _T("�µ�"), LVCFMT_CENTER, 120);
	InsertColumn(6, _T("����"), LVCFMT_CENTER, 120);
	InsertColumn(7, _T("��ݷ�"), LVCFMT_CENTER, 120);
	InsertColumn(8, _T("����"), LVCFMT_CENTER, 120);
	InsertColumn(9, _T("�̻󿩺�"), LVCFMT_CENTER, 120);
	InsertColumn(10, _T("����������"), LVCFMT_CENTER, 180);
	InsertColumn(11, _T("����"), LVCFMT_CENTER, 60);
	InsertColumn(12, _T("�� ����"), LVCFMT_CENTER, 100);
	ModifyStyle(LVS_TYPEMASK, LVS_REPORT);

	CString strItem;
	// �׸� ���� 30��
	for (int i = 0; i < 30; i++) {
		strItem.Format(_T("%d"), i + 1);
		InsertItem(i, strItem);
		SetItem(i, 1, LVIF_TEXT, _T("�ѱ�"), NULL, NULL, NULL, NULL);
		SetItem(i, 2, LVIF_TEXT, _T("1430010876337"), NULL, NULL, NULL, NULL);
		SetItem(i, 3, LVIF_TEXT, _T("JN17148851"), NULL, NULL, NULL, NULL);
		SetItem(i, 4, LVIF_TEXT, _T("õ��"), NULL, NULL, NULL, NULL);
		SetItem(i, 5, LVIF_TEXT, _T("-36.5��"), NULL, NULL, NULL, NULL);
		SetItem(i, 6, LVIF_TEXT, _T("20��"), NULL, NULL, NULL, NULL);
		SetItem(i, 7, LVIF_TEXT, _T("9.8"), NULL, NULL, NULL, NULL);
		SetItem(i, 8, LVIF_TEXT, _T("����"), NULL, NULL, NULL, NULL);
		SetItem(i, 9, LVIF_TEXT, _T("�̻�"), NULL, NULL, NULL, NULL);
		SetItem(i, 10, LVIF_TEXT, _T("2028-03-21"), NULL, NULL, NULL, NULL);
		SetItem(i, 11, LVIF_TEXT, _T("C"), NULL, NULL, NULL, NULL);
		// SetBtn 12
	}

	
}


BEGIN_MESSAGE_MAP(MY_GridListCtrl, CListCtrl)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_DRAWITEM()
END_MESSAGE_MAP()



// MY_GridListCtrl message handlers




int MY_GridListCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CListCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	return 0;
}


void MY_GridListCtrl::OnDestroy()
{
	CListCtrl::OnDestroy();

	// TODO: Add your message handler code here
}

