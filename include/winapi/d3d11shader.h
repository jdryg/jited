//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) Microsoft Corporation.  All rights reserved.
//
//  File:       D3D11Shader.h
//  Content:    D3D11 Shader Types and APIs
//
//////////////////////////////////////////////////////////////////////////////

#ifndef __D3D11SHADER_H__
#define __D3D11SHADER_H__

#include "guiddef.h"
#include "unknwn.h"
#include "d3dcommon.h"

typedef enum D3D11_SHADER_VERSION_TYPE
{
	D3D11_SHVER_PIXEL_SHADER    = 0,
	D3D11_SHVER_VERTEX_SHADER   = 1,
	D3D11_SHVER_GEOMETRY_SHADER = 2,
	
	// D3D11 Shaders
	D3D11_SHVER_HULL_SHADER     = 3,
	D3D11_SHVER_DOMAIN_SHADER   = 4,
	D3D11_SHVER_COMPUTE_SHADER  = 5,

	D3D11_SHVER_RESERVED0       = 0xFFF0,
} D3D11_SHADER_VERSION_TYPE;

#define D3D11_SHVER_GET_TYPE(_Version)  (((_Version) >> 16) & 0xffff)
#define D3D11_SHVER_GET_MAJOR(_Version) (((_Version) >> 4) & 0xf)
#define D3D11_SHVER_GET_MINOR(_Version) (((_Version) >> 0) & 0xf)

// Slot ID for library function return
#define D3D_RETURN_PARAMETER_INDEX (-1)

typedef D3D_RESOURCE_RETURN_TYPE D3D11_RESOURCE_RETURN_TYPE;

typedef D3D_CBUFFER_TYPE D3D11_CBUFFER_TYPE;

typedef struct _D3D11_SIGNATURE_PARAMETER_DESC
{
	LPCSTR                      SemanticName;   // Name of the semantic
	UINT                        SemanticIndex;  // Index of the semantic
	UINT                        Register;       // Number of member variables
	D3D_NAME                    SystemValueType;// A predefined system value, or D3D_NAME_UNDEFINED if not applicable
	D3D_REGISTER_COMPONENT_TYPE ComponentType;  // Scalar type (e.g. uint, float, etc.)
	BYTE                        Mask;           // Mask to indicate which components of the register
												// are used (combination of D3D10_COMPONENT_MASK values)
	BYTE                        ReadWriteMask;  // Mask to indicate whether a given component is 
												// never written (if this is an output signature) or
												// always read (if this is an input signature).
												// (combination of D3D_MASK_* values)
	UINT                        Stream;         // Stream index
	D3D_MIN_PRECISION           MinPrecision;   // Minimum desired interpolation precision
} D3D11_SIGNATURE_PARAMETER_DESC;

typedef struct _D3D11_SHADER_BUFFER_DESC
{
	LPCSTR                  Name;           // Name of the constant buffer
	D3D_CBUFFER_TYPE        Type;           // Indicates type of buffer content
	UINT                    Variables;      // Number of member variables
	UINT                    Size;           // Size of CB (in bytes)
	UINT                    uFlags;         // Buffer description flags
} D3D11_SHADER_BUFFER_DESC;

typedef struct _D3D11_SHADER_VARIABLE_DESC
{
	LPCSTR                  Name;           // Name of the variable
	UINT                    StartOffset;    // Offset in constant buffer's backing store
	UINT                    Size;           // Size of variable (in bytes)
	UINT                    uFlags;         // Variable flags
	LPVOID                  DefaultValue;   // Raw pointer to default value
	UINT                    StartTexture;   // First texture index (or -1 if no textures used)
	UINT                    TextureSize;    // Number of texture slots possibly used.
	UINT                    StartSampler;   // First sampler index (or -1 if no textures used)
	UINT                    SamplerSize;    // Number of sampler slots possibly used.
} D3D11_SHADER_VARIABLE_DESC;

