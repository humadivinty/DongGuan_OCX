// H264CUCtrl.cpp : CH264CUCtrl ActiveX 控件类的实现。

#include "stdafx.h"
#include "H264CU.h"
#include "H264CUCtrl.h"
#include "H264CUPropPage.h"
#include "afxdialogex.h"

#include "utilityTool/ToolFunction.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CH264CUCtrl, COleControl)

// 消息映射

BEGIN_MESSAGE_MAP(CH264CUCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()

// 调度映射

BEGIN_DISPATCH_MAP(CH264CUCtrl, COleControl)
	DISP_FUNCTION_ID(CH264CUCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
    DISP_FUNCTION_ID(CH264CUCtrl, "Login", dispidLogin, Login, VT_I2, VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR)
    DISP_FUNCTION_ID(CH264CUCtrl, "Logout", dispidLogout, Logout, VT_EMPTY, VTS_NONE)
    DISP_FUNCTION_ID(CH264CUCtrl, "OpenVideo", dispidOpenVideo, OpenVideo, VT_I2, VTS_I2)
    DISP_FUNCTION_ID(CH264CUCtrl, "CloseVideo", dispidCloseVideo, CloseVideo, VT_EMPTY, VTS_I2)
    DISP_FUNCTION_ID(CH264CUCtrl, "SetCaptureMass", dispidSetCaptureMass, SetCaptureMass, VT_I2, VTS_I2 VTS_I2)
    DISP_FUNCTION_ID(CH264CUCtrl, "GetCaptureMass", dispidGetCaptureMass, GetCaptureMass, VT_I2, VTS_I2)
    DISP_FUNCTION_ID(CH264CUCtrl, "SetOSDTimeInfo", dispidSetOSDTimeInfo, SetOSDTimeInfo, VT_I2, VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_BSTR)
    DISP_FUNCTION_ID(CH264CUCtrl, "GetOSDTimeInfo", dispidGetOSDTimeInfo, GetOSDTimeInfo, VT_I2, VTS_I2)
    DISP_FUNCTION_ID(CH264CUCtrl, "ColorDlg", dispidColorDlg, ColorDlg, VT_BSTR, VTS_I2 VTS_I2 VTS_I2)
    DISP_FUNCTION_ID(CH264CUCtrl, "SetOSDLogoInfo", dispidSetOSDLogoInfo, SetOSDLogoInfo, VT_I2, VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_BSTR)
    DISP_FUNCTION_ID(CH264CUCtrl, "GetOSDLogoInfo", dispidGetOSDLogoInfo, GetOSDLogoInfo, VT_I2, VTS_I2)
    DISP_FUNCTION_ID(CH264CUCtrl, "SetOSDUserDefInfo", dispidSetOSDUserDefInfo, SetOSDUserDefInfo, VT_I2, VTS_I2 VTS_I2 VTS_I2 VTS_BSTR VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_BSTR)
    DISP_FUNCTION_ID(CH264CUCtrl, "GetOSDUserDefInfo", dispidGetOSDUserDefInfo, GetOSDUserDefInfo, VT_I2, VTS_I2 VTS_I2)
    DISP_FUNCTION_ID(CH264CUCtrl, "SetRealTime", dispidSetRealTime, SetRealTime, VT_I2, VTS_I2)
    DISP_FUNCTION_ID(CH264CUCtrl, "GetRealTime", dispidGetRealTime, GetRealTime, VT_I2, VTS_NONE)
    DISP_FUNCTION_ID(CH264CUCtrl, "DownLoadPic", dispidDownLoadPic, DownLoadPic, VT_I2, VTS_BSTR VTS_I2 VTS_I2)
    DISP_FUNCTION_ID(CH264CUCtrl, "DirectoryDlg", dispidDirectoryDlg, DirectoryDlg, VT_BSTR, VTS_NONE)
    DISP_FUNCTION_ID(CH264CUCtrl, "SetSystemTime", dispidSetSystemTime, SetSystemTime, VT_I2, VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4)
END_DISPATCH_MAP()

// 事件映射

BEGIN_EVENT_MAP(CH264CUCtrl, COleControl)
    EVENT_CUSTOM_ID("FireCaptureMass", eventidFireCaptureMass, FireCaptureMass, VTS_I2)
    EVENT_CUSTOM_ID("OSDTimeInfo", eventidOSDTimeInfo, OSDTimeInfo, VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4)
    EVENT_CUSTOM_ID("OSDLogoInfo", eventidOSDLogoInfo, OSDLogoInfo, VTS_I4 VTS_BSTR VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4)
    EVENT_CUSTOM_ID("OSDUserDefInfo", eventidOSDUserDefInfo, OSDUserDefInfo, VTS_I4 VTS_BSTR VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4)
END_EVENT_MAP()

// 属性页

// TODO:  按需要添加更多属性页。  请记住增加计数!
BEGIN_PROPPAGEIDS(CH264CUCtrl, 1)
	PROPPAGEID(CH264CUPropPage::guid)
END_PROPPAGEIDS(CH264CUCtrl)

// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CH264CUCtrl, "H264CU.H264CUCtrl.1",
	0xa73f9a4, 0xc4c3, 0x41f6, 0x97, 0xc3, 0x76, 0xd, 0xec, 0xcc, 0xe3, 0xa7)

// 键入库 ID 和版本

IMPLEMENT_OLETYPELIB(CH264CUCtrl, _tlid, _wVerMajor, _wVerMinor)

// 接口 ID

const IID IID_DH264CU = { 0x47E7AE4C, 0xF5F0, 0x448B, { 0x90, 0x80, 0x5, 0x2A, 0x28, 0xF5, 0x8D, 0x8F } };
const IID IID_DH264CUEvents = { 0xCDF74B1B, 0x45E8, 0x42C8, { 0x8C, 0x79, 0xA8, 0xAA, 0xBA, 0xD8, 0xD3, 0x97 } };

// 控件类型信息

static const DWORD _dwH264CUOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CH264CUCtrl, IDS_H264CU, _dwH264CUOleMisc)

