#ifndef OBJBASE_H
#define OBJBASE_H

#include <windef.h>
#include <winerror.h>
#include <unknwn.h>
#include <propsys.h>

typedef WCHAR OLECHAR;
typedef OLECHAR* LPOLESTR;
typedef const OLECHAR* LPCOLESTR;

#define OLESTR(str) L##str

typedef enum tagCLSCTX
{
	CLSCTX_INPROC_SERVER = 0x1,
	CLSCTX_INPROC_HANDLER = 0x2,
	CLSCTX_LOCAL_SERVER = 0x4,
	CLSCTX_INPROC_SERVER16 = 0x8,
	CLSCTX_REMOTE_SERVER = 0x10,
	CLSCTX_INPROC_HANDLER16 = 0x20,
	CLSCTX_RESERVED1 = 0x40,
	CLSCTX_RESERVED2 = 0x80,
	CLSCTX_RESERVED3 = 0x100,
	CLSCTX_RESERVED4 = 0x200,
	CLSCTX_NO_CODE_DOWNLOAD = 0x400,
	CLSCTX_RESERVED5 = 0x800,
	CLSCTX_NO_CUSTOM_MARSHAL = 0x1000,
	CLSCTX_ENABLE_CODE_DOWNLOAD = 0x2000,
	CLSCTX_NO_FAILURE_LOG = 0x4000,
	CLSCTX_DISABLE_AAA = 0x8000,
	CLSCTX_ENABLE_AAA = 0x10000,
	CLSCTX_FROM_DEFAULT_CONTEXT = 0x20000,
	CLSCTX_ACTIVATE_X86_SERVER = 0x40000,
	CLSCTX_ACTIVATE_32_BIT_SERVER = CLSCTX_ACTIVATE_X86_SERVER,
	CLSCTX_ACTIVATE_64_BIT_SERVER = 0x80000,
	CLSCTX_ENABLE_CLOAKING = 0x100000,
	CLSCTX_APPCONTAINER = 0x400000,
	CLSCTX_ACTIVATE_AAA_AS_IU = 0x800000,
	CLSCTX_RESERVED6 = 0x1000000,
	CLSCTX_ACTIVATE_ARM32_SERVER = 0x2000000,
	CLSCTX_ALLOW_LOWER_TRUST_REGISTRATION = 0x4000000,
	CLSCTX_SERVER_MUST_BE_EQUAL_OR_GREATER_PRIVILEGE = 0x8000000,
	CLSCTX_DO_NOT_ELEVATE_SERVER = 0x10000000,
	CLSCTX_PS_DLL = 0x80000000
} 	CLSCTX;

#define CLSCTX_ALL    (CLSCTX_INPROC_SERVER | CLSCTX_INPROC_HANDLER | CLSCTX_LOCAL_SERVER | CLSCTX_REMOTE_SERVER)
#define CLSCTX_SERVER (CLSCTX_INPROC_SERVER | CLSCTX_LOCAL_SERVER | CLSCTX_REMOTE_SERVER)

typedef enum tagCOINIT {
	COINIT_APARTMENTTHREADED = 0x2,
	COINIT_MULTITHREADED = 0x0,
	COINIT_DISABLE_OLE1DDE = 0x4,
	COINIT_SPEED_OVER_MEMORY = 0x8
} COINIT;

typedef struct _COMDLG_FILTERSPEC {
	LPCWSTR pszName;
	LPCWSTR pszSpec;
} COMDLG_FILTERSPEC;

typedef struct IBindCtx IBindCtx;
typedef struct IRunningObjectTable IRunningObjectTable;
typedef struct IEnumString IEnumString;
typedef struct IMoniker IMoniker;
typedef struct IEnumMoniker IEnumMoniker;
typedef struct IStream IStream;
typedef struct IShellItem IShellItem;
typedef struct IShellItemArray IShellItemArray;
typedef struct IShellItemFilter IShellItemFilter;
typedef struct IEnumShellItems IEnumShellItems;
typedef struct IFileDialog IFileDialog;
typedef struct IFileDialogEvents IFileDialogEvents;
typedef struct IFileOperationProgressSink IFileOperationProgressSink;
typedef struct IFileSaveDialog IFileSaveDialog;
typedef struct IFileOpenDialog IFileOpenDialog;

typedef struct tagBIND_OPTS
{
	DWORD cbStruct;
	DWORD grfFlags;
	DWORD grfMode;
	DWORD dwTickCountDeadline;
} BIND_OPTS;

typedef struct tagBIND_OPTS* LPBIND_OPTS;

typedef IBindCtx* LPBC;
typedef IBindCtx* LPBINDCTX;

