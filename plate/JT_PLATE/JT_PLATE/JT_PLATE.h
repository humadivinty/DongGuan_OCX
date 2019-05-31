// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 JT_PLATE_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// JT_PLATE_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef JT_PLATE_EXPORTS
#define JT_PLATE_API  __declspec(dllexport)
#else
#define JT_PLATE_API   __declspec(dllimport)
#endif

#define DLL_DELC WINAPI

//1.1	动态库约定
//本DLL中所有函数的调用约定为stdcall调用方式。
//车牌识别厂商应提供JT_PLATE.DLL动态库，供收费系统软件开发商使用。
//消息机制说明：
//硬件触发后通过消息通知给收费软件，收费软件去获取相关的信息
//消息定义
//消息	Msg			    自定义
//消息ID定义
//消息ID以WPARAM参数传递(LPARAM = 0即可)，通过不同的ID区分不同的事件，消息ID定义如下：
//WPARAM                LPARAM
//硬触发识别后上报事件	      1				       0


EXTERN_C 
{

    //************************************
    // Method:        Plate_InitDevice
    // Describe:        初始化车牌识别仪
    // FullName:      Plate_InitDevice
    // Access:          public 
    // Returns:        JT_PLATE_API BOOL DLL_DELC
    // Returns Describe:  TRUE为初始化成功，FALSE为初始化失败
    // Parameter:    HWND hHandle  ; 接收消息的窗口的句柄
    // Parameter:    int Msg               ; 是识别数据消息号
    // Parameter:    int PorType         ; 端口类型  1：串口  ； 2：网口
    // Parameter:    char * PortName ; 为要初始化的串口号， 若是串口，则为串口号“Com1”,“Com2”等，若是网口，则为IP地址，如“192.168.1.11”
    // Parameter:    long Baudrate     ; 为串口波特率，是网口时，填0
    //************************************
    JT_PLATE_API  BOOL  DLL_DELC Plate_InitDevice(HWND hHandle, int Msg, int PorType, char *  PortName, long Baudrate);

    //************************************
    // Method:        Plate_CloseDevice
    // Describe:        关闭车牌识别仪， 关闭已经打开的车牌识别串口
    // FullName:      Plate_CloseDevice
    // Access:          public 
    // Returns:        JT_PLATE_API BOOL DLL_DELC
    // Returns Describe:  TRUE为关闭成功，FALSE为关闭失败
    //************************************
    JT_PLATE_API  BOOL  DLL_DELC Plate_CloseDevice();

    //************************************
    // Method:        Plate_Getinfo
    // Describe:        获取牌照识别结果
    // FullName:      Plate_Getinfo
    // Access:          public 
    // Returns:        JT_PLATE_API BOOL DLL_DELC
    // Returns Describe:  TRUE为识别成功，FALSE为识别失败
    // Parameter:    char * PlateInfor  ；为牌照识别结果
    // Parameter:    char * ColorInfo  ；为车牌颜色识别结果， 0:代表蓝色， 1：代表黄色， 2：代表
    //************************************
    JT_PLATE_API  BOOL  DLL_DELC Plate_Getinfo(char * PlateInfor, char * ColorInfo);

    //************************************
    // Method:        Plate_GetState
    // Describe:        获取牌照识别器状态
    // FullName:      Plate_GetState
    // Access:          public 
    // Returns:        JT_PLATE_API BOOL DLL_DELC
    // Returns Describe:           ；TRUE为获取状态成功，FALSE为获取状态失败
    // Parameter:    int * State ；0：正常，  1：故障
    //************************************
    JT_PLATE_API  BOOL  DLL_DELC Plate_GetState(int* State);

    //************************************
    // Method:        Plate_GetImage
    // Describe:        获取牌照识别图像信息， 获取牌照识别二值化图片信息
    // FullName:      Plate_GetImage
    // Access:          public 
    // Returns:        JT_PLATE_API BOOL DLL_DELC
    // Returns Describe:                     ；TRUE为获取图片成功，FALSE为获取图片失败
    // Parameter:    int ImageType     ； 0：二值化牌照图片； 1：车牌彩色小图； 2：车头彩色图片； 3: 完整的大照片（768*576），大小约20~30K
    // Parameter:    char * ImageInfo ； 为二值化图片的路径和文件名（JPG类型）
    //************************************
    JT_PLATE_API  BOOL  DLL_DELC Plate_GetImage(int ImageType, char * ImageInfo);

    //************************************
    // Method:        Plate_Capture
    // Describe:        模拟抓拍函数，调用该函数即可抓拍识别一次
    // FullName:      Plate_Capture
    // Access:          public 
    // Returns:        JT_PLATE_API BOOL DLL_DELC
    // Returns Describe: TRUE为抓拍成功，等待收到识别结果消息号就可以取识别结果了；FALSE为关闭失败
    //************************************
    JT_PLATE_API  BOOL  DLL_DELC Plate_Capture();

    //************************************
    // Method:        Plate_TakePhoto
    // Describe:        抓拍一张完整的大照片（768*576，大小约20~30K），并存到指定的路径（不需要车牌识别，不需要上报）
    // FullName:      Plate_TakePhoto
    // Access:          public 
    // Returns:        JT_PLATE_API BOOL DLL_DELC
    // Returns Describe:                       ；TRUE为保存图片成功，FALSE为保存图片失败
    // Parameter:    char * ImageInfo  ； 由调用者指定的图片的路径和文件名（JPG类型）
    //************************************
    JT_PLATE_API  BOOL  DLL_DELC Plate_TakePhoto(char * ImageInfo);

}