typedef struct _D3D11_SHADER_TYPE_DESC
{
	D3D_SHADER_VARIABLE_CLASS   Class;          // Variable class (e.g. object, matrix, etc.)
	D3D_SHADER_VARIABLE_TYPE    Type;           // Variable type (e.g. float, sampler, etc.)
	UINT                        Rows;           // Number of rows (for matrices, 1 for other numeric, 0 if not applicable)
	UINT                        Columns;        // Number of columns (for vectors & matrices, 1 for other numeric, 0 if not applicable)
	UINT                        Elements;       // Number of elements (0 if not an array)
	UINT                        Members;        // Number of members (0 if not a structure)
	UINT                        Offset;         // Offset from the start of structure (0 if not a structure member)
	LPCSTR                      Name;           // Name of type, can be NULL
} D3D11_SHADER_TYPE_DESC;

typedef D3D_TESSELLATOR_DOMAIN D3D11_TESSELLATOR_DOMAIN;

typedef D3D_TESSELLATOR_PARTITIONING D3D11_TESSELLATOR_PARTITIONING;

typedef D3D_TESSELLATOR_OUTPUT_PRIMITIVE D3D11_TESSELLATOR_OUTPUT_PRIMITIVE;

typedef struct _D3D11_SHADER_DESC
{
	UINT                    Version;                     // Shader version
	LPCSTR                  Creator;                     // Creator string
	UINT                    Flags;                       // Shader compilation/parse flags
	
	UINT                    ConstantBuffers;             // Number of constant buffers
	UINT                    BoundResources;              // Number of bound resources
	UINT                    InputParameters;             // Number of parameters in the input signature
	UINT                    OutputParameters;            // Number of parameters in the output signature

	UINT                    InstructionCount;            // Number of emitted instructions
	UINT                    TempRegisterCount;           // Number of temporary registers used 
	UINT                    TempArrayCount;              // Number of temporary arrays used
	UINT                    DefCount;                    // Number of constant defines 
	UINT                    DclCount;                    // Number of declarations (input + output)
	UINT                    TextureNormalInstructions;   // Number of non-categorized texture instructions
	UINT                    TextureLoadInstructions;     // Number of texture load instructions
	UINT                    TextureCompInstructions;     // Number of texture comparison instructions
	UINT                    TextureBiasInstructions;     // Number of texture bias instructions
	UINT                    TextureGradientInstructions; // Number of texture gradient instructions
	UINT                    FloatInstructionCount;       // Number of floating point arithmetic instructions used
	UINT                    IntInstructionCount;         // Number of signed integer arithmetic instructions used
	UINT                    UintInstructionCount;        // Number of unsigned integer arithmetic instructions used
	UINT                    StaticFlowControlCount;      // Number of static flow control instructions used
	UINT                    DynamicFlowControlCount;     // Number of dynamic flow control instructions used
	UINT                    MacroInstructionCount;       // Number of macro instructions used
	UINT                    ArrayInstructionCount;       // Number of array instructions used
	UINT                    CutInstructionCount;         // Number of cut instructions used
	UINT                    EmitInstructionCount;        // Number of emit instructions used
	D3D_PRIMITIVE_TOPOLOGY  GSOutputTopology;            // Geometry shader output topology
	UINT                    GSMaxOutputVertexCount;      // Geometry shader maximum output vertex count
	D3D_PRIMITIVE           InputPrimitive;              // GS/HS input primitive
	UINT                    PatchConstantParameters;     // Number of parameters in the patch constant signature
	UINT                    cGSInstanceCount;            // Number of Geometry shader instances
	UINT                    cControlPoints;              // Number of control points in the HS->DS stage
	D3D_TESSELLATOR_OUTPUT_PRIMITIVE HSOutputPrimitive;  // Primitive output by the tessellator
	D3D_TESSELLATOR_PARTITIONING HSPartitioning;         // Partitioning mode of the tessellator
	D3D_TESSELLATOR_DOMAIN  TessellatorDomain;           // Domain of the tessellator (quad, tri, isoline)
	// instruction counts
	UINT cBarrierInstructions;                           // Number of barrier instructions in a compute shader
	UINT cInterlockedInstructions;                       // Number of interlocked instructions
	UINT cTextureStoreInstructions;                      // Number of texture writes
} D3D11_SHADER_DESC;

typedef struct _D3D11_SHADER_INPUT_BIND_DESC
{
	LPCSTR                      Name;           // Name of the resource
	D3D_SHADER_INPUT_TYPE       Type;           // Type of resource (e.g. texture, cbuffer, etc.)
	UINT                        BindPoint;      // Starting bind point
	UINT                        BindCount;      // Number of contiguous bind points (for arrays)
	
	UINT                        uFlags;         // Input binding flags
	D3D_RESOURCE_RETURN_TYPE    ReturnType;     // Return type (if texture)
	D3D_SRV_DIMENSION           Dimension;      // Dimension (if texture)
	UINT                        NumSamples;     // Number of samples (0 if not MS texture)
} D3D11_SHADER_INPUT_BIND_DESC;

