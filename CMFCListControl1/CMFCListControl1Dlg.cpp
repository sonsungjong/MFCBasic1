
// CMFCListControl1Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "CMFCListControl1.h"
#include "CMFCListControl1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCMFCListControl1Dlg::CCMFCListControl1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CMFCLISTCONTROL1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCMFCListControl1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SCORE_LIST, m_score_list);
}

BEGIN_MESSAGE_MAP(CCMFCListControl1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CCMFCListControl1Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CCMFCListControl1Dlg::OnBnClickedCancel)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CCMFCListControl1Dlg message handlers

BOOL CCMFCListControl1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	// �÷� ��
	const wchar_t* p_column_name[MAX_COLUMN_COUNT] = {
		L"�й�", L"�̸�", L"����", L"����", L"����", L"���", L"����"
	};
	// �÷� ũ��
	int column_width_list[MAX_COLUMN_COUNT] = { 70, 90, 60, 60, 60, 60, 60 };
	// ����Ʈ ��Ʈ�ѿ� �÷� �߰�
	for (int i = 0; i < MAX_COLUMN_COUNT; i++) {
		m_score_list.InsertColumn(i, p_column_name[i], LVCFMT_CENTER, column_width_list[i]);
	}

	// �̸�
	const wchar_t* p_name_list[MAX_ROW_COUNT] = {
		L"�ѹ���", L"�輭��", L"�̵���", L"������", L"�̽ÿ�", L"������", L"���ֿ�",
		L"����ȣ", L"������", L"���ؿ�", L"���ؼ�", L"�̰ǿ�", L"�赵��", L"������",
		L"������", L"�ڿ���", L"�輱��", L"�̼���", L"������", L"�迬��", L"�ڹ���",
		L"������", L"������", L"������", L"������", L"�ڽ¿�", L"�̽���", L"������",
		L"����ȯ", L"������", L"���¹�", L"Ȳ����", L"������", L"������", L"�ڹμ�",
	};

	wchar_t student_number[7] = { 0, };				// �й�
	wchar_t score_value[8] = { 0, };

	// ���� ���ذ�
	srand(GetTickCount64());
	int value = 0, total = 0, ranking_list[MAX_ROW_COUNT] = { 1, };
	double average_list[MAX_ROW_COUNT] = { 0.0, };

	for (int i = 0; i < MAX_ROW_COUNT; i++) {
		memset(student_number, 0, sizeof(student_number));
		swprintf_s(student_number, 7, L"%06d", 230301 + i);						// �й�
		m_score_list.InsertItem(i, student_number);				// 0�� �׸� (�й�)
		m_score_list.SetItemText(i, 1, p_name_list[i]);				// i��° ���� 1�� �׸����� �߰� (�̸�)

		// ����(30~100)���� ����,����,���� ���� ���� + �������
		total = 0;
		for (int j = 2; j <= 4; j++) {
			value = 30 + rand() % 71;				// 30~100
			total += value;
			memset(score_value, 0, sizeof(score_value));
			swprintf_s(score_value, 8, L"%d", value);
			m_score_list.SetItemText(i, j, score_value);
		}

		// ��� ���
		average_list[i] = total / 3.0;
		ranking_list[i] = 1;
		memset(score_value, 0, sizeof(score_value));
		swprintf_s(score_value, 8, L"%.2f", average_list[i]);
		m_score_list.SetItemText(i, 5, score_value);
	}

	// ������� ���� ��� (sorting)
	for (int i = 0; i < MAX_ROW_COUNT; i++) {
		for (int sub_i = i + 1; sub_i < MAX_ROW_COUNT; sub_i++) {
			if (average_list[i] != average_list[sub_i]) {
				if (average_list[i] > average_list[sub_i]) {
					ranking_list[sub_i]++;
				}
				else {
					ranking_list[i]++;
				}
			}
		}
	}

	// ������ ����
	for (int i = 0; i < MAX_ROW_COUNT; i++) {
		memset(score_value, 0, sizeof(score_value));
		swprintf_s(score_value, 8, L"%d", ranking_list[i]);
		m_score_list.SetItemText(i, 6, score_value);				// 6��° �÷����� ������ �߰�
	}

	// CMFCListControl �Ӽ��߰�
	m_score_list.ModifyStyle(LVS_TYPEMASK, LVS_REPORT);
	m_score_list.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_score_list.EnableMarkSortedColumn();				// ���� �÷� ����ǥ�� (�⺻�� : ���� ȸ��)
	m_score_list.SetSortColumn(0);							// 0��° �÷� �������� �������� ����

	return TRUE;
}

void CCMFCListControl1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCMFCListControl1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCMFCListControl1Dlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CCMFCListControl1Dlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void CCMFCListControl1Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here

}