// CH264CUCtrl::CH264CUCtrlFactory::UpdateRegistry -
// 添加或移除 CH264CUCtrl 的系统注册表项

BOOL CH264CUCtrl::CH264CUCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO:  验证您的控件是否符合单元模型线程处理规则。
	// 有关更多信息，请参考 MFC 技术说明 64。
	// 如果您的控件不符合单元模型规则，则
	// 必须修改如下代码，将第六个参数从
	// afxRegApartmentThreading 改为 0。

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_H264CU,
			IDB_H264CU,
			afxRegApartmentThreading,
			_dwH264CUOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


// CH264CUCtrl::CH264CUCtrl - 构造函数

CH264CUCtrl::CH264CUCtrl()
{
	InitializeIIDs(&IID_DH264CU, &IID_DH264CUEvents);
	// TODO:  在此初始化控件的实例数据。
    Tool_WriteFormatLog("CH264CUCtrl()");
    InitializationOverlayText();
    m_pCamera6467 = nullptr;
    m_pImgData = nullptr;

}

// CH264CUCtrl::~CH264CUCtrl - 析构函数

CH264CUCtrl::~CH264CUCtrl()
{
	// TODO:  在此清理控件的实例数据。
    Tool_WriteFormatLog("~CH264CUCtrl()");
}

// CH264CUCtrl::OnDraw - 绘图函数

void CH264CUCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& /* rcInvalid */)
{
	if (!pdc)
		return;

	// TODO:  用您自己的绘图代码替换下面的代码。
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);
}

// CH264CUCtrl::DoPropExchange - 持久性支持

void CH264CUCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO:  为每个持久的自定义属性调用 PX_ 函数。
}


// CH264CUCtrl::GetControlFlags -
// 自定义 MFC 的 ActiveX 控件实现的标志。
//
DWORD CH264CUCtrl::GetControlFlags()
{
	DWORD dwFlags = COleControl::GetControlFlags();


	// 在活动和不活动状态之间进行转换时，
	// 不会重新绘制控件。
	dwFlags |= noFlickerActivate;
	return dwFlags;
}


// CH264CUCtrl::OnResetState - 将控件重置为默认状态

