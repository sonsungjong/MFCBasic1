
// ELCProjectDlg.h : header file
//

#pragma once
#include "TW_DCP.h"
#include "TW_DoubleLinkedList.h"

#define GRID_INTERVAL				8					// grid ����
#define OR_GATE 0
#define NOR_GATE 1
#define XNOR_GATE 2
#define XOR_GATE 3
#define AND_GATE 4
#define NAND_GATE 5
#define NOT_GATE 6

#define H_WIRE			0
#define V_WIRE			1

struct GateData
{
	unsigned short type;					// ����Ʈ����
	unsigned char label_index;			// �Է���ġ�� ���� ��
	unsigned char state;					// ������°�
	int contact_count;						// ����Ʈ ������ ����
	POINT contact_pos[32];				// ����Ʈ ������ ��ġ
	POINT pos;								// ����Ʈ ��ġ ���� (�� ���� ��ǥ)
};

struct WireData
{
	UINT8 type;					// 0 : �����������, 1: ������������
	UINT8 state;					// ���簪
	UINT16 length;				// ���Ǳ���
	POINT start_pos;						// ���ǽ����� (��������ǥ)
};

// CELCProjectDlg dialog
class CELCProjectDlg : public CDialogEx
{
private:
	TW_DCP m_dcp;						// �̹��� ��ü ���� ��ü
	TW_DCP m_gate_dcp;				// ����Ʈ �̹����� ������ �ִ� ��ü
	CRect m_rect;							// �׸� ��� ����
	TW_DoubleLinkedList m_gate_list;			// ������ ���� ����Ʈ�� ���
	TW_DoubleLinkedList m_wire_list;			// ������ ���� ������ ���

	UINT8 m_is_clicked = 0;			// ���콺 Ŭ�� ���� �÷���
	CPoint m_prev_position;			// �̵��Ÿ� ���� ������ǥ

	GateData* mp_selected_gate = nullptr;			// ���õ� ����Ʈ�� �ּҸ� ����� ����
	WireData* mp_selected_wire = nullptr;			// ���õ� ���̾��� �ּҸ� ����� ����

// Construction
public:
	CELCProjectDlg(CWnd* pParent = nullptr);	// standard constructor
	void DrawBoard();
	void AddWire(UINT8 a_wire_type);

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
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedAddHWireBtn();
	afx_msg void OnBnClickedAddVWireBtn();
};
