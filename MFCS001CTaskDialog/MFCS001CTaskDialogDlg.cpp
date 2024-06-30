
#include "pch.h"
#include "framework.h"
#include "MFCS001CTaskDialog.h"
#include "MFCS001CTaskDialogDlg.h"
#include "afxdialogex.h"

#include <afxtaskdialog.h>
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCS001CTaskDialogDlg dialog



CMFCS001CTaskDialogDlg::CMFCS001CTaskDialogDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCS001CTASKDIALOG_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCS001CTaskDialogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCS001CTaskDialogDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCS001CTaskDialogDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCS001CTaskDialogDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CMFCS001CTaskDialogDlg message handlers

BOOL CMFCS001CTaskDialogDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	mp_result_list = (CListBox*)GetDlgItem(IDC_LIST1);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCS001CTaskDialogDlg::OnPaint()
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
HCURSOR CMFCS001CTaskDialogDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCS001CTaskDialogDlg::OnBnClickedOk()
{
	//CDialogEx::OnOK();
	CTaskDialog dlg(L"C��� ���� ������ ���� �ʿ��� ������ �������ּ��� :)",
		L"C��� ���α׷��ֿ� ���� ������ �����Ű���?", L"������ ��������", TDCBF_CLOSE_BUTTON, TDF_ENABLE_HYPERLINKS | TDF_USE_COMMAND_LINKS, L"���ϴ� ����");
	
	dlg.AddCommandControl(50, L"1. �б� ���� ��� (&s)\nC ��� ������ ��ƴٰ� �ؼ� �̸� ���θ� �Ϸ��Ѵ�.");
	dlg.AddCommandControl(51, L"2. ��� �غ� (&j)\nC �� ����ϴ� �����ڰ� �ǰ� �; ������ �մϴ�.");
	dlg.AddCommandControl(52, L"3. ������ �ʿ��ؼ� (&w)\n���� �������� �������� ����ؾ� �մϴ�.");

	const wchar_t* p_exp_table[5] = {
		L"���α׷��� ��� ���ΰ� ó���̴�.",
		L"�ڷ���, ����, ���ǹ�, �ݺ���, �Է¹�, ��¹����� �����ߴ�.",
		L"�迭�� �Լ� Ȱ����� �����ߴ�.",
		L"�����Ϳ� ���� �޸� �Ҵ翡 ���� �����ߴ�.",
		L"C��� ���� ��ü������ ���� �ߴ�"
	};
	
	for (int i = 0; i < 5; i++) {
		dlg.AddRadioButton(20 + i, p_exp_table[i]);
	}
	dlg.SetMainIcon(TD_INFORMATION_ICON);
	//dlg.SetFooterIcon(TD_WARNING_ICON);

	mp_result_list->ResetContent();				// ����Ʈ�ڽ� ���� �ʱ�ȭ

	int result = dlg.DoModal();
	if (result == IDCLOSE) {
		mp_result_list->InsertString(-1, L"�ݱ� ��ư�� ������ ������ ������ �ʾҽ��ϴ�.");
	}
	else if (result >= 50 && result <= 52) {
		if (result == 50) {
			mp_result_list->InsertString(-1, L"[1. �б� ������ ���] �� ������");
		}
		else if (result == 51) {
			mp_result_list->InsertString(-1, L"[2. ��� �غ�] �� ������");
		}
		else if (result == 52) {
			mp_result_list->InsertString(-1, L"[3. ������ �ʿ��ؼ�] �� ������");
		}
		std::wstring str;
		str.assign(L"�߰� ���� : ");
		str.append(p_exp_table[dlg.GetSelectedRadioButtonID() - 20]);

		mp_result_list->InsertString(-1, str.c_str());
		mp_result_list->InsertString(-1, L"");

		mp_result_list->InsertString(-1, L"������ �����ּż� �����մϴ�.");
		mp_result_list->InsertString(-1, L"");
	}
}


void CMFCS001CTaskDialogDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}
