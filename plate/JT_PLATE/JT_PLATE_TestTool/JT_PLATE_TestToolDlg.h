
// JT_PLATE_TestToolDlg.h : 头文件
//

#pragma once

#define WM_MYMSG WM_USER+8

// CJT_PLATE_TestToolDlg 对话框
class CJT_PLATE_TestToolDlg : public CDialogEx
{
// 构造
public:
	CJT_PLATE_TestToolDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_JT_PLATE_TESTTOOL_DIALOG };

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
    afx_msg void OnBnClickedButtoninitdevice();
    afx_msg void OnBnClickedButtonClosedevice();
    afx_msg void OnBnClickedButtonGetinfo();
    afx_msg void OnBnClickedButtonGetstate();
    afx_msg void OnBnClickedButtonGetimage();
    afx_msg void OnBnClickedButtonCapture();
    afx_msg void OnBnClickedButtonTakephoto();

protected:
    afx_msg LRESULT OnUserResult(WPARAM wParam, LPARAM lParam);
};
