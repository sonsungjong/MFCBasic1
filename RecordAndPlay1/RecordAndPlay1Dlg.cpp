
// RecordAndPlay1Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "RecordAndPlay1.h"
#include "RecordAndPlay1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRecordAndPlay1Dlg dialog



CRecordAndPlay1Dlg::CRecordAndPlay1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RECORDANDPLAY1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	mh_wave_in = NULL;
	mh_wave_out = NULL;

	m_save_size = 0;
	m_play_index = m_playing_pos = m_play_pos = 0;
}

void CRecordAndPlay1Dlg::MakeWaveImage(short* ap_data, int a_data_size)
{
	::SetDCBrushColor(mh_image_dc, RGB(0, 0, 0));
	::SetDCPenColor(mh_image_dc, RGB(0, 0, 0));
	::Rectangle(mh_image_dc, 0, 0, m_image_rect.Width(), m_image_rect.Height());

	::SetDCPenColor(mh_image_dc, RGB(255, 255, 255));

	int cx = m_image_rect.Width(), cy = m_image_rect.Height();
	::MoveToEx(mh_image_dc, 0, (*ap_data + 32768) * cy / 65536, NULL);

	for (int i = 1; i < a_data_size; i++) {
		::LineTo(mh_image_dc, cx * i / (MAX_QUEUE_SIZE / 2), (*(ap_data + i) + 32768) * cy / 65536);
	}
}

void CRecordAndPlay1Dlg::MakeMemoryStructure()
{
	for (int i = 0; i < MAX_QUEUE_NUMBER; i++) {
		mp_block[i] = (WAVEHDR*)::HeapAlloc(GetProcessHeap(), 0, sizeof(WAVEHDR));
		mp_block[i]->lpData = (char*)::HeapAlloc(GetProcessHeap(), 0, MAX_QUEUE_SIZE);
	}
	mp_save_buffer = (char*)::HeapAlloc(GetProcessHeap(), 0, MAX_SAVE_SIZE);
}

void CRecordAndPlay1Dlg::FreeMemoryStructure()
{
	for (int i = 0; i < MAX_QUEUE_NUMBER; i++) {
		::HeapFree(GetProcessHeap(), 0, mp_block[i]->lpData);
		::HeapFree(GetProcessHeap(), 0, mp_block[i]);
	}
	::HeapFree(GetProcessHeap(), 0, mp_save_buffer);
}

void CRecordAndPlay1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CRecordAndPlay1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDOK, &CRecordAndPlay1Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CRecordAndPlay1Dlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_RECORD_START, &CRecordAndPlay1Dlg::OnBnClickedRecordStart)
	ON_BN_CLICKED(IDC_RECORD_STOP, &CRecordAndPlay1Dlg::OnBnClickedRecordStop)
	ON_BN_CLICKED(IDC_PLAY_START, &CRecordAndPlay1Dlg::OnBnClickedPlayStart)
	ON_BN_CLICKED(IDC_PLAY_STOP, &CRecordAndPlay1Dlg::OnBnClickedPlayStop)
	ON_MESSAGE(MM_WOM_DONE, &CRecordAndPlay1Dlg::OnMmWomDone)
	ON_MESSAGE(MM_WIM_DATA, &CRecordAndPlay1Dlg::OnMmWimData)
END_MESSAGE_MAP()


// CRecordAndPlay1Dlg message handlers

