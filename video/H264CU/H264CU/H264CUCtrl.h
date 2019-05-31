#pragma once

// H264CUCtrl.h : CH264CUCtrl ActiveX 控件类的声明。
#include "CameraModule/Camera6467_plate.h"

#define OVERLAY_MAX_ROW 7
#define OVERLAY_MAX_COL 40
// CH264CUCtrl : 有关实现的信息，请参阅 H264CUCtrl.cpp。

class CH264CUCtrl : public COleControl
{
	DECLARE_DYNCREATE(CH264CUCtrl)

// 构造函数
public:
	CH264CUCtrl();

// 重写
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	virtual DWORD GetControlFlags();

// 实现
protected:
	~CH264CUCtrl();

	DECLARE_OLECREATE_EX(CH264CUCtrl)    // 类工厂和 guid
	DECLARE_OLETYPELIB(CH264CUCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CH264CUCtrl)     // 属性页 ID
	DECLARE_OLECTLTYPE(CH264CUCtrl)		// 类型名称和杂项状态

// 消息映射
	DECLARE_MESSAGE_MAP()

// 调度映射
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// 事件映射
	DECLARE_EVENT_MAP()

// 调度和事件 ID
public:
	enum {
        dispidSetSystemTime = 18L,
        dispidDirectoryDlg = 17L,
        dispidDownLoadPic = 16L,
        dispidGetRealTime = 15L,
        dispidSetRealTime = 14L,
        eventidOSDUserDefInfo = 4L,
        dispidGetOSDUserDefInfo = 13L,
        dispidSetOSDUserDefInfo = 12L,
        eventidOSDLogoInfo = 3L,
        dispidGetOSDLogoInfo = 11L,
        dispidSetOSDLogoInfo = 10L,
        dispidColorDlg = 9L,
        eventidOSDTimeInfo = 2L,
        dispidGetOSDTimeInfo = 8L,
        dispidSetOSDTimeInfo = 7L,
        eventidFireCaptureMass = 1L,
        dispidGetCaptureMass = 6L,
        dispidSetCaptureMass = 5L,
        dispidCloseVideo = 4L,
        dispidOpenVideo = 3L,
        dispidLogout = 2L,
        dispidLogin = 1L
    };
protected:
    //************************************
    // Method:        Login
    // Describe:        登陆设备,这是最先调用的接口
    // FullName:      CH264CUCtrl::Login
    // Access:          protected 
    // Returns:        SHORT        //   1 用户名错误  2 密码错误 -1 其他错误  0成功
    // Returns Describe:        
    // Parameter:    LPCTSTR SeverIP        //服务器IP
    // Parameter:    LONG ServerPort        //服务器端口
    // Parameter:    LPCTSTR LoginName  //登陆名称
    // Parameter:    LPCTSTR LoginPsw      //登陆密码
    //************************************
    SHORT Login(LPCTSTR SeverIP, LONG ServerPort, LPCTSTR LoginName, LPCTSTR LoginPsw);

    //************************************
    // Method:        Logout
    // Describe:        注销设备
    // FullName:      CH264CUCtrl::Logout
    // Access:          protected 
    // Returns:        void
    // Returns Describe:
    //************************************
    void Logout();

    //************************************
    // Method:        OpenVideo
    // Describe:        打开视频,   先选择对应的窗口，调用该接口可在上面打开视频
    // FullName:      CH264CUCtrl::OpenVideo
    // Access:          protected 
    // Returns:        SHORT
    // Returns Describe:
    // Parameter:    SHORT Channel      // 如果是单通道,该参数置1，多通道对应通道号 1-16
    //************************************
    SHORT OpenVideo(SHORT Channel);

    //************************************
    // Method:        CloseVideo
    // Describe:        关闭视频,关闭对应通道视频
    // FullName:      CH264CUCtrl::CloseVideo
    // Access:          protected 
    // Returns:        void
    // Returns Describe:
    // Parameter:    SHORT Channel      // 如果是单通道,该参数置1，多通道对应通道号 1-16
    //************************************
    void CloseVideo(SHORT Channel);

