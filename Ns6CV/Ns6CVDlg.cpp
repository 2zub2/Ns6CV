
// Ns6CVDlg.cpp : ���� ����������
//

#include "stdafx.h"
#include "Ns6CV.h"
#include "Ns6CVDlg.h"
#include "afxdialogex.h"
#include "CV.cpp"
#include "settingsTV.h"
#include <Pathcch.h>

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
		edtFileName.GetS
		PathCchRemoveFileSpec(&(), NULL);
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
	
	SCL::settingsTV sclSettings;

	SCL::setting_initializer pgmInitialSettings[] =
	{
		{ "", ".SettingsVersion"  , ST_STR, "1.00.01", "Settings Version" },
		{ "", "ParmGlobalUI16"    , ST_UI16, "3"              , "" },
		{ "Section1","ParmBOOL"   , ST_BOOL, "FALSE"          , "" },
		{ "Section2","ParmUINT08" , ST_UI8 , "255"            , "" },
		{ "Section2","ParmUINT16" , ST_UI16, "65535"          , "" },
		{ "Section2","ParmUINT32" , ST_UI32, "4294967295abcd" , "" },
		{ "Section2","ParmUINT64" , ST_UI64, "42949672959999" , "" },
		{ "Section3","ParmINT08N" , ST_I8  , "-128"           , "" },
		{ "Section3","ParmINT08P" , ST_I8  ,  "127"           , "" },
		{ "Section3","ParmINT16N" , ST_I16 , "-32768"         , "" },
		{ "Section3","ParmINT16P" , ST_I16 ,  "32767"         , "" },
		{ "Section3","ParmINT32P" , ST_I32 , "2147483647"     , "" },
		{ "Section3","ParmINT32N" , ST_I32 , "-2147483648"    , "is an int32" },
		{ "Section3","ParmINT64P" , ST_I64 , "42949672959999" , "" },
		{ "Section3","ParmINT64N" , ST_I64 , "-42949672959999", "" },
		{ "Section4","ParmDBLE64" , ST_DBL , "5.1234567890123456", "" },
		{ "Section5","ParmSTRING" , ST_STR , "some string", "string type" },
		{ "Se\xe0\xb4\x95tion"    ,"ParmUTF8\xe0\xb4\x87STR", ST_STR , "some\xe3\x97\x94str\xe0\xb4\x86ng", "UTF-8 encoded strings" },
	};

	uint32_t numSettings =
		sizeof(pgmInitialSettings) / sizeof(SCL::setting_initializer);

	uint32_t rc = sclSettings.init(numSettings, pgmInitialSettings);

	string filename = "settings.txt";

	SCL::SettingsExportErrType erc =
		sclSettings.saveSettingsToFile(filename, true); // over-write
	if (erc = SCL::SERC_SUCCESS)
	{
		MessageBox(L"������ �������� �����", L"������", MB_OK);
	}

	
	//img.removeErosion(edtErosionSize);
}