void CH264CUCtrl::OnResetState()
{
	COleControl::OnResetState();  // 重置 DoPropExchange 中找到的默认值

	// TODO:  在此重置任意其他控件状态。
}


// CH264CUCtrl::AboutBox - 向用户显示“关于”框

void CH264CUCtrl::AboutBox()
{
	CDialogEx dlgAbout(IDD_ABOUTBOX_H264CU);
	dlgAbout.DoModal();
}


// CH264CUCtrl 消息处理程序


SHORT CH264CUCtrl::Login(LPCTSTR SeverIP, LONG ServerPort, LPCTSTR LoginName, LPCTSTR LoginPsw)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO:  在此添加调度处理程序代码

    Tool_WriteFormatLog("Login:: SeverIP = %s, ServerPort = %d, LoginName = %s, LoginPsw= %s",
        SeverIP,
        ServerPort,
        LoginName,
        LoginPsw);

    std::string strPlateIp(SeverIP);
    if (m_pCamera6467 != NULL
        && 0 == strcmp(strPlateIp.c_str(), m_pCamera6467->GetCameraIP())
        )
    {
        Tool_WriteFormatLog("Login, the camera %s is already connecting, return true.", strPlateIp.c_str());
        return 0;
    }
    int iRet = -1;
    m_pCamera6467 = std::make_shared<Camera6467_plate>();
    if (m_pCamera6467)
    {
        m_pCamera6467->SetCameraIP(SeverIP);
        iRet = m_pCamera6467->ConnectToCamera();
        Tool_WriteFormatLog("Login, ConnectToCamera , code = %d.", iRet);
    }
    else
    {
        Tool_WriteFormatLog("Login, create camera failed.");
    }
    if (iRet != 0)
    {
        iRet = -1;
    }

    Tool_WriteFormatLog("Login::  finish, return code = %d",iRet);
    return iRet;
}


void CH264CUCtrl::Logout()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    
    // TODO:  在此添加调度处理程序代码
    Tool_WriteFormatLog("Logout::  begin");
    m_pCamera6467 = nullptr;
    Tool_WriteFormatLog("Logout::  finish.");
}


SHORT CH264CUCtrl::OpenVideo(SHORT Channel)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO:  在此添加调度处理程序代码
    Tool_WriteFormatLog("OpenVideo::  begin, Channel = %d", Channel);
    if (m_pCamera6467 == nullptr)
    {
        Tool_WriteFormatLog("OpenVideo::  camera is not init, please init first.");
        return -1;
    }
    int iChannelID = Channel > 1 ? 1 : 0;
    m_pCamera6467->StartPlayVideoByChannel(iChannelID, this->GetSafeHwnd());

    Tool_WriteFormatLog("OpenVideo::  finish.");
    return 0;
}


void CH264CUCtrl::CloseVideo(SHORT Channel)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO:  在此添加调度处理程序代码
    Tool_WriteFormatLog("CloseVideo::  begin, Channel = %d", Channel);
    if (m_pCamera6467 == nullptr)
    {
        Tool_WriteFormatLog("CloseVideo::  camera is not init, please init first.");
        return;
    }
    int iChannelID = Channel > 1 ? 1 : 0;
    m_pCamera6467->StopPlayVideoByChannel(iChannelID);

    Tool_WriteFormatLog("CloseVideo::  finish.");
}


SHORT CH264CUCtrl::SetCaptureMass(SHORT channelNo, SHORT iMass)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO:  在此添加调度处理程序代码
    Tool_WriteFormatLog("SetCaptureMass::  begin, Channel = %d, iMass = %d", channelNo, iMass);
    if (m_pCamera6467 == nullptr)
    {
        Tool_WriteFormatLog("SetCaptureMass::  camera is not init, please init first.");
        return -1;
    }
    int iQuality = 30;
    switch (iMass)
    {
    case 0:
        iQuality = 100; 
        break;
    case 1:
        iQuality = 80;
        break;
    case 2:
        iQuality = 60;
        break;
    case 3:
        iQuality = 40;
        break;
    case 4:
        iQuality = 20;
        break;
    default:
        iQuality = 20;
        break;
    }
    Tool_WriteFormatLog("SetCaptureMass::  quality = %d.", iQuality);
    m_pCamera6467->SetCompressQualit(iQuality);

    Tool_WriteFormatLog("SetCaptureMass::  finish.");
    return 0;
}


