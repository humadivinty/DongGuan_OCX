
// mfc_ocx_demoDlg.h : ͷ�ļ�
//

#pragma once
#include "CDH264CU.h"


// Cmfc_ocx_demoDlg �Ի���
class Cmfc_ocx_demoDlg : public CDialogEx
{
// ����
public:
	Cmfc_ocx_demoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MFC_OCX_DEMO_DIALOG };

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
