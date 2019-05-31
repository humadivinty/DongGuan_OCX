#include "tinyxml/tinyxml.h"
#include "tinyxml/tinystr.h"
#include <string>
#include <list>
#include <map>
//#define MY_SPRINTF sprintf_s

#define SAFE_DELETE_OBJ(obj) \
if (NULL != obj)                                  \
{                                           \
    delete obj;                        \
    obj = NULL;                      \
}

#define SAFE_DELETE_ARRAY(arrayObj) \
if (NULL != arrayObj)                                  \
{                                           \
    delete[] arrayObj;                        \
    arrayObj = NULL;                      \
}

//ͨ���ڵ������Ҳ�������Ӧ�ڵ�
//ע��XMLTYPE Ϊ1ʱ��InputInfoΪXML·������Ϊ2ʱ,InputInfoΪ�������ļ�����
TiXmlElement Tool_SelectElementByName(const char* InputInfo, const char* pName, int iXMLType);

TiXmlElement* Tool_ReadElememt(TiXmlElement* InputElement, const char* pName);

bool Tool_GetElementTextByName(const char* InputInfo, const char* pName, int iXMLType, char* chTextValueBuffer, size_t& bufferLength);

bool Tool_InsertElementByName(const char* InputInfo, const char* pName, int iXMLType, const char* nodeName, const char* textValue, std::string& outputString);

void Tool_ReadKeyValueFromConfigFile(const char* FileName, const char* nodeName, const char* keyName, char* keyValue, int bufferSize);

void Tool_ReadIntValueFromConfigFile(const char* FileName, const char* nodeName, const char* keyName, int&keyValue);

void Tool_WriteKeyValueFromConfigFile(const char* FileName, const char* nodeName, const char* keyName, char* keyValue, int bufferSize);

//���IP����Ч��
int Tool_checkIP(const char* p);

bool Tool_IsFileExist(const char* FilePath);

bool Tool_MakeDir(const char* chImgPath);

long Tool_GetFileSize(const char *FileName);

bool Tool_PingIPaddress(const char* IpAddress);

//************************************
// Method:        Tool_Img_ScaleJpg
// Describe:        ѹ��ͼƬ��ָ��������С
// FullName:      Tool_Img_ScaleJpg
// Access:          public 
// Returns:        bool
// Returns Describe:
// Parameter:    PBYTE pbSrc   ����������� ԴͼƬ����ָ��
// Parameter:    int iSrcLen        ����������� ԴͼƬ���ݳ���
// Parameter:    PBYTE pbDst    ����������� ���ͼ������ݻ�����
// Parameter:    size_t * iDstLen   ������������������뻺������С���������ͼƬ��ʵ�ʴ�С
// Parameter:    int iDstWidth      �����������ָ����Ҫѹ���Ŀ���
// Parameter:    int iDstHeight     �����������ָ����Ҫѹ���ĸ߶�
// Parameter:    int compressQuality    �����������ָ��ѹ��������
//************************************
bool Tool_Img_ScaleJpg(PBYTE pbSrc, int iSrcLen, PBYTE pbDst, size_t *iDstLen, int iDstWidth, int iDstHeight, int compressQuality);

int Tool_GetEncoderClsid(const WCHAR* format, CLSID* pClsid);

void Tool_ExcuteShellCMD(char* pChCommand);

bool Tool_ExcuteCMDbyCreateProcess(const char* CmdName);

bool Tool_OverlayStringToImg(unsigned char** pImgsrc, long srcSize,
    unsigned char** pImgDest, long& DestSize,
    const wchar_t* DestString, int FontSize,
    int x, int y, int colorR, int colorG, int colorB,
    int compressQuality);

bool Tool_GetDataFromAppenedInfo(const char *pszAppendInfo, std::string strItemName, char *pszRstBuf, int *piRstBufLen);

void Tool_ExcuteCMD(char* pChCommand);

std::wstring Img_string2wstring(std::string strSrc);

#ifdef  USE_MFC
//ɾ��ָ���ļ���
bool DeleteDirectory(const char* strDirName);

//ɾ��ָ��Ŀ¼���� 'yyyy-mm-dd' ��ʽ�������ļ��У������޶�������Ϊʱ������ָ������
int CirclelaryDelete(const char* folderPath, int iBackUpDays);
#endif


int Tool_SafeCloseThread(HANDLE& threadHandle);

const char* Tool_GetCurrentPath();

SYSTEMTIME Tool_GetCurrentTime();

bool Tool_DimCompare(const char *szSrcPlateNo, const char *szDesPlateNo);

void Tool_WriteLog(const char*);

void Tool_WriteFormatLog(const char* szfmt, ...);

bool Tool_SaveFileToPath(const char* szPath, void* fileData, size_t fileSize);

std::list<std::string> getFilesPath(const std::string& cate_dir, const std::string& filter);

bool Tool_LoadFile(const char* fileName, void* pBuffer, size_t& fileSize);

bool Tool_LoadCamerXml(const char* fileName, std::map<std::string, int>& myMap);

void Tool_DeleteFileByCMD(const char* chFileName);

bool Tool_FindMapAndGetValue(std::map<std::string, int>& myMap, std::string keyName, int& value);

int Tool_AnalysisPlateColorNo(const char* szPlateNo);