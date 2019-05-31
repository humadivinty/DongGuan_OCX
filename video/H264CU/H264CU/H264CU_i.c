

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Fri Nov 23 13:56:36 2018
 */
/* Compiler settings for H264CU.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, LIBID_H264CULib,0x984B8CA7,0xC64A,0x4163,0xBB,0x32,0x04,0x4B,0x7B,0x20,0xC1,0xFA);


MIDL_DEFINE_GUID(IID, DIID__DH264CU,0x47E7AE4C,0xF5F0,0x448B,0x90,0x80,0x05,0x2A,0x28,0xF5,0x8D,0x8F);


MIDL_DEFINE_GUID(IID, DIID__DH264CUEvents,0xCDF74B1B,0x45E8,0x42C8,0x8C,0x79,0xA8,0xAA,0xBA,0xD8,0xD3,0x97);


MIDL_DEFINE_GUID(CLSID, CLSID_H264CU,0x0A73F9A4,0xC4C3,0x41F6,0x97,0xC3,0x76,0x0D,0xEC,0xCC,0xE3,0xA7);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



