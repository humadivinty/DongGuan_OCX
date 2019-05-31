
// JT_PLATE_TestToolDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "JT_PLATE_TestTool.h"
#include "JT_PLATE_TestToolDlg.h"
#include "afxdialogex.h"
#include "ToolFunc.h"

#include "../JT_PLATE/JT_PLATE.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifdef DEBUG
#pragma comment(lib, "../debug/JT_PLATE.lib")
#else
#pragma comment(lib, "../release/JT_PLATE.lib")
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CJT_PLATE_TestToolDlg �Ի���



CJT_PLATE_TestToolDlg::CJT_PLATE_TestToolDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CJT_PLATE_TestToolDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CJT_PLATE_TestToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CJT_PLATE_TestToolDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_MESSAGE(WM_MYMSG, &CJT_PLATE_TestToolDlg::OnUserResult)
    ON_BN_CLICKED(IDC_BUTTON_initDevice, &CJT_PLATE_TestToolDlg::OnBnClickedButtoninitdevice)
    ON_BN_CLICKED(IDC_BUTTON_CloseDevice, &CJT_PLATE_TestToolDlg::OnBnClickedButtonClosedevice)
    ON_BN_CLICKED(IDC_BUTTON_Getinfo, &CJT_PLATE_TestToolDlg::OnBnClickedButtonGetinfo)
    ON_BN_CLICKED(IDC_BUTTON_GetState, &CJT_PLATE_TestToolDlg::OnBnClickedButtonGetstate)
    ON_BN_CLICKED(IDC_BUTTON_GetImage, &CJT_PLATE_TestToolDlg::OnBnClickedButtonGetimage)
    ON_BN_CLICKED(IDC_BUTTON_Capture, &CJT_PLATE_TestToolDlg::OnBnClickedButtonCapture)
    ON_BN_CLICKED(IDC_BUTTON_TakePhoto, &CJT_PLATE_TestToolDlg::OnBnClickedButtonTakephoto)
END_MESSAGE_MAP()


// CJT_PLATE_TestToolDlg ��Ϣ�������

BOOL CJT_PLATE_TestToolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
    ((CComboBox*)GetDlgItem(IDC_COMBO_IMGTYPE))->AddString("0");
    ((CComboBox*)GetDlgItem(IDC_COMBO_IMGTYPE))->AddString("1");
    ((CComboBox*)GetDlgItem(IDC_COMBO_IMGTYPE))->AddString("2");
    ((CComboBox*)GetDlgItem(IDC_COMBO_IMGTYPE))->AddString("3");

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CJT_PLATE_TestToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CJT_PLATE_TestToolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CJT_PLATE_TestToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CJT_PLATE_TestToolDlg::OnBnClickedButtoninitdevice()
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    CString cstrCamIP;
    GetDlgItem(IDC_IPADDRESS1)->GetWindowText(cstrCamIP);

    char chIp[64] = {0};
    strcpy_s(chIp, sizeof(chIp), cstrCamIP.GetBuffer());
    cstrCamIP.ReleaseBuffer();

    BOOL bRet = Plate_InitDevice(m_hWnd, WM_MYMSG, 2, chIp, 9600);
    CString cstrLog;
    cstrLog.Format("Plate_InitDevice, handle = %p, msg = %d, ip address = %s, return value = %d",
        m_hWnd,
        WM_MYMSG,
        chIp,
        bRet);
    MessageBox(cstrLog);
}


void CJT_PLATE_TestToolDlg::OnBnClickedButtonClosedevice()
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    BOOL bRet = Plate_CloseDevice();
    CString cstrLog;
    cstrLog.Format("Plate_CloseDevice,  return value = %d", bRet);
    MessageBox(cstrLog);
}


void CJT_PLATE_TestToolDlg::OnBnClickedButtonGetinfo()
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    char chPlateNo[64] = {0};
    char chPlateColor = 0;
    BOOL bRet = Plate_Getinfo(chPlateNo, &chPlateColor);

    char szPlateColor[32] = {};
    sprintf_s(szPlateColor, sizeof(szPlateColor), "%d", chPlateColor);

    GetDlgItem(IDC_STATIC_plateNo)->SetWindowText(chPlateNo);
    GetDlgItem(IDC_STATIC_plateColor)->SetWindowText(szPlateColor);

    CString cstrLog;
    cstrLog.Format("Plate_Getinfo, chPlateNo = %s, chPlateColor =%d, return value = %d ",
        chPlateNo,
        szPlateColor,
        bRet);

    //MessageBox(cstrLog);
}


