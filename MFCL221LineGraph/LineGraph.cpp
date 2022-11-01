// LineGraph.cpp : implementation file
//

#include "pch.h"
#include "MFCL221LineGraph.h"
#include "LineGraph.h"


// LineGraph

IMPLEMENT_DYNAMIC(LineGraph, CWnd)

LineGraph::LineGraph()
{

}

LineGraph::~LineGraph()
{
}

void LineGraph::CreateGraph(int a_rect_id, CWnd* ap_parent, int a_ctrl_id)
{
	CRect r;
	ap_parent->GetDlgItem(a_rect_id)->GetWindowRect(r);
	ap_parent->ScreenToClient(r);

	Create(NULL, NULL, WS_CHILD | WS_VISIBLE, r, ap_parent, a_ctrl_id);
}

void LineGraph::LoadData(const TCHAR* ap_data_path)
{
	FILE* p_file = NULL;
	BID* p_data;

	if (0 == _wfopen_s(&p_file, ap_data_path, _T("rb")) && p_file != NULL) {
		while (1) {
			p_data = new BID;
			if (6 == fscanf_s(p_file, "%10s,%2s,%d,%d,%d,%d", p_data->data_of_week, 12, p_data->data_of_week, 3,
				&p_data->total, &p_data->neighbor, &p_data->adjoin, &p_data->etc)) {
				m_data_list.AddTail(p_data);
			}
			else {
				delete p_data;
				break;
			}
		}
		fclose(p_file);
		DrawGraph();
		Invalidate(0);
	}
}

void LineGraph::DrawGraph()
{
	// GDI
	//m_draw_dc.SelectStockObject(DC_BRUSH);
	//m_draw_dc.SelectStockObject(DC_PEN);
	//m_draw_dc.SetDCBrushColor(RGB(245, 252, 255));
	//m_draw_dc.SetDCPenColor(RGB(228, 255, 228));
	//m_draw_dc.Rectangle(m_rect);

	// GDI+
	//mp_brush->SetColor(Color(255, 245, 252, 255));
	mp_brush->SetColor(Color(255, 22, 32, 42));
	mp_pen->SetColor(Color(60, 100, 200, 100));
	mp_mem_graphic->FillRectangle(mp_brush, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom);			// 색깔있는 사각형
	mp_mem_graphic->DrawRectangle(mp_pen, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom);			// 테두리만 있는 사각형

	if (!m_data_list.GetCount()) {
		return;
	}

	int sx, sy, ex, ey;
	int max = 1;
	BID* p_data;
	POSITION position = m_data_list.GetHeadPosition();
	while (position != NULL) {
		p_data = (BID*)m_data_list.GetNext(position);
		if (max < p_data->total) {
			max = p_data->total;
		}
	}
	max += (int)(max * 0.1);

	double step = m_rect.Width() / (double)(m_data_list.GetCount() + 1);
	int height = m_rect.Height();
	position = m_data_list.GetHeadPosition();
	p_data = (BID*)m_data_list.GetNext(position);
	sx = (int)step;
	sy = height - height * p_data->total / max;

	mp_pen->SetColor(Color(255, 0, 199, 60));
	//m_draw_dc.SetDCPenColor(RGB(0, 199, 60));
	//m_draw_dc.MoveTo((int)step, height - height * p_data->total / max);

	for (int i = 2; position != NULL; i++) {
		p_data = (BID*)m_data_list.GetNext(position);
		//m_draw_dc.LineTo((int)(i * step), height - height * p_data->total/max);
		ex = (int)(step * i);
		ey = height - height * p_data->total / max;
		mp_mem_graphic->DrawLine(mp_pen, sx, sy, ex, ey);
		sx = ex;
		sy = ey;
	}

	//m_draw_dc.SetDCBrushColor(RGB(0, 255, 0));
	//m_draw_dc.SetDCPenColor(RGB(0, 255, 0));
	mp_brush->SetColor(Color(150, 68, 252, 68));

	position = m_data_list.GetHeadPosition();
	int x, y;
	for (int i = 1; position != NULL; i++) {
		p_data = (BID*)m_data_list.GetNext(position);
		//x = (int)(i * step);
		//y = height - height * p_data->total / max;
		//m_draw_dc.Ellipse(x - 3, y - 3, x + 3, y + 3);
		sx = (int)(i * step);
		sy = height - height * p_data->total / max;
		mp_mem_graphic->FillEllipse(mp_brush, sx - 3, sy - 3, 6, 6);
	}
}


BEGIN_MESSAGE_MAP(LineGraph, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_DESTROY()
END_MESSAGE_MAP()



// LineGraph message handlers




int LineGraph::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	// GDI+
	GdiplusStartupInput gpsi;
	if (GdiplusStartup(&m_token, &gpsi, NULL) != Ok) { return 0; }

	GetClientRect(m_rect);

	// GDI+
	mp_mem_image = new Bitmap(m_rect.Width(), m_rect.Height());					// 비트맵 작업 영역
	mp_mem_graphic = new Graphics(mp_mem_image);							// 비트맵에 그릴 GDI+
	mp_brush = new SolidBrush(Color(255, 255, 255, 255));						// 브러시색
	mp_pen = new Pen(Color(255, 0, 199, 60));								// 선 색
	mp_mem_graphic->SetSmoothingMode(SmoothingModeAntiAlias);				// 안티알리어싱

	// GDI
	//m_draw_image.Create(m_rect.Width(), m_rect.Height(), 32);
	//m_draw_dc.Attach(m_draw_image.GetDC());

	return 0; 
}


void LineGraph::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CWnd::OnPaint() for painting messages
	
	// GDI
	//m_draw_image.Draw(dc, 0, 0);

	// GDI+
	Graphics* p_graphic = new Graphics(dc);						// dc에 연결하고
	p_graphic->DrawImage(mp_mem_image, 0, 0);				// dc에 비트맵을 그린다
	delete p_graphic;
}


void LineGraph::OnDestroy()
{
	CWnd::OnDestroy();

	// TODO: Add your message handler code here
	BID* p_data;
	POSITION position = m_data_list.GetHeadPosition();

	while (position != NULL) {
		p_data = (BID*)m_data_list.GetNext(position);
		delete p_data;
	}
	m_data_list.RemoveAll();

	// GDI
	//m_draw_dc.Detach();						// Attach
	//m_draw_image.ReleaseDC();					// GetDC
	//m_draw_image.Destroy();					// Create

	// GDI+
	delete mp_mem_graphic;
	delete mp_mem_image;
	delete mp_brush;
	delete mp_pen;
	GdiplusShutdown(m_token);
}
