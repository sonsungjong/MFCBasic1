// InputData.cpp : implementation file
//

#include "pch.h"
#include "GdipUserControl1.h"
#include "afxdialogex.h"
#include "DCP.h"
#include "InputData.h"


// InputData dialog

IMPLEMENT_DYNAMIC(InputData, CDialogEx)

InputData::InputData(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_INPUT_DATA_DLG, pParent)
{

}

InputData::~InputData()
{
}

void InputData::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(InputData, CDialogEx)
	ON_BN_CLICKED(IDOK, &InputData::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &InputData::OnBnClickedCancel)
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_LOAD_FILE_BTN, &InputData::OnBnClickedLoadFileBtn)
END_MESSAGE_MAP()


// InputData message handlers


void InputData::OnBnClickedOk()
{
	// 파일을 읽고 입력값과 구조체에 셋팅해서 MySQL에 저장
	CDialogEx::OnOK();
}


void InputData::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}

BOOL InputData::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	GetClientRect(&m_input_data_size);
	m_dcp.CreateDCP(m_input_data_size.Width(), m_input_data_size.Height());
	m_dcp.Clear(RGB24(50, 70, 90));
	m_dcp.FillSolidRect(0, 0, m_input_data_size.Width(), 40, RGB24(30, 50, 70));
	m_dcp.DCPTextSetting(_T("맑은 고딕"), 14);
	m_dcp.DCPText(7, 7, _T("유도탄 생산데이터 입력"), RGB24(255, 255, 255));

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void InputData::OnPaint()
{
	CPaintDC dc(this);

	// 끝
	m_dcp.Draw(dc);
}




void InputData::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
}


HBRUSH InputData::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	UINT nID = pWnd->GetDlgCtrlID();

	switch (nID) {
	case IDC_STATIC:
		pDC->SetBkMode(TRANSPARENT);
		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);
		break;
	}

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}



void InputData::OnBnClickedLoadFileBtn()
{
	
}
