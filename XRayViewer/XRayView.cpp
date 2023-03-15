#include "pch.h"
#include "XRayViewer.h"
#include "XRayView.h"

IMPLEMENT_DYNAMIC(XRayView, CWnd)

XRayView::XRayView()
{
	mp_16bit_data = NULL;
	mp_image_pattern = NULL;
	m_pixel_count = 0;
	m_min = 0xFFFF;
	m_max = 0x0000;
	m_range = 0;
	m_image_width = 3072;
	m_image_height = 3072;

	m_zoom_level = 0;				// ����
	m_x = 0;				// �̹��� ������ġ
	m_y = 0;				// �̹��� ������ġ
	m_cx = m_image_width / 3;				// �̹��� ��
	m_cy = m_image_height / 3;				// �̹��� ����
	m_is_clicked = 0;								// ���콺 Ŭ�� (0 : Ŭ������)

	memset(m_color_table, 0, sizeof(m_color_table));
}

XRayView::~XRayView()
{
}


BEGIN_MESSAGE_MAP(XRayView, CWnd)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_MOUSEWHEEL()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

/*
��ġ ��ǥ�� �� ��ǥ�� �����ϴ� �ڵ�
logic_width : device_width = lx : dx
lx = dx * logic_width / device_width
*/
void XRayView::DpToLp(float a_dx, float a_dy, float* ap_lx, float* ap_ly)
{
	*ap_lx = a_dx * m_image_width / m_cx;
	*ap_ly = a_dy * m_image_height / m_cy;
}

/*
�� ��ǥ�� ��ġ ��ǥ�� �����ϴ� �ڵ�
logic_width : device_width = lx : dx
dx = lx * device_width / logic_width
*/
void XRayView::LpToDp(float a_lx, float a_ly, float* ap_dx, float* ap_dy)
{
	*ap_dx = a_lx * m_cx / m_image_width;
	*ap_dy = a_ly * m_cy / m_image_height;
}

int XRayView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	GetClientRect(m_client_rect);
	m_draw_image.Create(m_client_rect.Width(), m_client_rect.Height(), 32);
	m_draw_dc.Attach(m_draw_image.GetDC());
	m_draw_dc.SetStretchBltMode(COLORONCOLOR);
	m_draw_dc.SelectStockObject(NULL_BRUSH);
	m_draw_dc.SelectStockObject(DC_PEN);
	m_draw_dc.SetDCPenColor(RGB(0, 255, 0));

	return 0;
}

void XRayView::OnDestroy()
{
	CWnd::OnDestroy();

	// TODO: Add your message handler code here
	if (mp_16bit_data != NULL) {
		delete[] mp_16bit_data;
		delete[] mp_image_pattern;

		m_mem_bmp.DeleteObject();
		m_mem_dc.DeleteDC();
	}

	m_draw_dc.Detach();
	m_draw_image.ReleaseDC();
	m_draw_image.Destroy();
}


void XRayView::OnPaint()
{
	CPaintDC dc(this);

	m_draw_image.Draw(dc, 0, 0);				// ��ü�� �׷��� �׸��� ȭ�鿡 ���
}

int XRayView::LoadXRayImage(const TCHAR* ap_image_path)
{
	if (ReadImageDataFromFile(ap_image_path)) {
		CClientDC dc(this);
		// ������۸�
		m_mem_dc.CreateCompatibleDC(&dc);
		m_mem_bmp.CreateCompatibleBitmap(&dc, m_image_width, m_image_height);
		m_mem_dc.SelectObject(&m_mem_bmp);

		mp_image_pattern = new unsigned char[m_image_width * m_image_height* 4];
		unsigned short* p_src = mp_16bit_data;
		unsigned short color;
		unsigned char *p_dest = mp_image_pattern;

		memset(m_color_table, 0, sizeof(m_color_table));		// �̹��� ������ Ƚ���� �������� �ʱ�ȭ
		m_zoom_level = 0;
		m_x = 0;
		m_y = 0;
		m_cx = m_image_width / 3;
		m_cy = m_image_height / 3;

		for (int i = 0; i < m_pixel_count; i++, p_src++) {
			m_color_table[(*p_src) / 256].count++;
			if (m_min > *p_src) { m_min = *p_src; }
			else if (m_max < *p_src) { m_max = *p_src; }
		}
		m_range = m_max - m_min;
		
		// ���� ���� ���� �����·� ���� ( 0 �Ǵ� 1 ����)
		ColorInfo* p_color_data = m_color_table;
		for (int i = 0; i < 256; i++, p_color_data++) { p_color_data->is_enable = p_color_data->count != 0; }
		
		p_src = (unsigned short*)mp_16bit_data;

		for (int i = 0; i < m_pixel_count; i++, p_src++) {
			color = (*p_src - m_min) * 255 / m_range;
			//RGB�� ��� ���� ������ �����ϸ� ����̹����� �ȴ�
			*p_dest++ = (unsigned char)color;				// blue
			*p_dest++ = (unsigned char)color;				// green
			*p_dest++ = (unsigned char)color;				// red
			*p_dest++ = 0xFF;									// alpha
		}
		// ��Ʈ�ʿ� ����
		MakeDisplayImageFromPattern(mp_image_pattern);
		return 1;
	}
	return 0;
}

