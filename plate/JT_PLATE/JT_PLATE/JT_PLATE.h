// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� JT_PLATE_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// JT_PLATE_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef JT_PLATE_EXPORTS
#define JT_PLATE_API  __declspec(dllexport)
#else
#define JT_PLATE_API   __declspec(dllimport)
#endif

#define DLL_DELC WINAPI

//1.1	��̬��Լ��
//��DLL�����к����ĵ���Լ��Ϊstdcall���÷�ʽ��
//����ʶ����Ӧ�ṩJT_PLATE.DLL��̬�⣬���շ�ϵͳ���������ʹ�á�
//��Ϣ����˵����
//Ӳ��������ͨ����Ϣ֪ͨ���շ�������շ����ȥ��ȡ��ص���Ϣ
//��Ϣ����
//��Ϣ	Msg			    �Զ���
//��ϢID����
//��ϢID��WPARAM��������(LPARAM = 0����)��ͨ����ͬ��ID���ֲ�ͬ���¼�����ϢID�������£�
//WPARAM                LPARAM
//Ӳ����ʶ����ϱ��¼�	      1				       0


EXTERN_C 
{

    //************************************
    // Method:        Plate_InitDevice
    // Describe:        ��ʼ������ʶ����
    // FullName:      Plate_InitDevice
    // Access:          public 
    // Returns:        JT_PLATE_API BOOL DLL_DELC
    // Returns Describe:  TRUEΪ��ʼ���ɹ���FALSEΪ��ʼ��ʧ��
    // Parameter:    HWND hHandle  ; ������Ϣ�Ĵ��ڵľ��
    // Parameter:    int Msg               ; ��ʶ��������Ϣ��
    // Parameter:    int PorType         ; �˿�����  1������  �� 2������
    // Parameter:    char * PortName ; ΪҪ��ʼ���Ĵ��ںţ� ���Ǵ��ڣ���Ϊ���ںš�Com1��,��Com2���ȣ��������ڣ���ΪIP��ַ���硰192.168.1.11��
    // Parameter:    long Baudrate     ; Ϊ���ڲ����ʣ�������ʱ����0
    //************************************
    JT_PLATE_API  BOOL  DLL_DELC Plate_InitDevice(HWND hHandle, int Msg, int PorType, char *  PortName, long Baudrate);

    //************************************
    // Method:        Plate_CloseDevice
    // Describe:        �رճ���ʶ���ǣ� �ر��Ѿ��򿪵ĳ���ʶ�𴮿�
    // FullName:      Plate_CloseDevice
    // Access:          public 
    // Returns:        JT_PLATE_API BOOL DLL_DELC
    // Returns Describe:  TRUEΪ�رճɹ���FALSEΪ�ر�ʧ��
    //************************************
    JT_PLATE_API  BOOL  DLL_DELC Plate_CloseDevice();

    //************************************
    // Method:        Plate_Getinfo
    // Describe:        ��ȡ����ʶ����
    // FullName:      Plate_Getinfo
    // Access:          public 
    // Returns:        JT_PLATE_API BOOL DLL_DELC
    // Returns Describe:  TRUEΪʶ��ɹ���FALSEΪʶ��ʧ��
    // Parameter:    char * PlateInfor  ��Ϊ����ʶ����
    // Parameter:    char * ColorInfo  ��Ϊ������ɫʶ������ 0:������ɫ�� 1�������ɫ�� 2������
    //************************************
    JT_PLATE_API  BOOL  DLL_DELC Plate_Getinfo(char * PlateInfor, char * ColorInfo);

    //************************************
    // Method:        Plate_GetState
    // Describe:        ��ȡ����ʶ����״̬
    // FullName:      Plate_GetState
    // Access:          public 
    // Returns:        JT_PLATE_API BOOL DLL_DELC
    // Returns Describe:           ��TRUEΪ��ȡ״̬�ɹ���FALSEΪ��ȡ״̬ʧ��
    // Parameter:    int * State ��0��������  1������
    //************************************
    JT_PLATE_API  BOOL  DLL_DELC Plate_GetState(int* State);

    //************************************
    // Method:        Plate_GetImage
    // Describe:        ��ȡ����ʶ��ͼ����Ϣ�� ��ȡ����ʶ���ֵ��ͼƬ��Ϣ
    // FullName:      Plate_GetImage
    // Access:          public 
    // Returns:        JT_PLATE_API BOOL DLL_DELC
    // Returns Describe:                     ��TRUEΪ��ȡͼƬ�ɹ���FALSEΪ��ȡͼƬʧ��
    // Parameter:    int ImageType     �� 0����ֵ������ͼƬ�� 1�����Ʋ�ɫСͼ�� 2����ͷ��ɫͼƬ�� 3: �����Ĵ���Ƭ��768*576������СԼ20~30K
    // Parameter:    char * ImageInfo �� Ϊ��ֵ��ͼƬ��·�����ļ�����JPG���ͣ�
    //************************************
    JT_PLATE_API  BOOL  DLL_DELC Plate_GetImage(int ImageType, char * ImageInfo);

    //************************************
    // Method:        Plate_Capture
    // Describe:        ģ��ץ�ĺ��������øú�������ץ��ʶ��һ��
    // FullName:      Plate_Capture
    // Access:          public 
    // Returns:        JT_PLATE_API BOOL DLL_DELC
    // Returns Describe: TRUEΪץ�ĳɹ����ȴ��յ�ʶ������Ϣ�žͿ���ȡʶ�����ˣ�FALSEΪ�ر�ʧ��
    //************************************
    JT_PLATE_API  BOOL  DLL_DELC Plate_Capture();

    //************************************
    // Method:        Plate_TakePhoto
    // Describe:        ץ��һ�������Ĵ���Ƭ��768*576����СԼ20~30K�������浽ָ����·��������Ҫ����ʶ�𣬲���Ҫ�ϱ���
    // FullName:      Plate_TakePhoto
    // Access:          public 
    // Returns:        JT_PLATE_API BOOL DLL_DELC
    // Returns Describe:                       ��TRUEΪ����ͼƬ�ɹ���FALSEΪ����ͼƬʧ��
    // Parameter:    char * ImageInfo  �� �ɵ�����ָ����ͼƬ��·�����ļ�����JPG���ͣ�
    //************************************
    JT_PLATE_API  BOOL  DLL_DELC Plate_TakePhoto(char * ImageInfo);

}