    //************************************
    // Method:        SetCaptureMass
    // Describe:        设置图片质量,设置设备抓拍图片质量
    // FullName:      CH264CUCtrl::SetCaptureMass
    // Access:          protected 
    // Returns:        SHORT
    // Returns Describe:
    // Parameter:    SHORT channelNo        // 如果是单通道,该参数置1，多通道对应通道号 1-16
    // Parameter:    SHORT iMass                //// 0好 1较好 2一般 3较差 4差
    //************************************
    SHORT SetCaptureMass(SHORT channelNo, SHORT iMass);

    //************************************
    // Method:        GetCaptureMass
    // Describe:        查询设备抓拍图片的质量
    // FullName:      CH264CUCtrl::GetCaptureMass   
    // Access:          protected 
    // Returns:        SHORT
    // Returns Describe:
    // Parameter:    SHORT channelNo    // 如果是单通道,该参数置1，多通道对应通道号 1-16
    //************************************
    SHORT GetCaptureMass(SHORT channelNo);
    

    //************************************
    // Method:        FireCaptureMass
    // Describe:
    // FullName:      CH264CUCtrl::FireCaptureMass
    // Access:          protected 
    // Returns:        void
    // Returns Describe:
    // Parameter:    SHORT iMass        : 0好 1较好 2一般 3较差 4差
    //************************************
    void FireCaptureMass(SHORT iMass)
    {
        FireEvent(eventidFireCaptureMass, EVENT_PARAM(VTS_I2), iMass);
    }
    //************************************
    // Method:        SetOSDTimeInfo
    // Describe:
    // FullName:      CH264CUCtrl::SetOSDTimeInfo
    // Access:          protected 
    // Returns:        SHORT
    // Returns Describe:
    // Parameter:    SHORT channelNo  :如果是单通道,该参数置1，多通道对应通道号 1-16
    // Parameter:    SHORT timeFlag     :显示使能  1 显示时间；0 不显示
    // Parameter:    SHORT fontType     :字体  0 宋体；1 黑体
    // Parameter:    SHORT fontSize     :字号0－2 大、中、小
    // Parameter:    SHORT timeX        :起始X坐标
    // Parameter:    SHORT timeY        :起始Y坐标
    // Parameter:    LPCTSTR color      :颜色，字符串如：255#255#255#100#255#255#255#100//前景色RGB 透明值
    //************************************
    SHORT SetOSDTimeInfo(SHORT channelNo,
        SHORT timeFlag, 
        SHORT fontType, 
        SHORT fontSize, 
        SHORT timeX, 
        SHORT timeY,
        LPCTSTR color);

    //************************************
    // Method:        GetOSDTimeInfo
    // Describe:        查询OSD时间信息
    // FullName:      CH264CUCtrl::GetOSDTimeInfo
    // Access:          protected 
    // Returns:        SHORT
    // Returns Describe:
    // Parameter:    SHORT channelNo    :如果是单通道,该参数置1，多通道对应通道号 1-16
    //************************************
    SHORT GetOSDTimeInfo(SHORT channelNo);



    //************************************
    // Method:        OSDTimeInfo
    // Describe:        
    // FullName:      CH264CUCtrl::OSDTimeInfo
    // Access:          protected 
    // Returns:        void
    // Returns Describe:
    // Parameter:    LONG timeFlag   :表示颜色，前景色RGB， 透明值，背景色RGB，透明值
    // Parameter:    LONG fontType
    // Parameter:    LONG timeX
    // Parameter:    LONG timeY
    // Parameter:    LONG timeFColorR
    // Parameter:    LONG timeFColorG
    // Parameter:    LONG timeFColorB
    // Parameter:    LONG FColorValue
    // Parameter:    LONG timeBColorR
    // Parameter:    LONG timeBColorG
    // Parameter:    LONG timeBColorB
    // Parameter:    LONG BColorValue
    //************************************
    void OSDTimeInfo(LONG timeFlag, 
        LONG fontType, 
        LONG timeX,
        LONG timeY,
        LONG timeFColorR,
        LONG timeFColorG,
        LONG timeFColorB, 
        LONG FColorValue, 
        LONG timeBColorR, 
        LONG timeBColorG, 
        LONG timeBColorB,
        LONG BColorValue)
    {
        FireEvent(eventidOSDTimeInfo, 
            EVENT_PARAM(VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4), 
            timeFlag,
            fontType,
            timeX,
            timeY, 
            timeFColorR, 
            timeFColorG, 
            timeFColorB, 
            FColorValue,
            timeBColorR,
            timeBColorG,
            timeBColorB, 
            BColorValue);
    }

