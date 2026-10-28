/*-------------------------------------------------------------------------------------
 *
 * Copyright (c) Microsoft Corporation
 * Licensed under the MIT license
 *
 *-------------------------------------------------------------------------------------*/
#ifndef __dxgi_h__
#define __dxgi_h__

#include "guiddef.h"
#include "unknwn.h"

// Forward declarations
typedef struct IDXGIObject IDXGIObject;
typedef struct IDXGIDeviceSubObject IDXGIDeviceSubObject;
typedef struct IDXGIResource IDXGIResource;
typedef struct IDXGIKeyedMutex IDXGIKeyedMutex;
typedef struct IDXGISurface IDXGISurface;
typedef struct IDXGISurface1 IDXGISurface1;
typedef struct IDXGIAdapter IDXGIAdapter;
typedef struct IDXGIOutput IDXGIOutput;
typedef struct IDXGISwapChain IDXGISwapChain;
typedef struct IDXGIFactory IDXGIFactory;
typedef struct IDXGIDevice IDXGIDevice;
typedef struct IDXGIFactory1 IDXGIFactory1;
typedef struct IDXGIAdapter1 IDXGIAdapter1;
typedef struct IDXGIDevice1 IDXGIDevice1;

/* header files for imported files */
#include "dxgicommon.h"
#include "dxgitype.h"

#define DXGI_CPU_ACCESS_NONE                (0)
#define DXGI_CPU_ACCESS_DYNAMIC             (1)
#define DXGI_CPU_ACCESS_READ_WRITE          (2)
#define DXGI_CPU_ACCESS_SCRATCH             (3)
#define DXGI_CPU_ACCESS_FIELD               15
#define DXGI_USAGE_SHADER_INPUT             0x00000010UL
#define DXGI_USAGE_RENDER_TARGET_OUTPUT     0x00000020UL
#define DXGI_USAGE_BACK_BUFFER              0x00000040UL
#define DXGI_USAGE_SHARED                   0x00000080UL
#define DXGI_USAGE_READ_ONLY                0x00000100UL
#define DXGI_USAGE_DISCARD_ON_PRESENT       0x00000200UL
#define DXGI_USAGE_UNORDERED_ACCESS         0x00000400UL
   
typedef UINT DXGI_USAGE;

typedef struct DXGI_FRAME_STATISTICS
{
	UINT PresentCount;
	UINT PresentRefreshCount;
	UINT SyncRefreshCount;
	LARGE_INTEGER SyncQPCTime;
	LARGE_INTEGER SyncGPUTime;
} DXGI_FRAME_STATISTICS;

typedef struct DXGI_MAPPED_RECT
{
	INT Pitch;
	BYTE* pBits;
} DXGI_MAPPED_RECT;

typedef struct DXGI_ADAPTER_DESC
{
	WCHAR Description[128];
	UINT VendorId;
	UINT DeviceId;
	UINT SubSysId;
	UINT Revision;
	SIZE_T DedicatedVideoMemory;
	SIZE_T DedicatedSystemMemory;
	SIZE_T SharedSystemMemory;
	LUID AdapterLuid;
} DXGI_ADAPTER_DESC;

#if !defined(HMONITOR_DECLARED) && !defined(HMONITOR) && (!defined(WINVER) || WINVER < 0x0500)
#define HMONITOR_DECLARED
DECLARE_HANDLE(HMONITOR);
#endif

typedef struct DXGI_OUTPUT_DESC
{
	WCHAR DeviceName[32];
	RECT DesktopCoordinates;
	BOOL AttachedToDesktop;
	DXGI_MODE_ROTATION Rotation;
	HMONITOR Monitor;
} DXGI_OUTPUT_DESC;

typedef struct DXGI_SHARED_RESOURCE
{
	HANDLE Handle;
} DXGI_SHARED_RESOURCE;

#define	DXGI_RESOURCE_PRIORITY_MINIMUM	( 0x28000000 )
#define	DXGI_RESOURCE_PRIORITY_LOW	( 0x50000000 )
#define	DXGI_RESOURCE_PRIORITY_NORMAL	( 0x78000000 )
#define	DXGI_RESOURCE_PRIORITY_HIGH	( 0xa0000000 )
#define	DXGI_RESOURCE_PRIORITY_MAXIMUM	( 0xc8000000 )

typedef enum DXGI_RESIDENCY
{
	DXGI_RESIDENCY_FULLY_RESIDENT = 1,
	DXGI_RESIDENCY_RESIDENT_IN_SHARED_MEMORY = 2,
	DXGI_RESIDENCY_EVICTED_TO_DISK = 3
} DXGI_RESIDENCY;

typedef struct DXGI_SURFACE_DESC
{
	UINT Width;
	UINT Height;
	DXGI_FORMAT Format;
	DXGI_SAMPLE_DESC SampleDesc;
} DXGI_SURFACE_DESC;

typedef enum DXGI_SWAP_EFFECT
{
	DXGI_SWAP_EFFECT_DISCARD = 0,
	DXGI_SWAP_EFFECT_SEQUENTIAL = 1,
	DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL = 3,
	DXGI_SWAP_EFFECT_FLIP_DISCARD = 4
} DXGI_SWAP_EFFECT;

typedef enum DXGI_SWAP_CHAIN_FLAG
{
	DXGI_SWAP_CHAIN_FLAG_NONPREROTATED = 1,
	DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH = 2,
	DXGI_SWAP_CHAIN_FLAG_GDI_COMPATIBLE = 4,
	DXGI_SWAP_CHAIN_FLAG_RESTRICTED_CONTENT = 8,
	DXGI_SWAP_CHAIN_FLAG_RESTRICT_SHARED_RESOURCE_DRIVER = 16,
	DXGI_SWAP_CHAIN_FLAG_DISPLAY_ONLY = 32,
	DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT = 64,
	DXGI_SWAP_CHAIN_FLAG_FOREGROUND_LAYER = 128,
	DXGI_SWAP_CHAIN_FLAG_FULLSCREEN_VIDEO = 256,
	DXGI_SWAP_CHAIN_FLAG_YUV_VIDEO = 512,
	DXGI_SWAP_CHAIN_FLAG_HW_PROTECTED = 1024,
	DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING = 2048,
	DXGI_SWAP_CHAIN_FLAG_RESTRICTED_TO_ALL_HOLOGRAPHIC_DISPLAYS = 4096
} DXGI_SWAP_CHAIN_FLAG;

typedef struct DXGI_SWAP_CHAIN_DESC
{
	DXGI_MODE_DESC BufferDesc;
	DXGI_SAMPLE_DESC SampleDesc;
	DXGI_USAGE BufferUsage;
	UINT BufferCount;
	HWND OutputWindow;
	BOOL Windowed;
	DXGI_SWAP_EFFECT SwapEffect;
	UINT Flags;
} DXGI_SWAP_CHAIN_DESC;

typedef struct IDXGIObjectVtbl
{
	HRESULT (*Querystruct)(IDXGIObject* This, REFIID riid, void** ppvObject);
	ULONG (*AddRef)(IDXGIObject* This);
	ULONG (*Release)(IDXGIObject* This);
	HRESULT (*SetPrivateData)(IDXGIObject* This, REFGUID Name, UINT DataSize, const void* pData);
	HRESULT (*SetPrivateDatastruct)(IDXGIObject* This, REFGUID Name, const IUnknown* pUnknown);
	HRESULT (*GetPrivateData)(IDXGIObject* This, REFGUID Name, UINT* pDataSize, void* pData);
	HRESULT (*GetParent)(IDXGIObject* This, REFIID riid, void** ppParent);
} IDXGIObjectVtbl;

