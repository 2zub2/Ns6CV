
// Ns6CVDlg.h : ���� ���������
//

#pragma once

#include "CV.cpp"

// ���������� ���� CNs6CVDlg
class CNs6CVDlg : public CDialogEx
{
// ��������
public:
	CNs6CVDlg(CWnd* pParent = NULL);	// ����������� �����������

// ������ ����������� ����
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NS6CV_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// ��������� DDX/DDV


// ����������
protected:
	HICON m_hIcon;

	// ��������� ������� ����� ���������
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
