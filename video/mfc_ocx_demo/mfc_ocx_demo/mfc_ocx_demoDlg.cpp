
// mfc_ocx_demoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "mfc_ocx_demo.h"
#include "mfc_ocx_demoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int GetIntValueFromCString(CString& tempStr);
void GetStringValueFromCString(CString& tempStr, char* pbuffer, size_t bufSize);


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


// Cmfc_ocx_demoDlg �Ի���



Cmfc_ocx_demoDlg::Cmfc_ocx_demoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cmfc_ocx_demoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cmfc_ocx_demoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Cmfc_ocx_demoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BUTTON_LogOut, &Cmfc_ocx_demoDlg::OnBnClickedButtonLogout)
    ON_BN_CLICKED(IDC_BUTTON_Login, &Cmfc_ocx_demoDlg::OnBnClickedButtonLogin)
    ON_BN_CLICKED(IDC_BUTTON_OpenVideo, &Cmfc_ocx_demoDlg::OnBnClickedButtonOpenvideo)
    ON_BN_CLICKED(IDC_BUTTON_SetOSDUserDefInfo, &Cmfc_ocx_demoDlg::OnBnClickedButtonSetosduserdefinfo)
    ON_BN_CLICKED(IDC_BUTTON_CloseVideo, &Cmfc_ocx_demoDlg::OnBnClickedButtonClosevideo)
    ON_BN_CLICKED(IDC_BUTTON_SetCaptureMass, &Cmfc_ocx_demoDlg::OnBnClickedButtonSetcapturemass)
    ON_BN_CLICKED(IDC_BUTTON_SetOSDTimeInfo, &Cmfc_ocx_demoDlg::OnBnClickedButtonSetosdtimeinfo)
    ON_BN_CLICKED(IDC_BUTTON_SetRealTime, &Cmfc_ocx_demoDlg::OnBnClickedButtonSetrealtime)
    ON_BN_CLICKED(IDC_BUTTON_SetSystemTime, &Cmfc_ocx_demoDlg::OnBnClickedButtonSetsystemtime)
    ON_BN_CLICKED(IDC_BUTTON_DownLoadPic, &Cmfc_ocx_demoDlg::OnBnClickedButtonDownloadpic)
END_MESSAGE_MAP()


// Cmfc_ocx_demoDlg ��Ϣ�������

BOOL Cmfc_ocx_demoDlg::OnInitDialog()
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
    GetDlgItem(IDC_EDIT_color)->SetWindowText("255#255#255#100#255#255#255#100");

    m_bInitOcx = m_h264ocx.Create("LogOut", WS_CHILD | WS_VISIBLE, CRect(5, 5, 464, 261), this, 123);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void Cmfc_ocx_demoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Cmfc_ocx_demoDlg::OnPaint()
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
HCURSOR Cmfc_ocx_demoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cmfc_ocx_demoDlg::OnBnClickedButtonLogout()
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    m_h264ocx.Logout();

    CString strLog;
    strLog.Format("Logout, finish");
    MessageBox(strLog);
}


void Cmfc_ocx_demoDlg::OnBnClickedButtonLogin()
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    if (!m_bInitOcx)
    {
        MessageBox("OCX is not register, please registered it first.");
        return;
    }

    CString cstIPaddress;
    GetDlgItem(IDC_IPADDRESS1)->GetWindowText(cstIPaddress);
    char chIP[64] = {0};
    GetStringValueFromCString(cstIPaddress, chIP, sizeof(chIP));

    int iRet = m_h264ocx.Login(chIP, 123, "admin", "admin");
    CString strLog;
    strLog.Format("Login, return code = %d", iRet);
    MessageBox(strLog);
}


void Cmfc_ocx_demoDlg::OnBnClickedButtonOpenvideo()
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    if (!m_bInitOcx)
    {
        MessageBox("OCX is not register, please registered it first.");
        return;
    }

    CString cstrChannelID;
    GetDlgItem(IDC_EDIT_MASS)->GetWindowText(cstrChannelID);
    int iChannelID = GetIntValueFromCString(cstrChannelID);

    int iRet = m_h264ocx.OpenVideo(iChannelID);
    CString strLog;
    strLog.Format("OpenVideo, return code = %d", iRet);
    MessageBox(strLog);
}