struct IDXGIObject
{
	const IDXGIObjectVtbl* lpVtbl;
};

#ifdef COBJMACROS
#define IDXGIObject_Querystruct(This,riid,ppvObject) ((This)->lpVtbl->Querystruct(This,riid,ppvObject))
#define IDXGIObject_AddRef(This) ((This)->lpVtbl->AddRef(This))
#define IDXGIObject_Release(This) ((This)->lpVtbl->Release(This))
#define IDXGIObject_SetPrivateData(This,Name,DataSize,pData) ((This)->lpVtbl->SetPrivateData(This,Name,DataSize,pData))
#define IDXGIObject_SetPrivateDatastruct(This,Name,pUnknown) ((This)->lpVtbl->SetPrivateDatastruct(This,Name,pUnknown))
#define IDXGIObject_GetPrivateData(This,Name,pDataSize,pData) ((This)->lpVtbl->GetPrivateData(This,Name,pDataSize,pData))
#define IDXGIObject_GetParent(This,riid,ppParent) ((This)->lpVtbl->GetParent(This,riid,ppParent))
#endif // COBJMACROS

typedef struct IDXGIDeviceSubObjectVtbl
{
	HRESULT(*Querystruct)(IDXGIDeviceSubObject* This, REFIID riid, void** ppvObject);
	ULONG(*AddRef)(IDXGIDeviceSubObject* This);
	ULONG(*Release)(IDXGIDeviceSubObject* This);
	HRESULT(*SetPrivateData)(IDXGIDeviceSubObject* This, REFGUID Name, UINT DataSize, const void* pData);
	HRESULT(*SetPrivateDatastruct)(IDXGIDeviceSubObject* This, REFGUID Name, const IUnknown* pUnknown);
	HRESULT(*GetPrivateData)(IDXGIDeviceSubObject* This, REFGUID Name, UINT* pDataSize, void* pData);
	HRESULT(*GetParent)(IDXGIDeviceSubObject* This, REFIID riid, void** ppParent);
	HRESULT(*GetDevice)(IDXGIDeviceSubObject* This, REFIID riid, void** ppDevice);
} IDXGIDeviceSubObjectVtbl;

struct IDXGIDeviceSubObject
{
	const IDXGIDeviceSubObjectVtbl* lpVtbl;
};

#ifdef COBJMACROS
#define IDXGIDeviceSubObject_Querystruct(This,riid,ppvObject) ((This)->lpVtbl->Querystruct(This,riid,ppvObject))
#define IDXGIDeviceSubObject_AddRef(This) ((This)->lpVtbl->AddRef(This))
#define IDXGIDeviceSubObject_Release(This) ((This)->lpVtbl->Release(This))
#define IDXGIDeviceSubObject_SetPrivateData(This,Name,DataSize,pData) ((This)->lpVtbl->SetPrivateData(This,Name,DataSize,pData))
#define IDXGIDeviceSubObject_SetPrivateDatastruct(This,Name,pUnknown) ((This)->lpVtbl->SetPrivateDatastruct(This,Name,pUnknown))
#define IDXGIDeviceSubObject_GetPrivateData(This,Name,pDataSize,pData) ((This)->lpVtbl->GetPrivateData(This,Name,pDataSize,pData))
#define IDXGIDeviceSubObject_GetParent(This,riid,ppParent) ((This)->lpVtbl->GetParent(This,riid,ppParent))
#define IDXGIDeviceSubObject_GetDevice(This,riid,ppDevice) ((This)->lpVtbl->GetDevice(This,riid,ppDevice))
#endif // COBJMACROS

typedef struct IDXGIResourceVtbl
{
	HRESULT(*Querystruct)(IDXGIResource* This, REFIID riid, void** ppvObject);
	ULONG(*AddRef)(IDXGIResource* This);
	ULONG(*Release)(IDXGIResource* This);
	HRESULT(*SetPrivateData)(IDXGIResource* This, REFGUID Name, UINT DataSize, const void* pData);
	HRESULT(*SetPrivateDatastruct)(IDXGIResource* This, REFGUID Name, const IUnknown* pUnknown);
	HRESULT(*GetPrivateData)(IDXGIResource* This, REFGUID Name, UINT* pDataSize, void* pData);
	HRESULT(*GetParent)(IDXGIResource* This, REFIID riid, void** ppParent);
	HRESULT(*GetDevice)(IDXGIResource* This, REFIID riid, void** ppDevice);
	HRESULT(*GetSharedHandle)(IDXGIResource* This, HANDLE* pSharedHandle);
	HRESULT(*GetUsage)(IDXGIResource* This, DXGI_USAGE* pUsage);
	HRESULT(*SetEvictionPriority)(IDXGIResource* This, UINT EvictionPriority);
	HRESULT(*GetEvictionPriority)(IDXGIResource* This, UINT* pEvictionPriority);
} IDXGIResourceVtbl;

struct IDXGIResource
{
	const IDXGIResourceVtbl* lpVtbl;
};

#ifdef COBJMACROS
#define IDXGIResource_Querystruct(This,riid,ppvObject) ((This)->lpVtbl->Querystruct(This,riid,ppvObject))
#define IDXGIResource_AddRef(This) ((This)->lpVtbl->AddRef(This))
#define IDXGIResource_Release(This) ((This)->lpVtbl->Release(This))
#define IDXGIResource_SetPrivateData(This,Name,DataSize,pData) ((This)->lpVtbl->SetPrivateData(This,Name,DataSize,pData))
#define IDXGIResource_SetPrivateDatastruct(This,Name,pUnknown) ((This)->lpVtbl->SetPrivateDatastruct(This,Name,pUnknown))
#define IDXGIResource_GetPrivateData(This,Name,pDataSize,pData) ((This)->lpVtbl->GetPrivateData(This,Name,pDataSize,pData))
#define IDXGIResource_GetParent(This,riid,ppParent) ((This)->lpVtbl->GetParent(This,riid,ppParent))
#define IDXGIResource_GetDevice(This,riid,ppDevice) ((This)->lpVtbl->GetDevice(This,riid,ppDevice))
#define IDXGIResource_GetSharedHandle(This,pSharedHandle) ((This)->lpVtbl->GetSharedHandle(This,pSharedHandle))
#define IDXGIResource_GetUsage(This,pUsage) ((This)->lpVtbl->GetUsage(This,pUsage))
#define IDXGIResource_SetEvictionPriority(This,EvictionPriority) ((This)->lpVtbl->SetEvictionPriority(This,EvictionPriority))
#define IDXGIResource_GetEvictionPriority(This,pEvictionPriority) ((This)->lpVtbl->GetEvictionPriority(This,pEvictionPriority))
#endif // COBJMACROS

typedef struct IDXGIKeyedMutexVtbl
{
	HRESULT(*Querystruct)(IDXGIKeyedMutex* This, REFIID riid, void** ppvObject);
	ULONG(*AddRef)(IDXGIKeyedMutex* This);
	ULONG(*Release)(IDXGIKeyedMutex* This);
	HRESULT(*SetPrivateData)(IDXGIKeyedMutex* This, REFGUID Name, UINT DataSize, const void* pData);
	HRESULT(*SetPrivateDatastruct)(IDXGIKeyedMutex* This, REFGUID Name, const IUnknown* pUnknown);
	HRESULT(*GetPrivateData)(IDXGIKeyedMutex* This, REFGUID Name, UINT* pDataSize, void* pData);
	HRESULT(*GetParent)(IDXGIKeyedMutex* This, REFIID riid, void** ppParent);
	HRESULT(*GetDevice)(IDXGIKeyedMutex* This, REFIID riid, void** ppDevice);
	HRESULT(*AcquireSync)(IDXGIKeyedMutex* This, UINT64 Key, DWORD dwMilliseconds);
	HRESULT(*ReleaseSync)(IDXGIKeyedMutex* This, UINT64 Key);
} IDXGIKeyedMutexVtbl;

