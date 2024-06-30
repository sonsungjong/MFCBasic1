
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
	CTaskDialog dlg(L"C언어 강좌 진행을 위해 필요한 정보를 선택해주세요 :)",
		L"C언어 프로그래밍에 대한 경험이 있으신가요?", L"간단한 설문조사", TDCBF_CLOSE_BUTTON, TDF_ENABLE_HYPERLINKS | TDF_USE_COMMAND_LINKS, L"최하단 문구");
	
	dlg.AddCommandControl(50, L"1. 학교 수업 대비 (&s)\nC 언어 수업이 어렵다고 해서 미리 공부를 하려한다.");
	dlg.AddCommandControl(51, L"2. 취업 준비 (&j)\nC 언어를 사용하는 개발자가 되고 싶어서 배우려고 합니다.");
	dlg.AddCommandControl(52, L"3. 업무에 필요해서 (&w)\n새로 배정받은 업무에서 사용해야 합니다.");

	const wchar_t* p_exp_table[5] = {
		L"프로그래밍 언어 공부가 처음이다.",
		L"자료형, 변수, 조건문, 반복문, 입력문, 출력문까지 공부했다.",
		L"배열과 함수 활용까지 공부했다.",
		L"포인터와 동적 메모리 할당에 대해 공부했다.",
		L"C언어 문법 전체적으로 공부 했다"
	};
	
	for (int i = 0; i < 5; i++) {
		dlg.AddRadioButton(20 + i, p_exp_table[i]);
	}
	dlg.SetMainIcon(TD_INFORMATION_ICON);
	//dlg.SetFooterIcon(TD_WARNING_ICON);

	mp_result_list->ResetContent();				// 리스트박스 내용 초기화

	int result = dlg.DoModal();
	if (result == IDCLOSE) {
		mp_result_list->InsertString(-1, L"닫기 버튼을 눌러서 설문에 응하지 않았습니다.");
	}
	else if (result >= 50 && result <= 52) {
		if (result == 50) {
			mp_result_list->InsertString(-1, L"[1. 학교 수업에 대비] 를 선택함");
		}
		else if (result == 51) {
			mp_result_list->InsertString(-1, L"[2. 취업 준비] 를 선택함");
		}
		else if (result == 52) {
			mp_result_list->InsertString(-1, L"[3. 업무에 필요해서] 를 선택함");
		}
		std::wstring str;
		str.assign(L"추가 정보 : ");
		str.append(p_exp_table[dlg.GetSelectedRadioButtonID() - 20]);

		mp_result_list->InsertString(-1, str.c_str());
		mp_result_list->InsertString(-1, L"");

		mp_result_list->InsertString(-1, L"설문에 응해주셔서 감사합니다.");
		mp_result_list->InsertString(-1, L"");
	}
}


void CMFCS001CTaskDialogDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}
