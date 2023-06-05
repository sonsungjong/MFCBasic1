
// WOL_WakeOnLanDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "WOL_WakeOnLan.h"
#include "WOL_WakeOnLanDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


/*
Wake On Lan (WOL) 기능을 사용하려면 유선 네트워크(WOL 지원 무선 랜카드 가능)를 사용해야한다.
WOL 매직패킷을 전송하는 컴퓨터와 같은 네트워크상에 존재해야하기 때문에 같은 허브나 공유기에 있어야 동작한다.
두 대의 공유기를 연결해서 공유기 한 대를 AP처럼 사용하는 경우에는 서로 다른 공유기에 컴퓨터가 연결되어 있어도 한 개의 망으로 처리된다.
리눅스에서도 동일하게 동작한다.

1. 대상 컴퓨터의 MAC Address 와 IP Address를 얻어야한다
	- ipconfig /all -> 물리적 주소
	- 

2. 대상 컴퓨터가 WOL을 사용할 수 있도록 설정해야 한다.
	- Windows PowerShell을 실행하여 powercfg -devicequery wake_armed 라고 입력해서 WOL기능을 활성화
		(또는 '제어판' -> '네트워크 및 공유 센터' -> '어뎁터 설정 변경' -> 해당 컴퓨터의 네트워크 어뎁터를 더블 클릭 -> '속성' -> '구성' -> '전원 관리' -> '이 장치를 사용하여 컴퓨터의 대기 모드를 종료할 수 있음' 항목 선택)
	- 제어판 -> 전원옵션 -> 전원단추작동설정 -> 빠른시작켜기 -> 해제

3. WOL 제조사별 BIOS 설정
	- Asrock UEFI : Advanced -> ACPI Configuration -> PCI Devices Power On -> Enabled
	- 삼성 : 고급 -> PME에 의해 깨어남 -> 사용함
	- LG : LAN Power Under S3 를 LAN Power On -> LAN Power Under S4/S5 를 LAN Power On -> Wake on Lan from S4/S5 을 Enabled -> Wake Up by PCIE Device from S4/S5 를 Enabled
	- HP : Advanced -> Wake on PCI Device from S5 -> Enabled
	- ASUS : Power APM PCI/PCI-E enable -> Power APM Configuration -> Power On By Devices -> Enabled
	- GIGABYTE : Power Management Setup -> PME Event Wake Up -> Enabled

4. 대상 컴퓨터 끄기
	shutdown /s /f /t 0
	(최대 절전 모드는 shutdown /h)

5. WOL 프로그램 만들기
	대상 컴퓨터의 MAC Address 와 IP Address로 지정한 컴퓨터는 켠다
*/



CWOLWakeOnLanDlg::CWOLWakeOnLanDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WOL_WAKEONLAN_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	// 소켓 라이브러리 실행
	WSADATA wsadata;
	WSAStartup(0x0202, &wsadata);
}

void CWOLWakeOnLanDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CWOLWakeOnLanDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CWOLWakeOnLanDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CWOLWakeOnLanDlg::OnBnClickedCancel)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_WAKE_BTN, &CWOLWakeOnLanDlg::OnBnClickedWakeBtn)
	ON_BN_CLICKED(IDC_GET_MAC_ADDRESS, &CWOLWakeOnLanDlg::OnBnClickedGetMacAddress)
	ON_BN_CLICKED(IDC_GET_IP, &CWOLWakeOnLanDlg::OnBnClickedGetIp)
END_MESSAGE_MAP()


// CWOLWakeOnLanDlg message handlers

BOOL CWOLWakeOnLanDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWOLWakeOnLanDlg::OnPaint()
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
HCURSOR CWOLWakeOnLanDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CWOLWakeOnLanDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CWOLWakeOnLanDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void CWOLWakeOnLanDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	WSACleanup();				// 소켓 라이브러리 종료
}