struct IDXGIKeyedMutex
{
	const IDXGIKeyedMutexVtbl* lpVtbl;
};

#ifdef COBJMACROS
#define IDXGIKeyedMutex_Querystruct(This,riid,ppvObject) ((This)->lpVtbl->Querystruct(This,riid,ppvObject))
#define IDXGIKeyedMutex_AddRef(This) ((This)->lpVtbl->AddRef(This))
#define IDXGIKeyedMutex_Release(This) ((This)->lpVtbl->Release(This))
#define IDXGIKeyedMutex_SetPrivateData(This,Name,DataSize,pData) ((This)->lpVtbl->SetPrivateData(This,Name,DataSize,pData))
#define IDXGIKeyedMutex_SetPrivateDatastruct(This,Name,pUnknown) ((This)->lpVtbl->SetPrivateDatastruct(This,Name,pUnknown))
#define IDXGIKeyedMutex_GetPrivateData(This,Name,pDataSize,pData) ((This)->lpVtbl->GetPrivateData(This,Name,pDataSize,pData))
#define IDXGIKeyedMutex_GetParent(This,riid,ppParent) ((This)->lpVtbl->GetParent(This,riid,ppParent))
#define IDXGIKeyedMutex_GetDevice(This,riid,ppDevice) ((This)->lpVtbl->GetDevice(This,riid,ppDevice))
#define IDXGIKeyedMutex_AcquireSync(This,Key,dwMilliseconds) ((This)->lpVtbl->AcquireSync(This,Key,dwMilliseconds))
#define IDXGIKeyedMutex_ReleaseSync(This,Key) ((This)->lpVtbl->ReleaseSync(This,Key))
#endif // COBJMACROS

#define	DXGI_MAP_READ	( 1UL )
#define	DXGI_MAP_WRITE	( 2UL )
#define	DXGI_MAP_DISCARD	( 4UL )

typedef struct IDXGISurfaceVtbl
{
	HRESULT (*Querystruct)(IDXGISurface* This, REFIID riid, void** ppvObject);
	ULONG (*AddRef)(IDXGISurface* This);
	ULONG (*Release)(IDXGISurface* This);
	HRESULT (*SetPrivateData)(IDXGISurface* This, REFGUID Name, UINT DataSize, const void* pData);
	HRESULT (*SetPrivateDatastruct)(IDXGISurface* This, REFGUID Name, const IUnknown* pUnknown);
	HRESULT (*GetPrivateData)(IDXGISurface* This, REFGUID Name, UINT* pDataSize, void* pData);
	HRESULT (*GetParent)(IDXGISurface* This, REFIID riid, void** ppParent);
	HRESULT (*GetDevice)(IDXGISurface* This, REFIID riid, void** ppDevice);
	HRESULT (*GetDesc)(IDXGISurface* This, DXGI_SURFACE_DESC* pDesc);
	HRESULT (*Map)(IDXGISurface* This, DXGI_MAPPED_RECT* pLockedRect, UINT MapFlags);
	HRESULT (*Unmap)(IDXGISurface* This);
} IDXGISurfaceVtbl;

struct IDXGISurface
{
	const IDXGISurfaceVtbl* lpVtbl;
};

#ifdef COBJMACROS
#define IDXGISurface_Querystruct(This,riid,ppvObject) ((This)->lpVtbl->Querystruct(This,riid,ppvObject))
#define IDXGISurface_AddRef(This) ((This)->lpVtbl->AddRef(This))
#define IDXGISurface_Release(This) ((This)->lpVtbl->Release(This))
#define IDXGISurface_SetPrivateData(This,Name,DataSize,pData) ((This)->lpVtbl->SetPrivateData(This,Name,DataSize,pData))
#define IDXGISurface_SetPrivateDatastruct(This,Name,pUnknown) ((This)->lpVtbl->SetPrivateDatastruct(This,Name,pUnknown))
#define IDXGISurface_GetPrivateData(This,Name,pDataSize,pData) ((This)->lpVtbl->GetPrivateData(This,Name,pDataSize,pData))
#define IDXGISurface_GetParent(This,riid,ppParent) ((This)->lpVtbl->GetParent(This,riid,ppParent))
#define IDXGISurface_GetDevice(This,riid,ppDevice) ((This)->lpVtbl->GetDevice(This,riid,ppDevice))
#define IDXGISurface_GetDesc(This,pDesc) ((This)->lpVtbl->GetDesc(This,pDesc))
#define IDXGISurface_Map(This,pLockedRect,MapFlags) ((This)->lpVtbl->Map(This,pLockedRect,MapFlags))
#define IDXGISurface_Unmap(This) ((This)->lpVtbl->Unmap(This))
#endif // COBJMACROS

typedef struct IDXGISurface1Vtbl
{
	HRESULT (*Querystruct)(IDXGISurface1* This, REFIID riid, void** ppvObject);
	ULONG (*AddRef)(IDXGISurface1* This);
	ULONG (*Release)(IDXGISurface1* This);
	HRESULT (*SetPrivateData)(IDXGISurface1* This, REFGUID Name, UINT DataSize, const void* pData);
	HRESULT (*SetPrivateDatastruct)(IDXGISurface1* This, REFGUID Name, const IUnknown* pUnknown);
	HRESULT (*GetPrivateData)(IDXGISurface1* This, REFGUID Name, UINT* pDataSize, void* pData);
	HRESULT (*GetParent)(IDXGISurface1* This, REFIID riid, void** ppParent);
	HRESULT (*GetDevice)(IDXGISurface1* This, REFIID riid, void** ppDevice);
	HRESULT (*GetDesc)(IDXGISurface1* This, DXGI_SURFACE_DESC* pDesc);
	HRESULT (*Map)(IDXGISurface1* This, DXGI_MAPPED_RECT* pLockedRect, UINT MapFlags);
	HRESULT (*Unmap)(IDXGISurface1* This);
	HRESULT (*GetDC)(IDXGISurface1* This, BOOL Discard, HDC* phdc);
	HRESULT (*ReleaseDC)(IDXGISurface1* This, RECT* pDirtyRect);
} IDXGISurface1Vtbl;

struct IDXGISurface1
{
	const IDXGISurface1Vtbl* lpVtbl;
};

#ifdef COBJMACROS
#define IDXGISurface1_Querystruct(This,riid,ppvObject) ((This)->lpVtbl->Querystruct(This,riid,ppvObject))
#define IDXGISurface1_AddRef(This) ((This)->lpVtbl->AddRef(This))
#define IDXGISurface1_Release(This) ((This)->lpVtbl->Release(This))
#define IDXGISurface1_SetPrivateData(This,Name,DataSize,pData) ((This)->lpVtbl->SetPrivateData(This,Name,DataSize,pData))
#define IDXGISurface1_SetPrivateDatastruct(This,Name,pUnknown) ((This)->lpVtbl->SetPrivateDatastruct(This,Name,pUnknown))
#define IDXGISurface1_GetPrivateData(This,Name,pDataSize,pData) ((This)->lpVtbl->GetPrivateData(This,Name,pDataSize,pData))
#define IDXGISurface1_GetParent(This,riid,ppParent) ((This)->lpVtbl->GetParent(This,riid,ppParent))
#define IDXGISurface1_GetDevice(This,riid,ppDevice) ((This)->lpVtbl->GetDevice(This,riid,ppDevice))
#define IDXGISurface1_GetDesc(This,pDesc) ((This)->lpVtbl->GetDesc(This,pDesc))
#define IDXGISurface1_Map(This,pLockedRect,MapFlags) ((This)->lpVtbl->Map(This,pLockedRect,MapFlags))
#define IDXGISurface1_Unmap(This) ((This)->lpVtbl->Unmap(This))
#define IDXGISurface1_GetDC(This,Discard,phdc) ((This)->lpVtbl->GetDC(This,Discard,phdc))
#define IDXGISurface1_ReleaseDC(This,pDirtyRect) ((This)->lpVtbl->ReleaseDC(This,pDirtyRect))
#endif // COBJMACROS

