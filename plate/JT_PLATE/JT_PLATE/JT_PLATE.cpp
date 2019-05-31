// JT_PLATE.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "JT_PLATE.h"
#include "utilityTool/ToolFunction.h"
#include "CameraModule/Camera6467_plate.h"

std::shared_ptr<Camera6467_plate> g_Camera_Plate;
std::shared_ptr<uint8_t> g_pImgData;

uint8_t* GetImgBufferAddress()
{
    uint8_t* pData = NULL;
    if (!g_pImgData)
    {
        g_pImgData = std::shared_ptr<uint8_t>(new uint8_t[MAX_IMG_SIZE], std::default_delete<uint8_t[]>());
    }
    if (g_pImgData)
    {
        pData = g_pImgData.get();
        memset(pData, 0, MAX_IMG_SIZE);
    }
    return pData;
}


JT_PLATE_API BOOL DLL_DELC Plate_InitDevice(HWND hHandle, int Msg, int PorType, char * PortName, long Baudrate)
{
    Tool_WriteFormatLog("Plate_InitDevice, hHandle = %p, Msg = %d, PorType = %d, PortName = %s, Baudrate = %d .",
        hHandle,
        Msg,
        PorType,
        PortName,
        Baudrate);

    std::string strPlateIp(PortName);
    if (g_Camera_Plate != NULL
        && 0 == strcmp(strPlateIp.c_str(), g_Camera_Plate->GetCameraIP())
        )
    {
        Tool_WriteFormatLog("Plate_InitDevice, the camera %s is already connecting, return true.", strPlateIp.c_str());
        return TRUE;
    }

    g_Camera_Plate = std::make_shared<Camera6467_plate>(PortName, hHandle, Msg);
    //g_Camera_Plate->SetCameraIP(PortName);
    int iConnect = g_Camera_Plate->ConnectToCamera();
    Tool_WriteFormatLog("create plate camera finish, connect code = %d.", iConnect);
    
    BOOL bRet = TRUE;
    if (iConnect != 0)
    {
        //bRet = FALSE;
        Tool_WriteFormatLog("create plate camera finish, connect failed, but it will reconnect later, so return true.", iConnect);
    }

    Tool_WriteFormatLog("Plate_InitDevice return %d.", bRet);
    return bRet;
}

JT_PLATE_API BOOL DLL_DELC Plate_CloseDevice()
{
    Tool_WriteFormatLog("Plate_CloseDevice, begin .");
    if (g_Camera_Plate)
    {
        g_Camera_Plate = NULL;
    }

    Tool_WriteFormatLog("Plate_CloseDevice, finish.");
    return TRUE;
}

JT_PLATE_API BOOL DLL_DELC Plate_Getinfo(char * PlateInfor, char * ColorInfo)
{
    Tool_WriteFormatLog("Plate_Getinfo, begin PlateInfor = %p, ColorInfo = %p .", PlateInfor, ColorInfo);

    if (PlateInfor == NULL
        || ColorInfo == NULL)
    {
        Tool_WriteFormatLog("Plate_Getinfo, parameter is invalid ,return false .");
        return FALSE;
    }

    BOOL bRet = FALSE;
    if (g_Camera_Plate != nullptr)
    {        
        if (g_Camera_Plate->GetResultComplete())
        {          
            std::shared_ptr<CameraResult> pResult(g_Camera_Plate->GetOneResult());
            if (pResult != nullptr)
            {                
                Tool_WriteFormatLog("Plate_Getinfo, plate number = %s .", pResult->chPlateNO);
                //memcpy(PlateInfor, pResult->chPlateNO, strlen(pResult->chPlateNO) + 1);
                memcpy(PlateInfor, pResult->chPlateNO+2, strlen(pResult->chPlateNO) + 1);
                *ColorInfo = pResult->iPlateColor;
                Tool_WriteFormatLog("Plate_Getinfo, copy finish .");
                bRet = TRUE;
            }
            else
            {
                Tool_WriteFormatLog("Plate_Getinfo, GetOneResult failed .");
            }
        }
        else
        {
            Tool_WriteFormatLog("Plate_Getinfo, Result is not Complete.");
        }
    }
    else
    {
        Tool_WriteFormatLog("Plate_Getinfo, camera not connect .");
    }

    Tool_WriteFormatLog("Plate_Getinfo, finish, PlateInfor = %s, ColorInfo = %d .", PlateInfor, *ColorInfo);
    return bRet;
}

