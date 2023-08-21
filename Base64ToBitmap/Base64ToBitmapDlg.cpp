
// Base64ToBitmapDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Base64ToBitmap.h"

#include <Windows.h>
#include <wincred.h>
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment(lib, "Crypt32.lib")

#include "Base64ToBitmapDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBase64ToBitmapDlg dialog


CBase64ToBitmapDlg::CBase64ToBitmapDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BASE64TOBITMAP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

std::vector<BYTE> CBase64ToBitmapDlg::DecodeBase64(const std::string& base64) {
	DWORD dwSize = 0;
	DWORD dwDecodeSize = 0;
	CryptStringToBinaryA(base64.c_str(), 0, CRYPT_STRING_BASE64, NULL, &dwSize, NULL, NULL);
	std::vector<BYTE> buffer(dwSize);
	CryptStringToBinaryA(base64.c_str(), 0, CRYPT_STRING_BASE64, &buffer[0], &dwSize, NULL, NULL);
	return buffer;
}

void CBase64ToBitmapDlg::DisplayImage(HWND hwnd, const std::string& base64Image)
{
	std::vector<BYTE> imageData = DecodeBase64(base64Image);
	HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, imageData.size());
	void* pMem = GlobalLock(hMem);
	memcpy(pMem, imageData.data(), imageData.size());
	IStream* pStream = NULL;
	CreateStreamOnHGlobal(hMem, FALSE, &pStream);
	Gdiplus::Bitmap* pBitmap = Gdiplus::Bitmap::FromStream(pStream);
	pStream->Release();
	GlobalUnlock(hMem);
	GlobalFree(hMem);

	HWND hPicCtrl = ::GetDlgItem(hwnd, IDC_STATIC_IMAGE);
	HDC hdc = ::GetDC(hPicCtrl);
	Gdiplus::Graphics graphics(hdc);
	Gdiplus::Status status = graphics.DrawImage(pBitmap, 0, 0);
	::ReleaseDC(hPicCtrl, hdc);
	delete pBitmap;
}

HBITMAP CBase64ToBitmapDlg::CreateBitmapFromBuffer(BYTE* buffer)
{
	BITMAPFILEHEADER* file_header = (BITMAPFILEHEADER*)buffer;
	BITMAPINFOHEADER* info_header = (BITMAPINFOHEADER*)(file_header + 1);
	void* p_bitmap_bits = (void*)(buffer + file_header->bfOffBits);

	HBITMAP bitmap = CreateDIBitmap(::GetDC(NULL), info_header, CBM_INIT, p_bitmap_bits, (BITMAPINFO*)info_header, DIB_RGB_COLORS);
	return bitmap;
}

void CBase64ToBitmapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBase64ToBitmapDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CBase64ToBitmapDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CBase64ToBitmapDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CBase64ToBitmapDlg message handlers

BOOL CBase64ToBitmapDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
		// GDI+ 사용전에 해줘야하는 작업들
	GdiplusStartupInput gpsi;
	if (GdiplusStartup(&m_token, &gpsi, NULL) != Ok) {
		AfxMessageBox(_T("GDI+ 실패"));
	}

	DisplayImage(m_hWnd, base64Image);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBase64ToBitmapDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBase64ToBitmapDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CBase64ToBitmapDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CBase64ToBitmapDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}
