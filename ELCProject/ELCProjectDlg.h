
// ELCProjectDlg.h : header file
//

#pragma once
#include "TW_DCP.h"
#include "TW_DoubleLinkedList.h"

#define GRID_INTERVAL				7					// grid 간격
#define OR_GATE 0
#define NOR_GATE 1
#define XNOR_GATE 2
#define XOR_GATE 3
#define AND_GATE 4
#define NAND_GATE 5
#define NOT_GATE 6

struct GateData
{
	unsigned short type;					// 게이트종류
	unsigned char label_index;			// 입력장치의 고유 라벨
	unsigned char state;					// 현재상태값
	int contact_count;						// 게이트 접점의 개수
	POINT contact_pos[32];				// 게이트 접점의 위치
	POINT pos;								// 게이트 위치 정보 (점 단위 좌표)
};

// CELCProjectDlg dialog
class CELCProjectDlg : public CDialogEx
{
private:
	TW_DCP m_dcp;						// 이미지 전체 구성 객체
	TW_DCP m_gate_dcp;				// 게이트 이미지를 가지고 있는 객체
	CRect m_rect;							// 그림 출력 영역
	TW_DoubleLinkedList m_gate_list;			// 편집에 사용된 게이트의 목록
	UINT8 m_is_clicked = 0;			// 마우스 클릭 상태 플래그
	CPoint m_prev_position;			// 이동거리 계산용 이전좌표
	GateData* mp_selected_gate = nullptr;			// 선택된 게이트의 주소 기억할 포인터변수

// Construction
public:
	CELCProjectDlg(CWnd* pParent = nullptr);	// standard constructor
	void DrawBoard();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ELCPROJECT_DIALOG };
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
	afx_msg void OnBnClickedAddGateBtn(UINT a_ctrl_id);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