JT_PLATE_API BOOL DLL_DELC Plate_GetState(int* State)
{
    Tool_WriteFormatLog("Plate_GetState, begin ,State= %p .", State);
    int iRet = -1;
    if (g_Camera_Plate != nullptr )
    {
        //iRet = g_Camera_Plate->GetIttsStatus(pDevState);
        *State = g_Camera_Plate->GetCamStatus();
    }
    else
    {
        Tool_WriteFormatLog("Plate_GetState, camera not connect .");
        *State = 1;
    }

    Tool_WriteFormatLog("Plate_GetState, finish, return code 1, status = %d", iRet, *State);
    return TRUE;
}

JT_PLATE_API BOOL DLL_DELC Plate_GetImage(int ImageType, char * ImageInfo)
{
    Tool_WriteFormatLog("Plate_GetImage, begin ImageType = %d, ImageInfo = %s .", ImageType, ImageInfo);
    if (ImageInfo == NULL
        || strlen(ImageInfo) <= 0)
    {
        Tool_WriteFormatLog("Plate_GetImage, parameter is invalid ,return false .");
        return FALSE;
    }

    BOOL bRet = FALSE;
    if (g_Camera_Plate != nullptr)
    {
        void* pData = NULL;
        size_t iDataLength = 0;
        std::shared_ptr<CameraResult> pResult;
        if (g_Camera_Plate->GetResultComplete())
        {
            pResult = std::shared_ptr<CameraResult>(g_Camera_Plate->GetOneResult());
            if (pResult != nullptr)
            {
                switch (ImageType)
                {
                case 0:
                    pData = pResult->CIMG_BinImage.pbImgData;
                    iDataLength = pResult->CIMG_BinImage.dwImgSize;
                    break;

                case 1:
                    pData = pResult->CIMG_PlateImage.pbImgData;
                    iDataLength = pResult->CIMG_PlateImage.dwImgSize;
                    break;

                case 2:
                    pData = pResult->CIMG_LastSnapshot.pbImgData;
                    iDataLength = pResult->CIMG_LastSnapshot.dwImgSize;
                    break;

                default:
                    break;
                }
                Tool_WriteFormatLog("Plate_GetImage, pData= %p, size = %d .", pData, iDataLength);
            }
            else
            {
                Tool_WriteFormatLog("Plate_GetImage, GetOneResult failed .");
            }
        }
        else
        {
            Tool_WriteFormatLog("Plate_GetImage, Result is not Complete.");
        }

        CameraIMG destImg;
        if (ImageType == 3
            && g_Camera_Plate->GetOneJpegImg(destImg)
            )
        {
            Tool_WriteFormatLog("Plate_GetImage, GetOneJpegImg  success .");
            pData = destImg.pbImgData;
            iDataLength = destImg.dwImgSize;
        }

        if (ImageType == 3
            && pData != NULL
            && iDataLength > 0)
        {
            int iCompresssEnable = 1;
            int iCompressWidth = 768;
            int iCompressHeight = 576;
            int iQuality = 50;
            Tool_ReadIntValueFromConfigFile(INI_FILE_NAME, "Compress", "Enable", iCompresssEnable);
            Tool_ReadIntValueFromConfigFile(INI_FILE_NAME, "Compress", "width", iCompressWidth);
            Tool_ReadIntValueFromConfigFile(INI_FILE_NAME, "Compress", "height", iCompressHeight);
            Tool_ReadIntValueFromConfigFile(INI_FILE_NAME, "Compress", "Quality", iQuality);

            Tool_WriteFormatLog("Plate_GetImage, Compress ,enable = %d, width = %d, height= %d, Quality= %d .",
                iCompresssEnable,
                iCompressWidth,
                iCompressHeight,
                iQuality);

            uint8_t* pBuffer = GetImgBufferAddress();
            size_t iBufferLength = MAX_IMG_SIZE;
            if (iCompresssEnable >= 0
                && Tool_Img_ScaleJpg((uint8_t*)pData, iDataLength, pBuffer, &iBufferLength, iCompressWidth, iCompressHeight, iQuality)
                )
            {
                Tool_WriteFormatLog("Plate_GetImage, compress  success .", ImageInfo);
                pData = pBuffer;
                iDataLength = iBufferLength;
            }
            else
            {
                Tool_WriteFormatLog("Plate_GetImage, compress  failed .", ImageInfo);
            }
        }

        if (Tool_SaveFileToPath(ImageInfo, pData, iDataLength))
        {
            Tool_WriteFormatLog("Plate_GetImage, save to path %s  success .", ImageInfo);
            bRet = TRUE;
        }
        else
        {
            Tool_WriteFormatLog("Plate_GetImage, save to path %s  failed .", ImageInfo);
        }
    }
    else
    {
        Tool_WriteFormatLog("Plate_GetImage, camera not connect .");
    }

    return bRet;
}

