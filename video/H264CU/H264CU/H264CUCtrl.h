#pragma once

// H264CUCtrl.h : CH264CUCtrl ActiveX �ؼ����������
#include "CameraModule/Camera6467_plate.h"

#define OVERLAY_MAX_ROW 7
#define OVERLAY_MAX_COL 40
// CH264CUCtrl : �й�ʵ�ֵ���Ϣ������� H264CUCtrl.cpp��

class CH264CUCtrl : public COleControl
{
	DECLARE_DYNCREATE(CH264CUCtrl)

// ���캯��
public:
	CH264CUCtrl();

// ��д
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	virtual DWORD GetControlFlags();

// ʵ��
protected:
	~CH264CUCtrl();

	DECLARE_OLECREATE_EX(CH264CUCtrl)    // �๤���� guid
	DECLARE_OLETYPELIB(CH264CUCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CH264CUCtrl)     // ����ҳ ID
	DECLARE_OLECTLTYPE(CH264CUCtrl)		// �������ƺ�����״̬

// ��Ϣӳ��
	DECLARE_MESSAGE_MAP()

// ����ӳ��
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// �¼�ӳ��
	DECLARE_EVENT_MAP()

// ���Ⱥ��¼� ID
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
    // Describe:        ��½�豸,�������ȵ��õĽӿ�
    // FullName:      CH264CUCtrl::Login
    // Access:          protected 
    // Returns:        SHORT        //   1 �û�������  2 ������� -1 ��������  0�ɹ�
    // Returns Describe:        
    // Parameter:    LPCTSTR SeverIP        //������IP
    // Parameter:    LONG ServerPort        //�������˿�
    // Parameter:    LPCTSTR LoginName  //��½����
    // Parameter:    LPCTSTR LoginPsw      //��½����
    //************************************
    SHORT Login(LPCTSTR SeverIP, LONG ServerPort, LPCTSTR LoginName, LPCTSTR LoginPsw);

    //************************************
    // Method:        Logout
    // Describe:        ע���豸
    // FullName:      CH264CUCtrl::Logout
    // Access:          protected 
    // Returns:        void
    // Returns Describe:
    //************************************
    void Logout();

    //************************************
    // Method:        OpenVideo
    // Describe:        ����Ƶ,   ��ѡ���Ӧ�Ĵ��ڣ����øýӿڿ����������Ƶ
    // FullName:      CH264CUCtrl::OpenVideo
    // Access:          protected 
    // Returns:        SHORT
    // Returns Describe:
    // Parameter:    SHORT Channel      // ����ǵ�ͨ��,�ò�����1����ͨ����Ӧͨ���� 1-16
    //************************************
    SHORT OpenVideo(SHORT Channel);

    //************************************
    // Method:        CloseVideo
    // Describe:        �ر���Ƶ,�رն�Ӧͨ����Ƶ
    // FullName:      CH264CUCtrl::CloseVideo
    // Access:          protected 
    // Returns:        void
    // Returns Describe:
    // Parameter:    SHORT Channel      // ����ǵ�ͨ��,�ò�����1����ͨ����Ӧͨ���� 1-16
    //************************************
    void CloseVideo(SHORT Channel);

    //************************************
    // Method:        SetCaptureMass
    // Describe:        ����ͼƬ����,�����豸ץ��ͼƬ����
    // FullName:      CH264CUCtrl::SetCaptureMass
    // Access:          protected 
    // Returns:        SHORT
    // Returns Describe:
    // Parameter:    SHORT channelNo        // ����ǵ�ͨ��,�ò�����1����ͨ����Ӧͨ���� 1-16
    // Parameter:    SHORT iMass                //// 0�� 1�Ϻ� 2һ�� 3�ϲ� 4��
    //************************************
    SHORT SetCaptureMass(SHORT channelNo, SHORT iMass);

    //************************************
    // Method:        GetCaptureMass
    // Describe:        ��ѯ�豸ץ��ͼƬ������
    // FullName:      CH264CUCtrl::GetCaptureMass   
    // Access:          protected 
    // Returns:        SHORT
    // Returns Describe:
    // Parameter:    SHORT channelNo    // ����ǵ�ͨ��,�ò�����1����ͨ����Ӧͨ���� 1-16
    //************************************
    SHORT GetCaptureMass(SHORT channelNo);
    

