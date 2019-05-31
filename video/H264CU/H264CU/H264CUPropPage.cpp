// H264CUPropPage.cpp : CH264CUPropPage ����ҳ���ʵ�֡�

#include "stdafx.h"
#include "H264CU.h"
#include "H264CUPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CH264CUPropPage, COlePropertyPage)

// ��Ϣӳ��

BEGIN_MESSAGE_MAP(CH264CUPropPage, COlePropertyPage)
END_MESSAGE_MAP()

// ��ʼ���๤���� guid

IMPLEMENT_OLECREATE_EX(CH264CUPropPage, "H264CU.H264CUPropPage.1",
	0xff251c07, 0x4bd3, 0x41e0, 0x8a, 0xfe, 0xb7, 0x66, 0x9c, 0x10, 0xd7, 0xe6)

// CH264CUPropPage::CH264CUPropPageFactory::UpdateRegistry -
// ��ӻ��Ƴ� CH264CUPropPage ��ϵͳע�����

BOOL CH264CUPropPage::CH264CUPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_H264CU_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}

// CH264CUPropPage::CH264CUPropPage - ���캯��

CH264CUPropPage::CH264CUPropPage() :
	COlePropertyPage(IDD, IDS_H264CU_PPG_CAPTION)
{
}

// CH264CUPropPage::DoDataExchange - ��ҳ�����Լ��ƶ�����

void CH264CUPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}

// CH264CUPropPage ��Ϣ�������
