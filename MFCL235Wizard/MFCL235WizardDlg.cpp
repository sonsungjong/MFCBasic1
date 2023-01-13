
// MFCL235WizardDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCL235Wizard.h"
#include "MFCL235WizardDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCL235WizardDlg dialog



CMFCL235WizardDlg::CMFCL235WizardDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCL235WIZARD_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCL235WizardDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCL235WizardDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCL235WizardDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCL235WizardDlg::OnBnClickedCancel)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_PREV_BTN, &CMFCL235WizardDlg::OnBnClickedPrevBtn)
	ON_BN_CLICKED(IDC_NEXT_BTN, &CMFCL235WizardDlg::OnBnClickedNextBtn)
END_MESSAGE_MAP()


// CMFCL235WizardDlg message handlers

void CMFCL235WizardDlg::AddPage(CDialogEx* ap_page, int a_index, int a_dlg_id)
{
	mp_page[a_index] = ap_page;
	mp_page[a_index]->Create(a_dlg_id, this);
	mp_page[a_index]->SetWindowPos(NULL, m_wizard_rect.left, m_wizard_rect.top, m_wizard_rect.Width(), m_wizard_rect.Height(), 0);
}

BOOL CMFCL235WizardDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	GetDlgItem(IDC_WIZARD_RECT)->GetWindowRect(m_wizard_rect);
	ScreenToClient(m_wizard_rect);

	AddPage(new WizardPage1, 0, IDD_PAGE1);
	AddPage(new WizardPage2, 1, IDD_PAGE2);
	AddPage(new WizardPage3, 2, IDD_PAGE3);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCL235WizardDlg::OnPaint()
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
HCURSOR CMFCL235WizardDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCL235WizardDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CMFCL235WizardDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void CMFCL235WizardDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	for (int i = 0; i < MAX_PAGE_COUNT; i++) {
		mp_page[i]->DestroyWindow();
		delete mp_page[i];
		mp_page[i] = NULL;
	}
}

// 이전 페이지
void CMFCL235WizardDlg::OnBnClickedPrevBtn()
{
	if (m_page_index > 0) {
		m_page_index--;
		mp_page[m_page_index]->ShowWindow(SW_SHOWNA);						// Show Not Active
		mp_page[m_page_index +1]->ShowWindow(SW_HIDE);						// 하이드

		if (m_page_index == 0) { GetDlgItem(IDC_PREV_BTN)->EnableWindow(FALSE); }
		else if (m_page_index == (MAX_PAGE_COUNT -2)) { GetDlgItem(IDC_NEXT_BTN)->EnableWindow(TRUE); }
	}
}

// 다음 페이지
void CMFCL235WizardDlg::OnBnClickedNextBtn()
{
	if (m_page_index < MAX_PAGE_COUNT - 1) {
		m_page_index++;
		mp_page[m_page_index]->ShowWindow(SW_SHOWNA);
		mp_page[m_page_index -1]->ShowWindow(SW_HIDE);						// 하이드

		if (m_page_index == (MAX_PAGE_COUNT - 1)) { GetDlgItem(IDC_NEXT_BTN)->EnableWindow(FALSE); }
		else if (m_page_index == 1) { GetDlgItem(IDC_PREV_BTN)->EnableWindow(TRUE); }

		// 각 페이지별 작업을 정의한다 (Next버튼)
		if (m_page_index == 1) {
			// 첫번째 페이지에선 숫자를 가져온다
			// m_num1 = mp_page[m_page_index-1]->GetDlgItemInt(IDC_EDIT1);
			// m_num2 = mp_page[m_page_index-1]->GetDlgItemInt(IDC_EDIT2);
			((WizardPage1*)mp_page[m_page_index-1])->GetNumData(&m_num1, &m_num2);
		}
		else if (m_page_index == 2) {
			// 두번째 페이지에선 연산자를 가져온다
			int oper = ((WizardPage2*)mp_page[m_page_index - 1])->GetOpType();
			int result = 0;

			switch (oper) {
			case 0:
				result = m_num1 + m_num2;
				break;
			case 1:
				result = m_num1 - m_num2;
				break;
			case 2:
				result = m_num1 * m_num2;
				break;
			case 3:
				if (m_num2 != 0) result = m_num1 / m_num2;
				else result = 0;
				break;
			}
			//mp_page[m_page_index]->SetDlgItemInt(IDC_RESULT_EDIT, result);
			((WizardPage3*)mp_page[m_page_index])->SetResultValue(result);
		}
	}
}
