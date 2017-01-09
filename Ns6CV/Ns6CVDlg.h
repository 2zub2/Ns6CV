
// Ns6CVDlg.h : файл заголовка
//

#pragma once

#include "CV.cpp"

// диалоговое окно CNs6CVDlg
class CNs6CVDlg : public CDialogEx
{
// Создание
public:
	CNs6CVDlg(CWnd* pParent = NULL);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NS6CV_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString edtFileName;

	afx_msg void OnBnClickedButtonOpenImage();
	afx_msg void OnBnClickedButtonGo();
	CV img;
	afx_msg void OnBnClickedButtonLoadImage();
	afx_msg void OnBnClickedButtonView();
	CString edtSaveFileName;
	afx_msg void OnBnClickedButtonSave();
	int edtRemoveLightMethod;
	afx_msg void OnBnClickedButton3();
	double edtTresh;
	double edtMaxval;
	int edtTresholdMethod;
	afx_msg void OnBnClickedButtonTreshold();
	int edtErosionSize;
	afx_msg void OnBnClickedButtonErosion();
};