    //************************************
    // Method:        FireCaptureMass
    // Describe:
    // FullName:      CH264CUCtrl::FireCaptureMass
    // Access:          protected 
    // Returns:        void
    // Returns Describe:
    // Parameter:    SHORT iMass        : 0�� 1�Ϻ� 2һ�� 3�ϲ� 4��
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
    // Parameter:    SHORT channelNo  :����ǵ�ͨ��,�ò�����1����ͨ����Ӧͨ���� 1-16
    // Parameter:    SHORT timeFlag     :��ʾʹ��  1 ��ʾʱ�䣻0 ����ʾ
    // Parameter:    SHORT fontType     :����  0 ���壻1 ����
    // Parameter:    SHORT fontSize     :�ֺ�0��2 ���С�С
    // Parameter:    SHORT timeX        :��ʼX����
    // Parameter:    SHORT timeY        :��ʼY����
    // Parameter:    LPCTSTR color      :��ɫ���ַ����磺255#255#255#100#255#255#255#100//ǰ��ɫRGB ͸��ֵ
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
    // Describe:        ��ѯOSDʱ����Ϣ
    // FullName:      CH264CUCtrl::GetOSDTimeInfo
    // Access:          protected 
    // Returns:        SHORT
    // Returns Describe:
    // Parameter:    SHORT channelNo    :����ǵ�ͨ��,�ò�����1����ͨ����Ӧͨ���� 1-16
    //************************************
    SHORT GetOSDTimeInfo(SHORT channelNo);



    //************************************
    // Method:        OSDTimeInfo
    // Describe:        
    // FullName:      CH264CUCtrl::OSDTimeInfo
    // Access:          protected 
    // Returns:        void
    // Returns Describe:
    // Parameter:    LONG timeFlag   :��ʾ��ɫ��ǰ��ɫRGB�� ͸��ֵ������ɫRGB��͸��ֵ
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
    // Describe:        ��ɫ�Ի���
    // FullName:      CH264CUCtrl::ColorDlg
    // Access:          protected 
    // Returns:        BSTR
    // Returns Describe:  �ɹ���������ɫ�ַ���R#G#B(��C0#FF#8A)��ʧ�ܷ��ؿ�
    // Parameter:    SHORT byRed    :��
    // Parameter:    SHORT byGreen  :��
    // Parameter:    SHORT byBlue       :��
    //************************************
    BSTR ColorDlg(SHORT byRed, SHORT byGreen, SHORT byBlue);


    //************************************
    // Method:        SetOSDLogoInfo
    // Describe:        ����OSD Logo��Ϣ
    // FullName:      CH264CUCtrl::SetOSDLogoInfo
    // Access:          protected 
    // Returns:        SHORT
    // Returns Describe:
    // Parameter:    SHORT channelNo // ����ǵ�ͨ��,�ò�����1����ͨ����Ӧͨ���� 1-16
    // Parameter:    SHORT logoFlag     //��ʾʹ��  1 ��ʾlogo��0 ����ʾ
    // Parameter:    SHORT logo             // ��Ҫ��ʾ��logo��
    // Parameter:    SHORT fontType     //����  0 ���壻1 ����
    // Parameter:    SHORT fontSize     //�ֺ�0��2 ���С�С
    // Parameter:    SHORT logoX        //��ʼX����
    // Parameter:    SHORT logoY        //��ʼY����
    // Parameter:    LPCTSTR color      //��ɫ���ַ����磺255#255#255#100#255#255#255#100//ǰ��ɫRGB ͸��ֵ����ɫRGB͸��ֵ
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
    // Describe:        ��ѯOSD Logo
    // FullName:      CH264CUCtrl::GetOSDLogoInfo
    // Access:          protected 
    // Returns:        SHORT
    // Returns Describe:
    // Parameter:    SHORT channelNo         // ����ǵ�ͨ��,�ò�����1����ͨ����Ӧͨ���� 1-16
    //************************************
    SHORT GetOSDLogoInfo(SHORT channelNo);

    //************************************
    // Method:        OSDLogoInfo
    // Describe:        ֪ͨ�ͻ��˻�ȡOSD��Ϣ�¼�
    // FullName:      CH264CUCtrl::OSDLogoInfo
    // Access:          protected 
    // Returns:        void
    // Returns Describe:
    // Parameter:    LONG logoFlag      //��ʾʹ��  1 ��ʾlogo��0 ����ʾ
    // Parameter:    LPCTSTR logo       // ��Ҫ��ʾ��logo��
    // Parameter:    LONG fontType      //����  0 ���壻1 ����
    // Parameter:    LONG fontSize      //�ֺ�0��2 ���С�С
    // Parameter:    LONG timeX         //��ʼX����
    // Parameter:    LONG timeY         //��ʼY����
    // Parameter:    LONG timeFColorR   //��ʾ��ɫ��ǰ��ɫRGB�� ͸��ֵ������ɫRGB��͸��ֵ
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
    // Describe:        ����OSD�ַ�����
    // FullName:      CH264CUCtrl::SetOSDUserDefInfo
    // Access:          protected 
    // Returns:        SHORT
    // Returns Describe:
    // Parameter:    SHORT channelNo        // ����ǵ�ͨ��,�ò�����1����ͨ����Ӧͨ���� 1-16
    // Parameter:    SHORT index                //�ַ���������   ���ֻ��Ҫһ�����򣬿ɰѴ˲�����0
    // Parameter:    SHORT defFlag              //�ַ���ʾʹ��  1 ��ʾ�ַ����ӣ�0 ����ʾ
    // Parameter:    LPCTSTR logo               // ��Ҫ��ʾ�ĵ����ַ�
    // Parameter:    SHORT fontType           //����  0 ���壻1 ����
    // Parameter:    SHORT fontSize             //�ֺ�0��2 ���С�С
    // Parameter:    SHORT logoX                //��ʼX����
    // Parameter:    SHORT logoY                //��ʼY����
    // Parameter:    LPCTSTR color              //��ɫ���ַ����磺255#255#255#100#255#255#255#100//ǰ��ɫRGB ͸��ֵ����ɫRGB͸��ֵ
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
    // Describe:        ��ѯOSD�ַ�����
    // FullName:      CH264CUCtrl::GetOSDUserDefInfo
    // Access:          protected 
    // Returns:        SHORT
    // Returns Describe:
    // Parameter:    SHORT channelNo        // ����ǵ�ͨ��,�ò�����1����ͨ����Ӧͨ���� 1-16
    // Parameter:    SHORT index                 //�ַ���������   ���ֻ��Ҫһ�����򣬿ɰѴ˲�����0
    //************************************
    SHORT GetOSDUserDefInfo(SHORT channelNo, SHORT index);