    //************************************
    // Method:        ColorDlg
    // Describe:        颜色对话框
    // FullName:      CH264CUCtrl::ColorDlg
    // Access:          protected 
    // Returns:        BSTR
    // Returns Describe:  成功返回三颜色字符串R#G#B(如C0#FF#8A)，失败返回空
    // Parameter:    SHORT byRed    :红
    // Parameter:    SHORT byGreen  :绿
    // Parameter:    SHORT byBlue       :蓝
    //************************************
    BSTR ColorDlg(SHORT byRed, SHORT byGreen, SHORT byBlue);


    //************************************
    // Method:        SetOSDLogoInfo
    // Describe:        设置OSD Logo信息
    // FullName:      CH264CUCtrl::SetOSDLogoInfo
    // Access:          protected 
    // Returns:        SHORT
    // Returns Describe:
    // Parameter:    SHORT channelNo // 如果是单通道,该参数置1，多通道对应通道号 1-16
    // Parameter:    SHORT logoFlag     //显示使能  1 显示logo；0 不显示
    // Parameter:    SHORT logo             // 所要显示的logo字
    // Parameter:    SHORT fontType     //字体  0 宋体；1 黑体
    // Parameter:    SHORT fontSize     //字号0－2 大、中、小
    // Parameter:    SHORT logoX        //起始X坐标
    // Parameter:    SHORT logoY        //起始Y坐标
    // Parameter:    LPCTSTR color      //颜色，字符串如：255#255#255#100#255#255#255#100//前景色RGB 透明值背景色RGB透明值
    //************************************
    SHORT SetOSDLogoInfo(SHORT channelNo, 
        SHORT logoFlag,
        SHORT logo, 
        SHORT fontType, 
        SHORT fontSize,
        SHORT logoX, 
        SHORT logoY,
        LPCTSTR color);


    //************************************
    // Method:        GetOSDLogoInfo
    // Describe:        查询OSD Logo
    // FullName:      CH264CUCtrl::GetOSDLogoInfo
    // Access:          protected 
    // Returns:        SHORT
    // Returns Describe:
    // Parameter:    SHORT channelNo         // 如果是单通道,该参数置1，多通道对应通道号 1-16
    //************************************
    SHORT GetOSDLogoInfo(SHORT channelNo);

    //************************************
    // Method:        OSDLogoInfo
    // Describe:        通知客户端获取OSD信息事件
    // FullName:      CH264CUCtrl::OSDLogoInfo
    // Access:          protected 
    // Returns:        void
    // Returns Describe:
    // Parameter:    LONG logoFlag      //显示使能  1 显示logo；0 不显示
    // Parameter:    LPCTSTR logo       // 所要显示的logo字
    // Parameter:    LONG fontType      //字体  0 宋体；1 黑体
    // Parameter:    LONG fontSize      //字号0－2 大、中、小
    // Parameter:    LONG timeX         //起始X坐标
    // Parameter:    LONG timeY         //起始Y坐标
    // Parameter:    LONG timeFColorR   //表示颜色，前景色RGB， 透明值，背景色RGB，透明值
    // Parameter:    LONG timeFColorG
    // Parameter:    LONG timeFColorB
    // Parameter:    LONG FColorValue
    // Parameter:    LONG timeBColorR
    // Parameter:    LONG timeBColorG
    // Parameter:    LONG timeBColorB
    // Parameter:    LONG BColorValue
    //************************************
    void OSDLogoInfo(LONG logoFlag, LPCTSTR logo, LONG fontType, LONG fontSize, LONG timeX, LONG timeY, LONG timeFColorR, LONG timeFColorG, LONG timeFColorB, LONG FColorValue, LONG timeBColorR, LONG timeBColorG, LONG timeBColorB, LONG BColorValue)
    {
        FireEvent(eventidOSDLogoInfo,
            EVENT_PARAM(VTS_I4 VTS_BSTR VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4),
            logoFlag,
            logo,
            fontType, 
            fontSize,
            timeX,
            timeY,
            timeFColorR, 
            timeFColorG, 
            timeFColorB,
            FColorValue,
            timeBColorR, 
            timeBColorG,
            timeBColorB, 
            BColorValue);
    }

