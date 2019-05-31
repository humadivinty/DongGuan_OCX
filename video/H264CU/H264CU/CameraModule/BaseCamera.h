#ifndef CAMERA6467_H
#define CAMERA6467_H
#include "CameraResult.h"
#include <string>
#include <list>
#include <comdef.h>
#include <gdiplus.h>
using namespace Gdiplus;
#pragma  comment(lib, "gdiplus.lib")

#define CMD_DEL_VEH_HEAD 1
#define CMD_GET_VEH_LENGTH 2
#define  CMD_DEL_ALL_VEH 3
#define CMD_GET_VHE_HEAD 4


#define  BUFFERLENTH 256

unsigned int __stdcall  Camera_StatusCheckThread(LPVOID lpParam);

struct CameraInfo
{
    char chIP[20];                          //deviceIP
    char chDeviceID[3];
    char chStationID[7];
    char chLaneID[3];
    bool bLogEnable;
    bool bSynTimeEnable;
    bool bIsInit;
    int iDirection;
    CameraInfo()
    {
        memset(chIP, 0, 20);
        memset(chDeviceID, 0, 3);
        memset(chStationID, 0, 7);
        memset(chLaneID, 0, 3);
        bLogEnable = true;
        bSynTimeEnable = false;
        bIsInit = false;
        iDirection = 0;
    }
};

struct SaveModeInfo
{
    int iSafeModeEnable;
    char chBeginTime[260];
    char chEndTime[260];
    int iIndex;
    int iDataType;
    SaveModeInfo()
    {
        iSafeModeEnable = 0;
        iIndex = 0;
        iDataType = 0;
        memset(chBeginTime, 0, 260);
        memset(chEndTime, 0, 260);
    }
};

struct DeviceTime
{
    int iYear;
    int iMonth;
    int iDay;
    int iHour;
    int iMinutes;
    int iSecond;
    int iMilisecond;

    DeviceTime()
    {
        iYear = 0;
        iMonth = 0;
        iDay = 0;
        iHour = 0;
        iMinutes = 0;
        iSecond = 0;
        iMilisecond = 0;
    }
};

typedef struct _BasicInfo
{
    char szIP[64];              //�豸IP�������������豸����
    char szMask[64];            //�豸�������룬�����������豸����
    char szGateway[64];         //�豸���أ������������豸����
    char szMac[128];            //�豸������ַ�������������豸����
    char szModelVersion[128]; //�豸ģ�Ͱ汾�����ֶα���
    char szSN[128];             //�豸��ţ������������豸����
    char szWorkMode[128];       //�豸����ģʽ����������PCC200��PCC600��PCC200A
    char szDevType[128];        //�豸���ͣ���������PCC200��PCC600��PCC200A
    char szDevVersion[128];  //�豸�汾����������PCC200��PCC600��PCC200A
    char szMode[128];           //�豸����ģʽ��������ģʽ�������������豸����
    char szRemark[128];    //�����ֶΣ���������PCC200��PCC600
    char szBackupVersion[128];  //���ݰ汾����������PCC200��PCC600 
    char szFPGAVersion[128]; //FPGA�汾����������PCC200��PCC600
    char szKernelVersion[128];  //Kernel�汾����������PCC200��PCC600
    char szUbootVersion[128]; //Uboot�汾����������PCC200��PCC600
    char szUBLVersion[128];//UBL�汾����������PCC200��PCC600
}BasicInfo;

class BaseCamera
{
public:
    BaseCamera();
    BaseCamera(const char* chIP, HWND  hWnd, int Msg);
    //Camera6467(const char* chIP, HWND*  hWnd,int Msg);
    virtual ~BaseCamera() = 0;

    //void SetList(Result_lister* ResultList);
    bool SetCameraInfo(CameraInfo& camInfo);
    void SetLoginID(int iID);

    int GetCamStatus();
    int GetNetSatus();
    int GetLoginID();
    char* GetStationID();
    char* GetDeviceID();
    char*  GetLaneID();
    const char* GetCameraIP();
    void SetCameraIP(const char* ipAddress);
    void SetWindowsWnd(HWND  hWnd);
    void SetCameraIndex(int iIndex);
    bool GetDeviceTime(DeviceTime& deviceTime);
    bool GetStreamLength(IStream* pStream, ULARGE_INTEGER* puliLenth);