    //************************************
    // Method:        OSDUserDefInfo
    // Describe:        ֪ͨ�ͻ��˻�ȡOSD��Ϣ�¼�
    // FullName:      CH264CUCtrl::OSDUserDefInfo
    // Access:          protected 
    // Returns:        void
    // Returns Describe:
    // Parameter:    LONG logoFlag      //��ʾʹ��  1 ��ʾ�ַ����ӣ�0 ����ʾ
    // Parameter:    LPCTSTR logo       // ��Ҫ��ʾ�ĵ����ַ�
    // Parameter:    LONG fontType      //����  0 ���壻1 ����
    // Parameter:    LONG fontSize         //�ֺ�0��2 ���С�С
    // Parameter:    LONG timeX             //��ʼX����
    // Parameter:    LONG timeY             //��ʼY����
    // Parameter:    LONG timeFColorR   //��ʾ��ɫ��ǰ��ɫRGB�� ͸��ֵ������ɫRGB��͸��ֵ
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
    // Describe:        ������ʱ��ʵʱ-������
    // FullName:      CH264CUCtrl::SetRealTime
    // Access:          protected 
    // Returns:        SHORT
    // Returns Describe:
    // Parameter:    SHORT iRealTime        //0:ʵʱ�Ժü���ʱ��С 1:ʵʱ�ԽϺ�2:ʵʱ���� 3�����ԽϺ� 4�����Ժ�
    //************************************
    SHORT SetRealTime(SHORT iRealTime);

    //************************************
    // Method:        GetRealTime
    // Describe:        ��ѯ��ʱ
    // FullName:      CH264CUCtrl::GetRealTime
    // Access:          protected 
    // Returns:        SHORT        //0:ʵʱ�Ժ� 1:ʵʱ�ԽϺ� 2:ʵʱ���� 3�����ԽϺ� 4�����Ժ�
    // Returns Describe:        ��ѯ��ǰ�豸����ʱ��
    //************************************
    SHORT GetRealTime();

    //************************************
    // Method:        DownLoadPic
    // Describe:    ͼƬץ��, ץ��ͼƬ�����������֮ǰ���õ�ͼƬ�������б��棬�������Ŀ�Ⱥ͸߶���һ��Ϊ0����Ϊ0�������ԭ�ߴ�ץ�ģ�������������ߴ����480*240����ָ���ߴ����ץ��
    // FullName:      CH264CUCtrl::DownLoadPic
    // Access:          protected 
    // Returns:        SHORT        //0 ��ʾץ�ĳɹ�����0ʧ��
    // Returns Describe:
    // Parameter:    LPCTSTR szPath     //����Ϊ�ļ���ȫ·���������ļ���
    // Parameter:    SHORT nWidth       //ͼƬ�Ŀ��
    // Parameter:    SHORT nHeight      //ͼƬ�ĸ߶�
    //************************************
    SHORT DownLoadPic(LPCTSTR szPath, SHORT nWidth, SHORT nHeight);

    //************************************
    // Method:        DirectoryDlg
    // Describe:        ѡ���ļ���·���Ի��򣬿�����ָ������ͼƬ·��ʱ���øýӿ�
    // FullName:      CH264CUCtrl::DirectoryDlg
    // Access:          protected 
    // Returns:        BSTR     //����ѡ����ļ��е�·��
    // Returns Describe:
    //************************************
    BSTR DirectoryDlg();

    //************************************
    // Method:        SetSystemTime
    // Describe:        ͬ��pcʱ��
    // FullName:      CH264CUCtrl::SetSystemTime
    // Access:          protected 
    // Returns:        SHORT        //0 ��ʾ�ɹ�����0ʧ��
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

