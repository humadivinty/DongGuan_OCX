// H264CU.cpp : CH264CUApp 和 DLL 注册的实现。

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



// CH264CUApp::InitInstance - DLL 初始化

BOOL CH264CUApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO:  在此添加您自己的模块初始化代码。
	}

	return bInit;
}



// CH264CUApp::ExitInstance - DLL 终止

int CH264CUApp::ExitInstance()
{
	// TODO:  在此添加您自己的模块终止代码。

	return COleControlModule::ExitInstance();
}



// DllRegisterServer - 将项添加到系统注册表

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



// DllUnregisterServer - 将项从系统注册表中移除

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