typedef struct IBindCtxVtbl
{
	HRESULT (*QueryInterface)(IBindCtx* This, REFIID riid, void** ppvObject);
	ULONG (*AddRef)(IBindCtx* This);
	ULONG (*Release)(IBindCtx* This);
	HRESULT (*RegisterObjectBound)(IBindCtx* This, IUnknown* punk);
	HRESULT (*RevokeObjectBound)(IBindCtx* This, IUnknown* punk);
	HRESULT (*ReleaseBoundObjects)(IBindCtx* This);
	HRESULT (*SetBindOptions)(IBindCtx* This, BIND_OPTS* pbindopts);
	HRESULT (*GetBindOptions)(IBindCtx* This, BIND_OPTS* pbindopts);
	HRESULT (*GetRunningObjectTable)(IBindCtx* This, IRunningObjectTable** pprot);
	HRESULT (*RegisterObjectParam)(IBindCtx* This, LPOLESTR pszKey, IUnknown* punk);
	HRESULT (*GetObjectParam)(IBindCtx* This, LPOLESTR pszKey, IUnknown** ppunk);
	HRESULT (*EnumObjectParam)(IBindCtx* This, IEnumString** ppenum);
	HRESULT (*RevokeObjectParam)(IBindCtx* This, LPOLESTR pszKey);
} IBindCtxVtbl;

struct IBindCtx
{
	const IBindCtxVtbl* lpVtbl;
};

typedef IRunningObjectTable* LPRUNNINGOBJECTTABLE;

typedef struct IRunningObjectTableVtbl
{
	HRESULT (*QueryInterface)(IRunningObjectTable* This, REFIID riid, void** ppvObject);
	ULONG (*AddRef)(IRunningObjectTable* This);
	ULONG (*Release)(IRunningObjectTable* This);
	HRESULT (*Register)(IRunningObjectTable* This, DWORD grfFlags, IUnknown* punkObject, IMoniker* pmkObjectName, DWORD* pdwRegister);
	HRESULT (*Revoke)(IRunningObjectTable* This, DWORD dwRegister);
	HRESULT (*IsRunning)(IRunningObjectTable* This, IMoniker* pmkObjectName);
	HRESULT (*GetObject)(IRunningObjectTable* This, IMoniker* pmkObjectName, IUnknown** ppunkObject);
	HRESULT (*NoteChangeTime)(IRunningObjectTable* This, DWORD dwRegister, FILETIME* pfiletime);
	HRESULT (*GetTimeOfLastChange)(IRunningObjectTable* This, IMoniker* pmkObjectName, FILETIME* pfiletime);
	HRESULT (*EnumRunning)(IRunningObjectTable* This, IEnumMoniker** ppenumMoniker);
} IRunningObjectTableVtbl;

struct IRunningObjectTable
{
	const IRunningObjectTableVtbl* lpVtbl;
};

typedef struct IEnumStringVtbl
{
	HRESULT (*QueryInterface)(IEnumString* This, REFIID riid, void** ppvObject);
	ULONG (*AddRef)(IEnumString* This);
	ULONG (*Release)(IEnumString* This);
	HRESULT (*Next)(IEnumString* This, ULONG celt, LPOLESTR* rgelt, ULONG* pceltFetched);
	HRESULT (*Skip)(IEnumString* This, ULONG celt);
	HRESULT (*Reset)(IEnumString* This);
	HRESULT (*Clone)(IEnumString* This, IEnumString** ppenum);
} IEnumStringVtbl;

struct IEnumString
{
	const IEnumStringVtbl* lpVtbl;
};

typedef IMoniker* LPMONIKER;

typedef struct IMonikerVtbl
{
	HRESULT (*QueryInterface)(IMoniker* This, REFIID riid, void** ppvObject);
	ULONG (*AddRef)(IMoniker* This);
	ULONG (*Release)(IMoniker* This);
	HRESULT (*GetClassID)(IMoniker* This, CLSID* pClassID);
	HRESULT (*IsDirty)(IMoniker* This);
	HRESULT (*Load)(IMoniker* This, IStream* pStm);
	HRESULT (*Save)(IMoniker* This, IStream* pStm, BOOL fClearDirty);
	HRESULT (*GetSizeMax)(IMoniker* This, ULARGE_INTEGER* pcbSize);
	HRESULT (*BindToObject)(IMoniker* This, IBindCtx* pbc, IMoniker* pmkToLeft, REFIID riidResult, void** ppvResult);
	HRESULT (*BindToStorage)(IMoniker* This, IBindCtx* pbc, IMoniker* pmkToLeft, REFIID riid, void** ppvObj);
	HRESULT (*Reduce)(IMoniker* This, IBindCtx* pbc, DWORD dwReduceHowFar, IMoniker** ppmkToLeft, IMoniker** ppmkReduced);
	HRESULT (*ComposeWith)(IMoniker* This, IMoniker* pmkRight, BOOL fOnlyIfNotGeneric, IMoniker** ppmkComposite);
	HRESULT (*Enum)(IMoniker* This, BOOL fForward, IEnumMoniker** ppenumMoniker);
	HRESULT (*IsEqual)(IMoniker* This, IMoniker* pmkOtherMoniker);
	HRESULT (*Hash)(IMoniker* This, DWORD* pdwHash);
	HRESULT (*IsRunning)(IMoniker* This, IBindCtx* pbc, IMoniker* pmkToLeft, IMoniker* pmkNewlyRunning);
	HRESULT (*GetTimeOfLastChange)(IMoniker* This, IBindCtx* pbc, IMoniker* pmkToLeft, FILETIME* pFileTime);
	HRESULT (*Inverse)(IMoniker* This, IMoniker** ppmk);
	HRESULT (*CommonPrefixWith)(IMoniker* This, IMoniker* pmkOther, IMoniker** ppmkPrefix);
	HRESULT (*RelativePathTo)(IMoniker* This, IMoniker* pmkOther, IMoniker** ppmkRelPath);
	HRESULT (*GetDisplayName)(IMoniker* This, IBindCtx* pbc, IMoniker* pmkToLeft, LPOLESTR* ppszDisplayName);
	HRESULT (*ParseDisplayName)(IMoniker* This, IBindCtx* pbc, IMoniker* pmkToLeft, LPOLESTR pszDisplayName, ULONG* pchEaten, IMoniker** ppmkOut);
	HRESULT (*IsSystemMoniker)(IMoniker* This, DWORD* pdwMksys);
} IMonikerVtbl;

