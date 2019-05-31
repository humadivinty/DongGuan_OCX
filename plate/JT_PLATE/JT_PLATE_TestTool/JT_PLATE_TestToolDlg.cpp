
// JT_PLATE_TestToolDlg.cpp : 实现文件
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


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CJT_PLATE_TestToolDlg 对话框



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


// CJT_PLATE_TestToolDlg 消息处理程序

BOOL CJT_PLATE_TestToolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
    ((CComboBox*)GetDlgItem(IDC_COMBO_IMGTYPE))->AddString("0");
    ((CComboBox*)GetDlgItem(IDC_COMBO_IMGTYPE))->AddString("1");
    ((CComboBox*)GetDlgItem(IDC_COMBO_IMGTYPE))->AddString("2");
    ((CComboBox*)GetDlgItem(IDC_COMBO_IMGTYPE))->AddString("3");

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CJT_PLATE_TestToolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CJT_PLATE_TestToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CJT_PLATE_TestToolDlg::OnBnClickedButtoninitdevice()
{
    // TODO:  在此添加控件通知处理程序代码
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
    // TODO:  在此添加控件通知处理程序代码
    BOOL bRet = Plate_CloseDevice();
    CString cstrLog;
    cstrLog.Format("Plate_CloseDevice,  return value = %d", bRet);
    MessageBox(cstrLog);
}


void CJT_PLATE_TestToolDlg::OnBnClickedButtonGetinfo()
{
    // TODO:  在此添加控件通知处理程序代码
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
    // TODO:  在此添加控件通知处理程序代码
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
    // TODO:  在此添加控件通知处理程序代码
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
    // TODO:  在此添加控件通知处理程序代码
    BOOL bRet = Plate_Capture();

    CString cstrLog;
    cstrLog.Format("Plate_Capture,return value = %d ", bRet);
    MessageBox(cstrLog);
}


void CJT_PLATE_TestToolDlg::OnBnClickedButtonTakephoto()
{
    // TODO:  在此添加控件通知处理程序代码
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