SHORT CH264CUCtrl::GetCaptureMass(SHORT channelNo)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO:  在此添加调度处理程序代码
    //该方法不用实现
    return 0;
}


SHORT CH264CUCtrl::SetOSDTimeInfo(SHORT channelNo, 
    SHORT timeFlag,
    SHORT fontType,
    SHORT fontSize, 
    SHORT timeX,
    SHORT timeY,
    LPCTSTR color)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO:  在此添加调度处理程序代码
    Tool_WriteFormatLog("SetOSDTimeInfo::  channelNo = %d. \
        timeFlag = %d,  \
        fontType = %d,  \
        fontSize = %d,  \
        timeX = %d,  \
        timeY = %d, \
        color = %s",
        channelNo,
        timeFlag,
        fontType,
        fontSize,
        timeX,
        timeY,
        color);

    if (m_pCamera6467 == nullptr)
    {
        Tool_WriteFormatLog("SetOSDTimeInfo::  camera is not init, please init first.");
        return -1;
    }

    int iChanelNo = m_pCamera6467->ConvertIDToStreamID(channelNo);
    Tool_WriteFormatLog("convert channel ID  %d to video stream ID %d .", channelNo, iChanelNo);

    int iFontSize = GetFontSize(fontSize);
    int iFColorR = 255;
    int iFColorG = 255;
    int iFColorB = 255;
    int iFColorAlpha = 255;
    int iBColorR = 255;
    int iBColorG = 255;
    int iBColorB = 255;
    int iBColorAlpha = 255;
    if (!GetColor(color, iFColorR, iFColorG, iFColorB, iFColorAlpha, iBColorR, iBColorG, iBColorB, iBColorAlpha))
    {
        Tool_WriteFormatLog("Analysis color failed, use default.");
    }

    bool bSetEnable = true, bSetPos = true;
    if (!m_pCamera6467->SetOverlayTimeEnable(iChanelNo, (bool)timeFlag)
        && !m_pCamera6467->SetOverlayTimeEnable(1, (bool)timeFlag)
        )
    {
        Tool_WriteFormatLog("SetOverlayTimeEnable failed..");
        bSetEnable = false;
    }

    if (!m_pCamera6467->SetOverlayTimePos(iChanelNo, timeX, timeY)
        && !m_pCamera6467->SetOverlayTimePos(1, timeX, timeY)
        )
    {
        Tool_WriteFormatLog("SetOverlayTimePos failed..");
        bSetPos = false;
    }

    if (!bSetEnable && !bSetPos)
    {
        return -1;
    }
    return 0;
}


SHORT CH264CUCtrl::GetOSDTimeInfo(SHORT channelNo)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO:  在此添加调度处理程序代码
    //该方法不用实现
    return 0;
}


BSTR CH264CUCtrl::ColorDlg(SHORT byRed, SHORT byGreen, SHORT byBlue)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    CString strResult;

    // TODO:  在此添加调度处理程序代码
    //该方法不用实现

    return strResult.AllocSysString();
}


SHORT CH264CUCtrl::SetOSDLogoInfo(SHORT channelNo, 
    SHORT logoFlag,
    SHORT logo, 
    SHORT fontType, 
    SHORT fontSize, 
    SHORT logoX,
    SHORT logoY, 
    LPCTSTR color)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO:  在此添加调度处理程序代码
    //该方法不用实现

    return 0;
}


SHORT CH264CUCtrl::GetOSDLogoInfo(SHORT channelNo)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO:  在此添加调度处理程序代码
    //该方法不用实现
    return 0;
}