struct IMoniker
{
	const IMonikerVtbl* lpVtbl;
};

typedef IEnumMoniker* LPENUMMONIKER;

typedef struct IEnumMonikerVtbl
{
	HRESULT (*QueryInterface)(IEnumMoniker* This, REFIID riid, void** ppvObject);
	ULONG (*AddRef)(IEnumMoniker* This);
	ULONG (*Release)(IEnumMoniker* This);
	HRESULT (*Next)(IEnumMoniker* This, ULONG celt, IMoniker** rgelt, ULONG* pceltFetched);
	HRESULT (*Skip)(IEnumMoniker* This, ULONG celt);
	HRESULT (*Reset)(IEnumMoniker* This);
	HRESULT (*Clone)(IEnumMoniker* This, IEnumMoniker** ppenum);
} IEnumMonikerVtbl;

struct IEnumMoniker
{
	const IEnumMonikerVtbl* lpVtbl;
};

typedef struct tagSTATSTG
{
	LPOLESTR pwcsName;
	DWORD type;
	ULARGE_INTEGER cbSize;
	FILETIME mtime;
	FILETIME ctime;
	FILETIME atime;
	DWORD grfMode;
	DWORD grfLocksSupported;
	CLSID clsid;
	DWORD grfStateBits;
	DWORD reserved;
} STATSTG;

typedef IStream* LPSTREAM;

typedef struct IStreamVtbl
{
	HRESULT (*QueryInterface)(IStream* This, REFIID riid, void** ppvObject);
	ULONG (*AddRef)(IStream* This);
	ULONG (*Release)(IStream* This);
	HRESULT (*Read)(IStream* This, void* pv, ULONG cb, ULONG* pcbRead);
	HRESULT (*Write)(IStream* This, const void* pv, ULONG cb, ULONG* pcbWritten);
	HRESULT (*Seek)(IStream* This, LARGE_INTEGER dlibMove, DWORD dwOrigin, ULARGE_INTEGER* plibNewPosition);
	HRESULT (*SetSize)(IStream* This, ULARGE_INTEGER libNewSize);
	HRESULT (*CopyTo)(IStream* This, IStream* pstm, ULARGE_INTEGER cb, ULARGE_INTEGER* pcbRead, ULARGE_INTEGER* pcbWritten);
	HRESULT (*Commit)(IStream* This, DWORD grfCommitFlags);
	HRESULT (*Revert)(IStream* This);
	HRESULT (*LockRegion)(IStream* This, ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType);
	HRESULT (*UnlockRegion)(IStream* This, ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType);
	HRESULT (*Stat)(IStream* This, STATSTG* pstatstg, DWORD grfStatFlag);
	HRESULT (*Clone)(IStream* This, IStream** ppstm);
} IStreamVtbl;

struct IStream
{
	const IStreamVtbl* lpVtbl;
};

