#ifndef _PROPSYS_H
#define _PROPSYS_H

#include <windef.h>

typedef struct _tagpropertykey
{
	GUID fmtid;
	DWORD pid;
} PROPERTYKEY;

typedef struct tagPROPVARIANT PROPVARIANT;

#define REFPROPERTYKEY const PROPERTYKEY * const
#define REFPROPVARIANT const PROPVARIANT * const

typedef struct IPropertyStore IPropertyStore;
typedef struct IPropertyDescriptionList IPropertyDescriptionList;

typedef enum GETPROPERTYSTOREFLAGS
{
	GPS_DEFAULT = 0,
	GPS_HANDLERPROPERTIESONLY = 0x1,
	GPS_READWRITE = 0x2,
	GPS_TEMPORARY = 0x4,
	GPS_FASTPROPERTIESONLY = 0x8,
	GPS_OPENSLOWITEM = 0x10,
	GPS_DELAYCREATION = 0x20,
	GPS_BESTEFFORT = 0x40,
	GPS_NO_OPLOCK = 0x80,
	GPS_PREFERQUERYPROPERTIES = 0x100,
	GPS_EXTRINSICPROPERTIES = 0x200,
	GPS_EXTRINSICPROPERTIESONLY = 0x400,
	GPS_VOLATILEPROPERTIES = 0x800,
	GPS_VOLATILEPROPERTIESONLY = 0x1000,
	GPS_MASK_VALID = 0x1fff
} GETPROPERTYSTOREFLAGS;

EXTERN_C const IID IID_IPropertyStore;

typedef struct IPropertyStoreVtbl
{
	HRESULT (*QueryInterface)(IPropertyStore* This, REFIID riid, void** ppvObject);
	ULONG (*AddRef)(IPropertyStore* This);
	ULONG (*Release)(IPropertyStore* This);
	HRESULT (*GetCount)(IPropertyStore* This, DWORD* cProps);
	HRESULT (*GetAt)(IPropertyStore* This, DWORD iProp, PROPERTYKEY* pkey);
	HRESULT (*GetValue)(IPropertyStore* This, REFPROPERTYKEY key, PROPVARIANT* pv);
	HRESULT (*SetValue)(IPropertyStore* This, REFPROPERTYKEY key, REFPROPVARIANT propvar);
	HRESULT (*Commit)(IPropertyStore* This);
} IPropertyStoreVtbl;

struct IPropertyStore
{
	const IPropertyStoreVtbl* lpVtbl;
};

EXTERN_C const IID IID_IPropertyDescriptionList;

typedef struct IPropertyDescriptionListVtbl
{
	HRESULT (*QueryInterface)(IPropertyDescriptionList* This, REFIID riid, void** ppvObject);
	ULONG (*AddRef)(IPropertyDescriptionList* This);
	ULONG (*Release)(IPropertyDescriptionList* This);
	HRESULT (*GetCount)(IPropertyDescriptionList* This, UINT* pcElem);
	HRESULT (*GetAt)(IPropertyDescriptionList* This, UINT iElem, REFIID riid, void** ppv);
} IPropertyDescriptionListVtbl;

struct IPropertyDescriptionList
{
	const IPropertyDescriptionListVtbl* lpVtbl;
};

#endif // _PROPSYS_H