void CJT_PLATE_TestToolDlg::OnBnClickedButtonGetstate()
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    int iStatus = 0;
    BOOL bRet = Plate_GetState(&iStatus);
    char chTemp[256] = {0};
    sprintf_s(chTemp, sizeof(chTemp), "%d", iStatus);
    GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(chTemp);

    CString cstrLog;
    cstrLog.Format("Plate_GetState, iStatus =%d, return value = %d ",
        iStatus,
        bRet);
}


void CJT_PLATE_TestToolDlg::OnBnClickedButtonGetimage()
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    CString cstrImgType;
    GetDlgItem(IDC_COMBO_IMGTYPE)->GetWindowText(cstrImgType);
    int iImgType = atoi(cstrImgType.GetBuffer());
    cstrImgType.ReleaseBuffer();

    char chPath[256] = {0};
    switch (iImgType)
    {
    case 0:
        sprintf_s(chPath, sizeof(chPath), "%s\\result\\%lu_bin.bin", Tool_GetCurrentAppPath(), GetTickCount());
        break;
    case 1:
        sprintf_s(chPath, sizeof(chPath), "%s\\result\\%lu_small.bmp", Tool_GetCurrentAppPath(), GetTickCount());
        break;
    case 2:
        sprintf_s(chPath, sizeof(chPath), "%s\\result\\%lu_head.jpg", Tool_GetCurrentAppPath(), GetTickCount());
        break;
    case 3:
        sprintf_s(chPath, sizeof(chPath), "%s\\result\\%lu_full.jpg", Tool_GetCurrentAppPath(), GetTickCount());
        break;
    default:
        sprintf_s(chPath, sizeof(chPath), "%s\\result\\%lu_full.jpg", Tool_GetCurrentAppPath(), GetTickCount());
        break;
    }

    BOOL bRet = Plate_GetImage(iImgType, chPath);
    CString cstrLog;
    cstrLog.Format("Plate_GetImage, iImgType =%d, chPath = %s, return value = %d ",
        iImgType,
        chPath,
        bRet);

    GetDlgItem(IDC_STATIC_ResultPath)->SetWindowTextA(chPath);
}


void CJT_PLATE_TestToolDlg::OnBnClickedButtonCapture()
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    BOOL bRet = Plate_Capture();

    CString cstrLog;
    cstrLog.Format("Plate_Capture,return value = %d ", bRet);
    MessageBox(cstrLog);
}


void CJT_PLATE_TestToolDlg::OnBnClickedButtonTakephoto()
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    char chPath[256] = {0};
    sprintf_s(chPath, sizeof(chPath), "%s\\Result\\Capture_%lu.jpg", Tool_GetCurrentAppPath(), GetTickCount());
    BOOL bRet = Plate_TakePhoto(chPath);

    CString cstrLog;
    cstrLog.Format("Plate_TakePhoto,return value = %d ", bRet);
    MessageBox(cstrLog);
}

LRESULT CJT_PLATE_TestToolDlg::OnUserResult(WPARAM wParam, LPARAM lParam)
{

    OnBnClickedButtonGetinfo();
    int iImgType = 0;
    BOOL bRet = FALSE;
    char chPath[256] = { 0 };
    DWORD dwTime = GetTickCount();
    for (int i = 0; i < 4; i++)
    {
        iImgType = i;

        switch (iImgType)
        {
        case 0:
            sprintf_s(chPath, sizeof(chPath), "%s\\result\\%lu_bin.bin", Tool_GetCurrentAppPath(), dwTime);
            break;
        case 1:
            sprintf_s(chPath, sizeof(chPath), "%s\\result\\%lu_small.bmp", Tool_GetCurrentAppPath(), dwTime);
            break;
        case 2:
            sprintf_s(chPath, sizeof(chPath), "%s\\result\\%lu_head.jpg", Tool_GetCurrentAppPath(), dwTime);
            break;
        case 3:
            sprintf_s(chPath, sizeof(chPath), "%s\\result\\%lu_full.jpg", Tool_GetCurrentAppPath(), dwTime);
            break;
        default:
            sprintf_s(chPath, sizeof(chPath), "%s\\result\\%lu_full.jpg", Tool_GetCurrentAppPath(), dwTime);
            break;
        }
        if (Plate_GetImage(iImgType, chPath) == TRUE)
        {
            GetDlgItem(IDC_STATIC_ResultPath)->SetWindowTextA(chPath);
        }        
    }   
    return 0;
}