#define SHCIDS_ALLFIELDS        0x80000000L
#define SHCIDS_CANONICALONLY    0x10000000L
#define SHCIDS_BITMASK          0xFFFF0000L
#define SHCIDS_COLUMNMASK       0x0000FFFFL
#define SFGAO_CANCOPY           DROPEFFECT_COPY // Objects can be copied    (0x1)
#define SFGAO_CANMOVE           DROPEFFECT_MOVE // Objects can be moved     (0x2)
#define SFGAO_CANLINK           DROPEFFECT_LINK // Objects can be linked    (0x4)
#define SFGAO_STORAGE           0x00000008L     // supports BindToObject(IID_IStorage)
#define SFGAO_CANRENAME         0x00000010L     // Objects can be renamed
#define SFGAO_CANDELETE         0x00000020L     // Objects can be deleted
#define SFGAO_HASPROPSHEET      0x00000040L     // Objects have property sheets
#define SFGAO_DROPTARGET        0x00000100L     // Objects are drop target
#define SFGAO_CAPABILITYMASK    0x00000177L
#define SFGAO_PLACEHOLDER       0x00000800L     // File or folder is not fully present and recalled on open or access
#define SFGAO_SYSTEM            0x00001000L     // System object
#define SFGAO_ENCRYPTED         0x00002000L     // Object is encrypted (use alt color)
#define SFGAO_ISSLOW            0x00004000L     // 'Slow' object
#define SFGAO_GHOSTED           0x00008000L     // Ghosted icon
#define SFGAO_LINK              0x00010000L     // Shortcut (link)
#define SFGAO_SHARE             0x00020000L     // Shared
#define SFGAO_READONLY          0x00040000L     // Read-only
#define SFGAO_HIDDEN            0x00080000L     // Hidden object
#define SFGAO_DISPLAYATTRMASK   0x000FC000L
#define SFGAO_FILESYSANCESTOR   0x10000000L     // May contain children with SFGAO_FILESYSTEM
#define SFGAO_FOLDER            0x20000000L     // Support BindToObject(IID_IShellFolder)
#define SFGAO_FILESYSTEM        0x40000000L     // Is a win32 file system object (file/folder/root)
#define SFGAO_HASSUBFOLDER      0x80000000L     // May contain children with SFGAO_FOLDER (may be slow)
#define SFGAO_CONTENTSMASK      0x80000000L
#define SFGAO_VALIDATE          0x01000000L     // Invalidate cached information (may be slow)
#define SFGAO_REMOVABLE         0x02000000L     // Is this removeable media?
#define SFGAO_COMPRESSED        0x04000000L     // Object is compressed (use alt color)
#define SFGAO_BROWSABLE         0x08000000L     // Supports IShellFolder, but only implements CreateViewObject() (non-folder view)
#define SFGAO_NONENUMERATED     0x00100000L     // Is a non-enumerated object (should be hidden)
#define SFGAO_NEWCONTENT        0x00200000L     // Should show bold in explorer tree
#define SFGAO_CANMONIKER        0x00400000L     // Obsolete
#define SFGAO_HASSTORAGE        0x00400000L     // Obsolete
#define SFGAO_STREAM            0x00400000L     // Supports BindToObject(IID_IStream)
#define SFGAO_STORAGEANCESTOR   0x00800000L     // May contain children with SFGAO_STORAGE or SFGAO_STREAM
#define SFGAO_STORAGECAPMASK    0x70C50008L     // For determining storage capabilities, ie for open/save semantics
#define SFGAO_PKEYSFGAOMASK     0x81044000L     // Attributes that are masked out for PKEY_SFGAOFlags because they are considered to cause slow calculations or lack context (SFGAO_VALIDATE | SFGAO_ISSLOW | SFGAO_HASSUBFOLDER and others)
typedef ULONG SFGAOF;

typedef enum _SIGDN
{
	SIGDN_NORMALDISPLAY = 0,
	SIGDN_PARENTRELATIVEPARSING = (int)0x80018001,
	SIGDN_DESKTOPABSOLUTEPARSING = (int)0x80028000,
	SIGDN_PARENTRELATIVEEDITING = (int)0x80031001,
	SIGDN_DESKTOPABSOLUTEEDITING = (int)0x8004c000,
	SIGDN_FILESYSPATH = (int)0x80058000,
	SIGDN_URL = (int)0x80068000,
	SIGDN_PARENTRELATIVEFORADDRESSBAR = (int)0x8007c001,
	SIGDN_PARENTRELATIVE = (int)0x80080001,
	SIGDN_PARENTRELATIVEFORUI = (int)0x80094001
} SIGDN;

enum _SICHINTF
{
	SICHINT_DISPLAY = 0,
	SICHINT_ALLFIELDS = (int)0x80000000,
	SICHINT_CANONICAL = 0x10000000,
	SICHINT_TEST_FILESYSPATH_IF_NOT_EQUAL = 0x20000000
};
typedef DWORD SICHINTF;

typedef struct IShellItemVtbl
{
	HRESULT (*QueryInterface)(IShellItem* This, REFIID riid, void** ppvObject);
	ULONG (*AddRef)(IShellItem* This);
	ULONG (*Release)(IShellItem* This);
	HRESULT (*BindToHandler)(IShellItem* This, IBindCtx* pbc, REFGUID bhid, REFIID riid, void** ppv);
	HRESULT (*GetParent)(IShellItem* This, IShellItem** ppsi);
	HRESULT (*GetDisplayName)(IShellItem* This, SIGDN sigdnName, LPWSTR* ppszName);
	HRESULT (*GetAttributes)(IShellItem* This, SFGAOF sfgaoMask, SFGAOF* psfgaoAttribs);
	HRESULT (*Compare)(IShellItem* This, IShellItem* psi, SICHINTF hint, int* piOrder);
} IShellItemVtbl;

struct IShellItem
{
	const IShellItemVtbl* lpVtbl;
};

typedef enum SIATTRIBFLAGS
{
	SIATTRIBFLAGS_AND = 0x1,
	SIATTRIBFLAGS_OR = 0x2,
	SIATTRIBFLAGS_APPCOMPAT = 0x3,
	SIATTRIBFLAGS_MASK = 0x3,
	SIATTRIBFLAGS_ALLITEMS = 0x4000
} SIATTRIBFLAGS;

