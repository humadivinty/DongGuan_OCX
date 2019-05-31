#pragma once

// H264CUPropPage.h : CH264CUPropPage 属性页类的声明。


// CH264CUPropPage : 有关实现的信息，请参阅 H264CUPropPage.cpp。

class CH264CUPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CH264CUPropPage)
	DECLARE_OLECREATE_EX(CH264CUPropPage)

// 构造函数
public:
	CH264CUPropPage();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_H264CU };

// 实现
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 消息映射
protected:
	DECLARE_MESSAGE_MAP()
};