#define D3D_SHADER_REQUIRES_DOUBLES                         0x00000001
#define D3D_SHADER_REQUIRES_EARLY_DEPTH_STENCIL             0x00000002
#define D3D_SHADER_REQUIRES_UAVS_AT_EVERY_STAGE             0x00000004
#define D3D_SHADER_REQUIRES_64_UAVS                         0x00000008
#define D3D_SHADER_REQUIRES_MINIMUM_PRECISION               0x00000010
#define D3D_SHADER_REQUIRES_11_1_DOUBLE_EXTENSIONS          0x00000020
#define D3D_SHADER_REQUIRES_11_1_SHADER_EXTENSIONS          0x00000040
#define D3D_SHADER_REQUIRES_LEVEL_9_COMPARISON_FILTERING    0x00000080
#define D3D_SHADER_REQUIRES_TILED_RESOURCES                 0x00000100


typedef struct _D3D11_LIBRARY_DESC
{
	LPCSTR    Creator;           // The name of the originator of the library.
	UINT      Flags;             // Compilation flags.
	UINT      FunctionCount;     // Number of functions exported from the library.
} D3D11_LIBRARY_DESC;

typedef struct _D3D11_FUNCTION_DESC
{
	UINT                    Version;                     // Shader version
	LPCSTR                  Creator;                     // Creator string
	UINT                    Flags;                       // Shader compilation/parse flags
	
	UINT                    ConstantBuffers;             // Number of constant buffers
	UINT                    BoundResources;              // Number of bound resources

	UINT                    InstructionCount;            // Number of emitted instructions
	UINT                    TempRegisterCount;           // Number of temporary registers used 
	UINT                    TempArrayCount;              // Number of temporary arrays used
	UINT                    DefCount;                    // Number of constant defines 
	UINT                    DclCount;                    // Number of declarations (input + output)
	UINT                    TextureNormalInstructions;   // Number of non-categorized texture instructions
	UINT                    TextureLoadInstructions;     // Number of texture load instructions
	UINT                    TextureCompInstructions;     // Number of texture comparison instructions
	UINT                    TextureBiasInstructions;     // Number of texture bias instructions
	UINT                    TextureGradientInstructions; // Number of texture gradient instructions
	UINT                    FloatInstructionCount;       // Number of floating point arithmetic instructions used
	UINT                    IntInstructionCount;         // Number of signed integer arithmetic instructions used
	UINT                    UintInstructionCount;        // Number of unsigned integer arithmetic instructions used
	UINT                    StaticFlowControlCount;      // Number of static flow control instructions used
	UINT                    DynamicFlowControlCount;     // Number of dynamic flow control instructions used
	UINT                    MacroInstructionCount;       // Number of macro instructions used
	UINT                    ArrayInstructionCount;       // Number of array instructions used
	UINT                    MovInstructionCount;         // Number of mov instructions used
	UINT                    MovcInstructionCount;        // Number of movc instructions used
	UINT                    ConversionInstructionCount;  // Number of type conversion instructions used
	UINT                    BitwiseInstructionCount;     // Number of bitwise arithmetic instructions used
	D3D_FEATURE_LEVEL       MinFeatureLevel;             // Min target of the function byte code
	UINT64                  RequiredFeatureFlags;        // Required feature flags

	LPCSTR                  Name;                        // Function name
	INT                     FunctionParameterCount;      // Number of logical parameters in the function signature (not including return)
	BOOL                    HasReturn;                   // TRUE, if function returns a value, false - it is a subroutine
	BOOL                    Has10Level9VertexShader;     // TRUE, if there is a 10L9 VS blob
	BOOL                    Has10Level9PixelShader;      // TRUE, if there is a 10L9 PS blob
} D3D11_FUNCTION_DESC;

