// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //  �� Windows ͷ�ļ����ų�����ʹ�õ���Ϣ
// Windows ͷ�ļ�: 
#include <windows.h>



// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
#include "libHvDevice/HvDeviceNew.h"
#include "libHvDevice/HvCamera.h"
#pragma comment (lib, "libHvDevice/HvDevice.lib")

//#include <gdiplus.h>
//using namespace Gdiplus;
//#pragma  comment(lib, "gdiplus.lib")

#include <Shlwapi.h>
#include <DbgHelp.h>
#pragma comment (lib, "shlwapi.lib")
#pragma comment (lib, "dbghelp.lib")

#include <ctime>
#include<atltime.h>

#define DLL_VERSION "2018112001"
#define INI_FILE_NAME "\\Signalway_Config.ini"
#define DLL_LOG_NAME "XLW_PLATE.txt"

#define BIN_IMG_SIZE 280
#define COMPRESS_PLATE_IMG_SIZE 5*1024
#define COMPRESS_BIG_IMG_SIZE 100*1024

#ifdef WINXP
#define MY_SPRINTF sprintf
#else
#define MY_SPRINTF sprintf_s
#endif