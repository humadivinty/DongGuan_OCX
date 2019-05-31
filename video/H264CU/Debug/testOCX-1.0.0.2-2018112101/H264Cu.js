
function login()
{
    var inputLoginName=document.getElementById("Log_name");
    var inputLoginPsw=document.getElementById("Log_psw");
    var inputServerPort=document.getElementById("Log_ServerPort");
    var inputSeverIP=document.getElementById("Log_serverIP");
    var H264CU1=document.getElementById("H264CU1");
    var serverPort= parseInt(inputServerPort.value);
    var result=H264CU1.Login(inputSeverIP.value, serverPort.value, inputLoginName.value, inputLoginPsw.value);
    document.getElementById("Loging_Result").innerHTML=result;
}

function Func_LoginOut()
{
    var H264CU1=document.getElementById("H264CU1");
    H264CU1.Logout();
    alert("finish call.");
}

function Func_OpenVideo()
{
    var H264CU1 = document.getElementById("H264CU1");
    var channelNo=document.getElementById("Open_channelNo");
    var result = H264CU1.OpenVideo(channelNo.value);
    document.getElementById("OpenVideo_Result").innerHTML=result;
}

function Func_CloseVideo()
{
    var H264CU1 = document.getElementById("H264CU1");
    var channelNo=document.getElementById("CloseVideo_channelNo");
    var result = H264CU1.CloseVideo(channelNo.value);
    //document.getElementById("CloseVideo_Result").innerHTML=result;
    alert("finish call.");
}

function Func_SetCaptureMass()
{
    var H264CU1 = document.getElementById("H264CU1");
    var channelNo = document.getElementById("SetCaptureMass_ChannelNo");
    var iMass =document.getElementById("SetCaptureMass_iMass");
    var result = H264CU1.SetCaptureMass(channelNo.value, iMass.value);
    document.getElementById("SetCaptureMass_Result").innerHTML=result;
}

function Func_GetCaptureMass()
{
    var H264CU1 = document.getElementById("H264CU1");
    var channelNo = document.getElementById("GetCaptureMass_ChannelNo");
    var result = H264CU1.GetCaptureMass(channelNo.value);
    document.getElementById("GetCaptureMass_Result").innerHTML=result;
}

function Func_SetOSDTimeInfo()
{
    var H264CU1 = document.getElementById("H264CU1");
    var channelNo = document.getElementById("SetOSDTime_channelNo");
    var timeFlag = document.getElementById("SetOSDTime_timeFlag");
    var fontType = document.getElementById("SetOSDTime_fontType");
    var fontSize = document.getElementById("SetOSDTime_FontSize");
    var timeX = document.getElementById("SetOSDTime_timeX");
    var timeY = document.getElementById("SetOSDTime_timeY");
    var color = document.getElementById("SetOSDTime_color");
    var result = H264CU1.SetOSDTimeInfo(channelNo.value,
        timeFlag.value,
        fontType.value,
        fontSize.value,
        timeX.value,
        timeY.value,
    color);
    document.getElementById("SetOSDTimeInfo_Result").innerHTML=result;
}

function Func_GetOSDTimeInfo()
{
    var H264CU1 = document.getElementById("H264CU1");
    var channelNo = document.getElementById("GetOSDTimeInfo_channelNo");
    var result = H264CU1.GetOSDTimeInfo(channelNo.value);
    document.getElementById("GetOSDTimeInfo_Result").innerHTML=result;
}

function Func_ColorDlg()
{
    var H264CU1 = document.getElementById("H264CU1");
    var color_red = document.getElementById("ColorDlg_Red");
    var color_green = document.getElementById("ColorDlg_Green");
    var color_blue = document.getElementById("ColorDlg_Blue");
    
    var result = H264CU1.ColorDlg(color_red.value,
        color_green.value,
        color_blue.value);
    document.getElementById("ColorDlg_Result").innerHTML=result;
}

function Func_SetOSDLogoInfo()
{
    var H264CU1 = document.getElementById("H264CU1");

    var iChannelNo = document.getElementById("SetOSDLogoInfo_channelNo");
    var iLogoFlag = document.getElementById("SetOSDLogoInfo_logoFlag");
    var strLogo = document.getElementById("SetOSDLogoInfo_logo");
    var iFontType = document.getElementById("SetOSDLogoInfo_fontType");
    var iFontSize = document.getElementById("SetOSDLogoInfo_fontSize");
    var iLogoX = document.getElementById("SetOSDLogoInfo_timeX");
    var iLogoY = document.getElementById("SetOSDLogoInfo_timeY");
    var strColor = document.getElementById("SetOSDLogoInfo_color");
    
    var result = H264CU1.SetOSDLogoInfo(iChannelNo.value,
        iLogoFlag.value,
        strLogo.value,
        iFontType.value,
        iFontSize.value,
        iLogoX.value,
        iLogoY.value,
    strColor.value);
    document.getElementById("SetOSDLogoInfo_Result").innerHTML=result;
}