typedef struct _D3D11_PARAMETER_DESC
{
	LPCSTR                      Name;               // Parameter name.
	LPCSTR                      SemanticName;       // Parameter semantic name (+index).
	D3D_SHADER_VARIABLE_TYPE    Type;               // Element type.
	D3D_SHADER_VARIABLE_CLASS   Class;              // Scalar/Vector/Matrix.
	UINT                        Rows;               // Rows are for matrix parameters.
	UINT                        Columns;            // Components or Columns in matrix.
	D3D_INTERPOLATION_MODE      InterpolationMode;  // Interpolation mode.
	D3D_PARAMETER_FLAGS         Flags;              // Parameter modifiers.

	UINT                        FirstInRegister;    // The first input register for this parameter.
	UINT                        FirstInComponent;   // The first input register component for this parameter.
	UINT                        FirstOutRegister;   // The first output register for this parameter.
	UINT                        FirstOutComponent;  // The first output register component for this parameter.
} D3D11_PARAMETER_DESC;


//////////////////////////////////////////////////////////////////////////////
// Interfaces ////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

typedef struct ID3D11ShaderReflectionType ID3D11ShaderReflectionType;
typedef struct ID3D11ShaderReflectionType *LPD3D11SHADERREFLECTIONTYPE;

typedef struct ID3D11ShaderReflectionVariable ID3D11ShaderReflectionVariable;
typedef struct ID3D11ShaderReflectionVariable *LPD3D11SHADERREFLECTIONVARIABLE;

typedef struct ID3D11ShaderReflectionConstantBuffer ID3D11ShaderReflectionConstantBuffer;
typedef struct ID3D11ShaderReflectionConstantBuffer *LPD3D11SHADERREFLECTIONCONSTANTBUFFER;

typedef struct ID3D11ShaderReflection ID3D11ShaderReflection;
typedef struct ID3D11ShaderReflection *LPD3D11SHADERREFLECTION;

typedef struct ID3D11LibraryReflection ID3D11LibraryReflection;
typedef struct ID3D11LibraryReflection *LPD3D11LIBRARYREFLECTION;

typedef struct ID3D11FunctionReflection ID3D11FunctionReflection;
typedef struct ID3D11FunctionReflection *LPD3D11FUNCTIONREFLECTION;

typedef struct ID3D11FunctionParameterReflection ID3D11FunctionParameterReflection;
typedef struct ID3D11FunctionParameterReflection *LPD3D11FUNCTIONPARAMETERREFLECTION;

typedef struct ID3D11ModuleInstance ID3D11ModuleInstance;
typedef struct ID3D11Module ID3D11Module;
typedef struct ID3D11Linker ID3D11Linker;
typedef struct ID3D11LinkingNode ID3D11LinkingNode;
typedef struct ID3D11FunctionLinkingGraph ID3D11FunctionLinkingGraph;

typedef struct ID3D11ShaderReflectionTypeVtbl
{
	HRESULT                     (*GetDesc)(ID3D11ShaderReflectionType* This, D3D11_SHADER_TYPE_DESC* pDesc);
	ID3D11ShaderReflectionType* (*GetMemberTypeByIndex)(ID3D11ShaderReflectionType* This, UINT Index);
	ID3D11ShaderReflectionType* (*GetMemberTypeByName)(ID3D11ShaderReflectionType* This, LPCSTR Name);
	LPCSTR                      (*GetMemberTypeName)(ID3D11ShaderReflectionType* This, UINT Index);
	HRESULT                     (*IsEqual)(ID3D11ShaderReflectionType* This, ID3D11ShaderReflectionType* pType);
	ID3D11ShaderReflectionType* (*GetSubType)(ID3D11ShaderReflectionType* This);
	ID3D11ShaderReflectionType* (*GetBaseClass)(ID3D11ShaderReflectionType* This);
	UINT                        (*GetNumInterfaces)(ID3D11ShaderReflectionType* This);
	ID3D11ShaderReflectionType* (*GetInterfaceByIndex)(ID3D11ShaderReflectionType* This, UINT uIndex);
	HRESULT                     (*IsOfType)(ID3D11ShaderReflectionType* This, ID3D11ShaderReflectionType* pType);
	HRESULT                     (*ImplementsInterface)(ID3D11ShaderReflectionType* This, ID3D11ShaderReflectionType* pBase);
} ID3D11ShaderReflectionTypeVtbl;

struct ID3D11ShaderReflectionType
{
	const ID3D11ShaderReflectionTypeVtbl* lpVtbl;
};

