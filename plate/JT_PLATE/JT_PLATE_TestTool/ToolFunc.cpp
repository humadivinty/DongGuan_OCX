#include "stdafx.h"
#include "ToolFunc.h"

char* Tool_GetCurrentAppPath()
{
    static TCHAR szPath[256] = { 0 };
    if (strlen(szPath) <= 0)
    {
        GetModuleFileName(NULL, szPath, MAX_PATH - 1);
        PathRemoveFileSpec(szPath);
    }
    return szPath;
}