BOOL CRecordAndPlay1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	MakeMemoryStructure();

	GetDlgItem(IDC_IMAGE_RECT)->GetWindowRect(m_image_rect);
	ScreenToClient(m_image_rect);

	m_image.Create(m_image_rect.Width(), m_image_rect.Height(), 32);
	mh_image_dc = m_image.GetDC();

	::SelectObject(mh_image_dc, ::GetStockObject(DC_BRUSH));
	::SelectObject(mh_image_dc, ::GetStockObject(DC_PEN));

	m_wave_format.wFormatTag = WAVE_FORMAT_PCM;			// PCM
	m_wave_format.nChannels = 1;						// 마이크 녹음방식 : 모노
	m_wave_format.nSamplesPerSec = 8000;				// 샘플링주기 : 8KHz
	m_wave_format.wBitsPerSample = 16;					// 샘플링 단위 : 16Bits

	m_wave_format.nBlockAlign = m_wave_format.nChannels * m_wave_format.wBitsPerSample / 8;
	m_wave_format.nAvgBytesPerSec = m_wave_format.nSamplesPerSec * m_wave_format.nBlockAlign;
	m_wave_format.cbSize = 0;


	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CRecordAndPlay1Dlg::OnPaint()
{
		CPaintDC dc(this); // device context for painting
	if (IsIconic())
	{

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
		//CDialogEx::OnPaint();
		m_image.Draw(dc, m_image_rect.left, m_image_rect.top);
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CRecordAndPlay1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CRecordAndPlay1Dlg::OnDestroy()
{

	// TODO: Add your message handler code here
	OnBnClickedRecordStop();
	OnBnClickedPlayStop();

	m_image.ReleaseDC();
	m_image.Destroy();
	FreeMemoryStructure();

	
	CDialogEx::OnDestroy();
}


void CRecordAndPlay1Dlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CRecordAndPlay1Dlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void CRecordAndPlay1Dlg::OnBnClickedRecordStart()
{
	// TODO: Add your control notification handler code here
	if (mh_wave_out != NULL) {
		MessageBox(_T("재생 중에는 녹음을 할 수 없습니다."), _T("기능이 제한되어 있습니다."), MB_OK | MB_ICONSTOP);
		return;
	}

	if (mh_wave_in == NULL) {
		m_save_size = 0;
		for (int i = 0; i < MAX_QUEUE_NUMBER; i++) {
			mp_block[i]->dwBufferLength = MAX_QUEUE_SIZE;
			mp_block[i]->dwLoops = mp_block[i]->dwFlags = 0;
		}

		waveInOpen(&mh_wave_in, WAVE_MAPPER, &m_wave_format, (DWORD_PTR)m_hWnd, NULL, CALLBACK_WINDOW);

		for (int i = 0; i < MAX_QUEUE_NUMBER; i++) {
			waveInPrepareHeader(mh_wave_in, mp_block[i], sizeof(WAVEHDR));
			waveInAddBuffer(mh_wave_in, mp_block[i], sizeof(WAVEHDR));
		}
		waveInStart(mh_wave_in);
	}
}


void CRecordAndPlay1Dlg::OnBnClickedRecordStop()
{
	// TODO: Add your control notification handler code here
	if (mh_wave_in != NULL) {
		waveInStop(mh_wave_in);
		waveInReset(mh_wave_in);
		for (int i = 0; i < MAX_QUEUE_NUMBER; i++) {
			waveInUnprepareHeader(mh_wave_in, mp_block[i], sizeof(WAVEHDR));
		}
		waveInClose(mh_wave_in);
		mh_wave_in = NULL;
	}
}


void CRecordAndPlay1Dlg::OnBnClickedPlayStart()
{
	// TODO: Add your control notification handler code here
	if (mh_wave_in != NULL) {
		MessageBox(_T("녹음 중에는 재생을 할 수 없습니다."), _T("기능이 제한되어 있습니다."), MB_OK | MB_ICONSTOP);
		return;
	}

	if (m_save_size > 0 && mh_wave_out == NULL) {
		m_play_index = m_playing_pos = m_play_pos = 0;
		int i;
		for (i = 0; i < MAX_QUEUE_NUMBER; i++) {
			mp_block[i]->dwLoops = mp_block[i]->dwFlags = 0;
		}

		waveOutOpen(&mh_wave_out, NULL, &m_wave_format, (DWORD_PTR)m_hWnd, NULL, CALLBACK_WINDOW | WAVE_ALLOWSYNC);

		for (i = 0; i < MAX_QUEUE_NUMBER && m_play_pos < m_save_size; i++) {
			if ((m_play_pos + MAX_QUEUE_SIZE) < m_save_size) {
				memcpy(mp_block[i]->lpData, mp_save_buffer + m_play_pos, MAX_QUEUE_SIZE);
				mp_block[i]->dwBufferLength = MAX_QUEUE_SIZE;
				m_play_pos += MAX_QUEUE_SIZE;
			}
			else {
				int remain_size = m_save_size - m_play_pos;
				memcpy(mp_block[i]->lpData, mp_save_buffer + m_play_pos, remain_size);
				mp_block[i]->dwBufferLength = remain_size;
				m_play_pos += remain_size;
			}

			waveOutPrepareHeader(mh_wave_out, mp_block[i], sizeof(WAVEHDR));
			waveOutWrite(mh_wave_out, mp_block[i], sizeof(WAVEHDR));
		}

		if (i > 0) {
			MakeWaveImage((short*)mp_save_buffer, mp_block[0]->dwBufferLength >> 1);
			InvalidateRect(m_image_rect, 0);
		}
	}
}


void CRecordAndPlay1Dlg::OnBnClickedPlayStop()
{
	// TODO: Add your control notification handler code here
	if (mh_wave_out != NULL) {
		waveOutPause(mh_wave_out);
		waveOutReset(mh_wave_out);
		for (int i = 0; i < MAX_QUEUE_NUMBER; i++) {
			waveOutUnprepareHeader(mh_wave_out, mp_block[i], sizeof(WAVEHDR));
		}
		waveOutClose(mh_wave_out);
		mh_wave_out = NULL;
	}
}


afx_msg LRESULT CRecordAndPlay1Dlg::OnMmWimData(WPARAM wParam, LPARAM lParam)
{
	if (mh_wave_in != NULL) {
		WAVEHDR* p_wave_header = (WAVEHDR*)lParam;
		memcpy(mp_save_buffer + m_save_size, p_wave_header->lpData, p_wave_header->dwBytesRecorded);
		m_save_size += p_wave_header->dwBytesRecorded;

		MakeWaveImage((short*)p_wave_header->lpData, p_wave_header->dwBytesRecorded >> 1);
		InvalidateRect(m_image_rect, 0);

		waveInPrepareHeader(mh_wave_in, p_wave_header, sizeof(WAVEHDR));
		waveInAddBuffer(mh_wave_in, p_wave_header, sizeof(WAVEHDR));

		if (m_save_size + MAX_QUEUE_SIZE > MAX_SAVE_SIZE) {
			OnBnClickedRecordStop();
		}
	}
	return 0;
}

afx_msg LRESULT CRecordAndPlay1Dlg::OnMmWomDone(WPARAM wParam, LPARAM lParam)
{
	if (mh_wave_out != NULL) {
		WAVEHDR* p_wave_header = (WAVEHDR*)lParam;
		m_playing_pos += p_wave_header->dwBufferLength;
	}
	return 0;
}