SHORT CH264CUCtrl::SetOSDUserDefInfo(SHORT channelNo,
    SHORT index,
    SHORT defFlag,
    LPCTSTR logo,
    SHORT fontType,
    SHORT fontSize,
    SHORT logoX,
    SHORT logoY,
    LPCTSTR color)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO:  在此添加调度处理程序代码
    Tool_WriteFormatLog("SetOSDUserDefInfo::  channelNo = %d. \
                                index = %d,  \
                                        defFlag = %d,  \
                                                logo = %s,  \
                                                        fontType = %d,  \
                                                                fontSize = %d, \
                                                                        logoX = %d, \
                                                                                logoY = %d, \
                                                                                        color = %s",
                                                                                        channelNo,
                                                                                        index,
                                                                                        defFlag,
                                                                                        logo,
                                                                                        fontType,
                                                                                        fontSize,
                                                                                        logoX,
                                                                                        logoY,
                                                                                        color);
    
    if (m_pCamera6467 == nullptr)
    {
        Tool_WriteFormatLog("SetOSDTimeInfo::  camera is not init, please init first.");
        return -1;
    }

    int iChanelNo = m_pCamera6467->ConvertIDToStreamID(channelNo);
    Tool_WriteFormatLog("convert channel ID  %d to video stream ID %d .", channelNo, iChanelNo);

    bool bSetEnable = true;
    if (!m_pCamera6467->SetOverlayVideoTextEnable(iChanelNo, (bool)defFlag)
        && !m_pCamera6467->SetOverlayVideoTextEnable(1, (bool)defFlag)
        )
    {
        Tool_WriteFormatLog("SetOSDTimeInfo::  SetOverlayVideoTextEnable, failed.");
        bSetEnable = false;
    }
    if (0 == defFlag)
    {
        Tool_WriteFormatLog("SetOSDTimeInfo::  SetOverlayVideoTextEnable,false finish.");
        return bSetEnable ? 0 : -1;
    }
    int iFontSize = GetFontSize(fontSize);

    bool bSetPos = true;
    if (!m_pCamera6467->SetOverlayVideoTextPos(iChanelNo, logoX, logoY)
        && !m_pCamera6467->SetOverlayVideoTextPos(1, logoX, logoY)
        )
    {
        Tool_WriteFormatLog("SetOSDTimeInfo::  SetOverlayVideoTextPos, failed.");
        bSetPos = false;
    }

    int iFColorR = 255;
    int iFColorG = 255;
    int iFColorB = 255;
    int iFColorAlpha = 255;
    int iBColorR = 255;
    int iBColorG = 255;
    int iBColorB = 255;
    int iBColorAlpha = 255;
    if (!GetColor(color, iFColorR, iFColorG, iFColorB, iFColorAlpha, iBColorR, iBColorG, iBColorB, iBColorAlpha))
    {
        Tool_WriteFormatLog("Analysis color failed, use default.");
    }
    bool bSetColor = true;
    if (!m_pCamera6467->SetOverlayVedioFont(iChanelNo, iFontSize, iFColorR, iFColorG, iFColorB)
        && !m_pCamera6467->SetOverlayVedioFont(1, iFontSize, iFColorR, iFColorG, iFColorB)
        )
    {
        Tool_WriteFormatLog("SetOverlayVedioFont::  SetOverlayVideoTextPos, failed.");
        bSetColor = false;
    }

    Tool_WriteFormatLog("SetOSDTimeInfo::  begin to set overlay string buffer.");
    SetOverlayStringByRow(index, logo);
    Tool_WriteFormatLog("SetOSDTimeInfo::  finish set overlay string buffer.");
    Tool_WriteLog(m_chOverlayFinal);
    Tool_WriteLog("print finish.");
    bool bSetText = true;
    if (!m_pCamera6467->SetOverlayVideoText(iChanelNo, m_chOverlayFinal, strlen(m_chOverlayFinal) + 1)
        && !m_pCamera6467->SetOverlayVideoText(1, m_chOverlayFinal, strlen(m_chOverlayFinal) + 1)
        )
    {
        Tool_WriteFormatLog("SetOverlayVedioFont::  SetOverlayVideoTextPos, failed.");
        bSetText = false;
    }

    Tool_WriteFormatLog("SetOSDTimeInfo::  finish.");
    if (bSetColor
        && bSetText)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}