    //************************************
    // Method:        SetOSDUserDefInfo
    // Describe:        设置OSD字符叠加
    // FullName:      CH264CUCtrl::SetOSDUserDefInfo
    // Access:          protected 
    // Returns:        SHORT
    // Returns Describe:
    // Parameter:    SHORT channelNo        // 如果是单通道,该参数置1，多通道对应通道号 1-16
    // Parameter:    SHORT index                //字符叠加区域   如果只需要一块区域，可把此参数置0
    // Parameter:    SHORT defFlag              //字符显示使能  1 显示字符叠加；0 不显示
    // Parameter:    LPCTSTR logo               // 所要显示的叠加字符
    // Parameter:    SHORT fontType           //字体  0 宋体；1 黑体
    // Parameter:    SHORT fontSize             //字号0－2 大、中、小
    // Parameter:    SHORT logoX                //起始X坐标
    // Parameter:    SHORT logoY                //起始Y坐标
    // Parameter:    LPCTSTR color              //颜色，字符串如：255#255#255#100#255#255#255#100//前景色RGB 透明值背景色RGB透明值
    //************************************
    SHORT SetOSDUserDefInfo(SHORT channelNo, 
        SHORT index,
        SHORT defFlag, 
        LPCTSTR logo, 
        SHORT fontType,
        SHORT fontSize, 
        SHORT logoX,
        SHORT logoY,
        LPCTSTR color);
    
    //************************************
    // Method:        GetOSDUserDefInfo
    // Describe:        查询OSD字符叠加
    // FullName:      CH264CUCtrl::GetOSDUserDefInfo
    // Access:          protected 
    // Returns:        SHORT
    // Returns Describe:
    // Parameter:    SHORT channelNo        // 如果是单通道,该参数置1，多通道对应通道号 1-16
    // Parameter:    SHORT index                 //字符叠加区域   如果只需要一块区域，可把此参数置0
    //************************************
    SHORT GetOSDUserDefInfo(SHORT channelNo, SHORT index);


    //************************************
    // Method:        OSDUserDefInfo
    // Describe:        通知客户端获取OSD信息事件
    // FullName:      CH264CUCtrl::OSDUserDefInfo
    // Access:          protected 
    // Returns:        void
    // Returns Describe:
    // Parameter:    LONG logoFlag      //显示使能  1 显示字符叠加；0 不显示
    // Parameter:    LPCTSTR logo       // 所要显示的叠加字符
    // Parameter:    LONG fontType      //字体  0 宋体；1 黑体
    // Parameter:    LONG fontSize         //字号0－2 大、中、小
    // Parameter:    LONG timeX             //起始X坐标
    // Parameter:    LONG timeY             //起始Y坐标
    // Parameter:    LONG timeFColorR   //表示颜色，前景色RGB， 透明值，背景色RGB，透明值
    // Parameter:    LONG timeFColorG
    // Parameter:    LONG timeFColorB
    // Parameter:    LONG FColorValue
    // Parameter:    LONG timeBColorR
    // Parameter:    LONG timeBColorG
    // Parameter:    LONG timeBColorB
    // Parameter:    LONG BColorValue
    //************************************
    void OSDUserDefInfo(LONG logoFlag,
        LPCTSTR logo,
        LONG fontType,
        LONG fontSize, 
        LONG timeX, 
        LONG timeY,
        LONG timeFColorR,
        LONG timeFColorG, 
        LONG timeFColorB,
        LONG FColorValue,
        LONG timeBColorR, 
        LONG timeBColorG, 
        LONG timeBColorB, 
        LONG BColorValue)
    {
        FireEvent(eventidOSDUserDefInfo, 
            EVENT_PARAM(VTS_I4 VTS_BSTR VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4),
            logoFlag,
            logo, 
            fontType,
            fontSize,
            timeX,
            timeY, 
            timeFColorR, 
            timeFColorG, 
            timeFColorB, 
            FColorValue,
            timeBColorR, 
            timeBColorG, 
            timeBColorB, 
            BColorValue);
    }