typedef struct IShellItemArrayVtbl
{
	HRESULT (*QueryInterface)(IShellItemArray* This, REFIID riid, void** ppvObject);
	ULONG (*AddRef)(IShellItemArray* This);
	ULONG (*Release)(IShellItemArray* This);
	HRESULT (*BindToHandler)(IShellItemArray* This, IBindCtx* pbc, REFGUID bhid, REFIID riid, void** ppvOut);
	HRESULT (*GetPropertyStore)(IShellItemArray* This, GETPROPERTYSTOREFLAGS flags, REFIID riid, void** ppv);
	HRESULT (*GetPropertyDescriptionList)(IShellItemArray* This, REFPROPERTYKEY keyType, REFIID riid, void** ppv);
	HRESULT (*GetAttributes)(IShellItemArray* This, SIATTRIBFLAGS AttribFlags, SFGAOF sfgaoMask, SFGAOF* psfgaoAttribs);
	HRESULT (*GetCount)(IShellItemArray* This, DWORD* pdwNumItems);
	HRESULT (*GetItemAt)(IShellItemArray* This, DWORD dwIndex, IShellItem** ppsi);
	HRESULT (*EnumItems)(IShellItemArray* This, IEnumShellItems** ppenumShellItems);
} IShellItemArrayVtbl;

struct IShellItemArray
{
	const IShellItemArrayVtbl* lpVtbl;
};

typedef struct IEnumShellItemsVtbl
{
	HRESULT (*QueryInterface)(IEnumShellItems* This, REFIID riid, void** ppvObject);
	ULONG (*AddRef)(IEnumShellItems* This);
	ULONG (*Release)(IEnumShellItems* This);
	HRESULT (*Next)(IEnumShellItems* This, ULONG celt, IShellItem** rgelt, ULONG* pceltFetched);
	HRESULT (*Skip)(IEnumShellItems* This, ULONG celt);
	HRESULT (*Reset)(IEnumShellItems* This);
	HRESULT (*Clone)(IEnumShellItems* This, IEnumShellItems** ppenum);
} IEnumShellItemsVtbl;

struct IEnumShellItems
{
	const IEnumShellItemsVtbl* lpVtbl;
};

enum _SHCONTF
{
	SHCONTF_CHECKING_FOR_CHILDREN = 0x10,
	SHCONTF_FOLDERS = 0x20,
	SHCONTF_NONFOLDERS = 0x40,
	SHCONTF_INCLUDEHIDDEN = 0x80,
	SHCONTF_INIT_ON_FIRST_NEXT = 0x100,
	SHCONTF_NETPRINTERSRCH = 0x200,
	SHCONTF_SHAREABLE = 0x400,
	SHCONTF_STORAGE = 0x800,
	SHCONTF_NAVIGATION_ENUM = 0x1000,
	SHCONTF_FASTITEMS = 0x2000,
	SHCONTF_FLATLIST = 0x4000,
	SHCONTF_ENABLE_ASYNC = 0x8000,
	SHCONTF_INCLUDESUPERHIDDEN = 0x10000
};
typedef DWORD SHCONTF;

typedef struct IShellItemFilterVtbl
{
	HRESULT (*QueryInterface)(IShellItemFilter* This, REFIID riid, void** ppvObject);
	ULONG (*AddRef)(IShellItemFilter* This);
	ULONG (*Release)(IShellItemFilter* This);
	HRESULT (*IncludeItem)(IShellItemFilter* This, IShellItem* psi);
	HRESULT (*GetEnumFlagsForItem)(IShellItemFilter* This, IShellItem* psi, SHCONTF* pgrfFlags);
} IShellItemFilterVtbl;

struct IShellItemFilter
{
	const IShellItemFilterVtbl* lpVtbl;
};

enum _FILEOPENDIALOGOPTIONS
{
	FOS_OVERWRITEPROMPT = 0x2,
	FOS_STRICTFILETYPES = 0x4,
	FOS_NOCHANGEDIR = 0x8,
	FOS_PICKFOLDERS = 0x20,
	FOS_FORCEFILESYSTEM = 0x40,
	FOS_ALLNONSTORAGEITEMS = 0x80,
	FOS_NOVALIDATE = 0x100,
	FOS_ALLOWMULTISELECT = 0x200,
	FOS_PATHMUSTEXIST = 0x800,
	FOS_FILEMUSTEXIST = 0x1000,
	FOS_CREATEPROMPT = 0x2000,
	FOS_SHAREAWARE = 0x4000,
	FOS_NOREADONLYRETURN = 0x8000,
	FOS_NOTESTFILECREATE = 0x10000,
	FOS_HIDEMRUPLACES = 0x20000,
	FOS_HIDEPINNEDPLACES = 0x40000,
	FOS_NODEREFERENCELINKS = 0x100000,
	FOS_OKBUTTONNEEDSINTERACTION = 0x200000,
	FOS_DONTADDTORECENT = 0x2000000,
	FOS_FORCESHOWHIDDEN = 0x10000000,
	FOS_DEFAULTNOMINIMODE = 0x20000000,
	FOS_FORCEPREVIEWPANEON = 0x40000000,
	FOS_SUPPORTSTREAMABLEITEMS = 0x80000000
};
typedef DWORD FILEOPENDIALOGOPTIONS;