SHORT CH264CUCtrl::GetOSDUserDefInfo(SHORT channelNo, SHORT index)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO:  在此添加调度处理程序代码
    //该方法不用实现
    return 0;
}


SHORT CH264CUCtrl::SetRealTime(SHORT iRealTime)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO:  在此添加调度处理程序代码
    Tool_WriteFormatLog("SetRealTime::  begin, iRealTime = %d, return directory", iRealTime);
    return 0;
}


SHORT CH264CUCtrl::GetRealTime()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO:  在此添加调度处理程序代码
    //该方法不用实现
    return 0;
}


SHORT CH264CUCtrl::DownLoadPic(LPCTSTR szPath, SHORT nWidth, SHORT nHeight)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO:  在此添加调度处理程序代码
    Tool_WriteFormatLog("DownLoadPic,  nWidth = %d, nHeight = %d, szPath= %s.",
        nWidth,
        nHeight,
        szPath);

    if (szPath == NULL 
        || strlen(szPath) <= 0
        )
    {
        Tool_WriteFormatLog("parameter is invalid.");
        return -1;
    }

    if (m_pCamera6467 == nullptr)
    {
        Tool_WriteFormatLog("DownLoadPic::  camera is not init, please init first.");
        return -1;
    }
    
    if (!m_pCamera6467->GetOneJpegImg(m_CapImg))
    {
        Tool_WriteFormatLog("DownLoadPic: get cap image from JPEG stream failed.");
        return -2;
    }
    int iCompressQuality = m_pCamera6467->GetCompressQuality();
    int iDestImgWidth = 0;
    int iDestImgHeight = 0;
    if (nWidth == 0
        || nHeight == 0
        )
    {
        iDestImgWidth = -1;
        iDestImgHeight = -1;
    }
    else
    {
        iDestImgWidth = nWidth;
        iDestImgHeight = nHeight;
    }
    int iRet = -1;
    size_t iDestLen = MAX_IMG_SIZE;
    unsigned char* pbDest = GetImgBufferAddress();
    if ( pbDest != NULL
        &&Tool_Img_ScaleJpg(m_CapImg.pbImgData, m_CapImg.dwImgSize, pbDest,
        &iDestLen, iDestImgWidth, iDestImgHeight, iCompressQuality))
    {
        Tool_WriteFormatLog("DownLoadPic::  Tool_Img_ScaleJpg success, width = %d, height = %d, length = %d, quality = %d",
            iDestImgWidth,
            iDestImgHeight,
            iDestLen,
            iCompressQuality);

        if (Tool_SaveFileToPath(szPath, pbDest, iDestLen))
        {
            Tool_WriteFormatLog("DownLoadPic:: save to path success.");
            iRet = 0;
        }
        else
        {
            Tool_WriteFormatLog("DownLoadPic:: save to path failed.");
            iRet = -3;
        }
    }
    else
    {
        Tool_WriteFormatLog("DownLoadPic:: Tool_Img_ScaleJpg failed.");
        iRet = -4;
    }
    return iRet;
}


BSTR CH264CUCtrl::DirectoryDlg()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    CString strResult;

    // TODO:  在此添加调度处理程序代码
    //该方法不用实现
    return strResult.AllocSysString();
}


SHORT CH264CUCtrl::SetSystemTime(LONG year, LONG month, LONG day, LONG hour, LONG minut, LONG second)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    
    // TODO:  在此添加调度处理程序代码
    Tool_WriteFormatLog("SetSystemTime::  year = %d, month = %d, day= %d, hour = %d, minut= %d, second = %d.",
        year,
        month,
        day,
        hour,
        minut,
        second);

    if (m_pCamera6467 == nullptr)
    {
        Tool_WriteFormatLog("SetSystemTime::  camera is not init, please init first.");
        return -1;
    }

    if (year <= 1990 
        || month < 1
        || month > 31
        || day < 1
        || day > 31
        || hour < 0
        || hour > 24
        || minut < 0
        || minut > 60
        || second < 1
        || second >60)
    {
        Tool_WriteFormatLog("SetSystemTime::  parameter is invalid.");
        return -2;
    }

    if (!m_pCamera6467->SynTime(year, month, day, hour, minut, second, 0))
    {
        Tool_WriteFormatLog("DownLoadPic: SynTime failed.");
        return -3;
    }
    else
    {
        Tool_WriteFormatLog("DownLoadPic: SynTime success.");
        return 0;
    }
}

