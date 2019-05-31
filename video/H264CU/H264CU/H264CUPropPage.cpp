// H264CUPropPage.cpp : CH264CUPropPage 属性页类的实现。

#include "stdafx.h"
#include "H264CU.h"
#include "H264CUPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CH264CUPropPage, COlePropertyPage)

// 消息映射

BEGIN_MESSAGE_MAP(CH264CUPropPage, COlePropertyPage)
END_MESSAGE_MAP()

// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CH264CUPropPage, "H264CU.H264CUPropPage.1",
	0xff251c07, 0x4bd3, 0x41e0, 0x8a, 0xfe, 0xb7, 0x66, 0x9c, 0x10, 0xd7, 0xe6)

// CH264CUPropPage::CH264CUPropPageFactory::UpdateRegistry -
// 添加或移除 CH264CUPropPage 的系统注册表项

BOOL CH264CUPropPage::CH264CUPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_H264CU_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}

// CH264CUPropPage::CH264CUPropPage - 构造函数

CH264CUPropPage::CH264CUPropPage() :
	COlePropertyPage(IDD, IDS_H264CU_PPG_CAPTION)
{
}

// CH264CUPropPage::DoDataExchange - 在页和属性间移动数据

void CH264CUPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}

// CH264CUPropPage 消息处理程序
