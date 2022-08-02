
// MFCL123Thread1Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCL123Thread1.h"
#include "MFCL123Thread1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 멀티쓰레드를 사용할 땐 GetDlg에서 객체형태로 반환되는 것들은 사용안해야한다.
// 메인쓰레드가 쉴 때 지워버려 버그를 유발한다.
// 값을 가져오는 정도 GetDlgItemInt 같은 것들만 써야함



CMFCL123Thread1Dlg::CMFCL123Thread1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCL123THREAD1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCL123Thread1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATA_LIST, m_data_list);
}

BEGIN_MESSAGE_MAP(CMFCL123Thread1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCL123Thread1Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCL123Thread1Dlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_TEST_BTN, &CMFCL123Thread1Dlg::OnBnClickedTestBtn)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CMFCL123Thread1Dlg 메시지 처리기

BOOL CMFCL123Thread1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_thread_data.p_list_box = &m_data_list;
	m_thread_data.h_kill_event = CreateEvent(NULL, 1, 0, _T("Sung"));
	m_thread_data.h_thread = NULL;

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCL123Thread1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCL123Thread1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCL123Thread1Dlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CDialogEx::OnOK();
}


void CMFCL123Thread1Dlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}

DWORD WINAPI ThreadProc1(LPVOID lpParameter)
{
	ThreadData* p_data = (ThreadData*)lpParameter;
	CString str;			// 내부적으로 동적할당, 객체파괴자에서 메모리해제를 해줘야함
	int index;

	for (size_t i = 0; i < 10000; i++)
	{
		if (WaitForSingleObject(p_data->h_kill_event, 10) == WAIT_OBJECT_0)		// 20ms마다 h_kill_event 체크
		{
			break;
		}
		str.Format(_T("Item %05d"), i);
		index = p_data->p_list_box->InsertString(-1, str);			// 맨뒤에 추가된 문자열의 위치를 저장
		p_data->p_list_box->SetCurSel(index);						// 커서 이동
	}

	CloseHandle(p_data->h_thread);
	p_data->h_thread = NULL;

	return 0;
}

void CMFCL123Thread1Dlg::OnBnClickedTestBtn()
{
	//CString str;
	//int index;

	//for (size_t i = 0; i < 10000; i++)
	//{
	//	str.Format(_T("Item %05d"), i);
	//	index = m_data_list.InsertString(-1, str);			// 맨뒤에 추가된 문자열의 위치를 저장
	//	m_data_list.SetCurSel(index);						// 커서 이동
	//}
	
	m_thread_data.h_thread = CreateThread(NULL, 0, ThreadProc1, &m_thread_data, 0, NULL);					// 1MB (1024*1024)
}


void CMFCL123Thread1Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	//if (mh_thread != NULL)
		//TerminateThread(mh_thread, 0);			// 강제로 비정상종료 (동적할당 메모리누수) 예를들어 CString

	// 메인쓰레드와 워크쓰레드가 통신할 수 있게 만들어 동기화를 시키면 정상종료를 할 수 있음
	if (m_thread_data.h_thread != NULL)
	{
		SetEvent(m_thread_data.h_kill_event);			// kill이벤트 활성화 (1)

		MSG msg;

		while (m_thread_data.h_thread != NULL && GetMessage(&msg, NULL, 0, 0))				// 무한루프로 정상종료될때까지 무한루프
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// AfxMessageBox(_T("워크쓰레드 정상 종료 후 메인쓰레드 종료!"));
	}
}
