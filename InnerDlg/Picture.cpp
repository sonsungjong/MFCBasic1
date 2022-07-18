// Picture.cpp : implementation file
//

#include "pch.h"
#include "InnerDlg.h"
#include "Picture.h"
#include "afxdialogex.h"


// Picture dialog

IMPLEMENT_DYNAMIC(__Picture, CDialogEx)

__Picture::__Picture(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_INNER1, pParent)
{
    CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
    D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &mp_factory);
}

__Picture::~__Picture()
{
    if (mp_bitmap != NULL) {
        mp_bitmap->Release();
    }
    mp_factory->Release();
    CoUninitialize();
}

void __Picture::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(__Picture, CDialogEx)
    ON_WM_DESTROY()
    ON_WM_PAINT()
END_MESSAGE_MAP()


// Picture message handlers
int __Picture::LoadMyImage(ID2D1RenderTarget* ap_target, const TCHAR* ap_path)
{
    if (mp_bitmap != NULL) {
        mp_bitmap->Release();
        mp_bitmap = NULL;
    }
    IWICImagingFactory* p_wic_factory;
    CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&p_wic_factory));
    IWICBitmapDecoder* p_decoder;
    IWICBitmapFrameDecode* p_frame;
    IWICFormatConverter* p_converter;
    int result = 0;         // 0 : 그림읽기 실패, 1 : 그림읽기 성공

    if (S_OK == p_wic_factory->CreateDecoderFromFilename(ap_path, NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &p_decoder)) {
        if (S_OK == p_decoder->GetFrame(0, &p_frame)) {
            if (S_OK == p_wic_factory->CreateFormatConverter(&p_converter)) {
                if (S_OK == p_converter->Initialize(p_frame, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.0f, WICBitmapPaletteTypeCustom)) {
                    if (S_OK == ap_target->CreateBitmapFromWicBitmap(p_converter, NULL, &mp_bitmap)) {
                        result = 1;
                    }
                }
                p_converter->Release();
            }
            p_frame->Release();
        }
        p_decoder->Release();
    }
    p_wic_factory->Release();
    return result;
}

BOOL __Picture::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  Add extra initialization here
    ::RECT r;
    ::GetClientRect(m_hWnd, &r);
    mp_factory->CreateHwndRenderTarget(RenderTargetProperties(), HwndRenderTargetProperties(m_hWnd, SizeU(r.right, r.bottom)), &mp_render_target);
    m_image_rect.right = (float)r.right;
    m_image_rect.bottom = (float)r.bottom;
    LoadMyImage(mp_render_target, _T("../img/right_up.png"));

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}


void __Picture::OnDestroy()
{
    CDialogEx::OnDestroy();

    // TODO: Add your message handler code here
    if (mp_render_target != NULL) {
        mp_render_target->Release();
        mp_render_target = NULL;
    }
    PostQuitMessage(0);
}


void __Picture::OnPaint()
{
    CPaintDC dc(this); // device context for painting
                       // TODO: Add your message handler code here
                       // Do not call CDialogEx::OnPaint() for painting messages
}
