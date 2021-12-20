#include "pch.h"
#include "framework.h"
#include "ELCProject.h"
#include "ELCProjectDlg.h"

#define MAX_MODE_COUNT		4

Gdiplus::ARGB g_pen_color[MAX_MODE_COUNT] = {
	RGB24(0, 254, 145), RGB24(254, 254, 45),
	RGB24(0, 145, 254), RGB24(254, 145, 145)
};

Gdiplus::ARGB g_brush_color[MAX_MODE_COUNT] = {
	RGB32(32, 0, 254, 145), RGB32(32, 254, 254, 45),
	RGB32(32, 0, 145, 254), RGB32(32, 254, 145, 145)
};

void DrawGatePerMode(TW_DCP* ap_dcp, Gdiplus::GraphicsPath* ap_path, int a_x)
{
	Matrix m;
	m.Translate((float)(a_x+4), 4.0f);					// 이동
	ap_path->Transform(&m);
	m.Reset();
	m.Translate(0.0f, 70.0f);
	for (int i = 0; i < MAX_MODE_COUNT; i++) {
		ap_dcp->SetDCBrushColor(g_brush_color[i]);
		ap_dcp->SetDCPenColor(Gdiplus::DashStyleSolid, 2, g_pen_color[i]);
		ap_dcp->ShowPath(ap_path);

		ap_path->Transform(&m);
	}
}

// OR 게이트 벡터 패스
void DrawOrGate(TW_DCP* ap_dcp, int a_x)
{
	Gdiplus::GraphicsPath* p_or_gate_path = ap_dcp->CreatePath();
	p_or_gate_path->StartFigure();
	p_or_gate_path->AddLine(10, 0, 40, 0);
	
	PointF front_position[7] = {
		{40.0f, 0.0f},									// 시작점
		{70.0f, 10.0f}, {75.0f, 25.0f},		// 컨트롤 좌표
		{80.0f, 31.0f},								// 중간점
		{75.0f, 35.0f}, {70.0f, 50.0f},		// 컨트롤 좌표
		{40.0f, 62.0f}								// 끝점
	};

	p_or_gate_path->AddBeziers(front_position, 7);
	p_or_gate_path->AddLine(40, 62, 10, 62);

	PointF rear_position[7] = {
		{10.0f, 62.0f},									// 시작점
		{18.0f, 46.0f}, {20.0f, 36.0f},			// 컨트롤 좌표
		{20.0f, 31.0f},									// 중간점
		{20.0f, 25.0f}, {18.0f, 15.0f},			// 컨트롤 좌표
		{10.0f, 0.0f}										// 끝점
	};

	DrawGatePerMode(ap_dcp, p_or_gate_path, a_x);
	ap_dcp->DestroyPath(p_or_gate_path);
}

// NOR 게이트 벡터패스
void DrawNorGate(TW_DCP* ap_dcp, int a_x)
{
	Gdiplus::GraphicsPath* p_nor_gate_path = ap_dcp->CreatePath();
	p_nor_gate_path->StartFigure();
	p_nor_gate_path->AddEllipse(82, 26, 10, 10);
	p_nor_gate_path->AddLine(10, 0, 40, 0);
	PointF front_position[7] = {
		{40.0f, 0.0f},
		{70.0f, 10.0f}, {75.0f, 25.0f},
		{80.0f, 31.0f},
		{75.0f, 35.0f}, {70.0f, 50.0f},
		{40.0f, 62.0f}
	};
	p_nor_gate_path->AddBeziers(front_position, 7);
	p_nor_gate_path->AddLine(40, 62, 10, 62);
	PointF rear_position[7] = {
		{10.0f, 62.0f},
		{18.0f, 46.0f}, {20.0f, 36.0f},
		{20.0f, 31.0f},
		{20.0f, 25.0f}, {18.0f, 15.0f},
		{10.0f, 0.0f}
	};
	p_nor_gate_path->AddBeziers(rear_position, 7);
	p_nor_gate_path->CloseFigure();

	DrawGatePerMode(ap_dcp, p_nor_gate_path, a_x);
	ap_dcp->DestroyPath(p_nor_gate_path);
}

