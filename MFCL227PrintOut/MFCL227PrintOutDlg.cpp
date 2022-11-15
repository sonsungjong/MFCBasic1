
// MFCL227PrintOutDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCL227PrintOut.h"
#include "MFCL227PrintOutDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCL227PrintOutDlg dialog



CMFCL227PrintOutDlg::CMFCL227PrintOutDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCL227PRINTOUT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}



void CMFCL227PrintOutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PRINTER_LIST, m_printer_list);
}

BEGIN_MESSAGE_MAP(CMFCL227PrintOutDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCL227PrintOutDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCL227PrintOutDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_TEST_BTN, &CMFCL227PrintOutDlg::OnBnClickedTestBtn)
END_MESSAGE_MAP()


// CMFCL227PrintOutDlg message handlers

BOOL CMFCL227PrintOutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_normal_font.CreateFont(34, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("����ü"));
	m_title_font.CreateFont(60, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("����ü"));

	// �ý��ۿ� ��ġ�� ������ ������ �о ����� �����Ѵ�
	GetRegisteredPrinterList();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCL227PrintOutDlg::OnPaint()
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
HCURSOR CMFCL227PrintOutDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCL227PrintOutDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}


void CMFCL227PrintOutDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}

void CMFCL227PrintOutDlg::GetRegisteredPrinterList()
{
	TCHAR temp_string[4096] = { 0, };
	TCHAR detail_info[80] = { 0, };
	GetProfileString(_T("devices"), NULL, _T(""), temp_string, 4096);
	CString insert_data;

	TCHAR* p_next_string = temp_string;
	while (*p_next_string != '\0' || *(p_next_string + 1) != '\0')
	{
		GetProfileString(_T("devices"), p_next_string, _T(""), detail_info, 80);
		insert_data.Format(_T("%s,%s"), p_next_string, detail_info);
		m_printer_list.AddString(insert_data);
		p_next_string = p_next_string + _tcslen(p_next_string) + 1;
	}

	// �⺻ ������ �̸��� ��´�
	GetProfileString(_T("Windows"), _T("device"), _T(",,,"), temp_string, 80);
	int index = m_printer_list.FindString(-1, temp_string);
	if (index != CB_ERR) {
		m_printer_list.SetCurSel(index);
	}
}

void CMFCL227PrintOutDlg::GetPrinterName(CString* ap_driver_name, CString* ap_device_name)
{
	int index = m_printer_list.GetCurSel();
	if (index != CB_ERR) {
		CString printer_info;
		m_printer_list.GetLBText(index, printer_info);
		
		TCHAR *p_driver_string, *p_device_string;
		TCHAR* p_next_position = NULL, * p_current_position = (TCHAR*)(const TCHAR*)printer_info;

		// ��ġ �̸��� �и��Ѵ�. ��ġ �̸��� ù ��° ';' ���ڱ����̴�
		if ((p_next_position = _tcschr(p_current_position, ',')) != NULL)
		{
			p_device_string = new TCHAR[p_next_position - p_current_position + 1];
			memcpy(p_device_string, p_current_position, (p_next_position - p_current_position) << 1);
			// NULL ���ڸ� �߰��Ѵ�
			p_device_string[p_next_position - p_current_position] = '\0';
			p_current_position = p_next_position + 1;

			// ����̺� �̸��� �и��Ѵ�. ��ġ �̸� �ڿ� ������ ù ',' ���ڱ����� ����̹� �̸��̴�
			if ((p_next_position = _tcschr(p_current_position, ',')) != NULL) {
				// ����̹� �̸��� �����ϱ� ���� �޸� �Ҵ�
				p_driver_string = new TCHAR[p_next_position - p_current_position + 1];
				memcpy(p_driver_string, p_current_position, (p_next_position - p_current_position) << 1);
				// NULL���� �߰�
				p_driver_string[p_next_position - p_current_position] = '\0';

				// ����̹� �̸��� �����Ѵ�. ����̹� �̸��� "winspool"������ ���� ������
				*ap_driver_name = p_device_string;
				// ��ġ �̸��� �����Ѵ�. ��ġ �̸��� "Microsoft XPS Document Writer" ������ ���� ������
				*ap_device_name = p_driver_string;

				// ����̹� �̸� �и��� ����� �޸� ����
				delete[] p_driver_string;
			}
			// ��ġ �̸� �и��� ����� �޸� ����
			delete[] p_device_string;
		}
	}
}



void CMFCL227PrintOutDlg::OnBnClickedTestBtn()
{
	CString driver_name, device_name;
	GetPrinterName(&driver_name, &device_name);

	// ��ġ �̸��� ����̹� �̸��� ����ؼ� ������ �μ�� DC�� �����Ѵ�
	HDC h_printer_dc = ::CreateDC(device_name, driver_name, NULL, NULL);
	if (h_printer_dc != NULL) {
		// HDC ���� ����ؼ� CDC �ӽ� ��ü�� �����Ѵ�.
		CDC* pDC = CDC::FromHandle(h_printer_dc);
		// �����ͷ� ���� �μ� ������ �����Ѵ�
		static DOCINFO di = { sizeof(DOCINFO), _T("�׽�Ʈ �μ�"), NULL };
		// ������ �۾��� �����Ѵ�
		if (StartDoc(h_printer_dc, &di) > 0) {
			if (StartPage(h_printer_dc) > 0) {
				CPen line_pen(PS_SOLID, 2, RGB(0, 0, 0));
				CPen* p_old_pen = pDC->SelectObject(&line_pen);
				// ��¸�� ���� MM_LOMETRIC : 0.1mm, (x->, y ��)
				int old_mode = pDC->SetMapMode(MM_LOMETRIC);

				CFont* p_old_font = pDC->SelectObject(&m_title_font);
				pDC->TextOut(650, -210, _T("�μ⸦ �׽�Ʈ ���Դϴ�"));
				pDC->TextOut(800, -2750, _T("ȸ���̸�"));

				pDC->SelectObject(&m_normal_font);
				pDC->TextOut(840, -340, _T("2022�� 11�� 15��"));
				pDC->TextOut(1280, -500, _T("�� �� �� : �� �� ��"));

				pDC->Rectangle(320, -550, 1657, -2700);		// �ܰ�����

				pDC->MoveTo(320, -2440);
				pDC->LineTo(1657, -2440);		// ���μ�

				pDC->MoveTo(600, -2520);
				pDC->LineTo(1657, -2520);		// ���μ�

				pDC->TextOut(430, -2560, _T("����"));
				pDC->MoveTo(600, -2440);
				pDC->LineTo(600, -2700);			// ���μ�

				pDC->TextOut(703, -2460, _T("���"));
				pDC->MoveTo(865, -2440);
				pDC->LineTo(865, -2700);			// ���μ�

				pDC->TextOut(968, -2460, _T("����"));
				pDC->MoveTo(1130, -2440);
				pDC->LineTo(1130, -2700);		// ���μ�

				pDC->TextOut(1233, -2460, _T("�̻�"));
				pDC->MoveTo(1395, -2440);
				pDC->LineTo(1395, -2700);		// ���μ�

				pDC->TextOut(1490, -2460, _T("��ǥ"));

				EndPage(h_printer_dc);

				pDC->SelectObject(p_old_font);
				pDC->SelectObject(p_old_pen);
				pDC->SetMapMode(old_mode);
				line_pen.DeleteObject();
			}
			EndDoc(h_printer_dc);
		}
		::DeleteDC(h_printer_dc);
	}
}
