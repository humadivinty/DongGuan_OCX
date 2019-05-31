// CDH264CU.h : 由 Microsoft Visual C++ 创建的 ActiveX 控件包装器类的声明

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CDH264CU

class CDH264CU : public CWnd
{
protected:
	DECLARE_DYNCREATE(CDH264CU)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0xA73F9A4, 0xC4C3, 0x41F6, { 0x97, 0xC3, 0x76, 0xD, 0xEC, 0xCC, 0xE3, 0xA7 } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
						const RECT& rect, CWnd* pParentWnd, UINT nID, 
						CCreateContext* pContext = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); 
	}

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, 
				UINT nID, CFile* pPersist = NULL, BOOL bStorage = FALSE,
				BSTR bstrLicKey = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); 
	}

// 特性
public:

// 操作
public:

	void AboutBox()
	{
		InvokeHelper(DISPID_ABOUTBOX, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	short Login(LPCTSTR SeverIP, long ServerPort, LPCTSTR LoginName, LPCTSTR LoginPsw)
	{
		short result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_I2, (void*)&result, parms, SeverIP, ServerPort, LoginName, LoginPsw);
		return result;
	}
	void Logout()
	{
		InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	short OpenVideo(short Channel)
	{
		short result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_I2, (void*)&result, parms, Channel);
		return result;
	}
	void CloseVideo(short Channel)
	{
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Channel);
	}
	short SetCaptureMass(short channelNo, short iMass)
	{
		short result;
		static BYTE parms[] = VTS_I2 VTS_I2 ;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_I2, (void*)&result, parms, channelNo, iMass);
		return result;
	}
	short GetCaptureMass(short channelNo)
	{
		short result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_I2, (void*)&result, parms, channelNo);
		return result;
	}
	short SetOSDTimeInfo(short channelNo, short timeFlag, short fontType, short fontSize, short timeX, short timeY, LPCTSTR color)
	{
		short result;
		static BYTE parms[] = VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_BSTR ;
		InvokeHelper(0x7, DISPATCH_METHOD, VT_I2, (void*)&result, parms, channelNo, timeFlag, fontType, fontSize, timeX, timeY, color);
		return result;
	}
	short GetOSDTimeInfo(short channelNo)
	{
		short result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x8, DISPATCH_METHOD, VT_I2, (void*)&result, parms, channelNo);
		return result;
	}
	CString ColorDlg(short byRed, short byGreen, short byBlue)
	{
		CString result;
		static BYTE parms[] = VTS_I2 VTS_I2 VTS_I2 ;
		InvokeHelper(0x9, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, byRed, byGreen, byBlue);
		return result;
	}
	short SetOSDLogoInfo(short channelNo, short logoFlag, short logo, short fontType, short fontSize, short logoX, short logoY, LPCTSTR color)
	{
		short result;
		static BYTE parms[] = VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_BSTR ;
		InvokeHelper(0xa, DISPATCH_METHOD, VT_I2, (void*)&result, parms, channelNo, logoFlag, logo, fontType, fontSize, logoX, logoY, color);
		return result;
	}
	short GetOSDLogoInfo(short channelNo)
	{
		short result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0xb, DISPATCH_METHOD, VT_I2, (void*)&result, parms, channelNo);
		return result;
	}
	short SetOSDUserDefInfo(short channelNo, short index, short defFlag, LPCTSTR logo, short fontType, short fontSize, short logoX, short logoY, LPCTSTR color)
	{
		short result;
		static BYTE parms[] = VTS_I2 VTS_I2 VTS_I2 VTS_BSTR VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_BSTR ;
		InvokeHelper(0xc, DISPATCH_METHOD, VT_I2, (void*)&result, parms, channelNo, index, defFlag, logo, fontType, fontSize, logoX, logoY, color);
		return result;
	}
	short GetOSDUserDefInfo(short channelNo, short index)
	{
		short result;
		static BYTE parms[] = VTS_I2 VTS_I2 ;
		InvokeHelper(0xd, DISPATCH_METHOD, VT_I2, (void*)&result, parms, channelNo, index);
		return result;
	}
	short SetRealTime(short iRealTime)
	{
		short result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0xe, DISPATCH_METHOD, VT_I2, (void*)&result, parms, iRealTime);
		return result;
	}
	short GetRealTime()
	{
		short result;
		InvokeHelper(0xf, DISPATCH_METHOD, VT_I2, (void*)&result, NULL);
		return result;
	}
	short DownLoadPic(LPCTSTR szPath, short nWidth, short nHeight)
	{
		short result;
		static BYTE parms[] = VTS_BSTR VTS_I2 VTS_I2 ;
		InvokeHelper(0x10, DISPATCH_METHOD, VT_I2, (void*)&result, parms, szPath, nWidth, nHeight);
		return result;
	}
	CString DirectoryDlg()
	{
		CString result;
		InvokeHelper(0x11, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	short SetSystemTime(long year, long month, long day, long hour, long minut, long second)
	{
		short result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x12, DISPATCH_METHOD, VT_I2, (void*)&result, parms, year, month, day, hour, minut, second);
		return result;
	}


};
