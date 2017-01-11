
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
	CString edtSaveFileName;

	afx_msg void OnBnClickedButtonOpenImage();
	afx_msg void OnBnClickedButtonGo();
	CV workImage;
	afx_msg void OnBnClickedButtonLoadImage();
	afx_msg void OnBnClickedButtonView();
	
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButtonTreshold();
	afx_msg void OnBnClickedButtonErosion();
	afx_msg void OnBnClickedButtonOpenProperty();
	CString edtOptionFileName;
};