void CWOLWakeOnLanDlg::OnBnClickedWakeBtn()
{
	CString str;
	GetDlgItemText(IDC_MAC_EDIT, str);
	UINT8 mac_value[6];
	// 문자열로 구성된 MAC Address 에서 6개의 숫자르 분리한다
	int count = _stscanf_s(str.GetBuffer(), _T("%hhx-%hhx-%hhx-%hhx-%hhx-%hhx"), mac_value, mac_value + 1, mac_value + 2, mac_value + 3, mac_value + 4, mac_value + 5);

	if (count < 6) {				// MAC Address 형식에 문제가 있는 경우
		MessageBox(_T("12-34-56-78-90-AA 처럼 6개의 16진수로 입력해주세요."), _T("MAC Address가 잘못 입력되었습니다."), MB_ICONSTOP);
		return;
	}

	char ip_address[24];
	int port = 9;
	GetDlgItemTextA(m_hWnd, IDC_IP_EDIT, ip_address, 24);				// IP를 가져온다
	SOCKET h_socket = socket(AF_INET, SOCK_DGRAM, 0);					// Wake On Lan 소켓 생성

	// 프로토콜을 전송할 네트워크 장치에 대한 정보를 등록한다.
	struct sockaddr_in srv_addr;
	memset(&srv_addr, 0, sizeof(struct sockaddr_in));
	srv_addr.sin_family = AF_INET;
	srv_addr.sin_addr.s_addr = inet_addr(ip_address);						// 입력한 IP 주소로 Wake on Lan 프로토콜을 전송한다
	srv_addr.sin_port = htons(port);													// 포트는 9번 포트를 사용

	// 매킷 패킷 생성 (0xFF 6자리 이후 키고자 하는 컴퓨터의 MAC 주소 16번 반복
	UINT8 send_data[6 * 17];			// 매직 패킷의 크기 (102byte) 할당

	for (int i = 0; i < 6; i++) {
		send_data[i] = (UINT8)0xFF;
	}

	for (int i = 1; i < 17; i++) {
		memcpy(send_data + i * 6, mac_value, 6);
	}

	// 작성한 매직 패킷을 대상 컴퓨터로 전송한다
	sendto(h_socket, (char*)send_data, sizeof(send_data), 0, (LPSOCKADDR)&srv_addr, sizeof(srv_addr));
	closesocket(h_socket);						// 소켓 닫기
}


// 이 컴퓨터의 MAC Address 를 메시지 박스로 보여줌
void CWOLWakeOnLanDlg::OnBnClickedGetMacAddress()
{
#pragma comment(lib, "iphlpapi.lib")

	IP_ADAPTER_INFO adapter_info[16];
	DWORD buffer_len = sizeof(adapter_info);

	DWORD status = GetAdaptersInfo(adapter_info, &buffer_len);
	if (status != ERROR_SUCCESS) {
		TCHAR msg[256] = { 0, };
		_stprintf_s(msg, 256, _T("%ld"), status);
		MessageBox(msg, _T("Get AdaptersInfo Error"), MB_ICONSTOP);
		return;
	}

	PIP_ADAPTER_INFO p_adapter_info = adapter_info;
	while (p_adapter_info) {
		// AA-BB-CC-DD-EE-FF
		TCHAR mac[18] = { 0, };
		char str[256] = { 0, };
		CString wstr;
		sprintf(str, "%s(%s) : ", p_adapter_info->Description, p_adapter_info->IpAddressList.IpAddress.String);
		wstr = str;

		// Mac 주소 문자열로 구성
		for (int i = 0; i < 6; ++i) {
			_stprintf_s(mac + i * 3, 3, _T("%02X"), p_adapter_info->Address[i]);
			if (i != 5) {
				mac[i * 3 + 2] = '-';
			}
		}
		MessageBox(mac, wstr, MB_OK);
		p_adapter_info = p_adapter_info->Next;
	}
}

// 이 컴퓨터의 IP Address를 메시지 박스로 보여줌
void CWOLWakeOnLanDlg::OnBnClickedGetIp()
{
	// WSAStartup이 실행된 후
	TCHAR myip[256] = { 0, };
	char host_name[255] = { 0, };
	if (gethostname(host_name, sizeof(host_name) == 0)) {
		PHOSTENT phost_info = gethostbyname(host_name);
		if (phost_info != NULL) {
			for (int i = 0; phost_info->h_addr_list[i] != NULL; i++)
			{
				int ip[4] = { 0, };
				in_addr* p_addr = (in_addr*)phost_info->h_addr_list[i];
				ip[0] = p_addr->S_un.S_un_b.s_b1;
				ip[1] = p_addr->S_un.S_un_b.s_b2;
				ip[2] = p_addr->S_un.S_un_b.s_b3;
				ip[3] = p_addr->S_un.S_un_b.s_b4;
				_stprintf_s(myip, 256, _T("%d.%d.%d.%d"), ip[0], ip[1], ip[2], ip[3]);
			}
		}
	}

	MessageBox(myip, myip, MB_OK);
}