typedef enum FDE_OVERWRITE_RESPONSE
{
	FDEOR_DEFAULT = 0,
	FDEOR_ACCEPT = 1,
	FDEOR_REFUSE = 2
} FDE_OVERWRITE_RESPONSE;

typedef enum FDE_SHAREVIOLATION_RESPONSE
{
	FDESVR_DEFAULT = 0,
	FDESVR_ACCEPT = 1,
	FDESVR_REFUSE = 2
} FDE_SHAREVIOLATION_RESPONSE;

typedef enum FDAP
{
	FDAP_BOTTOM = 0,
	FDAP_TOP = 1
} FDAP;

typedef struct IFileDialogVtbl
{
    HRESULT (*QueryInterface)(IFileDialog* This, REFIID riid, void** ppvObject);
    ULONG (*AddRef)(IFileDialog* This);
    ULONG (*Release)(IFileDialog* This);
    HRESULT (*Show)(IFileDialog* This, HWND hwndOwner);
    HRESULT (*SetFileTypes)(IFileDialog* This, UINT cFileTypes, const COMDLG_FILTERSPEC* rgFilterSpec);
    HRESULT (*SetFileTypeIndex)(IFileDialog* This, UINT iFileType);
    HRESULT (*GetFileTypeIndex)(IFileDialog* This, UINT* piFileType);
    HRESULT (*Advise)(IFileDialog* This, IFileDialogEvents* pfde, DWORD* pdwCookie);
    HRESULT (*Unadvise)(IFileDialog* This, DWORD dwCookie);
    HRESULT (*SetOptions)(IFileDialog* This, FILEOPENDIALOGOPTIONS fos);
    HRESULT (*GetOptions)(IFileDialog* This, FILEOPENDIALOGOPTIONS* pfos);
    HRESULT (*SetDefaultFolder)(IFileDialog* This, IShellItem* psi);
    HRESULT (*SetFolder)(IFileDialog* This, IShellItem* psi);
    HRESULT (*GetFolder)(IFileDialog* This, IShellItem** ppsi);
    HRESULT (*GetCurrentSelection)(IFileDialog* This, IShellItem** ppsi);
    HRESULT (*SetFileName)(IFileDialog* This, LPCWSTR pszName);
	HRESULT (*GetFileName)(IFileDialog* This, LPWSTR* pszName);
	HRESULT (*SetTitle)(IFileDialog* This, LPCWSTR pszTitle);
	HRESULT (*SetOkButtonLabel)(IFileDialog* This, LPCWSTR pszText);
	HRESULT (*SetFileNameLabel)(IFileDialog* This, LPCWSTR pszLabel);
	HRESULT (*GetResult)(IFileDialog* This, IShellItem** ppsi);
	HRESULT (*AddPlace)(IFileDialog* This, IShellItem* psi, FDAP fdap);
	HRESULT (*SetDefaultExtension)(IFileDialog* This, LPCWSTR pszDefaultExtension);
	HRESULT (*Close)(IFileDialog* This, HRESULT hr);
	HRESULT (*SetClientGuid)(IFileDialog* This, REFGUID guid);
	HRESULT (*ClearClientData)(IFileDialog* This);
	HRESULT (*SetFilter)(IFileDialog* This, IShellItemFilter* pFilter);
} IFileDialogVtbl;

struct IFileDialog
{
    const IFileDialogVtbl* lpVtbl;
};

typedef struct IFileDialogEventsVtbl {
	HRESULT (*QueryInterface)(IFileDialogEvents* This, REFIID riid, void** ppvObject);
	ULONG (*AddRef)(IFileDialogEvents* This);
	ULONG (*Release)(IFileDialogEvents* This);
	HRESULT (*OnFileOk)(IFileDialogEvents* This, IFileDialog* pfd);
	HRESULT (*OnFolderChanging)(IFileDialogEvents* This, IFileDialog* pfd, IShellItem* psiFolder);
	HRESULT (*OnFolderChange)(IFileDialogEvents* This, IFileDialog* pfd);
	HRESULT (*OnSelectionChange)(IFileDialogEvents* This, IFileDialog* pfd);
	HRESULT (*OnShareViolation)(IFileDialogEvents* This, IFileDialog* pfd, IShellItem* psi, FDE_SHAREVIOLATION_RESPONSE* pResponse);
	HRESULT (*OnTypeChange)(IFileDialogEvents* This, IFileDialog* pfd);
	HRESULT (*OnOverwrite)(IFileDialogEvents* This, IFileDialog* pfd, IShellItem* psi, FDE_OVERWRITE_RESPONSE* pResponse);
} IFileDialogEventsVtbl;

struct IFileDialogEvents {
	const IFileDialogEventsVtbl *lpVtbl;
};