typedef struct IDXGIAdapterVtbl
{
	HRESULT (*Querystruct)(IDXGIAdapter* This, REFIID riid, void** ppvObject);
	ULONG (*AddRef)(IDXGIAdapter* This);
	ULONG (*Release)(IDXGIAdapter* This);
	HRESULT (*SetPrivateData)(IDXGIAdapter* This, REFGUID Name, UINT DataSize, const void* pData);
	HRESULT (*SetPrivateDatastruct)(IDXGIAdapter* This, REFGUID Name, const IUnknown* pUnknown);
	HRESULT (*GetPrivateData)(IDXGIAdapter* This, REFGUID Name, UINT* pDataSize, void* pData);
	HRESULT (*GetParent)(IDXGIAdapter* This, REFIID riid, void** ppParent);
	HRESULT (*EnumOutputs)(IDXGIAdapter* This, UINT Output, IDXGIOutput** ppOutput);
	HRESULT (*GetDesc)( IDXGIAdapter* This, DXGI_ADAPTER_DESC* pDesc);
	HRESULT (*CheckstructSupport)(IDXGIAdapter* This, REFGUID structName, LARGE_INTEGER* pUMDVersion);
} IDXGIAdapterVtbl;

struct IDXGIAdapter
{
	const IDXGIAdapterVtbl* lpVtbl;
};

#ifdef COBJMACROS
#define IDXGIAdapter_Querystruct(This,riid,ppvObject) ((This)->lpVtbl->Querystruct(This,riid,ppvObject))
#define IDXGIAdapter_AddRef(This) ((This)->lpVtbl->AddRef(This))
#define IDXGIAdapter_Release(This) ((This)->lpVtbl->Release(This))
#define IDXGIAdapter_SetPrivateData(This,Name,DataSize,pData) ((This)->lpVtbl->SetPrivateData(This,Name,DataSize,pData))
#define IDXGIAdapter_SetPrivateDatastruct(This,Name,pUnknown) ((This)->lpVtbl->SetPrivateDatastruct(This,Name,pUnknown))
#define IDXGIAdapter_GetPrivateData(This,Name,pDataSize,pData) ((This)->lpVtbl->GetPrivateData(This,Name,pDataSize,pData))
#define IDXGIAdapter_GetParent(This,riid,ppParent) ((This)->lpVtbl->GetParent(This,riid,ppParent))
#define IDXGIAdapter_EnumOutputs(This,Output,ppOutput) ((This)->lpVtbl->EnumOutputs(This,Output,ppOutput))
#define IDXGIAdapter_GetDesc(This,pDesc) ((This)->lpVtbl->GetDesc(This,pDesc))
#define IDXGIAdapter_CheckstructSupport(This,structName,pUMDVersion) ((This)->lpVtbl->CheckstructSupport(This,structName,pUMDVersion))
#endif // COBJMACROS

#define	DXGI_ENUM_MODES_INTERLACED	( 1UL )
#define	DXGI_ENUM_MODES_SCALING	( 2UL )

typedef struct IDXGIOutputVtbl
{
	HRESULT (*Querystruct)(IDXGIOutput* This, REFIID riid, void** ppvObject);
	ULONG (*AddRef)(IDXGIOutput* This);
	ULONG (*Release)(IDXGIOutput* This);
	HRESULT (*SetPrivateData)(IDXGIOutput* This, REFGUID Name, UINT DataSize, const void* pData);
	HRESULT (*SetPrivateDatastruct)(IDXGIOutput* This, REFGUID Name, const IUnknown* pUnknown);
	HRESULT (*GetPrivateData)(IDXGIOutput* This, REFGUID Name, UINT* pDataSize, void* pData);
	HRESULT (*GetParent)(IDXGIOutput* This, REFIID riid, void** ppParent);
	HRESULT (*GetDesc)(IDXGIOutput* This, DXGI_OUTPUT_DESC* pDesc);
	HRESULT (*GetDisplayModeList)(IDXGIOutput* This, DXGI_FORMAT EnumFormat, UINT Flags, UINT* pNumModes, DXGI_MODE_DESC* pDesc);
	HRESULT (*FindClosestMatchingMode)(IDXGIOutput* This, const DXGI_MODE_DESC* pModeToMatch, DXGI_MODE_DESC* pClosestMatch, IUnknown* pConcernedDevice);
	HRESULT (*WaitForVBlank)(IDXGIOutput* This);
	HRESULT (*TakeOwnership)(IDXGIOutput* This, IUnknown* pDevice, BOOL Exclusive);
	void (*ReleaseOwnership)(IDXGIOutput* This);
	HRESULT (*GetGammaControlCapabilities)(IDXGIOutput* This, DXGI_GAMMA_CONTROL_CAPABILITIES* pGammaCaps);
	HRESULT (*SetGammaControl)(IDXGIOutput* This, const DXGI_GAMMA_CONTROL* pArray);
	HRESULT (*GetGammaControl)(IDXGIOutput* This, DXGI_GAMMA_CONTROL* pArray);
	HRESULT (*SetDisplaySurface)(IDXGIOutput* This, IDXGISurface* pScanoutSurface);
	HRESULT (*GetDisplaySurfaceData)(IDXGIOutput* This, IDXGISurface* pDestination);
	HRESULT (*GetFrameStatistics)(IDXGIOutput* This, DXGI_FRAME_STATISTICS* pStats);
} IDXGIOutputVtbl;

struct IDXGIOutput
{
	const IDXGIOutputVtbl* lpVtbl;
};

#ifdef COBJMACROS
#define IDXGIOutput_Querystruct(This,riid,ppvObject) ((This)->lpVtbl->Querystruct(This,riid,ppvObject))
#define IDXGIOutput_AddRef(This) ((This)->lpVtbl->AddRef(This))
#define IDXGIOutput_Release(This) ((This)->lpVtbl->Release(This))
#define IDXGIOutput_SetPrivateData(This,Name,DataSize,pData) ((This)->lpVtbl->SetPrivateData(This,Name,DataSize,pData))
#define IDXGIOutput_SetPrivateDatastruct(This,Name,pUnknown) ((This)->lpVtbl->SetPrivateDatastruct(This,Name,pUnknown))
#define IDXGIOutput_GetPrivateData(This,Name,pDataSize,pData) ((This)->lpVtbl->GetPrivateData(This,Name,pDataSize,pData))
#define IDXGIOutput_GetParent(This,riid,ppParent) ((This)->lpVtbl->GetParent(This,riid,ppParent))
#define IDXGIOutput_GetDesc(This,pDesc) ((This)->lpVtbl->GetDesc(This,pDesc))
#define IDXGIOutput_GetDisplayModeList(This,EnumFormat,Flags,pNumModes,pDesc) ((This)->lpVtbl->GetDisplayModeList(This,EnumFormat,Flags,pNumModes,pDesc))
#define IDXGIOutput_FindClosestMatchingMode(This,pModeToMatch,pClosestMatch,pConcernedDevice) ((This)->lpVtbl->FindClosestMatchingMode(This,pModeToMatch,pClosestMatch,pConcernedDevice))
#define IDXGIOutput_WaitForVBlank(This) ((This)->lpVtbl->WaitForVBlank(This))
#define IDXGIOutput_TakeOwnership(This,pDevice,Exclusive) ((This)->lpVtbl->TakeOwnership(This,pDevice,Exclusive))
#define IDXGIOutput_ReleaseOwnership(This) ((This)->lpVtbl->ReleaseOwnership(This))
#define IDXGIOutput_GetGammaControlCapabilities(This,pGammaCaps) ((This)->lpVtbl->GetGammaControlCapabilities(This,pGammaCaps))
#define IDXGIOutput_SetGammaControl(This,pArray) ((This)->lpVtbl->SetGammaControl(This,pArray))
#define IDXGIOutput_GetGammaControl(This,pArray) ((This)->lpVtbl->GetGammaControl(This,pArray))
#define IDXGIOutput_SetDisplaySurface(This,pScanoutSurface) ((This)->lpVtbl->SetDisplaySurface(This,pScanoutSurface))
#define IDXGIOutput_GetDisplaySurfaceData(This,pDestination) ((This)->lpVtbl->GetDisplaySurfaceData(This,pDestination))
#define IDXGIOutput_GetFrameStatistics(This,pStats) ((This)->lpVtbl->GetFrameStatistics(This,pStats))
#endif // COBJMACROS

