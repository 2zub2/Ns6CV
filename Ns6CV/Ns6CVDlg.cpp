
// Ns6CVDlg.cpp : файл реализации
//

#include "stdafx.h"
#include "Ns6CV.h"
#include "Ns6CVDlg.h"
#include "afxdialogex.h"
#include "CV.cpp"
#include <Pathcch.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// диалоговое окно CNs6CVDlg



CNs6CVDlg::CNs6CVDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_NS6CV_DIALOG, pParent)
	, edtFileName(_T(""))
	, edtSaveFileName(_T(""))
	, edtOptionFileName(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNs6CVDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FILENAME, edtFileName);
	DDX_Text(pDX, IDC_EDIT_SAVENAME, edtSaveFileName);
	DDX_Text(pDX, IDC_EDIT_PROPERTY_FILENAME, edtOptionFileName);
}

BEGIN_MESSAGE_MAP(CNs6CVDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPEN_IMAGE, &CNs6CVDlg::OnBnClickedButtonOpenImage)
	ON_BN_CLICKED(IDC_BUTTON_GO, &CNs6CVDlg::OnBnClickedButtonGo)
	ON_BN_CLICKED(IDC_BUTTON_LOAD_IMAGE, &CNs6CVDlg::OnBnClickedButtonLoadImage)
	ON_BN_CLICKED(IDC_BUTTON_VIEW, &CNs6CVDlg::OnBnClickedButtonView)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CNs6CVDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_PROPERTY, &CNs6CVDlg::OnBnClickedButtonOpenProperty)
END_MESSAGE_MAP()


// обработчики сообщений CNs6CVDlg

BOOL CNs6CVDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CNs6CVDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CNs6CVDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CNs6CVDlg::OnBnClickedButtonOpenImage()
{
	CFileDialog dlg(TRUE);
	dlg.m_ofn.lpstrFilter = _T("Image file (*.jpg)\0*.jpg\0All Files (*.*)\0*.*\0\0");
	dlg.m_ofn.lpstrTitle = _T("Open image file");

	if (dlg.DoModal() == IDOK)
	{
		edtFileName = dlg.GetPathName();
		UpdateData(FALSE);
		CT2CA pszConvertedAnsiString(edtFileName);
		std::string strStd(pszConvertedAnsiString);
		workImage.setFileName(strStd);
	}
}


void CNs6CVDlg::OnBnClickedButtonGo()
{

}


void CNs6CVDlg::OnBnClickedButtonLoadImage()
{
	if (workImage.readImage() == -1)
	{
		MessageBox(L"ошибка загрузки файла", L"ошибка", MB_OK);
		return;
	}

	return;
}


void CNs6CVDlg::OnBnClickedButtonView()
{
	workImage.viewImage();
}


void CNs6CVDlg::OnBnClickedButtonSave()
{
	UpdateData(TRUE);

	if (workImage.saveImage())
	{
		MessageBox(L"ошибка сохранения файла", L"ошибка", MB_OK);
	}
}



void CNs6CVDlg::OnBnClickedButtonOpenProperty()
{
	CFileDialog dlg(TRUE);
	dlg.m_ofn.lpstrFilter = _T("Config file (*.cfg)\0*.jpg\0All Files (*.*)\0*.*\0\0");
	dlg.m_ofn.lpstrTitle = _T("Config image file");

	if (dlg.DoModal() == IDOK)
	{
		edtOptionFileName = dlg.GetPathName();
		UpdateData(FALSE);
		CT2CA pszConvertedAnsiString(edtOptionFileName);
		std::string strStd(pszConvertedAnsiString);
		workImage.readSettings(strStd);
		workImage.prepareSettingsTemplate();
	}
}