typedef struct ID3D11ShaderReflectionVariableVtbl
{
	HRESULT                               (*GetDesc)(ID3D11ShaderReflectionVariable* This, D3D11_SHADER_VARIABLE_DESC *pDesc);
	ID3D11ShaderReflectionType*           (*GetType)(ID3D11ShaderReflectionVariable* This);
	ID3D11ShaderReflectionConstantBuffer* (*GetBuffer)(ID3D11ShaderReflectionVariable* This);
	UINT                                  (*GetInterfaceSlot)(ID3D11ShaderReflectionVariable* This, UINT uArrayIndex);
} ID3D11ShaderReflectionVariableVtbl;

struct ID3D11ShaderReflectionVariable
{
	const ID3D11ShaderReflectionVariableVtbl* lpVtbl;
};

typedef struct ID3D11ShaderReflectionConstantBufferVtbl
{
	HRESULT                         (*GetDesc)(ID3D11ShaderReflectionConstantBuffer* This, D3D11_SHADER_BUFFER_DESC *pDesc);
	ID3D11ShaderReflectionVariable* (*GetVariableByIndex)(ID3D11ShaderReflectionConstantBuffer* This, UINT Index);
	ID3D11ShaderReflectionVariable* (*GetVariableByName)(ID3D11ShaderReflectionConstantBuffer* This, LPCSTR Name);
} ID3D11ShaderReflectionConstantBufferVtbl;

struct ID3D11ShaderReflectionConstantBuffer
{
	const ID3D11ShaderReflectionConstantBufferVtbl* lpVtbl;
};

// The ID3D11ShaderReflection IID may change from SDK version to SDK version
// if the reflection API changes.  This prevents new code with the new API
// from working with an old binary.  Recompiling with the new header
// will pick up the new IID.

typedef struct ID3D11ShaderReflectionVtbl
{
	HRESULT (*QueryInterface)(ID3D11ShaderReflection* This, REFIID iid, LPVOID *ppv);
	ULONG (*AddRef)(ID3D11ShaderReflection* This);
	ULONG (*Release)(ID3D11ShaderReflection* This);
	HRESULT (*GetDesc)(ID3D11ShaderReflection* This, D3D11_SHADER_DESC *pDesc);
	ID3D11ShaderReflectionConstantBuffer* (*GetConstantBufferByIndex)(ID3D11ShaderReflection* This, UINT Index);
	ID3D11ShaderReflectionConstantBuffer* (*GetConstantBufferByName)(ID3D11ShaderReflection* This, LPCSTR Name);
	HRESULT (*GetResourceBindingDesc)(ID3D11ShaderReflection* This, UINT ResourceIndex, D3D11_SHADER_INPUT_BIND_DESC *pDesc);
	HRESULT (*GetInputParameterDesc)(ID3D11ShaderReflection* This, UINT ParameterIndex, D3D11_SIGNATURE_PARAMETER_DESC *pDesc);
	HRESULT (*GetOutputParameterDesc)(ID3D11ShaderReflection* This, UINT ParameterIndex, D3D11_SIGNATURE_PARAMETER_DESC *pDesc);
	HRESULT (*GetPatchConstantParameterDesc)(ID3D11ShaderReflection* This, UINT ParameterIndex, D3D11_SIGNATURE_PARAMETER_DESC *pDesc);
	ID3D11ShaderReflectionVariable* (*GetVariableByName)(ID3D11ShaderReflection* This, LPCSTR Name);
	HRESULT (*GetResourceBindingDescByName)(ID3D11ShaderReflection* This, LPCSTR Name, D3D11_SHADER_INPUT_BIND_DESC *pDesc);
	UINT (*GetMovInstructionCount)(ID3D11ShaderReflection* This);
	UINT (*GetMovcInstructionCount)(ID3D11ShaderReflection* This);
	UINT (*GetConversionInstructionCount)(ID3D11ShaderReflection* This);
	UINT (*GetBitwiseInstructionCount)(ID3D11ShaderReflection* This);
	D3D_PRIMITIVE (*GetGSInputPrimitive)(ID3D11ShaderReflection* This);
	BOOL (*IsSampleFrequencyShader)(ID3D11ShaderReflection* This);
	UINT (*GetNumInterfaceSlots)(ID3D11ShaderReflection* This);
	HRESULT (*GetMinFeatureLevel)(ID3D11ShaderReflection* This, enum D3D_FEATURE_LEVEL* pLevel);
	UINT (*GetThreadGroupSize)(ID3D11ShaderReflection* This, UINT* pSizeX, UINT* pSizeY, UINT* pSizeZ);
	UINT64 (*GetRequiresFlags)(ID3D11ShaderReflection* This);
} ID3D11ShaderReflectionVtbl;