    int ConnectToCamera();
    void	InterruptionConnection();
    bool DisConnectCamera();

    virtual void ReadConfig();

    void WriteFormatLog(const char* szfmt, ...);
    bool WriteLog(const char* chlog);

    bool TakeCapture();
    bool SynTime();
    bool SynTime(int Year, int Month, int Day, int Hour, int Minute, int Second, int MilientSecond);
    bool SaveImgToDisk(char* chImgPath, BYTE* pImgData, DWORD dwImgSize);
    bool SaveImgToDisk(char* chImgPath, BYTE* pImgData, DWORD dwImgSize, int iWidth, int iHeight, int iType = 0);

    void SetMsg(UINT iConMsg, UINT iDsiConMsg);
    void SaveResultToBufferPath(CameraResult* pResult);

    void CompressImg(CameraIMG& camImg, DWORD requireSize);

    void SendMessageToPlateServer(int iMessageType = 1);
    //���豸�����ض����ֻ���к�С���˶Խ���Ч
    bool SenMessageToCamera(int iMessageType, int& iReturnValue, int& iErrorCode, int iArg = 0);
    


    //�����豸�ĵ����ַ���С����ɫ
    bool SetOverlayVedioFont(int iFontSize, int iColor);
    bool SetOverlayVedioFont(int iFontSize, int iColorr, int iColorG, int iColorB);
    bool SetOverlayVedioFont(int streamID, int iFontSize, int iColorr, int iColorG, int iColorB);
    bool SetOverlayVideoText(int streamId, char* overlayText, int textLength);
    bool SetOverlayVideoTextPos(int streamId, int posX, int posY);
    bool SetOverlayVideoTextEnable(int streamId, bool enable);
    bool SetOverlayTimeEnable(int streamID, bool enable);
    bool SetOverlayTimeFormat(int streamId, int iformat);
    bool SetOverlayTimePos(int streamId, int posX, int posY);

    //��ȡ�豸��Ӳ���汾��Ϣ
    bool GetHardWareInfo(BasicInfo& info);
    int ConvertIDToStreamID(int iIndex);
protected:
    void* m_hHvHandle;
    //void* m_hWnd;
    HWND m_hWnd;
    int m_iMsg;
    int m_iConnectMsg;
    int m_iDisConMsg;
    int m_iConnectStatus;
    int m_iLoginID;
    int m_iCompressQuality;
    int m_iDirection;
    int m_iIndex;

    bool m_bLogEnable;
    bool m_bSynTime;

    char m_chDeviceID[3];
    char m_chStationID[7];
    char m_chLaneID[3];

    std::string m_strIP;
    std::string m_strDeviceID;

    CLSID m_jpgClsid;
    CLSID m_bmpClsid;

    SaveModeInfo m_SaveModelInfo;

    CRITICAL_SECTION m_csLog;    

    void ReadHistoryInfo();
    void WriteHistoryInfo(SaveModeInfo& SaveInfo);

    inline void CopyDataToIMG(CameraIMG& DestImg,
        PBYTE pImgData,
        unsigned long width,
        unsigned long height, 
        unsigned long dataLenth, 
        WORD wImgType)
    {
        if (NULL != DestImg.pbImgData)
        {
            delete[] DestImg.pbImgData;
            DestImg.pbImgData = NULL;
        }

        DestImg.pbImgData = new(std::nothrow) BYTE[dataLenth];
        DestImg.dwImgSize = 0;
        if (NULL != DestImg.pbImgData)
        {
            memcpy(DestImg.pbImgData, pImgData, dataLenth);
            DestImg.wImgWidth = width;
            DestImg.wImgHeight = height;
            DestImg.dwImgSize = dataLenth;
            DestImg.wImgType = wImgType;
        }
    }    
    
//protected:
    CRITICAL_SECTION m_csFuncCallback;

public:
    static int  RecordInfoBeginCallBack(PVOID pUserData, DWORD dwCarID)
    {
        if (pUserData == NULL)
            return 0;

        BaseCamera* pThis = (BaseCamera*)pUserData;
        return pThis->RecordInfoBegin(dwCarID);
    };
    virtual int RecordInfoBegin(DWORD dwCarID) = 0;

    static int  RecordInfoEndCallBack(PVOID pUserData, DWORD dwCarID)
    {
        if (pUserData == NULL)
            return 0;

        BaseCamera* pThis = (BaseCamera*)pUserData;
        return pThis->RecordInfoEnd(dwCarID);
    };
    virtual int RecordInfoEnd(DWORD dwCarID) = 0;