typedef struct IFileOperationProgressSinkVtbl
{
	HRESULT (*QueryInterface)(IFileOperationProgressSink* This, REFIID riid, void** ppvObject);
	ULONG (*AddRef)(IFileOperationProgressSink* This);
	ULONG (*Release)(IFileOperationProgressSink* This);
	HRESULT (*StartOperations)(IFileOperationProgressSink* This);
	HRESULT (*FinishOperations)(IFileOperationProgressSink* This, HRESULT hrResult);
	HRESULT (*PreRenameItem)(IFileOperationProgressSink* This, DWORD dwFlags, IShellItem* psiItem, LPCWSTR pszNewName);
	HRESULT (*PostRenameItem)(IFileOperationProgressSink* This, DWORD dwFlags, IShellItem* psiItem, LPCWSTR pszNewName, HRESULT hrRename, IShellItem* psiNewlyCreated);
	HRESULT (*PreMoveItem)(IFileOperationProgressSink* This, DWORD dwFlags, IShellItem* psiItem, IShellItem* psiDestinationFolder, LPCWSTR pszNewName);
	HRESULT (*PostMoveItem)(IFileOperationProgressSink* This, DWORD dwFlags, IShellItem* psiItem, IShellItem* psiDestinationFolder, LPCWSTR pszNewName, HRESULT hrMove, IShellItem* psiNewlyCreated);
	HRESULT (*PreCopyItem)(IFileOperationProgressSink* This, DWORD dwFlags, IShellItem* psiItem, IShellItem* psiDestinationFolder, LPCWSTR pszNewName);
	HRESULT (*PostCopyItem)(IFileOperationProgressSink* This, DWORD dwFlags, IShellItem* psiItem, IShellItem* psiDestinationFolder, LPCWSTR pszNewName, HRESULT hrCopy, IShellItem* psiNewlyCreated);
	HRESULT (*PreDeleteItem)(IFileOperationProgressSink* This, DWORD dwFlags, IShellItem* psiItem);
	HRESULT (*PostDeleteItem)(IFileOperationProgressSink* This, DWORD dwFlags, IShellItem* psiItem, HRESULT hrDelete, IShellItem* psiNewlyCreated);
	HRESULT (*PreNewItem)(IFileOperationProgressSink* This, DWORD dwFlags, IShellItem* psiDestinationFolder, LPCWSTR pszNewName);
	HRESULT (*PostNewItem)(IFileOperationProgressSink* This, DWORD dwFlags, IShellItem* psiDestinationFolder, LPCWSTR pszNewName, LPCWSTR pszTemplateName, DWORD dwFileAttributes, HRESULT hrNew, IShellItem* psiNewItem);
	HRESULT (*UpdateProgress)(IFileOperationProgressSink* This, UINT iWorkTotal, UINT iWorkSoFar);
	HRESULT (*ResetTimer)(IFileOperationProgressSink* This);
	HRESULT (*PauseTimer)(IFileOperationProgressSink* This);
	HRESULT (*ResumeTimer)(IFileOperationProgressSink* This);
} IFileOperationProgressSinkVtbl;

struct IFileOperationProgressSink
{
    const IFileOperationProgressSinkVtbl* lpVtbl;
};

EXTERN_C const IID IID_IFileSaveDialog;

typedef struct IFileSaveDialogVtbl {
	HRESULT (*QueryInterface)(IFileSaveDialog* This, REFIID riid, void **ppvObject);
	ULONG (*AddRef)(IFileSaveDialog* This);
	ULONG (*Release)(IFileSaveDialog* This);
	HRESULT (*Show)(IFileSaveDialog* This, HWND hwndOwner);
	HRESULT (*SetFileTypes)(IFileSaveDialog* This, UINT cFileTypes, const COMDLG_FILTERSPEC *rgFilterSpec);
	HRESULT (*SetFileTypeIndex)(IFileSaveDialog* This, UINT iFileType);
	HRESULT (*GetFileTypeIndex)(IFileSaveDialog* This, UINT* piFileType);
	HRESULT (*Advise)(IFileSaveDialog* This, IFileDialogEvents* pfde, DWORD* pdwCookie);
	HRESULT (*Unadvise)(IFileSaveDialog* This, DWORD dwCookie);
	HRESULT (*SetOptions)(IFileSaveDialog* This, FILEOPENDIALOGOPTIONS fos);
	HRESULT (*GetOptions)(IFileSaveDialog* This, FILEOPENDIALOGOPTIONS* pfos);
	HRESULT (*SetDefaultFolder)(IFileSaveDialog* This, IShellItem* psi);
	HRESULT (*SetFolder)(IFileSaveDialog* This, IShellItem* psi);
	HRESULT (*GetFolder)(IFileSaveDialog* This, IShellItem** ppsi);
	HRESULT (*GetCurrentSelection)(IFileSaveDialog* This, IShellItem** ppsi);
	HRESULT (*SetFileName)(IFileSaveDialog* This, LPCWSTR pszName);
	HRESULT (*GetFileName)(IFileSaveDialog* This, LPWSTR *pszName);
	HRESULT (*SetTitle)(IFileSaveDialog* This, LPCWSTR pszTitle);
	HRESULT (*SetOkButtonLabel)(IFileSaveDialog* This, LPCWSTR pszText);
	HRESULT (*SetFileNameLabel)(IFileSaveDialog* This, LPCWSTR pszLabel);
	HRESULT (*GetResult)(IFileSaveDialog* This, IShellItem** ppsi);
	HRESULT (*AddPlace)(IFileSaveDialog* This, IShellItem* psi, FDAP fdap);
	HRESULT (*SetDefaultExtension)(IFileSaveDialog* This, LPCWSTR pszDefaultExtension);
	HRESULT (*Close)(IFileSaveDialog* This, HRESULT hr);
	HRESULT (*SetClientGuid)(IFileSaveDialog* This, REFGUID guid);
	HRESULT (*ClearClientData)(IFileSaveDialog* This);
	HRESULT (*SetFilter)(IFileSaveDialog* This, IShellItemFilter* pFilter);
	HRESULT (*SetSaveAsItem)(IFileSaveDialog* This, IShellItem* psi);
	HRESULT (*SetProperties)(IFileSaveDialog* This, IPropertyStore* pStore);
	HRESULT (*SetCollectedProperties)(IFileSaveDialog* This, IPropertyDescriptionList* pList, BOOL fAppendDefault);
	HRESULT (*GetProperties)(IFileSaveDialog* This, IPropertyStore** ppStore);
	HRESULT (*ApplyProperties)(IFileSaveDialog* This, IShellItem* psi, IPropertyStore* pStore, HWND hwnd, IFileOperationProgressSink* pSink);
} IFileSaveDialogVtbl;