struct ID3D11ShaderReflection
{
	const ID3D11ShaderReflectionVtbl* lpVtbl;
};

typedef struct ID3D11LibraryReflectionVtbl
{
	HRESULT (*QueryInterface)(ID3D11LibraryReflection* This, REFIID iid, LPVOID * ppv);
	ULONG (*AddRef)(ID3D11LibraryReflection* This);
	ULONG (*Release)(ID3D11LibraryReflection* This);
	HRESULT (*GetDesc)(ID3D11LibraryReflection* This, D3D11_LIBRARY_DESC * pDesc);
	ID3D11FunctionReflection* (*GetFunctionByIndex)(ID3D11LibraryReflection* This, INT FunctionIndex);
} ID3D11LibraryReflectionVtbl;

struct ID3D11LibraryReflection
{
	const ID3D11LibraryReflectionVtbl* lpVtbl;
};

typedef struct ID3D11FunctionReflectionVtbl
{
	HRESULT (*GetDesc)(ID3D11FunctionReflection* This, D3D11_FUNCTION_DESC * pDesc);
	ID3D11ShaderReflectionConstantBuffer* (*GetConstantBufferByIndex)(ID3D11FunctionReflection* This, UINT BufferIndex);
	ID3D11ShaderReflectionConstantBuffer* (*GetConstantBufferByName)(ID3D11FunctionReflection* This, LPCSTR Name);
	HRESULT (*GetResourceBindingDesc)(ID3D11FunctionReflection* This, UINT ResourceIndex, D3D11_SHADER_INPUT_BIND_DESC * pDesc);
	ID3D11ShaderReflectionVariable* (*GetVariableByName)(ID3D11FunctionReflection* This, LPCSTR Name);
	HRESULT (*GetResourceBindingDescByName)(ID3D11FunctionReflection* This, LPCSTR Name, D3D11_SHADER_INPUT_BIND_DESC * pDesc);
	// Use D3D_RETURN_PARAMETER_INDEX to get description of the return value.
	ID3D11FunctionParameterReflection* (*GetFunctionParameter)(ID3D11FunctionReflection* This, INT ParameterIndex);
} ID3D11FunctionReflectionVtbl;

struct ID3D11FunctionReflection
{
	const struct ID3D11FunctionReflectionVtbl* lpVtbl;
};

typedef struct ID3D11FunctionParameterReflectionVtbl
{
	HRESULT (*GetDesc)(ID3D11FunctionParameterReflection* This, D3D11_PARAMETER_DESC* pDesc);
} ID3D11FunctionParameterReflectionVtbl;

struct ID3D11FunctionParameterReflection
{
	const ID3D11FunctionParameterReflectionVtbl* lpVtbl;
};

typedef struct ID3D11ModuleInstanceVtbl
{
	HRESULT (*QueryInterface)(ID3D11ModuleInstance* This, REFIID iid, LPVOID * ppv);
	ULONG (*AddRef)(ID3D11ModuleInstance* This);
	ULONG (*Release)(ID3D11ModuleInstance* This);
	HRESULT (*BindConstantBuffer)(ID3D11ModuleInstance* This, UINT uSrcSlot, UINT uDstSlot, UINT cbDstOffset);
	HRESULT (*BindConstantBufferByName)(ID3D11ModuleInstance* This, LPCSTR pName, UINT uDstSlot, UINT cbDstOffset);
	HRESULT (*BindResource)(ID3D11ModuleInstance* This, UINT uSrcSlot, UINT uDstSlot, UINT uCount);
	HRESULT (*BindResourceByName)(ID3D11ModuleInstance* This, LPCSTR pName, UINT uDstSlot, UINT uCount);
	HRESULT (*BindSampler)(ID3D11ModuleInstance* This, UINT uSrcSlot, UINT uDstSlot, UINT uCount);
	HRESULT (*BindSamplerByName)(ID3D11ModuleInstance* This, LPCSTR pName, UINT uDstSlot, UINT uCount);
	HRESULT (*BindUnorderedAccessView)(ID3D11ModuleInstance* This, UINT uSrcSlot, UINT uDstSlot, UINT uCount);
	HRESULT (*BindUnorderedAccessViewByName)(ID3D11ModuleInstance* This, LPCSTR pName, UINT uDstSlot, UINT uCount);
	HRESULT (*BindResourceAsUnorderedAccessView)(ID3D11ModuleInstance* This, UINT uSrcSrvSlot, UINT uDstUavSlot, UINT uCount);
	HRESULT (*BindResourceAsUnorderedAccessViewByName)(ID3D11ModuleInstance* This, LPCSTR pSrvName, UINT uDstUavSlot, UINT uCount);
} ID3D11ModuleInstanceVtbl;

