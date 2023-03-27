#include "pch.h"
#include "KioskTips.h"
#include "afxdialogex.h"
#include "AddItemDlg.h"


// AddItemDlg dialog

IMPLEMENT_DYNAMIC(AddItemDlg, CDialogEx)

AddItemDlg::AddItemDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADD_ITEM, pParent)
{

}

AddItemDlg::~AddItemDlg()
{
}



void AddItemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(AddItemDlg, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDOK, &AddItemDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &AddItemDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_SELECT_IMAGE_BTN, &AddItemDlg::OnBnClickedSelectImageBtn)
END_MESSAGE_MAP()


// AddItemDlg message handlers


BOOL AddItemDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	GetDlgItem(IDC_IMAGE_RECT)->GetWindowRect(m_rect);
	ScreenToClient(m_rect);

	// 아이템 변경모드일 경우
	if (m_price != 0) {
		SetWindowText(_T("선택 항목의 내용을 변경합니다."));
		// 한글이름, 영문이름, 이미지경로, 가격을 출력
		SetDlgItemText(IDC_NAME_KOR_EDIT, m_name_kor);
		SetDlgItemText(IDC_NAME_ENG_EDIT, m_name_eng);
		SetDlgItemText(IDC_IMAGE_PATH_EDIT, m_image_path);
		SetDlgItemInt(IDC_PRICE_EDIT, m_price);

		// 현재 이미지 경로를 사용해서 이미지를 읽어들인다
		m_item_image.Load(m_image_path);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void AddItemDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	// 읽어들인 이미지가 있으면 해당 이미지를 제거(해제)
	if (m_item_image.IsNull() == false) {
		m_item_image.Destroy();
	}
}


void AddItemDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	// 읽은 이미지가 있으면 해당 이미지를 m_rect 에 출력
	if (m_item_image.IsNull() == false) {
		dc.SetStretchBltMode(COLORONCOLOR);
		m_item_image.Draw(dc, m_rect);
	}
}


void AddItemDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();

	// 사용자가 지정한 항목 정보를 멤버 변수에 저장!
	GetDlgItemText(IDC_NAME_KOR_EDIT, m_name_kor);
	GetDlgItemText(IDC_NAME_ENG_EDIT, m_name_eng);
	GetDlgItemText(IDC_IMAGE_PATH_EDIT, m_image_path);
	m_price = GetDlgItemInt(IDC_PRICE_EDIT);

	// 항목의 한글이름과 이미지경로는 반드시 입력을 해야한다!
	if (m_image_path.GetLength() > 0 && m_name_kor.GetLength() > 0) {
		CDialogEx::OnOK();
	}
	else {
		MessageBox(_T("항목 이름 또는 이미지 경로는 반드시 입력을 해야합니다."), _T("항목 정보 부족"), MB_ICONSTOP | MB_OK);
	}
}


void AddItemDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void AddItemDlg::OnBnClickedSelectImageBtn()
{
	// TODO: Add your control notification handler code here
	// 이미지 파일을 선택하기 위한 필터
	TCHAR name_filter[] = _T("이미지 파일 (*.*)|*.*|PNG 파일 (*.png)|*.png||");
	CFileDialog ins_dlg(TRUE, _T("png"), _T("*.png"), OFN_NOCHANGEDIR, name_filter);
	ins_dlg.m_ofn.nFilterIndex = 2;

	// 파일 열기 대화 상자 출력
	if (IDOK == ins_dlg.DoModal()) {
		// 기존의 이미지가 있으면 기존 이미지 제거
		if (m_item_image.IsNull() == false) { m_item_image.Destroy(); }

		// 선택한 이미지 경로를 EditCtrl에 출력
		SetDlgItemText(IDC_IMAGE_PATH_EDIT, ins_dlg.GetPathName());
		// 선택한 이미지를 읽는다
		m_item_image.Load(ins_dlg.GetPathName());
		// 읽은 이미지를 화면에 출력
		InvalidateRect(m_rect);
	}
}

void AddItemDlg::SetKidData(const TCHAR* ap_name_kor, const TCHAR* ap_name_eng, const TCHAR* ap_image_path, int a_price)
{
	m_name_kor = ap_name_kor;
	m_name_eng = ap_name_eng;
	m_image_path = ap_image_path;
	m_price = a_price;
}

const TCHAR* AddItemDlg::GetNameKor()
{
	return m_name_kor;
}

const TCHAR* AddItemDlg::GetNameEng()
{
	return m_name_eng;
}

const TCHAR* AddItemDlg::GetImagePath()
{
	return m_image_path;
}

int AddItemDlg::GetPrice()
{
	return m_price;
}
