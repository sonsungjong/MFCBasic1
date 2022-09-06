
// RecordAndPlay1Dlg.h : header file
//

#pragma once
#include <mmsystem.h>
#pragma comment(lib, "Winmm.lib")

#define MAX_QUEUE_NUMBER 3				// 버퍼개수
#define MAX_QUEUE_SIZE 4800				// 버퍼크기 0.3초
#define MAX_SAVE_SIZE			480000				// 30s * 16000 (30초)

// CRecordAndPlay1Dlg dialog
class CRecordAndPlay1Dlg : public CDialogEx
{
private:
	WAVEFORMATEX m_wave_format;

	HWAVEIN mh_wave_in;
	HWAVEOUT mh_wave_out;
	WAVEHDR* mp_block[MAX_QUEUE_NUMBER];
	
	char* mp_save_buffer;
	int m_save_size;
	int m_play_index, m_play_pos, m_playing_pos;

	CImage m_image;
	HDC mh_image_dc;
	CRect m_image_rect;

// Construction
public:
	CRecordAndPlay1Dlg(CWnd* pParent = nullptr);	// standard constructor

	void MakeWaveImage(short* ap_data, int a_data_size);
	void MakeMemoryStructure();
	void FreeMemoryStructure();



// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RECORDANDPLAY1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedRecordStart();
	afx_msg void OnBnClickedRecordStop();
	afx_msg void OnBnClickedPlayStart();
	afx_msg void OnBnClickedPlayStop();
protected:
	afx_msg LRESULT OnMmWomDone(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMmWimData(WPARAM wParam, LPARAM lParam);
};
