#pragma once

// H264CUPropPage.h : CH264CUPropPage ����ҳ���������


// CH264CUPropPage : �й�ʵ�ֵ���Ϣ������� H264CUPropPage.cpp��

class CH264CUPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CH264CUPropPage)
	DECLARE_OLECREATE_EX(CH264CUPropPage)

// ���캯��
public:
	CH264CUPropPage();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_H264CU };

// ʵ��
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ��Ϣӳ��
protected:
	DECLARE_MESSAGE_MAP()
};