int XRayView::ReadImageDataFromFile(const TCHAR* ap_image_path)
{
	if (mp_16bit_data != NULL) {
		delete[] mp_16bit_data;

		m_mem_bmp.DeleteObject();
		m_mem_dc.DeleteDC();
	}

	FILE* p_file = NULL;
	errno_t err;

	// ������ �б���� ����
	err = _tfopen_s(&p_file, ap_image_path, _T("rb"));
	if (err == 0 && p_file != NULL) {
		fseek(p_file, 0, SEEK_END);
		int image_size = ftell(p_file);
		m_pixel_count = image_size / sizeof(short);
		fseek(p_file, 0, SEEK_SET);

		mp_16bit_data = new unsigned short[m_pixel_count];
		fread(mp_16bit_data, 1, image_size, p_file);
		fclose(p_file);
	}
	else {
		// ���⿡ �����ϸ�
		mp_16bit_data = NULL;
		m_pixel_count = 0;
	}
	// �о���� �̹����� �� ���� ��ȯ
	return m_pixel_count;
}

//void XRayView::SetColorDataToListBox(CListBox* ap_list_box)
//{
//	if (mp_16bit_data == NULL) { return; }
//	ap_list_box->ResetContent();
//
//	CString str;
//	for (int i = 0; i < 256; i++) {
//		str.Format(_T("��� �� [%03d] : %d ��"), i, m_color_table[i]);
//		ap_list_box->InsertString(i, str);
//		ap_list_box->SetItemData(i, m_color_table[i]);
//	}
//}

void XRayView::UpdateRange()
{
	unsigned short* p_src = mp_16bit_data;
	unsigned char* p_dest = mp_image_pattern;

	m_max = 0x0000;
	m_min = 0xFFFF;
	for (int i = 0; i < m_pixel_count; i++, p_src++) {
		if (m_color_table[(*p_src) / 256].is_enable) {
			if (m_min > *p_src) { m_min = *p_src; }
			else if (m_max < *p_src) { m_max = *p_src; }
		}
	}
	if (m_min < m_max) { m_range = m_max - m_min; }
	else { m_range = 0xFFFF; }
}

void XRayView::MakeNormalPattern()
{
	unsigned short* p_src = mp_16bit_data;
	unsigned short color;
	unsigned char* p_dest = mp_image_pattern;

	for (int i = 0; i < m_pixel_count; i++, p_src++) {
		if (m_color_table[(*p_src)/256].is_enable) {
			if (m_min >= *p_src) { color = 0; }
			else if (m_max <= *p_src) { color = 255; }
			else color = (*p_src - m_min) * 255 / m_range;
		}
		else {
			color = 0;
		}

		*p_dest++ = (unsigned char)color;				// B
		*p_dest++ = (unsigned char)color;				// G
		*p_dest++ = (unsigned char)color;				// R
		*p_dest++ = 0xFF;				// A
	}
}

void XRayView::UpdateImage()
{
	MakeNormalPattern();
	MakeDisplayImageFromPattern(mp_image_pattern);
}