#define DXGI_MAX_SWAP_CHAIN_BUFFERS            (16)
#define DXGI_PRESENT_TEST                      0x00000001UL
#define DXGI_PRESENT_DO_NOT_SEQUENCE           0x00000002UL
#define DXGI_PRESENT_RESTART                   0x00000004UL
#define DXGI_PRESENT_DO_NOT_WAIT               0x00000008UL
#define DXGI_PRESENT_STEREO_PREFER_RIGHT       0x00000010UL
#define DXGI_PRESENT_STEREO_TEMPORARY_MONO     0x00000020UL
#define DXGI_PRESENT_RESTRICT_TO_OUTPUT        0x00000040UL
#define DXGI_PRESENT_USE_DURATION              0x00000100UL
#define DXGI_PRESENT_ALLOW_TEARING             0x00000200UL

typedef struct IDXGISwapChainVtbl
{
	HRESULT (*Querystruct)(IDXGISwapChain* This, REFIID riid, void** ppvObject);
	ULONG (*AddRef)(IDXGISwapChain* This);
	ULONG (*Release)(IDXGISwapChain* This);
	HRESULT (*SetPrivateData)(IDXGISwapChain* This, REFGUID Name, UINT DataSize, const void* pData);
	HRESULT (*SetPrivateDatastruct)(IDXGISwapChain* This, REFGUID Name, const IUnknown* pUnknown);
	HRESULT (*GetPrivateData)(IDXGISwapChain* This, REFGUID Name, UINT* pDataSize, void* pData);
	HRESULT (*GetParent)(IDXGISwapChain* This, REFIID riid, void** ppParent);
	HRESULT (*GetDevice)(IDXGISwapChain* This, REFIID riid, void** ppDevice);
	HRESULT (*Present)(IDXGISwapChain* This, UINT SyncInterval, UINT Flags);
	HRESULT (*GetBuffer)(IDXGISwapChain* This, UINT Buffer, REFIID riid, void** ppSurface);
	HRESULT (*SetFullscreenState)(IDXGISwapChain* This, BOOL Fullscreen, IDXGIOutput* pTarget);
	HRESULT (*GetFullscreenState)(IDXGISwapChain* This, BOOL* pFullscreen, IDXGIOutput** ppTarget);
	HRESULT (*GetDesc)(IDXGISwapChain* This, DXGI_SWAP_CHAIN_DESC* pDesc);
	HRESULT (*ResizeBuffers)(IDXGISwapChain* This, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);
	HRESULT (*ResizeTarget)(IDXGISwapChain* This, const DXGI_MODE_DESC* pNewTargetParameters);
	HRESULT (*GetContainingOutput)(IDXGISwapChain* This, IDXGIOutput** ppOutput);
	HRESULT (*GetFrameStatistics)(IDXGISwapChain* This, DXGI_FRAME_STATISTICS* pStats);
	HRESULT (*GetLastPresentCount)(IDXGISwapChain* This, UINT* pLastPresentCount);
} IDXGISwapChainVtbl;

struct IDXGISwapChain
{
	const IDXGISwapChainVtbl* lpVtbl;
};

#ifdef COBJMACROS
#define IDXGISwapChain_Querystruct(This,riid,ppvObject) ((This)->lpVtbl->Querystruct(This,riid,ppvObject))
#define IDXGISwapChain_AddRef(This) ((This)->lpVtbl->AddRef(This))
#define IDXGISwapChain_Release(This) ((This)->lpVtbl->Release(This))
#define IDXGISwapChain_SetPrivateData(This,Name,DataSize,pData) ((This)->lpVtbl->SetPrivateData(This,Name,DataSize,pData))
#define IDXGISwapChain_SetPrivateDatastruct(This,Name,pUnknown) ((This)->lpVtbl->SetPrivateDatastruct(This,Name,pUnknown))
#define IDXGISwapChain_GetPrivateData(This,Name,pDataSize,pData) ((This)->lpVtbl->GetPrivateData(This,Name,pDataSize,pData))
#define IDXGISwapChain_GetParent(This,riid,ppParent) ((This)->lpVtbl->GetParent(This,riid,ppParent))
#define IDXGISwapChain_GetDevice(This,riid,ppDevice) ((This)->lpVtbl->GetDevice(This,riid,ppDevice))
#define IDXGISwapChain_Present(This,SyncInterval,Flags) ((This)->lpVtbl->Present(This,SyncInterval,Flags))
#define IDXGISwapChain_GetBuffer(This,Buffer,riid,ppSurface) ((This)->lpVtbl->GetBuffer(This,Buffer,riid,ppSurface))
#define IDXGISwapChain_SetFullscreenState(This,Fullscreen,pTarget) ((This)->lpVtbl->SetFullscreenState(This,Fullscreen,pTarget))
#define IDXGISwapChain_GetFullscreenState(This,pFullscreen,ppTarget) ((This)->lpVtbl->GetFullscreenState(This,pFullscreen,ppTarget))
#define IDXGISwapChain_GetDesc(This,pDesc) ((This)->lpVtbl->GetDesc(This,pDesc))
#define IDXGISwapChain_ResizeBuffers(This,BufferCount,Width,Height,NewFormat,SwapChainFlags) ((This)->lpVtbl->ResizeBuffers(This,BufferCount,Width,Height,NewFormat,SwapChainFlags))
#define IDXGISwapChain_ResizeTarget(This,pNewTargetParameters) ((This)->lpVtbl->ResizeTarget(This,pNewTargetParameters))
#define IDXGISwapChain_GetContainingOutput(This,ppOutput) ((This)->lpVtbl->GetContainingOutput(This,ppOutput))
#define IDXGISwapChain_GetFrameStatistics(This,pStats) ((This)->lpVtbl->GetFrameStatistics(This,pStats))
#define IDXGISwapChain_GetLastPresentCount(This,pLastPresentCount) ((This)->lpVtbl->GetLastPresentCount(This,pLastPresentCount))
#endif // COBJMACROS

#define DXGI_MWA_NO_WINDOW_CHANGES      ( 1 << 0 )
#define DXGI_MWA_NO_ALT_ENTER           ( 1 << 1 )
#define DXGI_MWA_NO_PRINT_SCREEN        ( 1 << 2 )
#define DXGI_MWA_VALID                  ( 0x7 )

