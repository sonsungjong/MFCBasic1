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

	// ������ �������� ���
	if (m_price != 0) {
		SetWindowText(_T("���� �׸��� ������ �����մϴ�."));
		// �ѱ��̸�, �����̸�, �̹������, ������ ���
		SetDlgItemText(IDC_NAME_KOR_EDIT, m_name_kor);
		SetDlgItemText(IDC_NAME_ENG_EDIT, m_name_eng);
		SetDlgItemText(IDC_IMAGE_PATH_EDIT, m_image_path);
		SetDlgItemInt(IDC_PRICE_EDIT, m_price);

		// ���� �̹��� ��θ� ����ؼ� �̹����� �о���δ�
		m_item_image.Load(m_image_path);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void AddItemDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	// �о���� �̹����� ������ �ش� �̹����� ����(����)
	if (m_item_image.IsNull() == false) {
		m_item_image.Destroy();
	}
}


void AddItemDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	// ���� �̹����� ������ �ش� �̹����� m_rect �� ���
	if (m_item_image.IsNull() == false) {
		dc.SetStretchBltMode(COLORONCOLOR);
		m_item_image.Draw(dc, m_rect);
	}
}


void AddItemDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();

	// ����ڰ� ������ �׸� ������ ��� ������ ����!
	GetDlgItemText(IDC_NAME_KOR_EDIT, m_name_kor);
	GetDlgItemText(IDC_NAME_ENG_EDIT, m_name_eng);
	GetDlgItemText(IDC_IMAGE_PATH_EDIT, m_image_path);
	m_price = GetDlgItemInt(IDC_PRICE_EDIT);

	// �׸��� �ѱ��̸��� �̹�����δ� �ݵ�� �Է��� �ؾ��Ѵ�!
	if (m_image_path.GetLength() > 0 && m_name_kor.GetLength() > 0) {
		CDialogEx::OnOK();
	}
	else {
		MessageBox(_T("�׸� �̸� �Ǵ� �̹��� ��δ� �ݵ�� �Է��� �ؾ��մϴ�."), _T("�׸� ���� ����"), MB_ICONSTOP | MB_OK);
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
	// �̹��� ������ �����ϱ� ���� ����
	TCHAR name_filter[] = _T("�̹��� ���� (*.*)|*.*|PNG ���� (*.png)|*.png||");
	CFileDialog ins_dlg(TRUE, _T("png"), _T("*.png"), OFN_NOCHANGEDIR, name_filter);
	ins_dlg.m_ofn.nFilterIndex = 2;

	// ���� ���� ��ȭ ���� ���
	if (IDOK == ins_dlg.DoModal()) {
		// ������ �̹����� ������ ���� �̹��� ����
		if (m_item_image.IsNull() == false) { m_item_image.Destroy(); }

		// ������ �̹��� ��θ� EditCtrl�� ���
		SetDlgItemText(IDC_IMAGE_PATH_EDIT, ins_dlg.GetPathName());
		// ������ �̹����� �д´�
		m_item_image.Load(ins_dlg.GetPathName());
		// ���� �̹����� ȭ�鿡 ���
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