void XRayView::ChangeSelectColorImage(int a_color_index)
{
	unsigned short* p_src = mp_16bit_data;
	unsigned short color;
	unsigned char* p_dest = mp_image_pattern;
	ColorInfo* p_select_color = m_color_table + a_color_index;

	if (p_select_color->count && p_select_color->is_enable) {
		for (int i = 0; i < m_pixel_count; i++, p_src++) {
			if (a_color_index == (*p_src) / 256) {
				*(unsigned int*)p_dest = 0xFFFFFF00;
				p_dest += 4;				// �� ���� ��������
			}
			else {
				if (m_color_table[(*p_src) / 256].is_enable) {
					if (m_min >= *p_src) { color = 0; }
					else if (m_max <= *p_src) { color = 255; }
					else { color = (*p_src - m_min) * 255 / m_range; }
				}
				else { color = 0; }

				// RGB�� ��� ���� ������ �����ϸ� ����� �ȴ�
				*p_dest++ = (unsigned char)color;						// blue
				*p_dest++ = (unsigned char)color;						// green
				*p_dest++ = (unsigned char)color;						// red
				*p_dest++ = 0xFF;									// alpha
			}
		}
	}
	else {
		MakeNormalPattern();
	}

	MakeDisplayImageFromPattern(mp_image_pattern);
}

// �̹��� �������� ����� �̹����� ����
void XRayView::MakeDisplayImageFromPattern(unsigned char* ap_pattern)
{
	// ap_pattern -> m_mem_bmp -> m_draw_image
	m_mem_bmp.SetBitmapBits(m_image_width * m_image_height * 4, ap_pattern);
	MakeDisplayImage();
}

void XRayView::MakeDisplayImage()
{
	// ���������� ä���, �̹����� �׸���
	m_draw_dc.FillSolidRect(m_client_rect, RGB(0, 0, 0));
	m_draw_dc.StretchBlt(m_x, m_y, m_cx, m_cy, &m_mem_dc, 0, 0, m_image_width, m_image_height, SRCCOPY);
	m_draw_dc.Rectangle(m_x, m_y, m_x + m_cx, m_y + m_cy);
	Invalidate(FALSE);				// WM_PAINT �߻� (��ü���� ����)
}


BOOL XRayView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: Add your message handler code here and/or call default
	int old_zoom_level = m_zoom_level;				// 0 ~ 12
	if (zDelta < 0) {
		if (m_zoom_level > 0) { m_zoom_level--; }					// ���
	}
	else {
		if (m_zoom_level < 13) { m_zoom_level++; }				// Ȯ��
	}

	if (old_zoom_level != m_zoom_level) {
		POINT position;
		GetCursorPos(&position);
		::ScreenToClient(m_hWnd, &position);
		float mouse_x = (float)position.x;
		float mouse_y = (float)position.y;
		float lx, ly, dx, dy;

		DpToLp(mouse_x - m_x, mouse_y - m_y, &lx, &ly);
		m_cx = int(m_image_width / (3 - 0.2f * m_zoom_level));
		m_cy = int(m_image_height / (3 - 0.2f * m_zoom_level));
		LpToDp(lx, ly, &dx, &dy);

		m_x = int(mouse_x - dx);
		m_y = int(mouse_y - dy);
		// ����� ������ �ٽ� �׸���
		MakeDisplayImage();
	}

	return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}


void XRayView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (!m_is_clicked) {
		m_clicked_pos = point;
		m_is_clicked = 1;
		SetCapture();
	}

	CWnd::OnLButtonDown(nFlags, point);
}


void XRayView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_is_clicked == 1) {
		ReleaseCapture();
		m_is_clicked = 0;
	}

	CWnd::OnLButtonUp(nFlags, point);
}


void XRayView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_is_clicked == 1) {
		// clicked_pos �� ����� ��ǥ�� ���� ���콺 ��ǥ�� ���� �̵��Ÿ��� ���Ѵ�
		// �̵��Ÿ���ŭ ����� ������ġ�� �����Ѵ� (�̵�)
		m_x += (short)point.x - (short)m_clicked_pos.x;
		m_y += (short)point.y - (short)m_clicked_pos.y;
		m_clicked_pos = point;

		MakeDisplayImage();
		UpdateWindow();
	}

	CWnd::OnMouseMove(nFlags, point);
}
