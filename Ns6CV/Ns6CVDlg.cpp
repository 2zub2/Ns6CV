
// Ns6CVDlg.cpp : ���� ����������
//

#include "stdafx.h"
#include "Ns6CV.h"
#include "Ns6CVDlg.h"
#include "afxdialogex.h"
#include "CV.cpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���������� ���� CNs6CVDlg



CNs6CVDlg::CNs6CVDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_NS6CV_DIALOG, pParent)
	, edtFileName(_T(""))
	, edtSaveFileName(_T(""))
	, edtRemoveLightMethod(0)
	, edtTresh(0)
	, edtMaxval(0)
	, edtTresholdMethod(0)
	, edtErosionSize(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNs6CVDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FILENAME, edtFileName);
	DDX_Text(pDX, IDC_EDIT_SAVENAME, edtSaveFileName);
	DDX_Text(pDX, IDC_EDIT_LIGHT_METHOD, edtRemoveLightMethod);
	DDV_MinMaxInt(pDX, edtRemoveLightMethod, 0, 1);
	DDX_Text(pDX, IDC_EDIT_TRESH, edtTresh);
	DDX_Text(pDX, IDC_EDIT_MAXVAL, edtMaxval);
	DDX_Text(pDX, IDC_EDIT_THRESHOLD_METHOD, edtTresholdMethod);
	DDX_Text(pDX, IDC_EDIT_EROSION, edtErosionSize);
}

BEGIN_MESSAGE_MAP(CNs6CVDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPEN_IMAGE, &CNs6CVDlg::OnBnClickedButtonOpenImage)
	ON_BN_CLICKED(IDC_BUTTON_GO, &CNs6CVDlg::OnBnClickedButtonGo)
	ON_BN_CLICKED(IDC_BUTTON_LOAD_IMAGE, &CNs6CVDlg::OnBnClickedButtonLoadImage)
	ON_BN_CLICKED(IDC_BUTTON_VIEW, &CNs6CVDlg::OnBnClickedButtonView)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CNs6CVDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE_LIGHT, &CNs6CVDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON_TRESHOLD, &CNs6CVDlg::OnBnClickedButtonTreshold)
	ON_BN_CLICKED(IDC_BUTTON_EROSION, &CNs6CVDlg::OnBnClickedButtonErosion)
END_MESSAGE_MAP()


// ����������� ��������� CNs6CVDlg

BOOL CNs6CVDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ������ ������ ��� ����� ����������� ����.  ����� ������ ��� �������������,
	//  ���� ������� ���� ���������� �� �������� ����������
	SetIcon(m_hIcon, TRUE);			// ������� ������
	SetIcon(m_hIcon, FALSE);		// ������ ������

	// TODO: �������� �������������� �������������

	return TRUE;  // ������� �������� TRUE, ���� ����� �� ������� �������� ����������
}

// ��� ���������� ������ ����������� � ���������� ���� ����� ��������������� ����������� ���� �����,
//  ����� ���������� ������.  ��� ���������� MFC, ������������ ������ ���������� ��� �������������,
//  ��� ������������� ����������� ������� ��������.

void CNs6CVDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �������� ���������� ��� ���������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ������������ ������ �� ������ ����������� ��������������
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ��������� ������
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ������� �������� ��� ������� ��� ��������� ����������� ������� ��� �����������
//  ���������� ����.
HCURSOR CNs6CVDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CNs6CVDlg::OnBnClickedButtonOpenImage()
{
	CFileDialog dlg(TRUE);
	dlg.m_ofn.lpstrFilter = _T("JPEG Files (*.jpg)\0*.jpg\0All Files (*.*)\0*.*\0\0");
	dlg.m_ofn.lpstrTitle = _T("Open JPEG image file");

	if (dlg.DoModal() == IDOK)
	{
		edtFileName = dlg.GetFileTitle();
		UpdateData(FALSE);
		img.fileName = img.StringFromCString(edtFileName);
	}
}


void CNs6CVDlg::OnBnClickedButtonGo()
{
	CV cv;
	int size = 0;

	CT2CA pszConvertedAnsiString(edtFileName);
	std::string strStd(pszConvertedAnsiString);

	cv.fileName = cv::String(strStd);

	for (int size = 0; size < 6; size++)
	{
		cv.erosionSize = (int)size;

		if (cv.readImage() == -1)
		{
			MessageBox(L"������ �������� �����", L"������", MB_OK);
			return;
		}

		 
		cv.proccedImage(TRUE);
	}
}


void CNs6CVDlg::OnBnClickedButtonLoadImage()
{
	if (img.readImage() == -1)
	{
		MessageBox(L"������ �������� �����", L"������", MB_OK);
		return;
	}

	return;
}


void CNs6CVDlg::OnBnClickedButtonView()
{
	img.viewImage();
}


void CNs6CVDlg::OnBnClickedButtonSave()
{
	UpdateData(TRUE);

	if (img.saveImage(img.StringFromCString(edtSaveFileName)))
	{
		MessageBox(L"������ ���������� �����", L"������", MB_OK);
	}
}


void CNs6CVDlg::OnBnClickedButton3()
{
	UpdateData(TRUE);

	img.calculateLightPattern();
	img.removeLight(edtRemoveLightMethod);
}


void CNs6CVDlg::OnBnClickedButtonTreshold()
{
	UpdateData(TRUE);

	img.calculateThreshold(edtTresh, edtMaxval, edtTresholdMethod);
}


void CNs6CVDlg::OnBnClickedButtonErosion()
{
	UpdateData(TRUE);

	img.removeErosion(edtErosionSize);
}
