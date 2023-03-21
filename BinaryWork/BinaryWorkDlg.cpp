#include "pch.h"
#include "framework.h"
#include "BinaryWork.h"
#include "BinaryWorkDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CBinaryWorkDlg::CBinaryWorkDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BINARYWORK_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


void CBinaryWorkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBinaryWorkDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CBinaryWorkDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CBinaryWorkDlg::OnBnClickedCancel)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CBinaryWorkDlg message handlers

BOOL CBinaryWorkDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	SetBackgroundColor(RGB(98, 102, 120));
	m_bin_list.SubclassDlgItem(IDC_DATA_LIST, this);

	FILE* p_file = NULL;
	if (0 == _tfopen_s(&p_file, _T("tips.xls"), _T("rb")))				// tips.xls 파일을 연다
	{
		fseek(p_file, 0, SEEK_END);			// 파일 내용의 끝으로 이동
		m_file_size = ftell(p_file);				// 파일 크기를 얻는다
		fseek(p_file, 0, SEEK_SET);				// 파일 처음으로 복귀

		mp_file_data = new UINT8[m_file_size];					// 파일 크기만큼 메모리 할당
		fread(mp_file_data, 1, m_file_size, p_file);				// 내용 복사
		fclose(p_file);				// 파일 닫기

		UINT8* p_pos = mp_file_data;
		BDF* p_data;
		int step = m_file_size / BIN_COUNT;				// 몇 줄로 구성할지 미리 계산
		for (int i = 0; i < step; i++) {
			p_data = MakeOneLineData(i, BIN_COUNT, p_pos);				// 한줄 정보 구성
			m_bin_list.AddBinaryData(p_data);				// 리스트에 추가
			p_pos += BIN_COUNT;				// 위치를 다음 줄로 이동
		}

		int remain_count = m_file_size % BIN_COUNT;				// 남은 바이트가 있는지 확인
		if (remain_count) {					// 바이트가 남아있다면
			p_data = MakeOneLineData(step, remain_count, p_pos);			// 한줄 정보 구성
			m_bin_list.AddBinaryData(p_data);				// 리스트에 추가
		}
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBinaryWorkDlg::OnPaint()
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
HCURSOR CBinaryWorkDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CBinaryWorkDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CBinaryWorkDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void CBinaryWorkDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	if (mp_file_data != NULL) {
		delete[] mp_file_data;
	}
}

BDF* CBinaryWorkDlg::MakeOneLineData(int a_index, int a_data_size, UINT8* ap_bin_data)
{
	BDF* p_data = new BDF;

	p_data->p_bin = ap_bin_data;
	p_data->bin_data_size = a_data_size;
	p_data->str_len = _stprintf_s(p_data->str, 7, _T("%04d: "), a_index);
	for (int i = 0; i < a_data_size; i++) {
		p_data->str_len += _stprintf_s(p_data->str + p_data->str_len, 4, _T("%02hhX "), *ap_bin_data++);
	}

	return p_data;
}