// XNOR 게이트용 벡터 패스를 구성한다.
void DrawXnorGate(TW_DCP* ap_dcp, int a_x)
{
	Gdiplus::GraphicsPath* p_xnor_gate_path = ap_dcp->CreatePath();
	p_xnor_gate_path->StartFigure();

	mp_xnor_gate_path->AddEllipse(82, 26, 10, 10);

	mp_xnor_gate_path->AddLine(10, 0, 40, 0);

	PointF front_pos[7] = {
		{40.0f, 0.0f},  // 시작 점
		{70.0f, 10.0f}, {75.0f, 25.0f}, // 컨트롤 좌표
		{80.0f, 31.0f}, // 중간 점
		{75.0f, 35.0f}, {70.0f, 50.0f},  // 컨트롤 좌표
		{40.0f, 62.0f}  // 끝점
	};

	mp_xnor_gate_path->AddBeziers(front_pos, 7);
	mp_xnor_gate_path->AddLine(40, 62, 10, 62);

	PointF rear_pos[7] = {
		{10.0f, 62.0f},  // 시작 점
		{18.0f, 46.0f}, {20.0f, 36.0f},  // 컨트롤 좌표
		{20.0f, 31.0f},  // 중간 점
		{20.0f, 25.0f}, {18.0f, 15.0f},  // 컨트롤 좌표
		{10.0f, 0.0f}    // 끝점
	};

	mp_xnor_gate_path->AddBeziers(rear_pos, 7);
	mp_xnor_gate_path->CloseFigure();

	mp_xnor_gate_path->StartFigure();
	PointF tail_pos[13] = {
		{0.0f, 62.0f},  // 시작 점
		{8.0f, 46.0f}, {10.0f, 36.0f},  // 컨트롤 좌표
		{10.0f, 31.0f},  // 중간 점
		{10.0f, 25.0f}, {8.0f, 15.0f},  // 컨트롤 좌표
		{0.0f, 0.0f},    // 끝점
		{8.0f, 15.0f}, {10.0f, 25.0f},  // 컨트롤 좌표
		{10.0f, 31.0f},  // 중간 점
		{10.0f, 36.0f}, {8.0f, 46.0f}, // 컨트롤 좌표
		{0.0f, 62.0f}  // 시작 점
	};

	mp_xnor_gate_path->AddBeziers(tail_pos, 13);
	mp_xnor_gate_path->CloseFigure();
}

// XOR 게이트용 벡터 패스를 구성한다.
void CExamMFCDlg::MakeXorGate()
{
	mp_xor_gate_path = m_dcp.CreatePath();

	mp_xor_gate_path->StartFigure();
	mp_xor_gate_path->AddLine(10, 0, 40, 0);

	PointF front_pos[7] = {
		{40.0f, 0.0f},  // 시작 점
		{70.0f, 10.0f}, {75.0f, 25.0f}, // 컨트롤 좌표
		{80.0f, 31.0f}, // 중간 점
		{75.0f, 35.0f}, {70.0f, 50.0f},  // 컨트롤 좌표
		{40.0f, 62.0f}  // 끝점
	};

	mp_xor_gate_path->AddBeziers(front_pos, 7);
	mp_xor_gate_path->AddLine(40, 62, 10, 62);

	PointF rear_pos[7] = {
		{10.0f, 62.0f},  // 시작 점
		{18.0f, 46.0f}, {20.0f, 36.0f},  // 컨트롤 좌표
		{20.0f, 31.0f},  // 중간 점
		{20.0f, 25.0f}, {18.0f, 15.0f},  // 컨트롤 좌표
		{10.0f, 0.0f}    // 끝점
	};

	mp_xor_gate_path->AddBeziers(rear_pos, 7);
	mp_xor_gate_path->CloseFigure();

	mp_xor_gate_path->StartFigure();
	PointF tail_pos[13] = {
		{0.0f, 62.0f},  // 시작 점
		{8.0f, 46.0f}, {10.0f, 36.0f},  // 컨트롤 좌표
		{10.0f, 31.0f},  // 중간 점
		{10.0f, 25.0f}, {8.0f, 15.0f},  // 컨트롤 좌표
		{0.0f, 0.0f},    // 끝점
		{8.0f, 15.0f}, {10.0f, 25.0f},  // 컨트롤 좌표
		{10.0f, 31.0f},  // 중간 점
		{10.0f, 36.0f}, {8.0f, 46.0f}, // 컨트롤 좌표
		{0.0f, 62.0f}  // 시작 점
	};

	mp_xor_gate_path->AddBeziers(tail_pos, 13);
	mp_xor_gate_path->CloseFigure();
}

// AND 게이트용 벡터 패스를 구성한다.
void CExamMFCDlg::MakeAndGate()
{
	mp_and_gate_path = m_dcp.CreatePath();

	mp_and_gate_path->StartFigure();
	mp_and_gate_path->AddLine(10, 0, 40, 0);

	mp_and_gate_path->AddArc(10, 0, 60, 62, 270, 180);

	mp_and_gate_path->AddLine(40, 62, 10, 62);
	mp_and_gate_path->AddLine(10, 62, 10, 0);
}

// NAND 게이트용 벡터 패스를 구성한다.
void CExamMFCDlg::MakeNandGate()
{
	mp_nand_gate_path = m_dcp.CreatePath();

	mp_nand_gate_path->StartFigure();

	mp_nand_gate_path->AddEllipse(72, 26, 10, 10);
	mp_nand_gate_path->AddLine(10, 0, 40, 0);
	mp_nand_gate_path->AddArc(10, 0, 60, 62, 270, 180);
	mp_nand_gate_path->AddLine(40, 62, 10, 62);
	mp_nand_gate_path->AddLine(10, 62, 10, 0);
}

// NOT 게이트용 벡터 패스를 구성한다.
void CExamMFCDlg::MakeNotGate()
{
	mp_not_gate_path = m_dcp.CreatePath();

	mp_not_gate_path->StartFigure();

	mp_not_gate_path->AddEllipse(72, 26, 10, 10);
	mp_not_gate_path->AddLine(10, 0, 72, 31);
	mp_not_gate_path->AddLine(72, 31, 10, 62);
	mp_not_gate_path->AddLine(10, 62, 10, 0);
}


void TWAPI_MakeGateImage(TW_DCP* ap_dcp)
{
	DrawOrGate(ap_dcp, 0);
	DrawNorGate(ap_dcp, 100);
	DrawXnorGate(ap_dcp, 200);
}