typedef struct IDXGIFactoryVtbl
{
	HRESULT (*Querystruct)(IDXGIFactory* This, REFIID riid, void** ppvObject);
	ULONG (*AddRef)(IDXGIFactory* This);
	ULONG (*Release)(IDXGIFactory* This);
	HRESULT (*SetPrivateData)(IDXGIFactory* This, REFGUID Name, UINT DataSize, const void* pData);
	HRESULT (*SetPrivateDatastruct)(IDXGIFactory* This, REFGUID Name, const IUnknown* pUnknown);
	HRESULT (*GetPrivateData)(IDXGIFactory* This, REFGUID Name, UINT* pDataSize, void* pData);
	HRESULT (*GetParent)(IDXGIFactory* This, REFIID riid, void** ppParent);
	HRESULT (*EnumAdapters)(IDXGIFactory* This, UINT Adapter, IDXGIAdapter** ppAdapter);
	HRESULT (*MakeWindowAssociation)(IDXGIFactory* This, HWND WindowHandle, UINT Flags);
	HRESULT (*GetWindowAssociation)(IDXGIFactory* This, HWND* pWindowHandle);
	HRESULT (*CreateSwapChain)(IDXGIFactory* This, IUnknown* pDevice, DXGI_SWAP_CHAIN_DESC* pDesc, IDXGISwapChain** ppSwapChain);
	HRESULT (*CreateSoftwareAdapter)(IDXGIFactory* This, HMODULE Module, IDXGIAdapter** ppAdapter);
} IDXGIFactoryVtbl;

