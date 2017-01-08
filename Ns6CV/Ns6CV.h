
// Ns6CV.h : главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CNs6CVApp:
// О реализации данного класса см. Ns6CV.cpp
//

class CNs6CVApp : public CWinApp
{
public:
	CNs6CVApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CNs6CVApp theApp;