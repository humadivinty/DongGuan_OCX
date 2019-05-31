
// mfc_ocx_demoDlg.h : 头文件
//

#pragma once
#include "CDH264CU.h"


// Cmfc_ocx_demoDlg 对话框
class Cmfc_ocx_demoDlg : public CDialogEx
{
// 构造
public:
	Cmfc_ocx_demoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MFC_OCX_DEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedButtonLogout();

private:
    CDH264CU m_h264ocx;
    BOOL m_bInitOcx;

public:
    afx_msg void OnBnClickedButtonLogin();
    afx_msg void OnBnClickedButtonOpenvideo();
    afx_msg void OnBnClickedButtonSetosduserdefinfo();
    afx_msg void OnBnClickedButtonClosevideo();
    afx_msg void OnBnClickedButtonSetcapturemass();
    afx_msg void OnBnClickedButtonSetosdtimeinfo();
    afx_msg void OnBnClickedButtonSetrealtime();
    afx_msg void OnBnClickedButtonSetsystemtime();
    afx_msg void OnBnClickedButtonDownloadpic();
};
