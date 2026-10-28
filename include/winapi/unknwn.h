#ifndef __unknwn_h__
#define __unknwn_h__

#include "windef.h"
#include "guiddef.h"

// Forward Declarations
typedef struct IUnknown IUnknown;
typedef struct AsyncIUnknown AsyncIUnknown;
typedef struct IClassFactory IClassFactory;

//+-------------------------------------------------------------------------
//
//  Microsoft Windows
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//--------------------------------------------------------------------------

typedef IUnknown *LPUNKNOWN;

//////////////////////////////////////////////////////////////////
// IID_IUnknown and all other system IIDs are provided in UUID.LIB
// Link that library in with your proxies, clients and servers
//////////////////////////////////////////////////////////////////

typedef struct IUnknownVtbl
{
	HRESULT (*QueryInterface)(IUnknown* This, REFIID riid, void** ppvObject);
	ULONG (*AddRef)(IUnknown* This);		
	ULONG (*Release)(IUnknown* This);
} IUnknownVtbl;

struct IUnknown
{
	const IUnknownVtbl *lpVtbl;
};

#ifdef COBJMACROS
#define IUnknown_QueryInterface(This,riid,ppvObject) ((This)->lpVtbl->QueryInterface(This,riid,ppvObject))
#define IUnknown_AddRef(This) ((This)->lpVtbl->AddRef(This))
#define IUnknown_Release(This) ((This)->lpVtbl->Release(This))
#endif // COBJMACROS

HRESULT IUnknown_QueryInterface_Proxy(IUnknown* This, REFIID riid, void** ppvObject);
//void IUnknown_QueryInterface_Stub(IRpcStubBuffer* This, IRpcChannelBuffer* _pRpcChannelBuffer, PRPC_MESSAGE _pRpcMessage, DWORD* _pdwStubPhase);
ULONG IUnknown_AddRef_Proxy(IUnknown* This);
//void IUnknown_AddRef_Stub(IRpcStubBuffer* This, IRpcChannelBuffer* _pRpcChannelBuffer, PRPC_MESSAGE _pRpcMessage, DWORD* _pdwStubPhase);
ULONG IUnknown_Release_Proxy(IUnknown* This);
//void IUnknown_Release_Stub(IRpcStubBuffer* This, IRpcChannelBuffer* _pRpcChannelBuffer, PRPC_MESSAGE _pRpcMessage, DWORD*_pdwStubPhase);

typedef struct AsyncIUnknownVtbl
{
	HRESULT (*QueryInterface)(AsyncIUnknown* This, REFIID riid, void** ppvObject);
	ULONG (*AddRef)(AsyncIUnknown* This);
	ULONG (*Release)(AsyncIUnknown* This);		
	HRESULT (*Begin_QueryInterface)(AsyncIUnknown* This, REFIID riid);
	HRESULT (*Finish_QueryInterface)(AsyncIUnknown* This, void** ppvObject);
	HRESULT (*Begin_AddRef)(AsyncIUnknown* This);		
	ULONG (*Finish_AddRef)(AsyncIUnknown* This);		
	HRESULT (*Begin_Release)(AsyncIUnknown* This);		
	ULONG (*Finish_Release)(AsyncIUnknown* This);
} AsyncIUnknownVtbl;

struct AsyncIUnknown
{
	const AsyncIUnknownVtbl *lpVtbl;
};

#ifdef COBJMACROS
#define AsyncIUnknown_QueryInterface(This,riid,ppvObject) ((This)->lpVtbl->QueryInterface(This,riid,ppvObject))
#define AsyncIUnknown_AddRef(This) ((This)->lpVtbl->AddRef(This))
#define AsyncIUnknown_Release(This) ((This)->lpVtbl->Release(This))
#define AsyncIUnknown_Begin_QueryInterface(This,riid) ((This)->lpVtbl->Begin_QueryInterface(This,riid))
#define AsyncIUnknown_Finish_QueryInterface(This,ppvObject) ((This)->lpVtbl->Finish_QueryInterface(This,ppvObject))
#define AsyncIUnknown_Begin_AddRef(This) ((This)->lpVtbl->Begin_AddRef(This))
#define AsyncIUnknown_Finish_AddRef(This) ((This)->lpVtbl->Finish_AddRef(This))
#define AsyncIUnknown_Begin_Release(This) ((This)->lpVtbl->Begin_Release(This))
#define AsyncIUnknown_Finish_Release(This) ((This)->lpVtbl->Finish_Release(This))
#endif // COBJMACROS

typedef IClassFactory *LPCLASSFACTORY;

typedef struct IClassFactoryVtbl
{
	HRESULT (*QueryInterface)(IClassFactory * This, REFIID riid, void **ppvObject);		
	ULONG (*AddRef)(IClassFactory * This);		
	ULONG (*Release)(IClassFactory * This);		
	HRESULT (*CreateInstance)(IClassFactory * This, IUnknown *pUnkOuter, REFIID riid, void **ppvObject);
	HRESULT (*LockServer)(IClassFactory * This, BOOL fLock);
} IClassFactoryVtbl;

struct IClassFactory
{
	const IClassFactoryVtbl *lpVtbl;
};

#ifdef COBJMACROS
#define IClassFactory_QueryInterface(This,riid,ppvObject) ((This)->lpVtbl->QueryInterface(This,riid,ppvObject))
#define IClassFactory_AddRef(This) ((This)->lpVtbl->AddRef(This))
#define IClassFactory_Release(This) ((This)->lpVtbl->Release(This))
#define IClassFactory_CreateInstance(This,pUnkOuter,riid,ppvObject) ((This)->lpVtbl->CreateInstance(This,pUnkOuter,riid,ppvObject))
#define IClassFactory_LockServer(This,fLock) ((This)->lpVtbl->LockServer(This,fLock))
#endif // COBJMACROS

HRESULT IClassFactory_RemoteCreateInstance_Proxy(IClassFactory * This, REFIID riid, IUnknown **ppvObject);
//void IClassFactory_RemoteCreateInstance_Stub(IRpcStubBuffer *This, IRpcChannelBuffer *_pRpcChannelBuffer, PRPC_MESSAGE _pRpcMessage, DWORD *_pdwStubPhase);
HRESULT IClassFactory_RemoteLockServer_Proxy(IClassFactory * This, BOOL fLock);
//void IClassFactory_RemoteLockServer_Stub(IRpcStubBuffer *This, IRpcChannelBuffer *_pRpcChannelBuffer, PRPC_MESSAGE _pRpcMessage, DWORD *_pdwStubPhase);

HRESULT IClassFactory_CreateInstance_Proxy(IClassFactory * This, IUnknown *pUnkOuter, REFIID riid, void **ppvObject);

HRESULT IClassFactory_CreateInstance_Stub(IClassFactory * This, REFIID riid, IUnknown **ppvObject);
HRESULT IClassFactory_LockServer_Proxy(IClassFactory * This, BOOL fLock);
HRESULT IClassFactory_LockServer_Stub(IClassFactory * This, BOOL fLock);

static const IID IID_IUnknown = { 0x00000000, 0x0000, 0x0000, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46 };
static const IID IID_AsyncIUnknown = {};
static const IID IID_IClassFactory = {};

#endif // __unknwn_h__
