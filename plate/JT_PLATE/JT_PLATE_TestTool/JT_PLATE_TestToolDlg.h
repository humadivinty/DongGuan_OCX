
// JT_PLATE_TestToolDlg.h : ͷ�ļ�
//

#pragma once

#define WM_MYMSG WM_USER+8

// CJT_PLATE_TestToolDlg �Ի���
class CJT_PLATE_TestToolDlg : public CDialogEx
{
// ����
public:
	CJT_PLATE_TestToolDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_JT_PLATE_TESTTOOL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
