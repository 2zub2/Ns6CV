
// Ns6CV.h : ������� ���� ��������� ��� ���������� PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"		// �������� �������


// CNs6CVApp:
// � ���������� ������� ������ ��. Ns6CV.cpp
//

class CNs6CVApp : public CWinApp
{
public:
	CNs6CVApp();

// ���������������
public:
	virtual BOOL InitInstance();

// ����������

	DECLARE_MESSAGE_MAP()
};

extern CNs6CVApp theApp;