struct IFileSaveDialog {
	const IFileSaveDialogVtbl* lpVtbl;
};

typedef struct IFileOpenDialogVtbl
{
	HRESULT(*QueryInterface)(IFileOpenDialog* This, REFIID riid, void** ppvObject);
	ULONG(*AddRef)(IFileOpenDialog* This);
	ULONG(*Release)(IFileOpenDialog* This);
	HRESULT(*Show)(IFileOpenDialog* This, HWND hwndOwner);
	HRESULT(*SetFileTypes)(IFileOpenDialog* This, UINT cFileTypes, const COMDLG_FILTERSPEC* rgFilterSpec);
	HRESULT(*SetFileTypeIndex)(IFileOpenDialog* This, UINT iFileType);
	HRESULT(*GetFileTypeIndex)(IFileOpenDialog* This, UINT* piFileType);
	HRESULT(*Advise)(IFileOpenDialog* This, IFileDialogEvents* pfde, DWORD* pdwCookie);
	HRESULT(*Unadvise)(IFileOpenDialog* This, DWORD dwCookie);
	HRESULT(*SetOptions)(IFileOpenDialog* This, FILEOPENDIALOGOPTIONS fos);
	HRESULT(*GetOptions)(IFileOpenDialog* This, FILEOPENDIALOGOPTIONS* pfos);
	HRESULT(*SetDefaultFolder)(IFileOpenDialog* This, IShellItem* psi);
	HRESULT(*SetFolder)(IFileOpenDialog* This, IShellItem* psi);
	HRESULT(*GetFolder)(IFileOpenDialog* This, IShellItem** ppsi);
	HRESULT(*GetCurrentSelection)(IFileOpenDialog* This, IShellItem** ppsi);
	HRESULT(*SetFileName)(IFileOpenDialog* This, LPCWSTR pszName);
	HRESULT(*GetFileName)(IFileOpenDialog* This, LPWSTR* pszName);
	HRESULT(*SetTitle)(IFileOpenDialog* This, LPCWSTR pszTitle);
	HRESULT(*SetOkButtonLabel)(IFileOpenDialog* This, LPCWSTR pszText);
	HRESULT(*SetFileNameLabel)(IFileOpenDialog* This, LPCWSTR pszLabel);
	HRESULT(*GetResult)(IFileOpenDialog* This, IShellItem** ppsi);
	HRESULT(*AddPlace)(IFileOpenDialog* This, IShellItem* psi, FDAP fdap);
	HRESULT(*SetDefaultExtension)(IFileOpenDialog* This, LPCWSTR pszDefaultExtension);
	HRESULT(*Close)(IFileOpenDialog* This, HRESULT hr);
	HRESULT(*SetClientGuid)(IFileOpenDialog* This, REFGUID guid);
	HRESULT(*ClearClientData)(IFileOpenDialog* This);
	HRESULT(*SetFilter)(IFileOpenDialog* This, IShellItemFilter* pFilter);
	HRESULT(*GetResults)(IFileOpenDialog* This, IShellItemArray** ppenum);
	HRESULT(*GetSelectedItems)(IFileOpenDialog* This, IShellItemArray** ppsai);
} IFileOpenDialogVtbl;

struct IFileOpenDialog
{
	const IFileOpenDialogVtbl* lpVtbl;
};

EXTERN_C const CLSID CLSID_FileSaveDialog;

HRESULT CoInitializeEx(LPVOID pvReserved, DWORD dwCoInit);
void CoUninitialize(void);

HRESULT CoCreateInstance(REFCLSID rclsid, LPUNKNOWN pUnkOuter, DWORD dwClsContext, REFIID riid, LPVOID* ppv);

void CoTaskMemFree(LPVOID pv);

#endif // OBJBASE_H
