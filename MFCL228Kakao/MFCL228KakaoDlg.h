
// MFCL228KakaoDlg.h : header file
//

#pragma once
struct ChatRoomData
{
	HWND h_room_wnd;				// ����Ʈ�ڽ� �ڵ�
	HWND h_edit_wnd;				// ���� ��Ʈ�� �ڵ�
};

// CMFCL228KakaoDlg dialog
class CMFCL228KakaoDlg : public CDialogEx
{
private:
	// ȭ��ĸó
	HDC mh_mem_dc = NULL;			// �̹����� �����ϰ� ȭ�鿡 ����ϱ� ���� ����� DC
	HBITMAP mh_mem_bitmap = NULL;			// ȭ���� �����ϰ� ����� �� ����� ��Ʈ��

	// �޸� ������ ���ؼ� ȭ���� �޶������� üũ
	// ���� ���ϰ� ���� ������ ������ �޸��� �ּҸ� ������ ������
	unsigned char* mp_cur_data = NULL, * mp_backup_data = NULL;
	// ����͸� ���� ����(0:����, 1:����͸�)
	int m_start_flag = 0;
	// ����͸��� ������ �̹��� ũ��
	int m_image_data_size;
	// ĸó�� �̹����� ����� ���� (�� ������ŭ ĸó�� �����)
	CRect m_target_rect;
	// ����͸� �ǰ� �ִ� �̹����� ������ ä�ù��� ����
	ChatRoomData* mp_selected_room = NULL;

public:
	CMFCL228KakaoDlg(CWnd* pParent = nullptr);	// standard constructor
	// ����Ʈ �ڽ��� ��ϵ� ä�ù� ����� ��� ����� �Լ�
	void ResetChatRoomData();
	// ����͸��� ���� ������ ��� �����ϴ� �Լ�
	void DeleteMonObject();
	// ���α׷� ���¸� ǥ���ϴ� �Լ�, ������ Ȯ���� �� �ֵ��� �ð��� �߰��ؼ� ���
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