int CH264CUCtrl::GetFontSize(int SizeType)
{
    int iBigFontSize = 72;
    Tool_ReadIntValueFromConfigFile(INI_FILE_NAME, "Font", "BigSize", iBigFontSize);

    int iMiddleFontSize = 48;
    Tool_ReadIntValueFromConfigFile(INI_FILE_NAME, "Font", "MiddleSize", iMiddleFontSize);

    int iSmallFontSize = 32;
    Tool_ReadIntValueFromConfigFile(INI_FILE_NAME, "Font", "SmallSize", iSmallFontSize);

    int iSize = 32;
    switch (SizeType)
    {
    case 0:
        iSize = iBigFontSize;
        break;
    case 1:
        iSize = iMiddleFontSize;
        break;
    case 2:
        iSize = iSmallFontSize;
        break;
    default:
        iSize = iMiddleFontSize;
        break;
    }
    return iSize;
}

bool CH264CUCtrl::GetColor(const char* colorInfo,
    int& FcolorR,
    int& FColorG,
    int& FColorB,
    int& FColorAlpha,
    int& BcolorR,
    int& BColorG,
    int& BColorB,
    int& BColorAlpha)
{
    if (NULL == colorInfo)
    {
        return false;
    }
    sscanf_s(colorInfo, "%d#%d#%d#%d#%d#%d#%d#%d",
        &FcolorR, &FColorG, &FColorB, &FColorAlpha,
        &BcolorR, &BColorG, &BColorB, &BColorAlpha);
    return true;
}

void CH264CUCtrl::InitializationOverlayText()
{
    for (int i = 0; i < OVERLAY_MAX_ROW; i++)
    {
        for (int j = 0; j < OVERLAY_MAX_COL; j++)
        {
            m_chOverlayTemp[i][j] = '\0';
        }
    }
}

void CH264CUCtrl::SetOverlayStringByRow(int iIndex, const char* overlayText)
{
    const char* pValue = overlayText;
    memset(m_chOverlayTemp[iIndex], '\0', OVERLAY_MAX_COL);
    int iLength = strlen(overlayText);
    for (int i = 0; i < iLength && i < OVERLAY_MAX_COL; i++)
    {
        m_chOverlayTemp[iIndex][i] = *(pValue++);
    }

    char* pOverlay = m_chOverlayFinal;
    memset(pOverlay, '\0', OVERLAY_MAX_ROW * OVERLAY_MAX_COL);
    for (int i = 0; i < OVERLAY_MAX_ROW; i++)
    {
        memcpy(pOverlay, m_chOverlayTemp[i], strlen(m_chOverlayTemp[i]));
        pOverlay += strlen(m_chOverlayTemp[i]);
        *pOverlay = '\n';
        pOverlay += 1;
        if (i == OVERLAY_MAX_ROW -1)
        {
            *pOverlay = '\0';
            pOverlay += 1;
            break;
        }
    }
    m_chOverlayFinal[OVERLAY_MAX_COL*OVERLAY_MAX_ROW - 1] = '\0';

    //Tool_WriteFormatLog("m_chOverlayFinal:");
    //for (int j = 0; j < OVERLAY_MAX_COL*OVERLAY_MAX_ROW; j++)
    //{
    //    Tool_WriteFormatLog("%X", m_chOverlayFinal[j]);
    //}
}

uint8_t* CH264CUCtrl::GetImgBufferAddress()
{
    uint8_t* pData = NULL;
    if (!m_pImgData)
    {
        m_pImgData = std::shared_ptr<uint8_t>(new uint8_t[MAX_IMG_SIZE], std::default_delete<uint8_t[]>());
    }
    if (m_pImgData)
    {
        pData = m_pImgData.get();
        memset(pData, 0, MAX_IMG_SIZE);
    }
    return pData;
}
