
// WebViewDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "WebView.h"
#include "WebViewDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWebViewDlg dialog



CWebViewDlg::CWebViewDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WEBVIEW_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	mp_browser_app = NULL;
}

void CWebViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CWebViewDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CWebViewDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CWebViewDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_GO_BTN, &CWebViewDlg::OnBnClickedGoBtn)
	ON_BN_CLICKED(IDC_HOME_BTN, &CWebViewDlg::OnBnClickedHomeBtn)
	ON_BN_CLICKED(IDC_PREV_BTN, &CWebViewDlg::OnBnClickedPrevBtn)
	ON_BN_CLICKED(IDC_NEXT_BTN, &CWebViewDlg::OnBnClickedNextBtn)
	ON_BN_CLICKED(IDC_GET_SRC_BTN, &CWebViewDlg::OnBnClickedGetSrcBtn)
	ON_BN_CLICKED(IDC_GET_LINK_BTN, &CWebViewDlg::OnBnClickedGetLinkBtn)
END_MESSAGE_MAP()


// CWebViewDlg message handlers

BOOL CWebViewDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	AfxEnableControlContainer();				// OLE컨트롤 사용

	SetDlgItemText(IDC_URL_EDIT, _T("https://www.naver.com/"));

	CRect r;
	GetDlgItem(IDC_WEB_PAGE_RECT)->GetWindowRect(r);
	ScreenToClient(r);				// 좌표계를 클라이언트 기준으로

	if (m_web_browser_control.CreateControl(CLSID_WebBrowser, NULL, WS_VISIBLE | WS_CHILD, r, this, AFX_IDW_PANE_FIRST))
	{
		LPUNKNOWN p_unknown = m_web_browser_control.GetControlUnknown();
		HRESULT result = p_unknown->QueryInterface(IID_IWebBrowser2, (void**)&mp_browser_app);

		if (SUCCEEDED(result)) {
			// 성공적으로 인터페이스를 얻었다면 지정한 웹페이지를 열도록 명령한다.
			OpenHtmlPage(_T("https://www.naver.com/"));
		}
		else {
			// 인터페이스 얻기에 실패했다면 웹 컨트롤을 제거한다.
			m_web_browser_control.DestroyWindow();
			mp_browser_app = NULL;
		}
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWebViewDlg::OnPaint()
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
HCURSOR CWebViewDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CWebViewDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CWebViewDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}

void CWebViewDlg::OpenHtmlPage(const TCHAR* ap_page_url)
{
	if (mp_browser_app == NULL) {
		return;
	}

	COleSafeArray post_data;
	COleVariant target_url(ap_page_url, VT_BSTR);
	COleVariant headers((LPCTSTR)NULL, VT_BSTR);
	COleVariant target_frame_name((LPCTSTR)NULL, VT_BSTR);
	COleVariant flags((long)0, VT_I4);

	mp_browser_app->Navigate2(target_url, flags, target_frame_name, post_data, headers);
}

// 이동하기 버튼
void CWebViewDlg::OnBnClickedGoBtn()
{
	CString str;
	GetDlgItemText(IDC_URL_EDIT, str);
	OpenHtmlPage(str);				// 입력된 URL로 이동
}


void CWebViewDlg::OnBnClickedHomeBtn()
{
	if (mp_browser_app != NULL) {
		mp_browser_app->GoHome();				// 홈페이지
	}
}


void CWebViewDlg::OnBnClickedPrevBtn()
{
	if (mp_browser_app != NULL) {
		mp_browser_app->GoBack();				// 이전페이지
	}
}


void CWebViewDlg::OnBnClickedNextBtn()
{
	if (mp_browser_app != NULL) {
		mp_browser_app->GoForward();			// 다음페이지
	}
}

void CWebViewDlg::OnBnClickedGetSrcBtn()
{
	IDispatch* p_doc_dispatch = NULL;
	IHTMLDocument2* p_html_doc2 = NULL;

	mp_browser_app->get_Document(&p_doc_dispatch);
	HRESULT hr = p_doc_dispatch->QueryInterface(IID_IHTMLDocument2, (void**)&p_html_doc2);
	if (SUCCEEDED(hr)) {
		IHTMLElement* p_html_element = NULL;
		p_html_doc2->get_body((IHTMLElement**)&p_html_element);

		BSTR p = NULL;
		// 소스를 가져온다
		p_html_element->get_outerHTML(&p);
		SetDlgItemText(IDC_SRC_EDIT, p);
		// 소스를 가져오기위해 사용된 메모리를 해제
		::SysFreeString(p);

		p_html_element->Release();
		p_html_element = NULL;

		p_html_doc2->Release();
		p_html_doc2 = NULL;
	}

	p_doc_dispatch->Release();
	p_doc_dispatch = NULL;
}


void CWebViewDlg::OnBnClickedGetLinkBtn()
{
	IDispatch* p_doc_disp = NULL, * p_element_disp = NULL;
	IHTMLDocument2* p_html_doc2 = NULL;
	IHTMLElementCollection* p_element_collection = NULL;
	IHTMLElement* p_link_item = NULL;
	IHTMLAnchorElement* p_anchor_element;
	CString m_total_link_str, link_str;
	long element_count;

	mp_browser_app->get_Document(&p_doc_disp);
	HRESULT hr = p_doc_disp->QueryInterface(IID_IHTMLDocument2, (void**)&p_html_doc2);
	if (SUCCEEDED(hr)) {
		p_html_doc2->get_all(&p_element_collection);
		if (SUCCEEDED(hr)) {
			p_element_collection->get_length(&element_count);
			for (long i = 0; i < element_count; i++) {
				_variant_t vid(i, VT_I4);
				_variant_t vidx((long)0, VT_I4);
				p_element_collection->item(vid, vidx, &p_element_disp);
				hr = p_element_disp->QueryInterface(IID_IHTMLElement, (void**)&p_link_item);
				if (SUCCEEDED(hr)) {
					hr = p_link_item->QueryInterface(IID_IHTMLAnchorElement, (void**)&p_anchor_element);
					if (SUCCEEDED(hr)) {
						BSTR str = NULL, url = NULL;
						if (SUCCEEDED(p_link_item->get_innerText(&str))) {
							if (SUCCEEDED(p_anchor_element->get_href(&url))) {
								link_str.Format(_T("%s - %s\r\n"), str, url);
								m_total_link_str += link_str;
								::SysFreeString(url);
							}
							::SysFreeString(str);
						}
						p_anchor_element->Release();
						p_anchor_element = NULL;
					}
					p_link_item->Release();
					p_link_item = NULL;
				}
				p_element_disp->Release();
				p_element_disp = NULL;
			}
			p_element_collection->Release();
			p_element_collection = NULL;
			p_html_doc2->Release();
			p_html_doc2 = NULL;
		}
	}

	p_doc_disp->Release();
	p_doc_disp = NULL;

	SetDlgItemText(IDC_SRC_EDIT, m_total_link_str);
}