void Cmfc_ocx_demoDlg::OnBnClickedButtonSetosduserdefinfo()
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    if (!m_bInitOcx)
    {
        MessageBox("OCX is not register, please registered it first.");
        return;
    }

    CString cstrChannelID;
    GetDlgItem(IDC_EDIT_channelNo)->GetWindowText(cstrChannelID);
    int iChannelID = GetIntValueFromCString(cstrChannelID);

    CString cstrIndex;
    GetDlgItem(IDC_EDIT_index)->GetWindowText(cstrIndex);
    int iIndex = GetIntValueFromCString(cstrIndex);

    CString cstrFlag;
    GetDlgItem(IDC_EDIT_FLAG)->GetWindowText(cstrFlag);
    int iFlag = GetIntValueFromCString(cstrFlag);

    CString cstrFontType;
    GetDlgItem(IDC_EDIT_fontType)->GetWindowText(cstrFontType);
    int ifontType = GetIntValueFromCString(cstrFontType);

    CString cstrFontSize;
    GetDlgItem(IDC_EDIT_fontSize)->GetWindowText(cstrFontSize);
    int iFontSize = GetIntValueFromCString(cstrFontSize);

    CString cstrPoseX;
    GetDlgItem(IDC_EDIT_posX)->GetWindowText(cstrPoseX);
    int iPosX = GetIntValueFromCString(cstrPoseX);

    CString cstrPoseY;
    GetDlgItem(IDC_EDIT_posY)->GetWindowText(cstrPoseY);
    int iPosY = GetIntValueFromCString(cstrPoseY);

    CString cstrColor;
    GetDlgItem(IDC_EDIT_color)->GetWindowText(cstrColor);
    char chColor[256] = {0};
    GetStringValueFromCString(cstrColor, chColor, sizeof(chColor));

    CString cstrLogo;
    GetDlgItem(IDC_EDIT_Logo)->GetWindowText(cstrLogo);
    char chLogo[256] = { 0 };
    GetStringValueFromCString(cstrLogo, chLogo, sizeof(chLogo));


    int iRet = m_h264ocx.SetOSDUserDefInfo(iChannelID, 
        iIndex,
        iFlag,
        chLogo,
        ifontType,
        iFontSize,
        iPosX,
        iPosY,
        chColor);
    CString strLog;
    strLog.Format("SetOSDUserDefInfo, return code = %d", iRet);
    MessageBox(strLog);
}


void Cmfc_ocx_demoDlg::OnBnClickedButtonClosevideo()
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    if (!m_bInitOcx)
    {
        MessageBox("OCX is not register, please registered it first.");
        return;
    }

    CString cstrChannelID;
    GetDlgItem(IDC_EDIT_MASS)->GetWindowText(cstrChannelID);
    int iChannelID = atoi(cstrChannelID.GetBuffer());
    cstrChannelID.ReleaseBuffer();

    m_h264ocx.CloseVideo(iChannelID);
    CString strLog;
    strLog.Format("CloseVideo finish.");
    MessageBox(strLog);
}


void Cmfc_ocx_demoDlg::OnBnClickedButtonSetcapturemass()
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    if (!m_bInitOcx)
    {
        MessageBox("OCX is not register, please registered it first.");
        return;
    }

    CString cstrMass;
    GetDlgItem(IDC_EDIT_MASS)->GetWindowText(cstrMass);
    int iMass = atoi(cstrMass.GetBuffer());
    cstrMass.ReleaseBuffer();

    CString cstrChannelID;
    GetDlgItem(IDC_EDIT_MASS)->GetWindowText(cstrChannelID);
    int iChannelID = atoi(cstrChannelID.GetBuffer());
    cstrChannelID.ReleaseBuffer();

    int iRet = m_h264ocx.SetCaptureMass(iChannelID, iMass);
    CString strLog;
    strLog.Format("SetCaptureMass, return code = %d", iRet);
    MessageBox(strLog);
}


void Cmfc_ocx_demoDlg::OnBnClickedButtonSetosdtimeinfo()
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    if (!m_bInitOcx)
    {
        MessageBox("OCX is not register, please registered it first.");
        return;
    }

    CString cstrChannelID;
    GetDlgItem(IDC_EDIT_channelNo)->GetWindowText(cstrChannelID);
    int iChannelID = GetIntValueFromCString(cstrChannelID);

    CString cstrFlag;
    GetDlgItem(IDC_EDIT_FLAG)->GetWindowText(cstrFlag);
    int iFlag = GetIntValueFromCString(cstrFlag);

    CString cstrFontType;
    GetDlgItem(IDC_EDIT_fontType)->GetWindowText(cstrFontType);
    int ifontType = GetIntValueFromCString(cstrFontType);

    CString cstrFontSize;
    GetDlgItem(IDC_EDIT_fontSize)->GetWindowText(cstrFontSize);
    int iFontSize = GetIntValueFromCString(cstrFontSize);

    CString cstrPoseX;
    GetDlgItem(IDC_EDIT_posX)->GetWindowText(cstrPoseX);
    int iPosX = GetIntValueFromCString(cstrPoseX);

    CString cstrPoseY;
    GetDlgItem(IDC_EDIT_posY)->GetWindowText(cstrPoseY);
    int iPosY = GetIntValueFromCString(cstrPoseY);

    CString cstrColor;
    GetDlgItem(IDC_EDIT_color)->GetWindowText(cstrColor);
    char chColor[256] = { 0 };
    GetStringValueFromCString(cstrColor, chColor, sizeof(chColor));

    int iRet = m_h264ocx.SetOSDTimeInfo(iChannelID,
        iFlag,
        ifontType,
        iFontSize,
        iPosX,
        iPosY,
        chColor);
    CString strLog;
    strLog.Format("SetOSDTimeInfo, return code = %d", iRet);
    MessageBox(strLog);
}


