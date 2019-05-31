#include "stdafx.h"
#include "Camera6467_plate.h"
#include "libHvDevice/HvDeviceBaseType.h"
#include "libHvDevice/HvDeviceCommDef.h"
#include "libHvDevice/HvDeviceNew.h"
#include "libHvDevice/HvCamera.h"
#include "utilityTool/ToolFunction.h"
//#include "utilityTool/log4z.h"
#include <process.h>

#ifdef  USE_VIDEO
#include "H264_Api/H264.h"
#pragma comment(lib, "H264_Api/H264.lib")
#endif

#define CHECK_ARG(arg)\
if (arg == NULL) \
{\
    WriteFormatLog("%s is NULL", #arg); \
    return 0; \
}

unsigned int __stdcall Camera_SaveResultThread(LPVOID lpParam);

Camera6467_plate::Camera6467_plate() :
BaseCamera(),
m_iTimeInvl(10),
m_iCompressBigImgSize(COMPRESS_BIG_IMG_SIZE),
m_iCompressSamllImgSize(COMPRESS_PLATE_IMG_SIZE),
m_iCompressQuality(80),
m_iJPEGImgWidth(1920),
m_iJPEGImgHeight(1080),
m_pTempBin(NULL),
m_pTempBig1(NULL),
m_pCaptureImg(NULL),
m_pTempBig(NULL),
g_pUser(NULL),
g_func_ReconnectCallback(NULL),
g_ConnectStatusCallback(NULL),
g_func_DisconnectCallback(NULL),
m_CameraResult(NULL),
m_BufferResult(NULL),
m_bResultComplete(false),
m_bJpegComplete(false),
m_bSaveToBuffer(false),
m_bOverlay(false),
m_bCompress(false),
m_bStatusCheckThreadExit(false),
m_hFirstWinHandle(NULL),
m_hSecondWinHandle(NULL),
m_hPlayFirstH264(NULL),
m_hPlaySecondh264(NULL),
m_hStatusCheckThread(NULL)
{
    memset(m_chResultPath, '\0', sizeof(m_chResultPath));
    ReadConfig();
    InitializeCriticalSection(&m_csResult);

    m_hStatusCheckThread = (HANDLE)_beginthreadex(NULL, 0, Camera_StatusCheckThread, this, 0, NULL);
    //m_hSaveResultThread = (HANDLE)_beginthreadex(NULL, 0, Camera_SaveResultThread, this, 0, NULL);
    for (int i = 0; i < MAX_THREAD_COUNT; i++)
    {
        m_hSaveResultThread[i] = NULL;
    }
    //for (int i = 0; i < MAX_THREAD_COUNT; i++)
    //{
    //    m_hSaveResultThread[i] = (HANDLE)_beginthreadex(NULL, 0, Camera_SaveResultThread, this, 0, NULL);
    //}
}


Camera6467_plate::Camera6467_plate(const char* chIP, HWND hWnd, int Msg) :
BaseCamera(chIP, hWnd, Msg),
m_iTimeInvl(10),
m_iCompressBigImgSize(COMPRESS_BIG_IMG_SIZE),
m_iCompressSamllImgSize(COMPRESS_PLATE_IMG_SIZE),
m_iCompressQuality(80),
m_iJPEGImgWidth(1920),
m_iJPEGImgHeight(1080),
m_pTempBin(NULL),
m_pTempBig1(NULL),
m_pCaptureImg(NULL),
m_pTempBig(NULL),
g_pUser(NULL),
g_func_ReconnectCallback(NULL),
g_ConnectStatusCallback(NULL),
g_func_DisconnectCallback(NULL),
m_CameraResult(NULL),
m_BufferResult(NULL),
m_bResultComplete(false),
m_bJpegComplete(false),
m_bSaveToBuffer(false),
m_bOverlay(false),
m_bCompress(false),
m_bStatusCheckThreadExit(false),
m_hFirstWinHandle(NULL),
m_hSecondWinHandle(NULL),
m_hPlayFirstH264(NULL),
m_hPlaySecondh264(NULL),
m_hStatusCheckThread(NULL)
{
    memset(m_chResultPath, '\0', sizeof(m_chResultPath));
    ReadConfig();

    InitializeCriticalSection(&m_csResult);
    m_lsResultList.size();

    m_hStatusCheckThread = (HANDLE)_beginthreadex(NULL, 0, Camera_StatusCheckThread, this, 0, NULL);
    for (int i = 0; i < MAX_THREAD_COUNT; i++)
    {
        m_hSaveResultThread[i] = NULL;
    }
    //for (int i = 0; i < MAX_THREAD_COUNT; i++)
    //{
    //    m_hSaveResultThread[i] = (HANDLE)_beginthreadex(NULL, 0, Camera_SaveResultThread, this, 0, NULL);;
    //}
}

Camera6467_plate::~Camera6467_plate()
{
    SetCheckThreadExit(true);
    SetConnectStatus_Callback(NULL, NULL, 10);
    Tool_SafeCloseThread(m_hStatusCheckThread);
    //Tool_SafeCloseThread(m_hSaveResultThread);
    for (int i = 0; i < MAX_THREAD_COUNT; i++)
    {
        Tool_SafeCloseThread(m_hSaveResultThread[i]);
    }    

    InterruptionConnection();
#ifdef USE_VIDEO
    StopPlayVideoByChannel(0);
    StopPlayVideoByChannel(1);
#endif

    SAFE_DELETE_OBJ(m_CameraResult);
    SAFE_DELETE_OBJ(m_BufferResult);

    SAFE_DELETE_ARRAY(m_pTempBin);
    SAFE_DELETE_ARRAY(m_pTempBig1);
    SAFE_DELETE_ARRAY(m_pCaptureImg);
    SAFE_DELETE_ARRAY(m_pTempBig);

    DeleteCriticalSection(&m_csResult);
}

int Camera6467_plate::StartPlayVideo(int iChannelID, HANDLE& playHandle, const HWND winHandle)
{
    WriteFormatLog("StartPlayVideoByChannel, iChannelID = %d, playHndle = %p, winHandle = %p", iChannelID, playHandle, winHandle);
    
    char chCMD[256] = { 0 };
    if (iChannelID == 0)
    {
        sprintf_s(chCMD, sizeof(chCMD), "rtsp://%s:554/h264ESVideoTest", m_strIP.c_str());
        //m_iVedioChannelID = 0;
    }
    else
    {
        sprintf_s(chCMD, sizeof(chCMD), "rtsp://%s:554/h264ESVideoTestSecond", m_strIP.c_str());
        //m_iVedioChannelID = 1;
    }
    WriteFormatLog(chCMD);
    playHandle = H264_Play(winHandle, chCMD);
    WriteFormatLog("StartPlayVideoByChannel , return 0.");
    return 0;
}

void Camera6467_plate::StopPlayVideo(HANDLE& playHandle)
{
    WriteLog("StopPlayVideo begin.");
    if (playHandle)
    {
        H264_SetExitStatus(playHandle);
        H264_Destroy(playHandle);
        playHandle = NULL;
    }
    WriteLog("StopPlayVideo end.");
}

int Camera6467_plate::AnalysisVelchType(const char* vehType)
{
    if (vehType == NULL)
    {
        return UNKOWN_TYPE;
    }
    if (strstr(vehType, "客1"))
    {
        return BUS_TYPE_1;
    }
    else if (strstr(vehType, "客2"))
    {
        return BUS_TYPE_2;
        //printf("the Vehicle type code is 2.\n");
    }
    else if (strstr(vehType, "客3"))
    {
        return BUS_TYPE_3;
    }
    else if (strstr(vehType, "客4"))
    {
        return BUS_TYPE_4;
    }
    else if (strstr(vehType, "客5"))
    {
        return BUS_TYPE_5;
    }
    else if (strstr(vehType, "货1"))
    {
        return TRUCK_TYPE_1;
    }
    else if (strstr(vehType, "货2"))
    {
        return TRUCK_TYPE_2;
    }
    else if (strstr(vehType, "货3"))
    {
        return TRUCK_TYPE_3;
    }
    else if (strstr(vehType, "货4"))
    {
        return TRUCK_TYPE_4;
    }
    else if (strstr(vehType, "货5"))
    {
        return TRUCK_TYPE_5;
    }
    else
    {
        return UNKOWN_TYPE;
    }
}

bool Camera6467_plate::AnalysisAppendXml(const char* pAppInfo, CameraResult* pResult)
{
    if (NULL == pAppInfo
        || NULL == pResult)
    {
        WriteFormatLog("AnalysisAppendXml parameter is invalid.");
        return false;
    }
    WriteFormatLog("AnalysisAppendXml = %p, pResult = %p.", pAppInfo, pResult);

    if (0 != pResult->dw64TimeMS)
    {
        CTime tm(pResult->dw64TimeMS / 1000);
        //sprintf_s(record->chPlateTime, "%04d%02d%02d%02d%02d%02d%03d", tm.GetYear(), tm.GetMonth(), tm.GetDay(), tm.GetHour(), tm.GetMinute(), tm.GetSecond(), record->dw64TimeMS%1000);
        sprintf_s(pResult->chPlateTime, sizeof(pResult->chPlateTime), "%04d-%02d-%02d %02d:%02d:%02d",
            tm.GetYear(),
            tm.GetMonth(),
            tm.GetDay(),
            tm.GetHour(),
            tm.GetMinute(),
            tm.GetSecond());
    }
    else
    {
        SYSTEMTIME st;
        GetLocalTime(&st);
        //sprintf_s(record->chPlateTime, "%04d%02d%02d%02d%02d%02d%03d", st.wYear, st.wMonth, st.wDay	,st.wHour, st.wMinute,st.wSecond, st.wMilliseconds);
        sprintf_s(pResult->chPlateTime, sizeof(pResult->chPlateTime), "%04d-%02d-%02d %02d:%02d:%02d:%03d",
            st.wYear,
            st.wMonth,
            st.wDay,
            st.wHour,
            st.wMinute,
            st.wSecond);
    }

    char chTemp[BUFFERLENTH] = { 0 };
    int iLenth = BUFFERLENTH;

    if (Tool_GetDataFromAppenedInfo(pAppInfo, "Confidence", chTemp, &iLenth))
    {
        float fConfidence = 0;
        sscanf_s(chTemp, "%f", &fConfidence);
        pResult->fConfidenceLevel = fConfidence;
        //printf("the CarHeight  is %f.\n", fCarHeight);
    }
    WriteFormatLog("AnalysisAppendXml finish.");
    return true;
}

void Camera6467_plate::ReadConfig()
{
    char iniFileName[MAX_PATH] = { 0 };
    char iniDeviceInfoName[MAX_PATH] = { 0 };
#ifdef GUANGXI_DLL
    sprintf_s(iniFileName, "..\\DevInterfaces\\HVCR_Signalway_V%d_%d\\HVCR_Config\\HVCR_Signalway_V%d_%d.ini", PROTOCAL_VERSION, DLL_VERSION, PROTOCAL_VERSION, DLL_VERSION);
#else
    strcat_s(iniFileName, Tool_GetCurrentPath());
    strcat_s(iniFileName, INI_FILE_NAME);
#endif
    //char szPath[MAX_PATH] = {0};
    //sprintf_s(szPath, sizeof(szPath), "%s\\Result\\", Tool_GetCurrentPath());
    //Tool_ReadKeyValueFromConfigFile(INI_FILE_NAME, "Result", "Path", szPath, MAX_PATH);
    //strcpy_s(m_chResultPath, sizeof(m_chResultPath), szPath);

    Tool_ReadIntValueFromConfigFile(INI_FILE_NAME, "JPEG", "width", m_iJPEGImgWidth);
    m_iJPEGImgWidth = (m_iJPEGImgWidth <= 0) ? 1920 : m_iJPEGImgWidth;

    Tool_ReadIntValueFromConfigFile(INI_FILE_NAME, "JPEG", "height", m_iJPEGImgHeight);
    m_iJPEGImgHeight = (m_iJPEGImgHeight <= 0) ? 1080 : m_iJPEGImgHeight;

    BaseCamera::ReadConfig();
}

void Camera6467_plate::SetCheckThreadExit(bool bExit)
{
    EnterCriticalSection(&m_csFuncCallback);
    m_bStatusCheckThreadExit = bExit;
    LeaveCriticalSection(&m_csFuncCallback);
}

bool Camera6467_plate::GetCheckThreadExit()
{
    bool bExit = false;
    EnterCriticalSection(&m_csFuncCallback);
    bExit = m_bStatusCheckThreadExit;
    LeaveCriticalSection(&m_csFuncCallback);
    return bExit;
}

void Camera6467_plate::SaveOverlayResult()
{
    char chLog[MAX_PATH] = {0};
    if (m_bOverlay)
    {
        if (m_pTempBig1 == NULL)
        {
            m_pTempBig1 = new BYTE[MAX_IMG_SIZE];
            memset(m_pTempBig1, 0, MAX_IMG_SIZE);
        }
        else
        {
            memset(m_pTempBig1, 0, MAX_IMG_SIZE);
        }

        char chOverlayInfo[256] = { 0 };
        if (strstr(m_CameraResult->chPlateNO, "无"))
        {
            sprintf_s(chOverlayInfo, sizeof(chOverlayInfo), "时间:%s   车牌号: *****", m_CameraResult->chPlateTime);
        }
        else
        {
            sprintf_s(chOverlayInfo, sizeof(chOverlayInfo), "时间:%s   车牌号: %s", m_CameraResult->chPlateTime, m_CameraResult->chPlateNO);
        }
        std::string strOverlayInfo(chOverlayInfo);
        std::wstring wstrOverlayIno = Img_string2wstring(strOverlayInfo);

        if (m_CameraResult->CIMG_BestSnapshot.dwImgSize > 0 && m_CameraResult->CIMG_BestSnapshot.pbImgData)
        {
            if (m_pTempBig1)
            {
                memset(m_pTempBig1, 0, MAX_IMG_SIZE);
                long iDestSize = MAX_IMG_SIZE;

                memset(chLog, 0, sizeof(chLog));
                sprintf_s(chLog, sizeof(chLog), "BestSnapshot开始字符叠加， text = %s", chOverlayInfo);
                WriteLog(chLog);
                bool bOverlay = Tool_OverlayStringToImg(&m_CameraResult->CIMG_BestSnapshot.pbImgData,
                    m_CameraResult->CIMG_BestSnapshot.dwImgSize,
                    &m_pTempBig1, iDestSize,
                    wstrOverlayIno.c_str(), 32,
                    10, 30, 255, 255, 255,
                    50);
                if (bOverlay)
                {
                    memset(chLog, 0, sizeof(chLog));
                    sprintf_s(chLog, sizeof(chLog), "字符叠加成功, size = %ld, begin copy..", iDestSize);
                    WriteLog(chLog);

                    delete[] m_CameraResult->CIMG_BestSnapshot.pbImgData;
                    m_CameraResult->CIMG_BestSnapshot.pbImgData = new BYTE[iDestSize];
                    memcpy(m_CameraResult->CIMG_BestSnapshot.pbImgData, m_pTempBig1, iDestSize);
                    m_CameraResult->CIMG_BestSnapshot.dwImgSize = iDestSize;

                    WriteLog("finish copy.");
                }
                else
                {
                    WriteLog("字符叠加失败,使用原图数据.");
                }

            }
        }

        if (m_CameraResult->CIMG_LastSnapshot.dwImgSize > 0 && m_CameraResult->CIMG_LastSnapshot.pbImgData)
        {
            if (m_pTempBig1)
            {
                memset(m_pTempBig1, 0, MAX_IMG_SIZE);
                long iDestSize = MAX_IMG_SIZE;

                memset(chLog, 0, sizeof(chLog));
                MY_SPRINTF(chLog, "LastSnapshot 开始字符叠加， text = %s", chOverlayInfo);
                WriteLog(chLog);
                bool bOverlay = Tool_OverlayStringToImg(&m_CameraResult->CIMG_LastSnapshot.pbImgData, 
                    m_CameraResult->CIMG_LastSnapshot.dwImgSize,
                    &m_pTempBig1, iDestSize,
                    wstrOverlayIno.c_str(), 32,
                    10, 10, 255, 255, 255,
                    50);
                if (bOverlay)
                {
                    memset(chLog, 0, sizeof(chLog));
                    MY_SPRINTF(chLog, "字符叠加成功, size = %ld, begin copy..", iDestSize);
                    WriteLog(chLog);

                    delete[] m_CameraResult->CIMG_LastSnapshot.pbImgData;
                    m_CameraResult->CIMG_LastSnapshot.pbImgData = new BYTE[iDestSize];
                    memcpy(m_CameraResult->CIMG_LastSnapshot.pbImgData, m_pTempBig1, iDestSize);
                    m_CameraResult->CIMG_LastSnapshot.dwImgSize = iDestSize;

                    WriteLog("finish copy.");
                }
                else
                {
                    WriteLog("字符叠加失败,使用原图数据.");
                }
            }
        }
    }
}

int Camera6467_plate::RecordInfoBegin(DWORD dwCarID)
{
    WriteFormatLog("RecordInfoBegin -begin- dwCarID = %lu", dwCarID);

    if (dwCarID == m_dwLastCarID)
    {
        WriteLog("相同carID,丢弃该结果");
        return 0;
    }
    SetResultComplete(false);
    SAFE_DELETE_OBJ(m_CameraResult);

    m_CameraResult = new CameraResult();
    if (m_CameraResult)
    {
        sprintf_s(m_CameraResult->chServerIP, sizeof(m_CameraResult->chServerIP), "%s", m_strIP.c_str());
        m_CameraResult->dwCarID = dwCarID;
    }

    WriteFormatLog("RecordInfoBegin -end- dwCarID = %lu", dwCarID);
    return 0;
}

int Camera6467_plate::RecordInfoEnd(DWORD dwCarID)
{
    WriteFormatLog("RecordInfoEnd begin, dwCarID = %d", dwCarID);

    if (dwCarID != m_dwLastCarID)
    {
        m_dwLastCarID = dwCarID;
    }
    else
    {
        WriteLog("相同CarID, 丢弃该结果");
        return 0;
    }

    if (NULL == m_CameraResult)
    {
        return 0;
    }

    EnterCriticalSection(&m_csResult);

    SAFE_DELETE_OBJ(m_BufferResult);
    m_BufferResult = new CameraResult(*m_CameraResult);
    m_bResultComplete = true;

    LeaveCriticalSection(&m_csResult);

    SAFE_DELETE_OBJ(m_CameraResult);

    if (NULL != m_hWnd)
    {
        WriteLog("PostMessage");
        //::PostMessage(*((HWND*)m_hWnd),m_iMsg, 1, 0);
        ::PostMessage(m_hWnd, m_iMsg, (WPARAM)1, 0);
    }

    WriteFormatLog("RecordInfoEnd end, dwCarID = %lu, list size = %d", dwCarID, m_lsResultList.size());
    return 0;
}

int Camera6467_plate::RecordInfoPlate(DWORD dwCarID,
    LPCSTR pcPlateNo,
    LPCSTR pcAppendInfo,
    DWORD dwRecordType,
    DWORD64 dw64TimeMS)
{
    SetResultComplete(false);
    CHECK_ARG(m_CameraResult);

    WriteFormatLog("RecordInfoPlate -begin- dwCarID = %lu", dwCarID);

    if (dwCarID == m_dwLastCarID)
    {
        BaseCamera::WriteLog("相同carID,丢弃该结果");
        return 0;
    }
//#ifdef DEBUG
//    char chName[256] = { 0 };
//    sprintf_s(chName, "%lu.xml", GetTickCount());
//    Tool_SaveFileToPath(chName, (void*)pcAppendInfo, strlen(pcAppendInfo));
//#endif // DEBUG

    if (m_CameraResult->dwCarID == dwCarID)
    {
        m_CameraResult->dw64TimeMS = dw64TimeMS;
        sprintf_s(m_CameraResult->chPlateNO, sizeof(m_CameraResult->chPlateNO), "%s", pcPlateNo);
        //m_CameraResult->strAppendInfo = std::string(pcAppendInfo);
        if (strlen(pcAppendInfo) < sizeof(m_CameraResult->pcAppendInfo) )
        {
            memset(m_CameraResult->pcAppendInfo, '\0', sizeof(m_CameraResult->pcAppendInfo));
            memcpy(m_CameraResult->pcAppendInfo, pcAppendInfo, strlen(pcAppendInfo));
        }
        else
        {
            WriteFormatLog("RecordInfoPlate -begin- strlen(pcAppendInfo) %u < %u sizeof(m_CameraResult->pcAppendInfo)",
                strlen(pcAppendInfo),
                sizeof(m_CameraResult->pcAppendInfo));
        }
        m_CameraResult->iPlateColor = Tool_AnalysisPlateColorNo(pcPlateNo);
        AnalysisAppendXml(pcAppendInfo, m_CameraResult);

        BaseCamera::WriteLog(m_CameraResult->chPlateNO);  
        BaseCamera::WriteLog(pcAppendInfo);
    }

    WriteFormatLog("RecordInfoPlate -end- dwCarID = %lu", dwCarID);
    return 0;
}

int Camera6467_plate::RecordInfoBigImage(DWORD dwCarID,
    WORD wImgType,
    WORD wWidth,
    WORD wHeight,
    PBYTE pbPicData,
    DWORD dwImgDataLen,
    DWORD dwRecordType,
    DWORD64 dw64TimeMS)
{
    SetResultComplete(false);

    CHECK_ARG(m_CameraResult);

    WriteFormatLog("RecordInfoBigImage -begin- dwCarID = %ld, dwRecordType = %#x， ImgType=%d, size = %ld",
        dwCarID, 
        dwRecordType, 
        wImgType,
        dwImgDataLen);

    if (dwCarID == m_dwLastCarID)
    {
        WriteLog("相同carID,丢弃该结果");
        return 0;
    }
    if (m_CameraResult->dwCarID == dwCarID)
    {
        if (wImgType == RECORD_BIGIMG_BEST_SNAPSHOT)
        {
            WriteLog("RecordInfoBigImage BEST_SNAPSHO  ");

            CopyDataToIMG(m_CameraResult->CIMG_BestSnapshot, pbPicData, wWidth, wHeight, dwImgDataLen, wImgType);
        }
        else if (wImgType == RECORD_BIGIMG_LAST_SNAPSHOT)
        {
            WriteLog("RecordInfoBigImage LAST_SNAPSHOT  ");

            CopyDataToIMG(m_CameraResult->CIMG_LastSnapshot, pbPicData, wWidth, wHeight, dwImgDataLen, wImgType);
        }
        else if (wImgType == RECORD_BIGIMG_BEGIN_CAPTURE)
        {
            WriteLog("RecordInfoBigImage BEGIN_CAPTURE  ");

            CopyDataToIMG(m_CameraResult->CIMG_BeginCapture, pbPicData, wWidth, wHeight, dwImgDataLen, wImgType);
        }
        else if (wImgType == RECORD_BIGIMG_BEST_CAPTURE)
        {
            WriteLog("RecordInfoBigImage BEST_CAPTURE  ");

            CopyDataToIMG(m_CameraResult->CIMG_BestCapture, pbPicData, wWidth, wHeight, dwImgDataLen, wImgType);
        }
        else if (wImgType == RECORD_BIGIMG_LAST_CAPTURE)
        {
            WriteLog("RecordInfoBigImage LAST_CAPTURE  ");

            CopyDataToIMG(m_CameraResult->CIMG_LastCapture, pbPicData, wWidth, wHeight, dwImgDataLen, wImgType);
        }
        else
        {
            WriteLog("RecordInfoBigImage other Image, put it to  LAST_CAPTURE .");
            CopyDataToIMG(m_CameraResult->CIMG_LastCapture, pbPicData, wWidth, wHeight, dwImgDataLen, wImgType);
        }
    }

    WriteFormatLog("RecordInfoBigImage -end- dwCarID = %lu", dwCarID);

    return 0;
}

int Camera6467_plate::RecordInfoSmallImage(DWORD dwCarID,
    WORD wWidth,
    WORD wHeight,
    PBYTE pbPicData,
    DWORD dwImgDataLen,
    DWORD dwRecordType,
    DWORD64 dw64TimeMS)
{
    SetResultComplete(false);
    if (NULL == m_CameraResult)
    {
        return -1;
    }
    WriteFormatLog( "RecordInfoSmallImage  -begin- dwCarID = %lu", dwCarID);

    if (dwCarID == m_dwLastCarID)
    {
        WriteLog("相同carID,丢弃该结果");
        return 0;
    }

    int iBuffLen = 1024 * 1024;
    if (m_CameraResult->dwCarID == dwCarID)
    {
        if (NULL != m_CameraResult->CIMG_PlateImage.pbImgData)
        {
            delete[] m_CameraResult->CIMG_PlateImage.pbImgData;
            m_CameraResult->CIMG_PlateImage.pbImgData = NULL;
        }
        m_CameraResult->CIMG_PlateImage.pbImgData = new BYTE[iBuffLen];
        WriteLog("RecordInfoSmallImage 内存申请.");
        if (m_CameraResult->CIMG_PlateImage.pbImgData != NULL)
        {
            WriteLog("RecordInfoSmallImage 内存申请成功.");
            memset(m_CameraResult->CIMG_PlateImage.pbImgData, 0, iBuffLen);
            HRESULT Hr = HVAPIUTILS_SmallImageToBitmapEx(pbPicData,
                wWidth,
                wHeight,
                m_CameraResult->CIMG_PlateImage.pbImgData,
                &iBuffLen);
            if (Hr == S_OK)
            {
                m_CameraResult->CIMG_PlateImage.wImgWidth = wWidth;
                m_CameraResult->CIMG_PlateImage.wImgHeight = wHeight;
                m_CameraResult->CIMG_PlateImage.dwImgSize = iBuffLen;
                if (m_Small_IMG_Temp.pbImgData == NULL)
                {
                    m_Small_IMG_Temp.pbImgData = new BYTE[MAX_IMG_SIZE];
                    memset(m_Small_IMG_Temp.pbImgData, 0, MAX_IMG_SIZE);
                }
                if (m_Small_IMG_Temp.pbImgData)
                {
                    size_t iDestLenth = MAX_IMG_SIZE;
                    memset(m_Small_IMG_Temp.pbImgData, 0, MAX_IMG_SIZE);
                    WriteLog("convert bmp to jpeg , begin .");
                    bool bScale = Tool_Img_ScaleJpg(m_CameraResult->CIMG_PlateImage.pbImgData,
                        m_CameraResult->CIMG_PlateImage.dwImgSize,
                        m_Small_IMG_Temp.pbImgData,
                        &iDestLenth,
                        m_CameraResult->CIMG_PlateImage.wImgWidth,
                        m_CameraResult->CIMG_PlateImage.wImgHeight,
                        80);
                    if (bScale)
                    {
                        WriteLog("convert bmp to jpeg success, begin copy.");
                        memset(m_CameraResult->CIMG_PlateImage.pbImgData, 0, m_CameraResult->CIMG_PlateImage.dwImgSize);
                        memcpy(m_CameraResult->CIMG_PlateImage.pbImgData, m_Small_IMG_Temp.pbImgData, iDestLenth);
                        m_CameraResult->CIMG_PlateImage.dwImgSize = iDestLenth;
                        WriteLog("convert bmp to jpeg success, finish copy.");
                    }
                    else
                    {
                        WriteLog("convert bmp to jpeg failed, use default.");
                    }
                }
            }
            else
            {
                WriteLog("HVAPIUTILS_SmallImageToBitmapEx 失败.");
            }
        }
        else
        {
            WriteLog("RecordInfoSmallImage 内存申请失败.");
        }
    }
    WriteFormatLog("RecordInfoSmallImage  -end- dwCarID = %lu", dwCarID);
    return 0;
}

int Camera6467_plate::RecordInfoBinaryImage(DWORD dwCarID,
    WORD wWidth,
    WORD wHeight,
    PBYTE pbPicData,
    DWORD dwImgDataLen,
    DWORD dwRecordType,
    DWORD64 dw64TimeMS)
{
    SetResultComplete(false);

    if (NULL == m_CameraResult)
    {
        return -1;
    }
    WriteFormatLog("RecordInfoBinaryImage -begin- dwCarID = %lu", dwCarID);


    if (dwCarID == m_dwLastCarID)
    {
        WriteLog("相同carID,丢弃该结果");
        return 0;
    }
    //int iBufferlength = 1024 * 1024;
    //if (m_pTempBin == NULL)
    //{
    //    m_pTempBin = new BYTE[1024 * 1024];
    //    memset(m_pTempBin, 0x00, iBufferlength);
    //}
    //if (m_pTempBin)
    //{
    //    memset(m_pTempBin, 0x00, iBufferlength);

    //    HRESULT hRet = HVAPIUTILS_BinImageToBitmapEx(pbPicData, m_pTempBin, &iBufferlength);
    //    if (hRet == S_OK)
    //    {
    //        if (m_Bin_IMG_Temp.pbImgData == NULL)
    //        {
    //            m_Bin_IMG_Temp.pbImgData = new BYTE[MAX_IMG_SIZE];
    //            memset(m_Bin_IMG_Temp.pbImgData, 0x00, MAX_IMG_SIZE);
    //        }
    //        if (m_Bin_IMG_Temp.pbImgData)
    //        {
    //            DWORD iDestLenth = MAX_IMG_SIZE;
    //            memset(m_Bin_IMG_Temp.pbImgData, 0x00, MAX_IMG_SIZE);
    //            WriteLog("bin, convert bmp to jpeg , begin .");
    //            bool bScale = Tool_Img_ScaleJpg(m_pTempBin,
    //                iBufferlength,
    //                m_Bin_IMG_Temp.pbImgData,
    //                &iDestLenth,
    //                wWidth,
    //                wHeight,
    //                90);
    //            if (bScale)
    //            {
    //                WriteLog("bin, convert bmp to jpeg success, begin copy.");
    //                CopyDataToIMG(m_CameraResult->CIMG_BinImage, m_Bin_IMG_Temp.pbImgData, wWidth, wHeight, iDestLenth, 0);
    //                WriteLog("bin, convert bmp to jpeg success, finish copy.");
    //            }
    //            else
    //            {
    //                WriteLog("bin, convert bmp to jpeg failed, use default.");
    //            }
    //        }
    //        else
    //        {
    //            WriteLog("m_Bin_IMG_Temp  is null.");
    //        }
    //    }
    //    else
    //    {
    //        WriteLog("HVAPIUTILS_BinImageToBitmapEx, failed, use default.");
    //        CopyDataToIMG(m_CameraResult->CIMG_BinImage, pbPicData, wWidth, wHeight, dwImgDataLen, 0);
    //    }
    //}
    //else
    {
        //WriteLog("m_pTempBin is NULL ,  use default.");
        CopyDataToIMG(m_CameraResult->CIMG_BinImage, pbPicData, wWidth, wHeight, dwImgDataLen, 0);
    }
    WriteFormatLog("RecordInfoBinaryImage -end- dwCarID = %lu", dwCarID);
    return 0;
}

int Camera6467_plate::DeviceJPEGStream(PBYTE pbImageData,
    DWORD dwImageDataLen,
    DWORD dwImageType,
    LPCSTR szImageExtInfo)
{
    static int iCout = 0;
    if (iCout++ > 100)
    {
        WriteLog("receive one jpeg frame.");
        iCout = 0;
    }

    EnterCriticalSection(&m_csResult);
    m_bJpegComplete = false;

    m_CIMG_StreamJPEG.dwImgSize = dwImageDataLen;
    m_CIMG_StreamJPEG.wImgWidth = m_iJPEGImgWidth;
    m_CIMG_StreamJPEG.wImgHeight = m_iJPEGImgHeight;
    if (NULL == m_CIMG_StreamJPEG.pbImgData)
    {
        m_CIMG_StreamJPEG.pbImgData = new unsigned char[MAX_IMG_SIZE];
        memset(m_CIMG_StreamJPEG.pbImgData, 0, MAX_IMG_SIZE);
    }
    if (m_CIMG_StreamJPEG.pbImgData)
    {
        memset(m_CIMG_StreamJPEG.pbImgData, 0, MAX_IMG_SIZE);
        memcpy(m_CIMG_StreamJPEG.pbImgData, pbImageData, dwImageDataLen);
        m_bJpegComplete = true;
    }
    LeaveCriticalSection(&m_csResult);

    return 0;
}

void Camera6467_plate::SetDisConnectCallback(void* funcDisc, void* pUser)
{
    EnterCriticalSection(&m_csFuncCallback);
    g_func_DisconnectCallback = funcDisc;
    g_pUser = pUser;
    LeaveCriticalSection(&m_csFuncCallback);
}

void Camera6467_plate::SetReConnectCallback(void* funcReco, void* pUser)
{
    EnterCriticalSection(&m_csFuncCallback);
    g_func_ReconnectCallback = funcReco;
    g_pUser = pUser;
    LeaveCriticalSection(&m_csFuncCallback);
}

bool Camera6467_plate::GetOneJpegImg(CameraIMG &destImg)
{
    WriteLog("GetOneJpegImg::begin.");
    bool bRet = false;

    if (!destImg.pbImgData)
    {
        WriteLog("GetOneJpegImg:: allocate memory.");
        destImg.pbImgData = new unsigned char[MAX_IMG_SIZE];
        memset(destImg.pbImgData, 0, MAX_IMG_SIZE);
        WriteLog("GetOneJpegImg:: allocate memory success.");
    }

    EnterCriticalSection(&m_csResult);
    if (m_bJpegComplete)
    {
        if (destImg.pbImgData)
        {
            memset(destImg.pbImgData, 0, MAX_IMG_SIZE);
            memcpy(destImg.pbImgData, m_CIMG_StreamJPEG.pbImgData, m_CIMG_StreamJPEG.dwImgSize);

            destImg.dwImgSize = m_CIMG_StreamJPEG.dwImgSize;
            destImg.wImgHeight = m_CIMG_StreamJPEG.wImgHeight;
            destImg.wImgWidth = m_CIMG_StreamJPEG.wImgWidth;
            bRet = true;
            WriteLog("GetOneJpegImg success.");
            m_bJpegComplete = false;
        }
        else
        {
            WriteLog("GetOneJpegImg:: allocate memory failed.");
        }
    }
    else
    {
        WriteLog("GetOneJpegImg the image is not ready.");
    }
    LeaveCriticalSection(&m_csResult);
    WriteLog("GetOneJpegImg:: end.");

    return bRet;
}

void Camera6467_plate::SetCompressQualit(int quality)
{
    EnterCriticalSection(&m_csFuncCallback);
    m_iCompressQuality = (quality > 0) ? quality : 30;
    LeaveCriticalSection(&m_csFuncCallback);
}

int Camera6467_plate::GetCompressQuality()
{
    int iQuality = 30;
    EnterCriticalSection(&m_csFuncCallback);
    iQuality = m_iCompressQuality;
    LeaveCriticalSection(&m_csFuncCallback);
    return iQuality;
}

void Camera6467_plate::SendConnetStateMsg(bool isConnect)
{
    //if (m_hWnd == NULL)
    //	return;

    if (isConnect)
    {
        //EnterCriticalSection(&m_csFuncCallback);
        //if (g_ConnectStatusCallback)
        //{
        //    LeaveCriticalSection(&m_csFuncCallback);
        //    //char chIP[32] = { 0 };
        //    //sprintf_s(chIP, "%s", m_strIP.c_str());
        //    //g_ConnectStatusCallback(m_iIndex, 0, g_pUser);
        //}
        //else
        //{
        //    LeaveCriticalSection(&m_csFuncCallback);
        //}
        if (m_hWnd)
        {
            EnterCriticalSection(&m_csFuncCallback);
            ::PostMessage(m_hWnd, m_iConnectMsg, NULL, NULL);
            LeaveCriticalSection(&m_csFuncCallback);
        }

    }
    else
    {
        //EnterCriticalSection(&m_csFuncCallback);
        //if (g_ConnectStatusCallback)
        //{
        //    LeaveCriticalSection(&m_csFuncCallback);
        //    char chIP[32] = { 0 };
        //    sprintf_s(chIP, "%s", m_strIP.c_str());
        //    //g_ConnectStatusCallback(m_iIndex, -100, g_pUser);
        //}
        //else
        //{
        //    LeaveCriticalSection(&m_csFuncCallback);
        //}
        if (m_hWnd)
        {
            EnterCriticalSection(&m_csFuncCallback);
            ::PostMessage(m_hWnd, m_iDisConMsg, NULL, NULL);
            LeaveCriticalSection(&m_csFuncCallback);
        }
    }
}

void Camera6467_plate::SetConnectStatus_Callback(void* func, void* pUser, int TimeInterval)
{
    EnterCriticalSection(&m_csFuncCallback);
    g_ConnectStatusCallback = func;
    g_pUser = pUser;
    m_iTimeInvl = TimeInterval;
    LeaveCriticalSection(&m_csFuncCallback);
}

bool Camera6467_plate::GetResultComplete()
{
    bool bFinish = false;
    EnterCriticalSection(&m_csResult);
    bFinish = m_bResultComplete;
    LeaveCriticalSection(&m_csResult);
    return bFinish;
}

CameraResult* Camera6467_plate::GetOneResult()
{
    CameraResult* tempResult = NULL;
    //EnterCriticalSection(&m_csResult);	
    //if (m_ResultList.size() > 0)
    //{
    //	tempResult = m_ResultList.front();
    //	m_ResultList.pop_front();
    //}
    //LeaveCriticalSection(&m_csResult);

    if (GetResultComplete())
    {
        EnterCriticalSection(&m_csResult);
        tempResult = new CameraResult(*m_BufferResult);
        LeaveCriticalSection(&m_csResult);
    }
    return tempResult;
}

void Camera6467_plate::SerializationResult(std::shared_ptr<CameraResult>& pResult)
{
    LOGFMTD("SerializationResult begin.");
    SYSTEMTIME systime;
    GetLocalTime(&systime);//本地时间
    DWORD dwTick = GetTickCount();

    std::string outputBinPath;
    std::string outputAppendInfo;
    //if (SaveCIMG(pResult->CIMG_BinImage, systime, dwTick, 0, outputBinPath))
    //{
    //    LOGFMTD("save bin image success.");
    //    if (Tool_InsertElementByName(pResult->strAppendInfo.c_str(), "Result", 2, "BinImgPath", outputBinPath.c_str(), outputAppendInfo))
    //    {
    //        pResult->strAppendInfo = outputAppendInfo;
    //    }
    //}

    //std::string outputSmallPath;
    //if (SaveCIMG(pResult->CIMG_PlateImage, systime, dwTick, 1, outputSmallPath))
    //{
    //    LOGFMTD("save small image success.");
    //    if (Tool_InsertElementByName(pResult->strAppendInfo.c_str(), "Result", 2, "SmallImgPath", outputSmallPath.c_str(), outputAppendInfo))
    //    {
    //        pResult->strAppendInfo = outputAppendInfo;
    //    }
    //}

    //std::string outputLastSnapshotPath;
    //if (SaveCIMG(pResult->CIMG_LastSnapshot, systime, dwTick, 2, outputLastSnapshotPath))
    //{
    //    LOGFMTD("save LastSnapshot image success.");
    //    if (Tool_InsertElementByName(pResult->strAppendInfo.c_str(), "Result", 2, "LastSnapshotPath", outputLastSnapshotPath.c_str(), outputAppendInfo))
    //    {
    //        pResult->strAppendInfo = outputAppendInfo;
    //    }
    //}

    //std::string outputBestSnapshotPath;
    //if (SaveCIMG(pResult->CIMG_BestSnapshot, systime, dwTick, 3, outputBestSnapshotPath))
    //{
    //    LOGFMTD("save BestSnapshot image success.");
    //    if (Tool_InsertElementByName(pResult->strAppendInfo.c_str(), "Result", 2, "BestSnapshotPath", outputBestSnapshotPath.c_str(), outputAppendInfo))
    //    {
    //        pResult->strAppendInfo = outputAppendInfo;
    //    }
    //}

    //if (Tool_InsertElementByName(pResult->strAppendInfo.c_str(), "Result", 2, "ITTS_IP", m_strIP.c_str(), outputAppendInfo))
    //{
    //    pResult->strAppendInfo = outputAppendInfo;
    //}

    //bool bSaveSuccess = false;
    //for (int i = 0; i < 5; i++)
    //{
    //    if (Tool_SaveFileToPath(chAppenInfoPath, (void*)pResult->strAppendInfo.c_str(), pResult->strAppendInfo.length()))
    //    {
    //        LOGFMTD("save AppenInfo %s success.", chAppenInfoPath);
    //        bSaveSuccess = true;
    //        break;
    //    }
    //    else
    //    {
    //        WriteFormatLog("save AppenInfo %s failed.", chAppenInfoPath);
    //    }
    //    Sleep(50);
    //}


    if (SaveCIMG(pResult->CIMG_BinImage, systime, dwTick, 0, outputBinPath))
    {
        LOGFMTD("save bin image success.");
        outputAppendInfo = "";
        if (Tool_InsertElementByName(pResult->pcAppendInfo, "Result", 2, "BinImgPath", outputBinPath.c_str(), outputAppendInfo))
        {
            if (outputAppendInfo.length() < sizeof(pResult->pcAppendInfo))
            {
                memset(pResult->pcAppendInfo, '\0', sizeof(pResult->pcAppendInfo));
                memcpy(pResult->pcAppendInfo, outputAppendInfo.c_str(), outputAppendInfo.length());
            }
            else
            {
                LOGFMTE("insert  BinImgPath failed, size is too small.");
            }
        }
    }

    std::string outputSmallPath;
    if (SaveCIMG(pResult->CIMG_PlateImage, systime, dwTick, 1, outputSmallPath))
    {
        LOGFMTD("save small image success.");
        outputAppendInfo = "";
        if (Tool_InsertElementByName(pResult->pcAppendInfo, "Result", 2, "SmallImgPath", outputSmallPath.c_str(), outputAppendInfo))
        {
            if (outputAppendInfo.length() < sizeof(pResult->pcAppendInfo))
            {
                memset(pResult->pcAppendInfo, '\0', sizeof(pResult->pcAppendInfo));
                memcpy(pResult->pcAppendInfo, outputAppendInfo.c_str(), outputAppendInfo.length());
            }
            else
            {
                LOGFMTE("insert  SmallImgPath failed, size is too small.");
            }
        }
    }

    std::string outputLastSnapshotPath;
    if (SaveCIMG(pResult->CIMG_LastSnapshot, systime, dwTick, 2, outputLastSnapshotPath))
    {
        LOGFMTD("save LastSnapshot image success.");
        outputAppendInfo = "";
        if (Tool_InsertElementByName(pResult->pcAppendInfo, "Result", 2, "LastSnapshotPath", outputLastSnapshotPath.c_str(), outputAppendInfo))
        {
            if (outputAppendInfo.length() < sizeof(pResult->pcAppendInfo))
            {
                memset(pResult->pcAppendInfo, '\0', sizeof(pResult->pcAppendInfo));
                memcpy(pResult->pcAppendInfo, outputAppendInfo.c_str(), outputAppendInfo.length());
            }
            else
            {
                LOGFMTE("insert  LastSnapshotPath failed, size is too small.");
            }
        }
    }

    std::string outputBestSnapshotPath;
    if (SaveCIMG(pResult->CIMG_BestSnapshot, systime, dwTick, 3, outputBestSnapshotPath))
    {
        LOGFMTD("save BestSnapshot image success.");
        outputAppendInfo = "";
        if (Tool_InsertElementByName(pResult->pcAppendInfo, "Result", 2, "BestSnapshotPath", outputBestSnapshotPath.c_str(), outputAppendInfo))
        {
            if (outputAppendInfo.length() < sizeof(pResult->pcAppendInfo))
            {
                memset(pResult->pcAppendInfo, '\0', sizeof(pResult->pcAppendInfo));
                memcpy(pResult->pcAppendInfo, outputAppendInfo.c_str(), outputAppendInfo.length());
            }
            else
            {
                LOGFMTE("insert  BestSnapshotPath failed, size is too small.");
            }
        }
    }

    outputAppendInfo = "";
    if (Tool_InsertElementByName(pResult->pcAppendInfo, "Result", 2, "ITTS_IP", m_strIP.c_str(), outputAppendInfo))
    {
        if (outputAppendInfo.length() < sizeof(pResult->pcAppendInfo))
        {
            memset(pResult->pcAppendInfo, '\0', sizeof(pResult->pcAppendInfo));
            memcpy(pResult->pcAppendInfo, outputAppendInfo.c_str(), outputAppendInfo.length());
        }
        else
        {
            LOGFMTE("insert  ITTS_IP failed, size is too small.");
        }
    }

    char chAppenInfoPath[MAX_PATH] = { 0 };
    sprintf_s(chAppenInfoPath, sizeof(chAppenInfoPath), "%s\\%04d-%02d-%02d-%lu.xml",
        m_chResultPath,
        systime.wYear,
        systime.wMonth,
        systime.wDay,
        dwTick);

    bool bSaveSuccess = false;
    for (int i = 0; i < 5; i++)
    {
        if (Tool_SaveFileToPath(chAppenInfoPath, (void*)pResult->pcAppendInfo, strlen(pResult->pcAppendInfo)+1))
        {
            LOGFMTD("save AppenInfo %s success.", chAppenInfoPath);
            bSaveSuccess = true;
            break;
        }
        else
        {
            WriteFormatLog("save AppenInfo %s failed.", chAppenInfoPath);
        }
        Sleep(50);
    }

    if (!bSaveSuccess)
    {
        LOGFMTE("SerializationResult:: save appendInfo failed, delete remain file.");
        LOGFMTE("DeleteFile(%s) = %d", outputBinPath.c_str(), DeleteFile(outputBinPath.c_str()));
        LOGFMTE("DeleteFile(%s) = %d", outputSmallPath.c_str(), DeleteFile(outputSmallPath.c_str()));
        LOGFMTE("DeleteFile(%s) = %d", outputLastSnapshotPath.c_str(), DeleteFile(outputLastSnapshotPath.c_str()));
        LOGFMTE("DeleteFile(%s) = %d", outputBestSnapshotPath.c_str(), DeleteFile(outputBestSnapshotPath.c_str()));
    }

    LOGFMTD("SerializationResult finish.");
}

void Camera6467_plate::SerializationResultEx(std::shared_ptr<CameraResult>& pResult)
{
    //typedef struct {
    //    INT64 iObjecSize;
    //}ResultInfo;

    //ResultInfo info;
    //info.iObjecSize = sizeof(ResultInfo) + sizeof(CameraResult)+pResult->CIMG_BestSnapshot.dwImgSize +
    //    pResult->CIMG_LastSnapshot.dwImgSize +
    //    pResult->CIMG_BeginCapture.dwImgSize +
    //    pResult->CIMG_BestCapture.dwImgSize +
    //    pResult->CIMG_LastCapture.dwImgSize +
    //    pResult->CIMG_PlateImage.dwImgSize +
    //    pResult->CIMG_BinImage.dwImgSize;

    SYSTEMTIME systime;
    GetLocalTime(&systime);//本地时间
    DWORD dwTick = GetTickCount();

    MakeSureDirectoryPathExists(m_chResultPath);

    char szFileName[MAX_PATH] = { 0 };
    sprintf_s(szFileName, sizeof(szFileName), "%s\\%04d-%02d-%02d-%lu.dat",
        m_chResultPath,
        systime.wYear,
        systime.wMonth,
        systime.wDay,
        dwTick);

    pResult->SerializationToDisk(szFileName);

    //FILE* pfile = NULL;
    //errno_t errCode;
    //_set_errno(0);
    //errCode = fopen_s(&pfile, szFileName, "wb");
    //if (errCode != 0)
    //{
    //    LOGFMTE("SerializationResultEx:: open file failed., error code = %d", errCode);
    //    return;
    //}
    //if (!pfile)
    //{
    //    LOGFMTE("SerializationResultEx:: open file failed ,pfile== NULL, error code = %d", errCode);
    //    return;
    //}

    //fwrite(&info, sizeof(byte), sizeof(ResultInfo), pfile);
    //fwrite(pResult, sizeof(byte), sizeof(CameraResult), pfile);
    //if (pResult->CIMG_BestSnapshot.dwImgSize > 0)
    //{
    //    fwrite(pResult->CIMG_BestSnapshot.pbImgData, sizeof(byte), pResult->CIMG_BestSnapshot.dwImgSize, pfile);
    //}
    //if (pResult->CIMG_LastSnapshot.dwImgSize > 0)
    //{
    //    fwrite(pResult->CIMG_LastSnapshot.pbImgData, sizeof(byte), pResult->CIMG_LastSnapshot.dwImgSize, pfile);
    //}
    //if (pResult->CIMG_BeginCapture.dwImgSize > 0)
    //{
    //    fwrite(pResult->CIMG_BeginCapture.pbImgData, sizeof(byte), pResult->CIMG_BeginCapture.dwImgSize, pfile);
    //}
    //if (pResult->CIMG_BestCapture.dwImgSize > 0)
    //{
    //    fwrite(pResult->CIMG_BestCapture.pbImgData, sizeof(byte), pResult->CIMG_BestCapture.dwImgSize, pfile);
    //}
    //if (pResult->CIMG_LastCapture.dwImgSize > 0)
    //{
    //    fwrite(pResult->CIMG_LastCapture.pbImgData, sizeof(byte), pResult->CIMG_LastCapture.dwImgSize, pfile);
    //}
    //if (pResult->CIMG_PlateImage.dwImgSize > 0)
    //{
    //    fwrite(pResult->CIMG_PlateImage.pbImgData, sizeof(byte), pResult->CIMG_PlateImage.dwImgSize, pfile);
    //}
    //if (pResult->CIMG_BinImage.dwImgSize > 0)
    //{
    //    fwrite(pResult->CIMG_BinImage.pbImgData, sizeof(byte), pResult->CIMG_BinImage.dwImgSize, pfile);
    //}

    ////fflush(pfile);
    //fclose(pfile);
    //pfile = NULL;
}

bool Camera6467_plate::SaveCIMG(CameraIMG& imgStruct, SYSTEMTIME& systime, DWORD tickCount, int iType, std::string& outputPath)
{
#define BIN_IMG  0
#define SMALL_IMG 1
#define  BIG_IMG 2
#define  SP_IMG 3
    bool bRet = false;
    if (imgStruct.dwImgSize > 0)
    {
        char szImgPath[MAX_PATH] = { 0 };
        sprintf_s(szImgPath, sizeof(szImgPath), "%s\\%04d-%02d-%02d-%u_s",
            m_chResultPath,
            systime.wYear,
            systime.wMonth,
            systime.wDay,
            tickCount);

        switch (iType)
        {
        case BIN_IMG:
            strcat_s(szImgPath, sizeof(szImgPath), ".bin");
            break;
        case SMALL_IMG:
            strcat_s(szImgPath, sizeof(szImgPath), "_small.jpg");
            break;
        case BIG_IMG:
            strcat_s(szImgPath, sizeof(szImgPath), "_big1.jpg");
            break;
        case SP_IMG:
            strcat_s(szImgPath, sizeof(szImgPath), "_big2.jpg");
            break;
        default:
            strcat_s(szImgPath, sizeof(szImgPath), "_big1.jpg");
            break;
        }
        outputPath = szImgPath;
        bRet = SaveImgToDisk(szImgPath, imgStruct.pbImgData, imgStruct.dwImgSize);
    }
    return bRet;
}

void Camera6467_plate::SaveResult()
{
    std::shared_ptr<CameraResult> pTempResult;
    while (!GetCheckThreadExit())
    {
        if (m_lsResultList.empty())
        {
            Sleep(50);
            continue;
        }
        m_lsResultList.front(pTempResult);
        if (pTempResult)
        {            
            SerializationResultEx(pTempResult);
        }
        Sleep(10);
    }
}

bool Camera6467_plate::SetUpLoaderCallback(void* callbackFunc)
{
    return false;
}

void Camera6467_plate::UpLoadCameraStatus()
{
    //STDEVSTATE devState;
    EnterCriticalSection(&m_csFuncCallback); 

    if (g_ConnectStatusCallback == NULL)
    {
        LeaveCriticalSection(&m_csFuncCallback);
        return;
    }
    LeaveCriticalSection(&m_csFuncCallback);

    WriteFormatLog("UpLoadCameraStatus, g_ConnectStatusCallback= %p, begin.", g_ConnectStatusCallback);
    EnterCriticalSection(&m_csFuncCallback);
    //((VPR_GetStatus)g_ConnectStatusCallback)(&m_CusdevState);
    LeaveCriticalSection(&m_csFuncCallback);
    WriteFormatLog("UpLoadCameraStatus, g_ConnectStatusCallback= %p, finish.", g_ConnectStatusCallback);
}

void Camera6467_plate::StartPlayVideoByChannel(int iChannelID, const HWND winHandle)
{
    if (iChannelID == 0)
    {
        StartPlayVideo(iChannelID, m_hPlayFirstH264, winHandle);
    }
    else
    {
        StartPlayVideo(iChannelID, m_hPlaySecondh264, winHandle);
    }
}

int Camera6467_plate::StopPlayVideoByChannel(int iChannelID)
{
    if (iChannelID == 0)
    {
        WriteFormatLog("StopPlayVideoByChannel 0, begin.");
        StopPlayVideo(m_hPlayFirstH264);
    }
    else if (iChannelID == 1)
    {
        WriteFormatLog("StopPlayVideoByChannel 1, begin.");
        StopPlayVideo(m_hPlaySecondh264);
    }
    WriteFormatLog("StopPlayVideoByChannel, end.");
    return 0;
}

void* Camera6467_plate::GetVideoHandleByChannel(int iChannerlID)
{
    if (iChannerlID == 0)
    {
        return m_hPlayFirstH264;
    }
    else
    {
        return m_hPlaySecondh264;
    }
}

int Camera6467_plate::GetChannelIDByHandle(void* handle)
{
    if (handle == NULL)
    {
        return -1;
    }
    else if (handle == m_hPlayFirstH264)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

bool Camera6467_plate::TakeOnePictureFromVedio(int channelID, CameraIMG& camImg, int iImgType /*= 0*/)
{
    bool bRet = false;

    if (m_pCaptureImg == NULL)
    {
        m_pCaptureImg = new BYTE[MAX_IMG_SIZE];
    }
    if (m_pCaptureImg)
    {
        memset(m_pCaptureImg, 0, MAX_IMG_SIZE);
        int iLength = MAX_IMG_SIZE;
        int iWidth = 1920;
        int iHeight = 1080;
        int iTryTime = 5;
        while (iTryTime--)
        {
            if (channelID == 0 && m_hPlayFirstH264)
            {
                bRet = H264_GetOneBmpImg(m_hPlayFirstH264, m_pCaptureImg, iLength, iWidth, iHeight);
            }
            else if (channelID == 1 && m_hPlaySecondh264)
            {
                bRet = H264_GetOneBmpImg(m_hPlaySecondh264, m_pCaptureImg, iLength, iWidth, iHeight);
            }
            else
            {
                WriteLog("TakeOnePictureFromVedio , 参数错误.");
                break;
            }
            //bRet = H264_GetOneImg( m_hPlayH264, m_pCaptureImg, iLength, iWidth, iHeight );
            if (bRet)
            {
                break;
            }
            Sleep(50);
        }
        if (bRet)
        {
            if (iImgType == 0)
            {
                //BMP format
                if (camImg.pbImgData == NULL)
                {
                    camImg.pbImgData = new BYTE[MAX_IMG_SIZE];
                }
                if (camImg.pbImgData)
                {
                    memset(camImg.pbImgData, 0, MAX_IMG_SIZE);
                    memcpy(camImg.pbImgData, m_pCaptureImg, iLength);
                    camImg.dwImgSize = iLength;
                    camImg.wImgWidth = iWidth;
                    camImg.wImgHeight = iHeight;
                }
                else
                {
                    WriteLog("iput image data is null.");
                }
            }
            else
            {
                //JPEG format
                if (m_pTempBig == NULL)
                {
                    m_pTempBig = new BYTE[MAX_IMG_SIZE];
                }
                if (m_pTempBig)
                {
                    memset(m_pTempBig, 0, MAX_IMG_SIZE);
                    size_t iDestLength = MAX_IMG_SIZE;
                    bool bScale = Tool_Img_ScaleJpg(m_pCaptureImg, iLength, m_pTempBig, &iDestLength, iWidth, iHeight, 80);
                    if (bScale)
                    {
                        WriteLog("Img_ScaleJpg success.");
                        if (camImg.pbImgData == NULL)
                        {
                            camImg.pbImgData = new BYTE[MAX_IMG_SIZE];
                        }
                        if (camImg.pbImgData)
                        {
                            memset(camImg.pbImgData, 0, MAX_IMG_SIZE);
                            memcpy(camImg.pbImgData, m_pTempBig, iDestLength);
                            camImg.dwImgSize = iDestLength;
                            camImg.wImgWidth = iWidth;
                            camImg.wImgHeight = iHeight;
                        }
                        else
                        {
                            WriteLog("iput image data is null.");
                        }
                    }
                    else
                    {
                        memset(camImg.pbImgData, 0, MAX_IMG_SIZE);
                        memcpy(camImg.pbImgData, m_pCaptureImg, iLength);
                        camImg.dwImgSize = iLength;
                        camImg.wImgWidth = iWidth;
                        camImg.wImgHeight = iHeight;
                        WriteLog("Img_ScaleJpg failed, use default");
                    }
                }
                else
                {
                    WriteLog("Ig_funcBigImg_OSD_Callback =null or  m_pTempBig = null.");
                }
            }
        }
        else
        {
            WriteLog("H264_GetOneImg failed.");
        }
    }
    else
    {
        WriteLog("m_CaptureImg = null");
    }

    return bRet;
}

int Camera6467_plate::GetChanelIDByWinHandle(void* handle)
{
    if (handle == NULL)
    {
        return -1;
    }
    if (handle == m_hFirstWinHandle)
    {
        return 0;
    }
    else if (handle == m_hSecondWinHandle)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

void Camera6467_plate::recordChannelWinHandle(int channelID, void* handle)
{
    if (channelID == 0)
    {
        m_hFirstWinHandle = handle;
    }
    else
    {
        m_hSecondWinHandle = handle;
    }
}

void Camera6467_plate::SetResultComplete(bool bfinish)
{
    EnterCriticalSection(&m_csResult);
    m_bResultComplete = bfinish;
    LeaveCriticalSection(&m_csResult);
}

int Camera6467_plate::GetTimeInterval()
{
    int iTimeInterval = 1;
    EnterCriticalSection(&m_csFuncCallback);
    iTimeInterval = m_iTimeInvl;
    LeaveCriticalSection(&m_csFuncCallback);
    return iTimeInterval;
}

void Camera6467_plate::CheckStatus()
{
    int iLastStatus = -1;
    INT64 iLastTick = 0, iCurrentTick = 0;
    int iFirstConnctSuccess = -1;

    while (!GetCheckThreadExit())
    {
        Sleep(50);
        iCurrentTick = GetTickCount();
        int iTimeInterval = GetTimeInterval();
        if ((iCurrentTick - iLastTick) >= (iTimeInterval * 1000))
        {
            UpLoadCameraStatus();
            int iStatus = GetCamStatus();
            //if (iStatus != iLastStatus)
            {
                if (iStatus == 0)
                {
                    //if (iStatus != iLastStatus)
                    //{
                    //	pThis->SendConnetStateMsg(true);
                    //}
                    //SendConnetStateMsg(true);
                    WriteLog("设备连接正常.");
                    iFirstConnctSuccess = 0;
                }
                else
                {
                    //SendConnetStateMsg(false);
                    WriteLog("设备连接失败, 尝试重连");

                    if (iFirstConnctSuccess == -1
                        && 0 == ConnectToCamera()
                        )
                    {
                        iFirstConnctSuccess = 0;
                        WriteLog(" 尝试重连 成功");
                    }
                }
            }
            iLastStatus = iStatus;

            iLastTick = iCurrentTick;
        }
    }
}

unsigned int __stdcall Camera_SaveResultThread(LPVOID lpParam)
{
    if (lpParam == NULL)
    {
        return 0;
    }
    LOGFMTD("Camera_SaveResultThread, begin");
    Camera6467_plate* pCamera = (Camera6467_plate*)lpParam;
    pCamera->SaveResult();   
    LOGFMTD("Camera_SaveResultThread, finish");
    return 0;
}