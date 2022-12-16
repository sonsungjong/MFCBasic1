
// MFCL228KakaoDlg.h : header file
//

#pragma once
struct ChatRoomData
{
	HWND h_room_wnd;				// 리스트박스 핸들
	HWND h_edit_wnd;				// 에딧 컨트롤 핸들
};

// CMFCL228KakaoDlg dialog
class CMFCL228KakaoDlg : public CDialogEx
{
private:
	// 화면캡처
	HDC mh_mem_dc = NULL;			// 이미지를 복사하고 화면에 출력하기 위해 사용할 DC
	HBITMAP mh_mem_bitmap = NULL;			// 화면을 복사하고 출력할 때 사용할 비트맵

	// 메모리 패턴을 비교해서 화면이 달라졌는지 체크
	// 이전 패턴과 현재 패턴을 저장한 메모리의 주소를 저장할 포인터
	unsigned char* mp_cur_data = NULL, * mp_backup_data = NULL;
	// 모니터링 진행 상태(0:중지, 1:모니터링)
	int m_start_flag = 0;
	// 모니터링할 영역의 이미지 크기
	int m_image_data_size;
	// 캡처된 이미지를 출력할 영역 (이 영역만큼 캡처가 진행됨)
	CRect m_target_rect;
	// 모니터링 되고 있는 이미지를 전송할 채팅방의 정보
	ChatRoomData* mp_selected_room = NULL;

public:
	CMFCL228KakaoDlg(CWnd* pParent = nullptr);	// standard constructor
	// 리스트 박스에 등록된 채팅방 목록을 모두 지우는 함수
	void ResetChatRoomData();
	// 모니터링에 사용된 정보를 모두 제거하는 함수
	void DeleteMonObject();
	// 프로그램 상태를 표시하는 함수, 시점을 확인할 수 있도록 시간을 추가해서 출력
	void AddEventString(const TCHAR* ap_string);

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCL228KAKAO_DIALOG };
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
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CListBox m_room_list;
	afx_msg void OnBnClickedFindRoomBtn();
	afx_msg void OnBnClickedSendBtn();
	afx_msg void OnDestroy();
private:
	CComboBox m_event_list;
public:
	afx_msg void OnBnClickedStartMonitorBtn();
	afx_msg void OnBnClickedStopMonitorBtn();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