struct ID3D11ModuleInstance
{
	const ID3D11ModuleInstanceVtbl* lpVtbl;
};

typedef struct ID3D11ModuleVtbl
{
	HRESULT (*QueryInterface)(ID3D11Module* This, REFIID iid, LPVOID * ppv);
	ULONG (*AddRef)(ID3D11Module* This);
	ULONG (*Release)(ID3D11Module* This);
	// Create an instance of a module for resource re-binding.
	HRESULT (*CreateInstance)(ID3D11Module* This, LPCSTR pNamespace, struct ID3D11ModuleInstance** ppModuleInstance);
} ID3D11ModuleVtbl;

struct ID3D11Module
{
	const ID3D11ModuleVtbl* lpVtbl;
};

typedef struct ID3D11LinkerVtbl
{
	HRESULT (*QueryInterface)(ID3D11Linker* This, REFIID iid, LPVOID * ppv);
	ULONG (*AddRef)(ID3D11Linker* This);
	ULONG (*Release)(ID3D11Linker* This);

	// Link the shader and produce a shader blob suitable to D3D runtime.
	HRESULT (*Link)(ID3D11Linker* This, struct ID3D11ModuleInstance * pEntry, LPCSTR pEntryName, LPCSTR pTargetName, UINT uFlags, ID3DBlob** ppShaderBlob, ID3DBlob** ppErrorBuffer);

	// Add an instance of a library module to be used for linking.
	HRESULT (*UseLibrary)(ID3D11Linker* This, struct ID3D11ModuleInstance * pLibraryMI);

	// Add a clip plane with the plane coefficients taken from a cbuffer entry for 10L9 shaders.
	HRESULT (*AddClipPlaneFromCBuffer)(ID3D11Linker* This, UINT uCBufferSlot, UINT uCBufferEntry);
} ID3D11LinkerVtbl;

struct ID3D11Linker
{
	const ID3D11LinkerVtbl* lpVtbl;
};

typedef struct ID3D11LinkingNodeVtbl
{
	HRESULT (*QueryInterface)(ID3D11LinkingNode* This, REFIID iid, LPVOID * ppv);
	ULONG (*AddRef)(ID3D11LinkingNode* This);
	ULONG (*Release)(ID3D11LinkingNode* This);
} ID3D11LinkingNodeVtbl;

struct ID3D11LinkingNode
{
	const ID3D11LinkingNodeVtbl* lpVtbl;
};

