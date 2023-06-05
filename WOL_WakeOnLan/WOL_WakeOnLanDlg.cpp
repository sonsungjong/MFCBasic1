
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
Wake On Lan (WOL) ����� ����Ϸ��� ���� ��Ʈ��ũ(WOL ���� ���� ��ī�� ����)�� ����ؾ��Ѵ�.
WOL ������Ŷ�� �����ϴ� ��ǻ�Ϳ� ���� ��Ʈ��ũ�� �����ؾ��ϱ� ������ ���� ��곪 �����⿡ �־�� �����Ѵ�.
�� ���� �����⸦ �����ؼ� ������ �� �븦 APó�� ����ϴ� ��쿡�� ���� �ٸ� �����⿡ ��ǻ�Ͱ� ����Ǿ� �־ �� ���� ������ ó���ȴ�.
������������ �����ϰ� �����Ѵ�.

1. ��� ��ǻ���� MAC Address �� IP Address�� �����Ѵ�
	- ipconfig /all -> ������ �ּ�
	- 

2. ��� ��ǻ�Ͱ� WOL�� ����� �� �ֵ��� �����ؾ� �Ѵ�.
	- Windows PowerShell�� �����Ͽ� powercfg -devicequery wake_armed ��� �Է��ؼ� WOL����� Ȱ��ȭ
		(�Ǵ� '������' -> '��Ʈ��ũ �� ���� ����' -> '��� ���� ����' -> �ش� ��ǻ���� ��Ʈ��ũ ��͸� ���� Ŭ�� -> '�Ӽ�' -> '����' -> '���� ����' -> '�� ��ġ�� ����Ͽ� ��ǻ���� ��� ��带 ������ �� ����' �׸� ����)
	- ������ -> �����ɼ� -> ���������۵����� -> ���������ѱ� -> ����

3. WOL �����纰 BIOS ����
	- Asrock UEFI : Advanced -> ACPI Configuration -> PCI Devices Power On -> Enabled
	- �Ｚ : ��� -> PME�� ���� ��� -> �����
	- LG : LAN Power Under S3 �� LAN Power On -> LAN Power Under S4/S5 �� LAN Power On -> Wake on Lan from S4/S5 �� Enabled -> Wake Up by PCIE Device from S4/S5 �� Enabled
	- HP : Advanced -> Wake on PCI Device from S5 -> Enabled
	- ASUS : Power APM PCI/PCI-E enable -> Power APM Configuration -> Power On By Devices -> Enabled
	- GIGABYTE : Power Management Setup -> PME Event Wake Up -> Enabled

4. ��� ��ǻ�� ����
	shutdown /s /f /t 0
	(�ִ� ���� ���� shutdown /h)

5. WOL ���α׷� �����
	��� ��ǻ���� MAC Address �� IP Address�� ������ ��ǻ�ʹ� �Ҵ�
*/



CWOLWakeOnLanDlg::CWOLWakeOnLanDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WOL_WAKEONLAN_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	// ���� ���̺귯�� ����
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
	WSACleanup();				// ���� ���̺귯�� ����
}


void CWOLWakeOnLanDlg::OnBnClickedWakeBtn()
{
	CString str;
	GetDlgItemText(IDC_MAC_EDIT, str);
	UINT8 mac_value[6];
	// ���ڿ��� ������ MAC Address ���� 6���� ���ڸ� �и��Ѵ�
	int count = _stscanf_s(str.GetBuffer(), _T("%hhx-%hhx-%hhx-%hhx-%hhx-%hhx"), mac_value, mac_value + 1, mac_value + 2, mac_value + 3, mac_value + 4, mac_value + 5);

	if (count < 6) {				// MAC Address ���Ŀ� ������ �ִ� ���
		MessageBox(_T("12-34-56-78-90-AA ó�� 6���� 16������ �Է����ּ���."), _T("MAC Address�� �߸� �ԷµǾ����ϴ�."), MB_ICONSTOP);
		return;
	}

	char ip_address[24];
	int port = 9;
	GetDlgItemTextA(m_hWnd, IDC_IP_EDIT, ip_address, 24);				// IP�� �����´�
	SOCKET h_socket = socket(AF_INET, SOCK_DGRAM, 0);					// Wake On Lan ���� ����

	// ���������� ������ ��Ʈ��ũ ��ġ�� ���� ������ ����Ѵ�.
	struct sockaddr_in srv_addr;
	memset(&srv_addr, 0, sizeof(struct sockaddr_in));
	srv_addr.sin_family = AF_INET;
	srv_addr.sin_addr.s_addr = inet_addr(ip_address);						// �Է��� IP �ּҷ� Wake on Lan ���������� �����Ѵ�
	srv_addr.sin_port = htons(port);													// ��Ʈ�� 9�� ��Ʈ�� ���

	// ��Ŷ ��Ŷ ���� (0xFF 6�ڸ� ���� Ű���� �ϴ� ��ǻ���� MAC �ּ� 16�� �ݺ�
	UINT8 send_data[6 * 17];			// ���� ��Ŷ�� ũ�� (102byte) �Ҵ�

	for (int i = 0; i < 6; i++) {
		send_data[i] = (UINT8)0xFF;
	}

	for (int i = 1; i < 17; i++) {
		memcpy(send_data + i * 6, mac_value, 6);
	}

	// �ۼ��� ���� ��Ŷ�� ��� ��ǻ�ͷ� �����Ѵ�
	sendto(h_socket, (char*)send_data, sizeof(send_data), 0, (LPSOCKADDR)&srv_addr, sizeof(srv_addr));
	closesocket(h_socket);						// ���� �ݱ�
}


// �� ��ǻ���� MAC Address �� �޽��� �ڽ��� ������
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

		// Mac �ּ� ���ڿ��� ����
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

// �� ��ǻ���� IP Address�� �޽��� �ڽ��� ������
void CWOLWakeOnLanDlg::OnBnClickedGetIp()
{
	// WSAStartup�� ����� ��
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