JT_PLATE_API BOOL DLL_DELC Plate_Capture()
{
    Tool_WriteFormatLog("Plate_Capture, begin  .");
    BOOL bRet = FALSE;
    if (g_Camera_Plate != nullptr)
    {
        if (g_Camera_Plate->TakeCapture())
        {
            Tool_WriteFormatLog("Plate_Capture, Take Capture  success .");
            bRet = TRUE;
        }
        else
        {
            Tool_WriteFormatLog("Plate_Capture, Take Capture  failed .");
        }
    }
    else
    {
        Tool_WriteFormatLog("Plate_Capture, camera not connect .");
    }

    Tool_WriteFormatLog("Plate_Capture, finish, return code = %d", bRet);
    return bRet;
}

JT_PLATE_API BOOL DLL_DELC Plate_TakePhoto(char * ImageInfo)
{
    Tool_WriteFormatLog("Plate_TakePhoto, begin ImageInfo = %s .", ImageInfo);
    if (ImageInfo == NULL
        || strlen(ImageInfo) <= 0)
    {
        Tool_WriteFormatLog("Plate_TakePhoto, parameter is invalid ,return false .");
        return FALSE;
    }

    BOOL bRet = FALSE;
    if (g_Camera_Plate != nullptr)
    {
        CameraIMG destImg;
        if (g_Camera_Plate->GetOneJpegImg(destImg))
        {
            Tool_WriteFormatLog("Plate_TakePhoto, GetOneJpegImg  success .");
            unsigned char* pData = destImg.pbImgData;
            size_t iDataLength = destImg.dwImgSize;

            if ( pData != NULL
                && iDataLength > 0)
            {
                int iCompresssEnable = 1;
                int iCompressWidth = 768;
                int iCompressHeight = 576;
                int iQuality = 80;
                Tool_ReadIntValueFromConfigFile(INI_FILE_NAME, "Compress", "Enable", iCompresssEnable);
                Tool_ReadIntValueFromConfigFile(INI_FILE_NAME, "Compress", "width", iCompressWidth);
                Tool_ReadIntValueFromConfigFile(INI_FILE_NAME, "Compress", "height", iCompressHeight);
                Tool_ReadIntValueFromConfigFile(INI_FILE_NAME, "Compress", "Quality", iQuality);

                Tool_WriteFormatLog("Plate_TakePhoto, Compress ,enable = %d, width = %d, height= %d, Quality= %d .",
                    iCompresssEnable,
                    iCompressWidth,
                    iCompressHeight,
                    iQuality);

                uint8_t* pBuffer = GetImgBufferAddress();
                size_t iBufferLength = MAX_IMG_SIZE;
                if (iCompresssEnable >= 0
                    && Tool_Img_ScaleJpg((uint8_t*)pData, iDataLength, pBuffer, &iBufferLength, iCompressWidth, iCompressHeight, iQuality)
                    )
                {
                    Tool_WriteFormatLog("Plate_TakePhoto, compress  success .", ImageInfo);
                    pData = pBuffer;
                    iDataLength = iBufferLength;
                }
                else
                {
                    Tool_WriteFormatLog("Plate_TakePhoto, compress  failed .", ImageInfo);
                }
            }

            if (Tool_SaveFileToPath(ImageInfo, pData, iDataLength))
            {
                Tool_WriteFormatLog("Plate_TakePhoto, save to path %s  success .", ImageInfo);
                bRet = TRUE;
            }
            else
            {
                Tool_WriteFormatLog("Plate_TakePhoto, save to path %s  failed .", ImageInfo);
            }            
        }
        else
        {
            Tool_WriteFormatLog("Plate_TakePhoto, GetOneJpegImg  failed .");
        }
    }
    else
    {
        Tool_WriteFormatLog("Plate_TakePhoto, camera not connect .");
    }

    Tool_WriteFormatLog("Plate_TakePhoto, finish, return code = %d", bRet);
    return bRet;
}
