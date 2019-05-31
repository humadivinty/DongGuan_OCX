// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //  从 Windows 头文件中排除极少使用的信息
// Windows 头文件: 
#include <windows.h>



// TODO:  在此处引用程序需要的其他头文件
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