
// JT_PLATE_TestTool.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CJT_PLATE_TestToolApp: 
// �йش����ʵ�֣������ JT_PLATE_TestTool.cpp
//

class CJT_PLATE_TestToolApp : public CWinApp
{
public:
	CJT_PLATE_TestToolApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CJT_PLATE_TestToolApp theApp;