struct IDXGIFactory
{
	const IDXGIFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS
#define IDXGIFactory_Querystruct(This,riid,ppvObject) ((This)->lpVtbl->Querystruct(This,riid,ppvObject))
#define IDXGIFactory_AddRef(This) ((This)->lpVtbl->AddRef(This))
#define IDXGIFactory_Release(This) ((This)->lpVtbl->Release(This))
#define IDXGIFactory_SetPrivateData(This,Name,DataSize,pData) ((This)->lpVtbl->SetPrivateData(This,Name,DataSize,pData))
#define IDXGIFactory_SetPrivateDatastruct(This,Name,pUnknown) ((This)->lpVtbl->SetPrivateDatastruct(This,Name,pUnknown))
#define IDXGIFactory_GetPrivateData(This,Name,pDataSize,pData) ((This)->lpVtbl->GetPrivateData(This,Name,pDataSize,pData))
#define IDXGIFactory_GetParent(This,riid,ppParent) ((This)->lpVtbl->GetParent(This,riid,ppParent))
#define IDXGIFactory_EnumAdapters(This,Adapter,ppAdapter) ((This)->lpVtbl->EnumAdapters(This,Adapter,ppAdapter))
#define IDXGIFactory_MakeWindowAssociation(This,WindowHandle,Flags) ((This)->lpVtbl->MakeWindowAssociation(This,WindowHandle,Flags))
#define IDXGIFactory_GetWindowAssociation(This,pWindowHandle) ((This)->lpVtbl->GetWindowAssociation(This,pWindowHandle))
#define IDXGIFactory_CreateSwapChain(This,pDevice,pDesc,ppSwapChain) ((This)->lpVtbl->CreateSwapChain(This,pDevice,pDesc,ppSwapChain))
#define IDXGIFactory_CreateSoftwareAdapter(This,Module,ppAdapter) ((This)->lpVtbl->CreateSoftwareAdapter(This,Module,ppAdapter))
#endif // COBJMACROS

HRESULT WINAPI CreateDXGIFactory1(REFIID riid, void** ppFactory);

typedef struct IDXGIDeviceVtbl
{
	HRESULT (*Querystruct)(IDXGIDevice* This, REFIID riid, void** ppvObject);
	ULONG (*AddRef)(IDXGIDevice* This);
	ULONG (*Release)(IDXGIDevice* This);
	HRESULT (*SetPrivateData)(IDXGIDevice* This, REFGUID Name, UINT DataSize, const void* pData);
	HRESULT (*SetPrivateDatastruct)(IDXGIDevice* This, REFGUID Name, const IUnknown* pUnknown);
	HRESULT (*GetPrivateData)(IDXGIDevice* This, REFGUID Name, UINT* pDataSize, void* pData);
	HRESULT (*GetParent)(IDXGIDevice* This, REFIID riid, void** ppParent);
	HRESULT (*GetAdapter)(IDXGIDevice* This, IDXGIAdapter** pAdapter);
	HRESULT (*CreateSurface)(IDXGIDevice* This, const DXGI_SURFACE_DESC* pDesc, UINT NumSurfaces, DXGI_USAGE Usage, const DXGI_SHARED_RESOURCE* pSharedResource, IDXGISurface** ppSurface);
	HRESULT (*QueryResourceResidency)(IDXGIDevice* This, IUnknown* const* ppResources, DXGI_RESIDENCY* pResidencyStatus, UINT NumResources);
	HRESULT (*SetGPUThreadPriority)(IDXGIDevice* This, INT Priority);
	HRESULT (*GetGPUThreadPriority)(IDXGIDevice* This, INT* pPriority);
} IDXGIDeviceVtbl;

struct IDXGIDevice
{
	const IDXGIDeviceVtbl* lpVtbl;
};

#ifdef COBJMACROS
#define IDXGIDevice_Querystruct(This,riid,ppvObject) ((This)->lpVtbl->Querystruct(This,riid,ppvObject))
#define IDXGIDevice_AddRef(This) ((This)->lpVtbl->AddRef(This))
#define IDXGIDevice_Release(This) ((This)->lpVtbl->Release(This))
#define IDXGIDevice_SetPrivateData(This,Name,DataSize,pData) ((This)->lpVtbl->SetPrivateData(This,Name,DataSize,pData))
#define IDXGIDevice_SetPrivateDatastruct(This,Name,pUnknown) ((This)->lpVtbl->SetPrivateDatastruct(This,Name,pUnknown))
#define IDXGIDevice_GetPrivateData(This,Name,pDataSize,pData) ((This)->lpVtbl->GetPrivateData(This,Name,pDataSize,pData))
#define IDXGIDevice_GetParent(This,riid,ppParent) ((This)->lpVtbl->GetParent(This,riid,ppParent))
#define IDXGIDevice_GetAdapter(This,pAdapter) ((This)->lpVtbl->GetAdapter(This,pAdapter))
#define IDXGIDevice_CreateSurface(This,pDesc,NumSurfaces,Usage,pSharedResource,ppSurface) ((This)->lpVtbl->CreateSurface(This,pDesc,NumSurfaces,Usage,pSharedResource,ppSurface))
#define IDXGIDevice_QueryResourceResidency(This,ppResources,pResidencyStatus,NumResources) ((This)->lpVtbl->QueryResourceResidency(This,ppResources,pResidencyStatus,NumResources))
#define IDXGIDevice_SetGPUThreadPriority(This,Priority) ((This)->lpVtbl->SetGPUThreadPriority(This,Priority))
#define IDXGIDevice_GetGPUThreadPriority(This,pPriority) ((This)->lpVtbl->GetGPUThreadPriority(This,pPriority))
#endif // COBJMACROS

typedef enum DXGI_ADAPTER_FLAG
{
	DXGI_ADAPTER_FLAG_NONE = 0,
	DXGI_ADAPTER_FLAG_REMOTE = 1,
	DXGI_ADAPTER_FLAG_SOFTWARE = 2,
	DXGI_ADAPTER_FLAG_FORCE_DWORD = 0xffffffff
} DXGI_ADAPTER_FLAG;

typedef struct DXGI_ADAPTER_DESC1
{
	WCHAR Description[128];
	UINT VendorId;
	UINT DeviceId;
	UINT SubSysId;
	UINT Revision;
	SIZE_T DedicatedVideoMemory;
	SIZE_T DedicatedSystemMemory;
	SIZE_T SharedSystemMemory;
	LUID AdapterLuid;
	UINT Flags;
} DXGI_ADAPTER_DESC1;

typedef struct DXGI_DISPLAY_COLOR_SPACE
{
	FLOAT PrimaryCoordinates[8][2];
	FLOAT WhitePoints[16][2];
} DXGI_DISPLAY_COLOR_SPACE;

typedef struct IDXGIFactory1Vtbl
{
	HRESULT (*Querystruct)(IDXGIFactory1* This, REFIID riid, void** ppvObject);
	ULONG (*AddRef)(IDXGIFactory1* This);
	ULONG (*Release)(IDXGIFactory1* This);
	HRESULT (*SetPrivateData)(IDXGIFactory1* This, REFGUID Name, UINT DataSize, const void* pData);
	HRESULT (*SetPrivateDatastruct)(IDXGIFactory1* This, REFGUID Name, const IUnknown* pUnknown);
	HRESULT (*GetPrivateData)(IDXGIFactory1* This, REFGUID Name, UINT* pDataSize, void* pData);
	HRESULT (*GetParent)(IDXGIFactory1* This, REFIID riid, void** ppParent);
	HRESULT (*EnumAdapters)(IDXGIFactory1* This, UINT Adapter, IDXGIAdapter** ppAdapter);
	HRESULT (*MakeWindowAssociation)(IDXGIFactory1* This, HWND WindowHandle, UINT Flags);
	HRESULT (*GetWindowAssociation)(IDXGIFactory1* This, HWND* pWindowHandle);
	HRESULT (*CreateSwapChain)(IDXGIFactory1* This, IUnknown* pDevice, DXGI_SWAP_CHAIN_DESC* pDesc, IDXGISwapChain** ppSwapChain);
	HRESULT (*CreateSoftwareAdapter)(IDXGIFactory1* This, HMODULE Module, IDXGIAdapter** ppAdapter);
	HRESULT (*EnumAdapters1)(IDXGIFactory1* This, UINT Adapter, IDXGIAdapter1** ppAdapter);
	BOOL (*IsCurrent)(IDXGIFactory1* This);
} IDXGIFactory1Vtbl;

struct IDXGIFactory1
{
	const IDXGIFactory1Vtbl* lpVtbl;
};

#ifdef COBJMACROS
#define IDXGIFactory1_Querystruct(This,riid,ppvObject) ((This)->lpVtbl->Querystruct(This,riid,ppvObject))
#define IDXGIFactory1_AddRef(This) ((This)->lpVtbl->AddRef(This))
#define IDXGIFactory1_Release(This) ((This)->lpVtbl->Release(This))
#define IDXGIFactory1_SetPrivateData(This,Name,DataSize,pData) ((This)->lpVtbl->SetPrivateData(This,Name,DataSize,pData))
#define IDXGIFactory1_SetPrivateDatastruct(This,Name,pUnknown) ((This)->lpVtbl->SetPrivateDatastruct(This,Name,pUnknown))
#define IDXGIFactory1_GetPrivateData(This,Name,pDataSize,pData) ((This)->lpVtbl->GetPrivateData(This,Name,pDataSize,pData))
#define IDXGIFactory1_GetParent(This,riid,ppParent) ((This)->lpVtbl->GetParent(This,riid,ppParent))
#define IDXGIFactory1_EnumAdapters(This,Adapter,ppAdapter) ((This)->lpVtbl->EnumAdapters(This,Adapter,ppAdapter))
#define IDXGIFactory1_MakeWindowAssociation(This,WindowHandle,Flags) ((This)->lpVtbl->MakeWindowAssociation(This,WindowHandle,Flags))
#define IDXGIFactory1_GetWindowAssociation(This,pWindowHandle) ((This)->lpVtbl->GetWindowAssociation(This,pWindowHandle))
#define IDXGIFactory1_CreateSwapChain(This,pDevice,pDesc,ppSwapChain) ((This)->lpVtbl->CreateSwapChain(This,pDevice,pDesc,ppSwapChain))
#define IDXGIFactory1_CreateSoftwareAdapter(This,Module,ppAdapter) ((This)->lpVtbl->CreateSoftwareAdapter(This,Module,ppAdapter))
#define IDXGIFactory1_EnumAdapters1(This,Adapter,ppAdapter) ((This)->lpVtbl->EnumAdapters1(This,Adapter,ppAdapter))
#define IDXGIFactory1_IsCurrent(This) ((This)->lpVtbl->IsCurrent(This))
#endif // COBJMACROS

typedef struct IDXGIAdapter1Vtbl
{
	HRESULT (*Querystruct)(IDXGIAdapter1* This, REFIID riid, void** ppvObject);
	ULONG (*AddRef)(IDXGIAdapter1* This);
	ULONG (*Release)(IDXGIAdapter1* This);
	HRESULT (*SetPrivateData)(IDXGIAdapter1* This, REFGUID Name, UINT DataSize, const void* pData);
	HRESULT (*SetPrivateDatastruct)(IDXGIAdapter1* This, REFGUID Name, const IUnknown* pUnknown);
	HRESULT (*GetPrivateData)(IDXGIAdapter1* This, REFGUID Name, UINT* pDataSize, void* pData);
	HRESULT (*GetParent)(IDXGIAdapter1* This, REFIID riid, void** ppParent);
	HRESULT (*EnumOutputs)(IDXGIAdapter1* This, UINT Output, IDXGIOutput** ppOutput);
	HRESULT (*GetDesc)(IDXGIAdapter1* This, DXGI_ADAPTER_DESC* pDesc);
	HRESULT (*CheckstructSupport)(IDXGIAdapter1* This, REFGUID structName, LARGE_INTEGER* pUMDVersion);
	HRESULT (*GetDesc1)(IDXGIAdapter1* This, DXGI_ADAPTER_DESC1* pDesc);
} IDXGIAdapter1Vtbl;

struct IDXGIAdapter1
{
	const IDXGIAdapter1Vtbl* lpVtbl;
};

#ifdef COBJMACROS
#define IDXGIAdapter1_Querystruct(This,riid,ppvObject) ((This)->lpVtbl->Querystruct(This,riid,ppvObject))
#define IDXGIAdapter1_AddRef(This) ((This)->lpVtbl->AddRef(This))
#define IDXGIAdapter1_Release(This) ((This)->lpVtbl->Release(This))
#define IDXGIAdapter1_SetPrivateData(This,Name,DataSize,pData) ((This)->lpVtbl->SetPrivateData(This,Name,DataSize,pData))
#define IDXGIAdapter1_SetPrivateDatastruct(This,Name,pUnknown) ((This)->lpVtbl->SetPrivateDatastruct(This,Name,pUnknown))
#define IDXGIAdapter1_GetPrivateData(This,Name,pDataSize,pData) ((This)->lpVtbl->GetPrivateData(This,Name,pDataSize,pData))
#define IDXGIAdapter1_GetParent(This,riid,ppParent) ((This)->lpVtbl->GetParent(This,riid,ppParent))
#define IDXGIAdapter1_EnumOutputs(This,Output,ppOutput) ((This)->lpVtbl->EnumOutputs(This,Output,ppOutput))
#define IDXGIAdapter1_GetDesc(This,pDesc) ((This)->lpVtbl->GetDesc(This,pDesc))
#define IDXGIAdapter1_CheckstructSupport(This,structName,pUMDVersion) ((This)->lpVtbl->CheckstructSupport(This,structName,pUMDVersion))
#define IDXGIAdapter1_GetDesc1(This,pDesc) ((This)->lpVtbl->GetDesc1(This,pDesc))
#endif // COBJMACROS

typedef struct IDXGIDevice1Vtbl
{
	HRESULT (*Querystruct)(IDXGIDevice1* This, REFIID riid, void** ppvObject);
	ULONG (*AddRef)(IDXGIDevice1* This);
	ULONG (*Release)(IDXGIDevice1* This);
	HRESULT (*SetPrivateData)(IDXGIDevice1* This, REFGUID Name, UINT DataSize, const void* pData);
	HRESULT (*SetPrivateDatastruct)(IDXGIDevice1* This, REFGUID Name, const IUnknown* pUnknown);
	HRESULT (*GetPrivateData)(IDXGIDevice1* This, REFGUID Name, UINT* pDataSize, void* pData);
	HRESULT (*GetParent)(IDXGIDevice1* This, REFIID riid, void** ppParent);
	HRESULT (*GetAdapter)(IDXGIDevice1* This, IDXGIAdapter** pAdapter);
	HRESULT (*CreateSurface)(IDXGIDevice1* This, const DXGI_SURFACE_DESC* pDesc, UINT NumSurfaces, DXGI_USAGE Usage, const DXGI_SHARED_RESOURCE* pSharedResource, IDXGISurface** ppSurface);
	HRESULT (*QueryResourceResidency)(IDXGIDevice1* This, IUnknown* const* ppResources, DXGI_RESIDENCY* pResidencyStatus, UINT NumResources);
	HRESULT (*SetGPUThreadPriority)(IDXGIDevice1* This, INT Priority);
	HRESULT (*GetGPUThreadPriority)(IDXGIDevice1* This, INT* pPriority);
	HRESULT (*SetMaximumFrameLatency)(IDXGIDevice1* This, UINT MaxLatency);
	HRESULT (*GetMaximumFrameLatency)(IDXGIDevice1* This, UINT* pMaxLatency);
} IDXGIDevice1Vtbl;

struct IDXGIDevice1
{
	const IDXGIDevice1Vtbl* lpVtbl;
};

#ifdef COBJMACROS
#define IDXGIDevice1_Querystruct(This,riid,ppvObject) ((This)->lpVtbl->Querystruct(This,riid,ppvObject))
#define IDXGIDevice1_AddRef(This) ((This)->lpVtbl->AddRef(This))
#define IDXGIDevice1_Release(This) ((This)->lpVtbl->Release(This))
#define IDXGIDevice1_SetPrivateData(This,Name,DataSize,pData) ((This)->lpVtbl->SetPrivateData(This,Name,DataSize,pData))
#define IDXGIDevice1_SetPrivateDatastruct(This,Name,pUnknown) ((This)->lpVtbl->SetPrivateDatastruct(This,Name,pUnknown))
#define IDXGIDevice1_GetPrivateData(This,Name,pDataSize,pData) ((This)->lpVtbl->GetPrivateData(This,Name,pDataSize,pData))
#define IDXGIDevice1_GetParent(This,riid,ppParent) ((This)->lpVtbl->GetParent(This,riid,ppParent))
#define IDXGIDevice1_GetAdapter(This,pAdapter) ((This)->lpVtbl->GetAdapter(This,pAdapter))
#define IDXGIDevice1_CreateSurface(This,pDesc,NumSurfaces,Usage,pSharedResource,ppSurface) ((This)->lpVtbl->CreateSurface(This,pDesc,NumSurfaces,Usage,pSharedResource,ppSurface))
#define IDXGIDevice1_QueryResourceResidency(This,ppResources,pResidencyStatus,NumResources) ((This)->lpVtbl->QueryResourceResidency(This,ppResources,pResidencyStatus,NumResources))
#define IDXGIDevice1_SetGPUThreadPriority(This,Priority) ((This)->lpVtbl->SetGPUThreadPriority(This,Priority))
#define IDXGIDevice1_GetGPUThreadPriority(This,pPriority) ((This)->lpVtbl->GetGPUThreadPriority(This,pPriority))
#define IDXGIDevice1_SetMaximumFrameLatency(This,MaxLatency) ((This)->lpVtbl->SetMaximumFrameLatency(This,MaxLatency))
#define IDXGIDevice1_GetMaximumFrameLatency(This,pMaxLatency) ((This)->lpVtbl->GetMaximumFrameLatency(This,pMaxLatency))
#endif // COBJMACROS

static const GUID IID_IDXGIObject          = { 0xaec22fb8, 0x76f3, 0x4639, 0x9b, 0xe0, 0x28, 0xeb, 0x43, 0xa6, 0x7a, 0x2e };
static const GUID IID_IDXGIDeviceSubObject = { 0x3d3e0379, 0xf9de, 0x4d58, 0xbb, 0x6c, 0x18, 0xd6, 0x29, 0x92, 0xf1, 0xa6 };
static const GUID IID_IDXGIResource        = { 0x035f3ab4, 0x482e, 0x4e50, 0xb4, 0x1f, 0x8a, 0x7f, 0x8b, 0xd8, 0x96, 0x0b };
static const GUID IID_IDXGIKeyedMutex      = { 0x9d8e1289, 0xd7b3, 0x465f, 0x81, 0x26, 0x25, 0x0e, 0x34, 0x9a, 0xf8, 0x5d };
static const GUID IID_IDXGISurface         = { 0xcafcb56c, 0x6ac3, 0x4889, 0xbf, 0x47, 0x9e, 0x23, 0xbb, 0xd2, 0x60, 0xec };
static const GUID IID_IDXGISurface1        = { 0x4AE63092, 0x6327, 0x4c1b, 0x80, 0xAE, 0xBF, 0xE1, 0x2E, 0xA3, 0x2B, 0x86 };
static const GUID IID_IDXGIAdapter         = { 0x2411e7e1, 0x12ac, 0x4ccf, 0xbd, 0x14, 0x97, 0x98, 0xe8, 0x53, 0x4d, 0xc0 };
static const GUID IID_IDXGIOutput          = { 0xae02eedb, 0xc735, 0x4690, 0x8d, 0x52, 0x5a, 0x8d, 0xc2, 0x02, 0x13, 0xaa };
static const GUID IID_IDXGISwapChain       = { 0x310d36a0, 0xd2e7, 0x4c0a, 0xaa, 0x04, 0x6a, 0x9d, 0x23, 0xb8, 0x88, 0x6a };
static const GUID IID_IDXGIFactory         = { 0x7b7166ec, 0x21c7, 0x44ae, 0xb2, 0x1a, 0xc9, 0xae, 0x32, 0x1a, 0xe3, 0x69 };
static const GUID IID_IDXGIDevice          = { 0x54ec77fa, 0x1377, 0x44e6, 0x8c, 0x32, 0x88, 0xfd, 0x5f, 0x44, 0xc8, 0x4c };
static const GUID IID_IDXGIFactory1        = { 0x770aae78, 0xf26f, 0x4dba, 0xa8, 0x29, 0x25, 0x3c, 0x83, 0xd1, 0xb3, 0x87 };
static const GUID IID_IDXGIAdapter1        = { 0x29038f61, 0x3839, 0x4626, 0x91, 0xfd, 0x08, 0x68, 0x79, 0x01, 0x1a, 0x05 };
static const GUID IID_IDXGIDevice1         = { 0x77db970f, 0x6276, 0x48ba, 0xba, 0x28, 0x07, 0x01, 0x43, 0xb4, 0x39, 0x2c };

#endif // __dxgi_h__