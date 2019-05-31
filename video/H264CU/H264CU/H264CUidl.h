

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


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


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __H264CUidl_h__
#define __H264CUidl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DH264CU_FWD_DEFINED__
#define ___DH264CU_FWD_DEFINED__
typedef interface _DH264CU _DH264CU;
#endif 	/* ___DH264CU_FWD_DEFINED__ */


#ifndef ___DH264CUEvents_FWD_DEFINED__
#define ___DH264CUEvents_FWD_DEFINED__
typedef interface _DH264CUEvents _DH264CUEvents;
#endif 	/* ___DH264CUEvents_FWD_DEFINED__ */


#ifndef __H264CU_FWD_DEFINED__
#define __H264CU_FWD_DEFINED__

#ifdef __cplusplus
typedef class H264CU H264CU;
#else
typedef struct H264CU H264CU;
#endif /* __cplusplus */

#endif 	/* __H264CU_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __H264CULib_LIBRARY_DEFINED__
#define __H264CULib_LIBRARY_DEFINED__

/* library H264CULib */
/* [control][version][uuid] */ 


EXTERN_C const IID LIBID_H264CULib;

#ifndef ___DH264CU_DISPINTERFACE_DEFINED__
#define ___DH264CU_DISPINTERFACE_DEFINED__

/* dispinterface _DH264CU */
/* [uuid] */ 


EXTERN_C const IID DIID__DH264CU;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("47E7AE4C-F5F0-448B-9080-052A28F58D8F")
    _DH264CU : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DH264CUVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DH264CU * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DH264CU * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DH264CU * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DH264CU * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DH264CU * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DH264CU * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DH264CU * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DH264CUVtbl;

    interface _DH264CU
    {
        CONST_VTBL struct _DH264CUVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DH264CU_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DH264CU_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DH264CU_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DH264CU_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DH264CU_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DH264CU_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DH264CU_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DH264CU_DISPINTERFACE_DEFINED__ */


#ifndef ___DH264CUEvents_DISPINTERFACE_DEFINED__
#define ___DH264CUEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DH264CUEvents */
/* [uuid] */ 


EXTERN_C const IID DIID__DH264CUEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("CDF74B1B-45E8-42C8-8C79-A8AABAD8D397")
    _DH264CUEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DH264CUEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DH264CUEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DH264CUEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DH264CUEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DH264CUEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DH264CUEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DH264CUEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DH264CUEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DH264CUEventsVtbl;

    interface _DH264CUEvents
    {
        CONST_VTBL struct _DH264CUEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DH264CUEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DH264CUEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DH264CUEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DH264CUEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DH264CUEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DH264CUEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DH264CUEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DH264CUEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_H264CU;

#ifdef __cplusplus

class DECLSPEC_UUID("0A73F9A4-C4C3-41F6-97C3-760DECCCE3A7")
H264CU;
#endif
#endif /* __H264CULib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