function Func_GetOSDLogoInfo()
{
    var H264CU1 = document.getElementById("H264CU1");
    var iChannelNo = document.getElementById("GetOSDLogoInfo_channelNo");

    
    var result = H264CU1.GetOSDLogoInfo(iChannelNo.value);
    document.getElementById("GetOSDLogoInfo_Result").innerHTML=result;
}

function Func_SetOSDUserDefInfo()
{
    var H264CU1 = document.getElementById("H264CU1");

    var iChannelNo = document.getElementById("SetOSDUserDefInfo_channelNo");
    var iIndex = document.getElementById("SetOSDUserDefInfo_index");
    var idefFlag = document.getElementById("SetOSDUserDefInfo_defFlag");
    var strLogo = document.getElementById("SetOSDUserDefInfo_logo");
    var iFontType = document.getElementById("SetOSDUserDefInfo_font_type");
    var iFontSize = document.getElementById("SetOSDUserDefInfo_fontSize");
    var iTimeX = document.getElementById("SetOSDUserDefInfo_timeX");
    var iTimeY = document.getElementById("SetOSDUserDefInfo_timeY");
    var strColor = document.getElementById("SetOSDUserDefInfo_color");
    
    var result = H264CU1.SetOSDUserDefInfo(iChannelNo.value,
        iIndex.value,
        idefFlag.value,
        strLogo.value,
        iFontType.value,
        iFontSize.value,
        iTimeX.value,
        iTimeY.value,
    strColor.value);
    document.getElementById("SetOSDUserDefInfo_Result").innerHTML=result;
}

function Func_GetOSDUserDefInfo()
{
    var H264CU1 = document.getElementById("H264CU1");
    var iChannelNo = document.getElementById("GetOSDUserDefInfo_channelNo");
    var iIndex = document.getElementById("GetOSDUserDefInfo_index");

    var result = H264CU1.GetOSDUserDefInfo(iChannelNo.value,iIndex.value);
    document.getElementById("GetOSDUserDefInfo_Result").innerHTML=result;
}

function Func_SetRealTime()
{
    var H264CU1 = document.getElementById("H264CU1");
    var iRealTime = document.getElementById("SetRealTime_iRealTime");

    var result = H264CU1.SetRealTime(iRealTime.value);
    document.getElementById("SetRealTime_Result").innerHTML=result;
}

function Func_GetRealTime()
{
    var H264CU1 = document.getElementById("H264CU1");
    
    var result = H264CU1.GetRealTime();
    document.getElementById("GetRealTime_Result").innerHTML=result;
}

function Func_DownLoadPic()
{
    var H264CU1 = document.getElementById("H264CU1");
    var strPath = document.getElementById("DownLoadPic_szPath");
    var iWidth = document.getElementById("DownLoadPic_width");
    var iHeight = document.getElementById("DownLoadPic_height");

    var result = H264CU1.DownLoadPic(strPath.value,
        iWidth.value,
    iHeight.value);
    document.getElementById("DownLoadPic_Result").innerHTML=result;
}

function Func_DirectoryDlge()
{
    var H264CU1 = document.getElementById("H264CU1");
    
    var result = H264CU1.DirectoryDlg();
    document.getElementById("DirectoryDlg_Result").innerHTML=result;
}


function Func_SetSystemTime()
{
    var H264CU1 = document.getElementById("H264CU1");
    var iYear = document.getElementById("SetSystemTime_year");
    var iMonth = document.getElementById("SetSystemTime_month");
    var iDay = document.getElementById("SetSystemTime_day");
    var iHour = document.getElementById("SetSystemTime_hour");
    var iMinut = document.getElementById("SetSystemTime_minut");
    var iSecond = document.getElementById("SetSystemTime_second");

    var result = H264CU1.SetSystemTime(iYear.value,
        iMonth.value,
        iDay.value,
        iHour.value,
        iMinut.value,
    iSecond.value);
    document.getElementById("SetSystemTime_Result").innerHTML=result;
}