    //************************************
    // Method:        SetRealTime
    // Describe:        设置延时（实时-流畅）
    // FullName:      CH264CUCtrl::SetRealTime
    // Access:          protected 
    // Returns:        SHORT
    // Returns Describe:
    // Parameter:    SHORT iRealTime        //0:实时性好即延时最小 1:实时性较好2:实时性中 3流畅性较好 4流畅性好
    //************************************
    SHORT SetRealTime(SHORT iRealTime);

    //************************************
    // Method:        GetRealTime
    // Describe:        查询延时
    // FullName:      CH264CUCtrl::GetRealTime
    // Access:          protected 
    // Returns:        SHORT        //0:实时性好 1:实时性较好 2:实时性中 3流畅性较好 4流畅性好
    // Returns Describe:        查询当前设备的延时性
    //************************************
    SHORT GetRealTime();

    //************************************
    // Method:        DownLoadPic
    // Describe:    图片抓拍, 抓拍图片的质量会根据之前设置的图片质量进行保存，如果传入的宽度和高度有一个为0，或都为0，则进行原尺寸抓拍；如果传入正常尺寸比如480*240，则按指定尺寸进行抓拍
    // FullName:      CH264CUCtrl::DownLoadPic
    // Access:          protected 
    // Returns:        SHORT        //0 表示抓拍成功，非0失败
    // Returns Describe:
    // Parameter:    LPCTSTR szPath     //这里为文件的全路径，包括文件名
    // Parameter:    SHORT nWidth       //图片的宽度
    // Parameter:    SHORT nHeight      //图片的高度
    //************************************
    SHORT DownLoadPic(LPCTSTR szPath, SHORT nWidth, SHORT nHeight);

    //************************************
    // Method:        DirectoryDlg
    // Describe:        选择文件夹路径对话框，可用于指定保存图片路径时调用该接口
    // FullName:      CH264CUCtrl::DirectoryDlg
    // Access:          protected 
    // Returns:        BSTR     //返回选择的文件夹的路径
    // Returns Describe:
    //************************************
    BSTR DirectoryDlg();

    //************************************
    // Method:        SetSystemTime
    // Describe:        同步pc时间
    // FullName:      CH264CUCtrl::SetSystemTime
    // Access:          protected 
    // Returns:        SHORT        //0 表示成功，非0失败
    // Returns Describe:
    // Parameter:    LONG year
    // Parameter:    LONG month
    // Parameter:    LONG day
    // Parameter:    LONG hour
    // Parameter:    LONG minut
    // Parameter:    LONG second
    //************************************
    SHORT SetSystemTime(LONG year, LONG month, LONG day, LONG hour, LONG minut, LONG second);


    private:
        std::shared_ptr<Camera6467_plate> m_pCamera6467;
        std::shared_ptr<uint8_t> m_pImgData;
        char m_chOverlayTemp[OVERLAY_MAX_ROW ][OVERLAY_MAX_COL];
        char m_chOverlayFinal[OVERLAY_MAX_ROW * OVERLAY_MAX_COL];
        CameraIMG m_CapImg;
         
    private:
        int GetFontSize(int SizeType);
        bool GetShowTime(int showType);
        bool GetColor(const char* colorInfo,
            int& FcolorR,
            int& FColorG,
            int& FColorB, 
            int& FColorAlpha,
            int& BcolorR,
            int& BColorG,
            int& BColorB,
            int& BColorAlpha );
        void InitializationOverlayText();
        void SetOverlayStringByRow(int iIndex, const char* overlayText);
        uint8_t* GetImgBufferAddress();
};