    static int  RecordInfoPlateCallBack(PVOID pUserData,
        DWORD dwCarID,
        LPCSTR pcPlateNo,
        LPCSTR pcAppendInfo,
        DWORD dwRecordType,
        DWORD64 dw64TimeMS)
    {
        if (pUserData == NULL)
            return 0;

        BaseCamera* pThis = (BaseCamera*)pUserData;
        return pThis->RecordInfoPlate(dwCarID, pcPlateNo, pcAppendInfo, dwRecordType, dw64TimeMS);
    }
    virtual int RecordInfoPlate(DWORD dwCarID,
        LPCSTR pcPlateNo,
        LPCSTR pcAppendInfo,
        DWORD dwRecordType,
        DWORD64 dw64TimeMS) = 0;

    static int  RecordInfoBigImageCallBack(PVOID pUserData,
        DWORD dwCarID,
        WORD  wImgType,
        WORD  wWidth,
        WORD  wHeight,
        PBYTE pbPicData,
        DWORD dwImgDataLen,
        DWORD dwRecordType,
        DWORD64 dw64TimeMS)
    {
        if (pUserData == NULL)
            return 0;

        BaseCamera* pThis = (BaseCamera*)pUserData;
        return pThis->RecordInfoBigImage(dwCarID, wImgType, wWidth, wHeight, pbPicData, dwImgDataLen, dwRecordType, dw64TimeMS);
    }
    virtual int RecordInfoBigImage(DWORD dwCarID,
        WORD  wImgType,
        WORD  wWidth,
        WORD  wHeight,
        PBYTE pbPicData,
        DWORD dwImgDataLen,
        DWORD dwRecordType,
        DWORD64 dw64TimeMS) = 0;

    static int  RecordInfoSmallImageCallBack(PVOID pUserData,
        DWORD dwCarID,
        WORD wWidth,
        WORD wHeight,
        PBYTE pbPicData,
        DWORD dwImgDataLen,
        DWORD dwRecordType,
        DWORD64 dw64TimeMS)
    {
        if (pUserData == NULL)
            return 0;

        BaseCamera* pThis = (BaseCamera*)pUserData;
        return pThis->RecordInfoSmallImage(dwCarID, wWidth, wHeight, pbPicData, dwImgDataLen, dwRecordType, dw64TimeMS);
    }
    virtual int RecordInfoSmallImage(DWORD dwCarID,
        WORD wWidth,
        WORD wHeight,
        PBYTE pbPicData,
        DWORD dwImgDataLen,
        DWORD dwRecordType,
        DWORD64 dw64TimeMS) = 0;

    static int  RecordInfoBinaryImageCallBack(PVOID pUserData,
        DWORD dwCarID,
        WORD wWidth,
        WORD wHeight,
        PBYTE pbPicData,
        DWORD dwImgDataLen,
        DWORD dwRecordType,
        DWORD64 dw64TimeMS)
    {
        if (pUserData == NULL)
            return 0;

        BaseCamera* pThis = (BaseCamera*)pUserData;
        return pThis->RecordInfoBinaryImage(dwCarID, wWidth, wHeight, pbPicData, dwImgDataLen, dwRecordType, dw64TimeMS);
    }
    virtual int RecordInfoBinaryImage(DWORD dwCarID,
        WORD wWidth,
        WORD wHeight,
        PBYTE pbPicData,
        DWORD dwImgDataLen,
        DWORD dwRecordType,
        DWORD64 dw64TimeMS) = 0;

    static int  JPEGStreamCallBack(
        PVOID pUserData,
        PBYTE pbImageData,
        DWORD dwImageDataLen,
        DWORD dwImageType,
        LPCSTR szImageExtInfo
        )
    {
        if (pUserData == NULL)
            return 0;

        BaseCamera* pThis = (BaseCamera*)pUserData;
        return pThis->DeviceJPEGStream(pbImageData, dwImageDataLen, dwImageType, szImageExtInfo);

    };
    virtual int DeviceJPEGStream(
        PBYTE pbImageData,
        DWORD dwImageDataLen,
        DWORD dwImageType,
        LPCSTR szImageExtInfo) = 0;

    virtual void CheckStatus() = 0;
};

#endif