typedef struct ID3D11FunctionLinkingGraphVtbl
{
	HRESULT (*QueryInterface)(ID3D11FunctionLinkingGraph* This, REFIID iid, LPVOID * ppv);
	ULONG (*AddRef)(ID3D11FunctionLinkingGraph* This);
	ULONG (*Release)(ID3D11FunctionLinkingGraph* This);

	// Create a shader module out of FLG description.
	HRESULT (*CreateModuleInstance)(ID3D11FunctionLinkingGraph* This, struct ID3D11ModuleInstance** ppModuleInstance, ID3DBlob** ppErrorBuffer);
	HRESULT (*SetInputSignature)(ID3D11FunctionLinkingGraph* This, const D3D11_PARAMETER_DESC * pInputParameters, UINT cInputParameters, struct ID3D11LinkingNode ** ppInputNode);
	HRESULT (*SetOutputSignature)(ID3D11FunctionLinkingGraph* This, const D3D11_PARAMETER_DESC * pOutputParameters, UINT cOutputParameters, struct ID3D11LinkingNode ** ppOutputNode);
	HRESULT (*CallFunction)(ID3D11FunctionLinkingGraph* This, LPCSTR pModuleInstanceNamespace, struct ID3D11Module * pModuleWithFunctionPrototype, LPCSTR pFunctionName, struct ID3D11LinkingNode ** ppCallNode);
	HRESULT (*PassValue)(ID3D11FunctionLinkingGraph* This, struct ID3D11LinkingNode * pSrcNode, INT SrcParameterIndex, struct ID3D11LinkingNode * pDstNode, INT DstParameterIndex);
	HRESULT (*PassValueWithSwizzle)(ID3D11FunctionLinkingGraph* This, struct ID3D11LinkingNode * pSrcNode, INT SrcParameterIndex, LPCSTR pSrcSwizzle, struct ID3D11LinkingNode * pDstNode, INT DstParameterIndex, LPCSTR pDstSwizzle);
	HRESULT (*GetLastError)(ID3D11FunctionLinkingGraph* This, ID3DBlob** ppErrorBuffer);
	HRESULT (*GenerateHlsl)(ID3D11FunctionLinkingGraph* This, UINT uFlags, ID3DBlob ** ppBuffer);
} ID3D11FunctionLinkingGraphVtbl;

struct ID3D11FunctionLinkingGraph
{
	const ID3D11FunctionLinkingGraphVtbl* lpVtbl;
};

static const GUID IID_ID3D11ShaderReflectionType           = { 0x6e6ffa6a, 0x9bae, 0x4613, 0xa5, 0x1e, 0x91, 0x65, 0x2d, 0x50, 0x8c, 0x21 };
static const GUID IID_ID3D11ShaderReflectionVariable       = { 0x51f23923, 0xf3e5, 0x4bd1, 0x91, 0xcb, 0x60, 0x61, 0x77, 0xd8, 0xdb, 0x4c };
static const GUID IID_ID3D11ShaderReflectionConstantBuffer = { 0xeb62d63d, 0x93dd, 0x4318, 0x8a, 0xe8, 0xc6, 0xf8, 0x3a, 0xd3, 0x71, 0xb8 };
static const GUID IID_ID3D11ShaderReflection               = { 0x8d536ca1, 0x0cca, 0x4956, 0xa8, 0x37, 0x78, 0x69, 0x63, 0x75, 0x55, 0x84 };
static const GUID IID_ID3D11LibraryReflection              = { 0x54384f1b, 0x5b3e, 0x4bb7, 0xae, 0x01, 0x60, 0xba, 0x30, 0x97, 0xcb, 0xb6 };
static const GUID IID_ID3D11FunctionReflection             = { 0x207bcecb, 0xd683, 0x4a06, 0xa8, 0xa3, 0x9b, 0x14, 0x9b, 0x9f, 0x73, 0xa4 };
static const GUID IID_ID3D11FunctionParameterReflection    = { 0x42757488, 0x334f, 0x47fe, 0x98, 0x2e, 0x1a, 0x65, 0xd0, 0x8c, 0xc4, 0x62 };
static const GUID IID_ID3D11ModuleInstance                 = { 0x469e07f7, 0x045a, 0x48d5, 0xaa, 0x12, 0x68, 0xa4, 0x78, 0xcd, 0xf7, 0x5d };
static const GUID IID_ID3D11Module                         = { 0xcac701ee, 0x80fc, 0x4122, 0x82, 0x42, 0x10, 0xb3, 0x9c, 0x8c, 0xec, 0x34 };
static const GUID IID_ID3D11Linker                         = { 0x59a6cd0e, 0xe10d, 0x4c1f, 0x88, 0xc0, 0x63, 0xab, 0xa1, 0xda, 0xf3, 0x0e };
static const GUID IID_ID3D11LinkingNode                    = { 0xd80dd70c, 0x8d2f, 0x4751, 0x94, 0xa1, 0x03, 0xc7, 0x9b, 0x35, 0x56, 0xdb };
static const GUID IID_ID3D11FunctionLinkingGraph           = { 0x54133220, 0x1ce8, 0x43d3, 0x82, 0x36, 0x98, 0x55, 0xc5, 0xce, 0xec, 0xff };

#endif //__D3D11SHADER_H__
