
// mfc_ocx_demo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Cmfc_ocx_demoApp: 
// �йش����ʵ�֣������ mfc_ocx_demo.cpp
//

class Cmfc_ocx_demoApp : public CWinApp
{
public:
	Cmfc_ocx_demoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Cmfc_ocx_demoApp theApp;