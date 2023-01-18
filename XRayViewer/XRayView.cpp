// XRayView.cpp : implementation file
//

#include "pch.h"
#include "XRayViewer.h"
#include "XRayView.h"


// XRayView

IMPLEMENT_DYNAMIC(XRayView, CWnd)

XRayView::XRayView()
{
	mp_16bit_data = NULL;
	mp_image_pattern = NULL;
	m_pixel_count = 0;
	m_min = 0xFFFF;
	m_max = 0x0000;
	m_range = 0;
	memset(m_color_table, 0, sizeof(m_color_table));
}

XRayView::~XRayView()
{
}


BEGIN_MESSAGE_MAP(XRayView, CWnd)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_PAINT()
END_MESSAGE_MAP()

int XRayView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

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
}


void XRayView::OnPaint()
{
	CPaintDC dc(this);

	CRect r;
	GetClientRect(r);
	dc.SetStretchBltMode(COLORONCOLOR);
	dc.StretchBlt(0, 0, r.Width(), r.Height(), &m_mem_dc, 0, 0, IMG_WIDTH, IMG_HEIGHT, SRCCOPY);
}

int XRayView::LoadXRayImage(const TCHAR* ap_image_path)
{
	if (ReadImageDataFromFile(ap_image_path)) {
		CClientDC dc(this);
		m_mem_dc.CreateCompatibleDC(&dc);
		m_mem_bmp.CreateCompatibleBitmap(&dc, IMG_WIDTH, IMG_HEIGHT);
		m_mem_dc.SelectObject(&m_mem_bmp);

		mp_image_pattern = new unsigned char[IMG_WIDTH * IMG_HEIGHT * 4];
		unsigned short* p_src = mp_16bit_data;
		unsigned short color;
		unsigned char *p_dest = mp_image_pattern;

		for (int i = 0; i < m_pixel_count; i++, p_src++) {
			m_color_table[(*p_src) / 256]++;
			if (m_min > *p_src) { m_min = *p_src; }
			else if (m_max < *p_src) { m_max = *p_src; }
		}
		m_range = m_max - m_min;
		p_src = (unsigned short*)mp_16bit_data;

		for (int i = 0; i < m_pixel_count; i++, p_src++) {
			color = (*p_src - m_min) * 255 / m_range;
			//RGB에 모두 같은 색상을 대입하면 흑백이미지가 된다
			*p_dest++ = (unsigned char)color;				// blue
			*p_dest++ = (unsigned char)color;				// green
			*p_dest++ = (unsigned char)color;				// red
			*p_dest++ = 0xFF;									// alpha
		}
		// 비트맵에 저장
		m_mem_bmp.SetBitmapBits(IMG_WIDTH * IMG_HEIGHT * 4, mp_image_pattern);
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

	// 파일을 읽기모드로 연다
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
		// 열기에 실패하면
		mp_16bit_data = NULL;
		m_pixel_count = 0;
	}
	// 읽어들인 이미지의 점 갯수 반환
	return m_pixel_count;
}

void XRayView::SetColorDataToListBox(CListBox* ap_list_box)
{
	if (mp_16bit_data == NULL) { return; }
	ap_list_box->ResetContent();

	CString str;
	for (int i = 0; i < 256; i++) {
		str.Format(_T("흑뱃 농도 [%03d] : %d 점"), i, m_color_table[i]);
		ap_list_box->InsertString(i, str);
		ap_list_box->SetItemData(i, m_color_table[i]);
	}
}

void XRayView::UpdateRange(unsigned char a_enable_colors[])
{
	unsigned short* p_src = mp_16bit_data;
	unsigned char* p_dest = mp_image_pattern;

	m_max = 0x0000;
	m_min = 0xFFFF;
	for (int i = 0; i < m_pixel_count; i++, p_src++) {
		if (a_enable_colors[(*p_src) / 256]) {
			if (m_min > *p_src) { m_min = *p_src; }
			else if (m_max < *p_src) { m_max = *p_src; }
		}
	}
	if (m_min < m_max) { m_range = m_max - m_min; }
	else { m_range = 0xFFFF; }
}

void XRayView::MakeNormalPattern(unsigned char a_enable_colors[])
{
	unsigned short* p_src = mp_16bit_data;
	unsigned short color;
	unsigned char* p_dest = mp_image_pattern;

	for (int i = 0; i < m_pixel_count; i++, p_src++) {
		if (a_enable_colors[(*p_src)/256]) {
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

void XRayView::UpdateImage(unsigned char a_enable_colors[])
{
	MakeNormalPattern(a_enable_colors);
	m_mem_bmp.SetBitmapBits(IMG_WIDTH * IMG_HEIGHT * 4, mp_image_pattern);
	Invalidate(0);
}

void XRayView::ChangeSelectColorImage(unsigned char a_enable_colors[], int a_color_index, int a_color_count)
{
	unsigned short* p_src = mp_16bit_data;
	unsigned short color;
	unsigned char* p_dest = mp_image_pattern;

	if (a_color_count && a_enable_colors[a_color_index]) {
		for (int i = 0; i < m_pixel_count; i++, p_src++) {
			if (a_color_index == (*p_src) / 256) {
				*(unsigned int*)p_dest = 0xFFFFFF00;
				p_dest += 4;				// 한 점을 지나간다
			}
			else {
				if (m_min >= *p_src) { color = 0; }
				else if (m_max <= *p_src) { color = 255; }
				else { color = (*p_src - m_min) * 255 / m_range; }

				// RGB에 모두 같은 색상을 대입하면 흑백이 된다
				*p_dest++ = (unsigned char)color;						// blue
				*p_dest++ = (unsigned char)color;						// green
				*p_dest++ = (unsigned char)color;						// red
				*p_dest++ = 0xFF;									// alpha
			}
		}
	}
	else {
		MakeNormalPattern(a_enable_colors);
	}

	// 구성된 비트패턴을 비트맵에 저장
	m_mem_bmp.SetBitmapBits(IMG_WIDTH * IMG_HEIGHT * 4, mp_image_pattern);
	Invalidate(0);
}
