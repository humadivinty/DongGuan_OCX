// H264CU.cpp : CH264CUApp �� DLL ע���ʵ�֡�

#include "stdafx.h"
#include "H264CU.h"

#include "utilityTool/ToolFunction.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CH264CUApp theApp;

const GUID CDECL _tlid = { 0x984B8CA7, 0xC64A, 0x4163, { 0xBB, 0x32, 0x4, 0x4B, 0x7B, 0x20, 0xC1, 0xFA } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CH264CUApp::InitInstance - DLL ��ʼ��

BOOL CH264CUApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO:  �ڴ�������Լ���ģ���ʼ�����롣
	}

	return bInit;
}



// CH264CUApp::ExitInstance - DLL ��ֹ

int CH264CUApp::ExitInstance()
{
	// TODO:  �ڴ�������Լ���ģ����ֹ���롣

	return COleControlModule::ExitInstance();
}



// DllRegisterServer - ������ӵ�ϵͳע���

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);
    Tool_WriteFormatLog("DllRegisterServer");

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - �����ϵͳע������Ƴ�

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);
    Tool_WriteFormatLog("DllUnregisterServer");

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