void Cmfc_ocx_demoDlg::OnBnClickedButtonSetrealtime()
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    if (!m_bInitOcx)
    {
        MessageBox("OCX is not register, please registered it first.");
        return;
    }

    CString cstrRealTime;
    GetDlgItem(IDC_EDIT_RealTime)->GetWindowText(cstrRealTime);
    int iRealTime = GetIntValueFromCString(cstrRealTime);    

    int iRet = m_h264ocx.SetRealTime(iRealTime);
    CString strLog;
    strLog.Format("SetRealTime, return code = %d", iRet);
    MessageBox(strLog);
}


void Cmfc_ocx_demoDlg::OnBnClickedButtonSetsystemtime()
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    if (!m_bInitOcx)
    {
        MessageBox("OCX is not register, please registered it first.");
        return;
    }

    CString cstrYear;
    GetDlgItem(IDC_EDIT_YEAR)->GetWindowText(cstrYear);
    int iYear = GetIntValueFromCString(cstrYear);

    CString cstrMonth;
    GetDlgItem(IDC_EDIT_MONTH)->GetWindowText(cstrMonth);
    int iMonth = GetIntValueFromCString(cstrMonth);

    CString cstrDay;
    GetDlgItem(IDC_EDIT_DAY)->GetWindowText(cstrDay);
    int iDay = GetIntValueFromCString(cstrDay);

    CString cstrHour;
    GetDlgItem(IDC_EDIT_HOUR)->GetWindowText(cstrHour);
    int iHour = GetIntValueFromCString(cstrHour);

    CString cstrMinute;
    GetDlgItem(IDC_EDIT_MINUT)->GetWindowText(cstrMinute);
    int iMinute = GetIntValueFromCString(cstrMinute);

    CString cstrSecond;
    GetDlgItem(IDC_EDIT_SECOND)->GetWindowText(cstrSecond);
    int iSecond = GetIntValueFromCString(cstrSecond);

    int iRet = m_h264ocx.SetSystemTime(iYear,
        iMonth,
        iDay,
        iHour,
        iMinute,
        iSecond);
    CString strLog;
    strLog.Format("SetSystemTime, %d-%d-%d %d:%d:%d, return code = %d",
        iYear,
        iMonth,
        iDay,
        iHour,
        iMinute,
        iSecond,
        iRet);
    MessageBox(strLog);
}

int GetIntValueFromCString(CString& tempStr)
{
    int iValue = atoi(tempStr.GetBuffer());
    tempStr.ReleaseBuffer();
    return iValue;
}

void GetStringValueFromCString(CString& tempStr, char* pbuffer, size_t bufSize)
{
    sprintf_s(pbuffer, bufSize, "%s", tempStr.GetBuffer());
    tempStr.ReleaseBuffer();
}

void Cmfc_ocx_demoDlg::OnBnClickedButtonDownloadpic()
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    if (!m_bInitOcx)
    {
        MessageBox("OCX is not register, please registered it first.");
        return;
    }

    CString cstrPath;
    GetDlgItem(IDC_EDIT_PIC_PATH)->GetWindowText(cstrPath);
    char chPath[256] = {0};
    GetStringValueFromCString(cstrPath, chPath, sizeof(chPath));

    CString cstrWidth;
    GetDlgItem(IDC_EDIT_PIC_WIdth)->GetWindowText(cstrWidth);
    int iWidth = GetIntValueFromCString(cstrWidth);

    CString cstrHeight;
    GetDlgItem(IDC_EDIT_Pic_height)->GetWindowText(cstrHeight);
    int iHeight = GetIntValueFromCString(cstrHeight);

    int iRet = m_h264ocx.DownLoadPic(chPath, iWidth, iHeight);
    CString strLog;
    strLog.Format("DownLoadPic, width = %d, height = %d, return code = %d", iWidth, iHeight, iRet);
    MessageBox(strLog);
}
