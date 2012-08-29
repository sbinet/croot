/* @brief a C-API wrapper for (some of) the C++ classes of ROOT
 */

#ifndef CROOT_CROOT_H
#define CROOT_CROOT_H 1

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#if __GNUC__ >= 4
#  define CROOT_HASCLASSVISIBILITY
#endif

#if defined(CROOT_HASCLASSVISIBILITY)
#  define CROOT_IMPORT __attribute__((visibility("default")))
#  define CROOT_EXPORT __attribute__((visibility("default")))
#  define CROOT_LOCAL  __attribute__((visibility("hidden")))
#else
#  define CROOT_IMPORT
#  define CROOT_EXPORT
#  define CROOT_LOCAL
#endif

#define CROOT_API CROOT_EXPORT

#ifdef __cplusplus
extern "C" {
#endif

typedef int CRoot_Bool;

/* Option_t */
typedef const char CRoot_Option;

/* TObject */
typedef void* CRoot_Object;

CROOT_API
const char*
CRoot_Object_ClassName(CRoot_Object self);

CROOT_API
CRoot_Object
CRoot_Object_Clone(CRoot_Object self,
                   const char *newname);

CROOT_API
CRoot_Object
CRoot_Object_FindObject(CRoot_Object self, 
                        const char *name);

CROOT_API
const char*
CRoot_Object_GetName(CRoot_Object self);

CROOT_API
const char*
CRoot_Object_GetTitle(CRoot_Object self);

CROOT_API
CRoot_Bool
CRoot_Object_InheritsFrom(CRoot_Object self, 
                          const char *classname);

CROOT_API
void
CRoot_Object_Print(CRoot_Object self,
                   CRoot_Option *option);


/* TObjArray */
typedef void *CRoot_ObjArray;

/* TBranch */
typedef void *CRoot_Branch;

CROOT_API
char*
CRoot_Branch_GetAddress(CRoot_Branch self);

/* TTree */
typedef void* CRoot_Tree;

CROOT_API
CRoot_Tree
CRoot_Tree_new(const char *name, const char *title, int32_t splitlevel);

CROOT_API
void
CRoot_Tree_delete(CRoot_Tree self);

CROOT_API
CRoot_Branch
CRoot_Tree_Branch(CRoot_Tree self,
                  const char *name, const char *classname,
                  void *addobj, int32_t bufsize, int32_t splitlevel);

CROOT_API
CRoot_Branch
CRoot_Tree_Branch2(CRoot_Tree self,
                   const char *name, void *address, const char *leaflist,
                   int32_t bufsize);

CROOT_API
int
CRoot_Tree_Fill(CRoot_Tree self);

CROOT_API
CRoot_Branch
CRoot_Tree_GetBranch(CRoot_Tree self,
                     const char *name);

CROOT_API
int64_t
CRoot_Tree_GetEntries(CRoot_Tree self);

CROOT_API
int32_t
CRoot_Tree_GetEntry(CRoot_Tree self,
                    int64_t entry, int32_t getall);

CROOT_API
CRoot_ObjArray
CRoot_Tree_GetListOfBranches(CRoot_Tree self);

CROOT_API
CRoot_ObjArray
CRoot_Tree_GetListOfLeaves(CRoot_Tree self);

CROOT_API
int64_t
CRoot_Tree_GetSelectedRows(CRoot_Tree self);

CROOT_API
double*
CRoot_Tree_GetVal(CRoot_Tree self,
                  int32_t i);

CROOT_API
double*
CRoot_Tree_GetV1(CRoot_Tree self);

CROOT_API
double*
CRoot_Tree_GetV2(CRoot_Tree self);

CROOT_API
double*
CRoot_Tree_GetV3(CRoot_Tree self);

CROOT_API
double*
CRoot_Tree_GetV4(CRoot_Tree self);

CROOT_API
double*
CRoot_Tree_GetW(CRoot_Tree self);

CROOT_API
int64_t
CRoot_Tree_LoadTree(CRoot_Tree self,
                    int64_t entry);

CROOT_API
int32_t
CRoot_Tree_MakeClass(CRoot_Tree self,
                     const char *classname, CRoot_Option *option);

CROOT_API
CRoot_Bool
CRoot_Tree_Notify(CRoot_Tree self);

CROOT_API
void
CRoot_Tree_Print(CRoot_Tree self,
                 CRoot_Option *option);

CROOT_API
int64_t
CRoot_Tree_Process(CRoot_Tree self,
                   const char *filename, CRoot_Option *option,
                   int64_t nentries, int64_t firstentry);

CROOT_API
int64_t
CRoot_Tree_Project(CRoot_Tree self,
                   const char *hname, const char *varexp,
                   const char *selection, CRoot_Option *option,
                   int64_t nentries, int64_t firstentry);

CROOT_API
int32_t
CRoot_Tree_SetBranchAddress(CRoot_Tree self,
                            const char *bname, void *addr, CRoot_Branch *ptr);

CROOT_API
void
CRoot_Tree_SetBranchStatus(CRoot_Tree self,
                           const char *bname, CRoot_Bool status, 
                           uint32_t *found);

CROOT_API
int32_t
CRoot_Tree_Write(CRoot_Tree self,
                 const char *name, int32_t option, int32_t bufsize);

/* TChain */
typedef void* CRoot_Chain;

CROOT_API
CRoot_Chain
CRoot_Chain_new(const char *name, const char *title);

CROOT_API
void
CRoot_Chain_delete(CRoot_Chain self);

CROOT_API
int32_t
CRoot_Chain_Add(CRoot_Chain self,
                const char *name, int64_t nentries);

CROOT_API
int32_t
CRoot_Chain_AddFile(CRoot_Chain self,
                    const char *name, int64_t nentries, const char *tname);

CROOT_API
int64_t
CRoot_Chain_GetEntries(CRoot_Chain self);

CROOT_API
int32_t
CRoot_Chain_GetEntry(CRoot_Chain self,
                     int64_t entry, int32_t getall);

/* TFile */
typedef void* CRoot_File;

typedef enum {
    kDefault =0,
    kLocal   =1,
    kNet     =2,
    kWeb     =3,
    kFile    =4
} CRoot_FileType;

CROOT_API
CRoot_File
CRoot_File_Open(const char *name, 
                CRoot_Option *option,
                const char *ftitle,
                int32_t compress,
                int32_t netopt);

CROOT_API
CRoot_Bool
CRoot_File_cd(CRoot_File self, const char *path);

CROOT_API
void
CRoot_File_Close(CRoot_File self, CRoot_Option *option);

CROOT_API
int
CRoot_File_GetFd(CRoot_File self);

CROOT_API
CRoot_Object
CRoot_File_Get(CRoot_File self, const char *namecycle);

CROOT_API
CRoot_Bool
CRoot_File_IsOpen(CRoot_File self);

CROOT_API
CRoot_Bool
CRoot_File_ReadBuffer(CRoot_File self,
                      char *buf, int64_t pos, int32_t len);

CROOT_API
CRoot_Bool
CRoot_File_ReadBuffers(CRoot_File self,
                       char *buf, int64_t *pos, int32_t *len, int32_t nbuf);

CROOT_API
int32_t
CRoot_File_WriteBuffer(CRoot_File self,
                       const char *buf, int32_t len);

CROOT_API
int32_t
CRoot_File_Write(CRoot_File self, 
                 const char *name, int32_t opt, int32_t bufsiz);

/* TRandom */
typedef void *CRoot_Random;

extern CRoot_Random CRoot_gRandom;

CROOT_API
int32_t
CRoot_Random_Binomial(CRoot_Random self, int32_t ntot, double prob);

CROOT_API
double
CRoot_Random_Gaus(CRoot_Random self,
                  double mean, double sigma);

CROOT_API
void
CRoot_Random_Rannorf(CRoot_Random self,
                     float *a, float *b);

CROOT_API
void
CRoot_Random_Rannord(CRoot_Random self,
                     double *a, double *b);

CROOT_API
double
CRoot_Random_Rndm(CRoot_Random self,
                  int32_t i);

/* TMath */

CROOT_API
double
CRoot_Math_Sin(double);

CROOT_API
double
CRoot_Math_Cos(double);

CROOT_API
double
CRoot_Math_Tan(double);

CROOT_API
double
CRoot_Math_SinH(double);

CROOT_API
double
CRoot_Math_CosH(double);

CROOT_API
double
CRoot_Math_TanH(double);

CROOT_API
double
CRoot_Math_ASin(double);

CROOT_API
double
CRoot_Math_ACos(double);

CROOT_API
double
CRoot_Math_ATan(double);

CROOT_API
double
CRoot_Math_ATan2(double, double);

CROOT_API
double
CRoot_Math_ASinH(double);

CROOT_API
double
CRoot_Math_ACosH(double);

CROOT_API
double
CRoot_Math_ATanH(double);

CROOT_API
double
CRoot_Math_Hypot(double x, double y);

CROOT_API
double
CRoot_Math_Sqrt(double);

CROOT_API
double
CRoot_Math_Ceil(double);

CROOT_API
int32_t
CRoot_Math_CeilNint(double);

CROOT_API
double
CRoot_Math_Floor(double);

CROOT_API
int32_t
CRoot_Math_FloorNint(double);

CROOT_API
double
CRoot_Math_Exp(double);

CROOT_API
double
CRoot_Math_Ldexp(double x, int32_t exp);

CROOT_API
double
CRoot_Math_Factorial(int32_t i);

CROOT_API
double
CRoot_Math_Power(double x, double y);

CROOT_API
double
CRoot_Math_Log(double);

CROOT_API
double
CRoot_Math_Log2(double);

CROOT_API
double
CRoot_Math_Log10(double);

/* -- CINT-API -- */
#if 1
typedef void* CRoot_Cint_TagInfo;

CROOT_API
CRoot_Cint_TagInfo
CRoot_Cint_TagInfo_new();

CROOT_API
void
CRoot_Cint_TagInfo_delete(CRoot_Cint_TagInfo ti);

CROOT_API
void
CRoot_Cint_TagInfo_SetTagName(CRoot_Cint_TagInfo self, const char* tagname);

CROOT_API
void
CRoot_Cint_TagInfo_SetTagType(CRoot_Cint_TagInfo self, char tagtype);

CROOT_API
void
CRoot_Cint_TagInfo_SetTagNum(CRoot_Cint_TagInfo self, short tagnum);

CROOT_API
const char*
CRoot_Cint_TagInfo_GetTagName(CRoot_Cint_TagInfo self);

CROOT_API
char
CRoot_Cint_TagInfo_GetTagType(CRoot_Cint_TagInfo self);

CROOT_API
short
CRoot_Cint_TagInfo_GetTagNum(CRoot_Cint_TagInfo self);

CROOT_API
int
CRoot_Cint_TagInfo_GetLinkedTagNum(CRoot_Cint_TagInfo self);

CROOT_API
int
CRoot_Cint_Defined_TagName(const char* tagname, int noerror);

#ifdef __cplusplus
typedef void (*CRoot_Cint_incsetup)(void);
#else  /* __cplusplus */
typedef void (*CRoot_Cint_incsetup)();
#endif /* __cplusplus */

CROOT_API
int
CRoot_Cint_TagTable_Setup(int tagnum, int size, int cpplink, int isabstract,
                          const char* comment, 
                          CRoot_Cint_incsetup setup_memvar,
                          CRoot_Cint_incsetup setup_memfunc);

CROOT_API
int
CRoot_Cint_Tag_MemVar_Setup(int tagnum);

CROOT_API
int
CRoot_Cint_MemVar_Setup(void *p, int type, int reftype,
                        int constvar, 
                        int tagnum,
                        int typenum,
                        int statictype,
                        int var_access,
                        const char* expr,
                        int definemacro,
                        const char* comment);
 
CROOT_API
int
CRoot_Cint_Tag_MemVar_Reset();
#endif

/* --- Reflex API --- */
typedef void* CRoot_Reflex_Type;
typedef void* CRoot_Reflex_Member;
typedef void* CRoot_Reflex_Scope;
typedef void* CRoot_Reflex_ClassBuilder;
typedef void* CRoot_Reflex_FunctionBuilder;

/**
 * typedef for function member type (necessary for return value of
 * getter function)
 */
typedef void (*CRoot_Reflex_StubFunction)(void*, void*, void*, void*);

/** typedef for function for Offset calculation */
typedef size_t (*CRoot_Reflex_OffsetFunction)(void*);

// these defines are used for the modifiers they are used in the following
// classes
// BA = BASE
// CL = CLASS
// FU = FUNCTION
// DM = DATAMEMBER
// FM = FUNCTIONMEMBER
// TY = TYPE
// ME = MEMBER
//                                             BA  CL  DM  FM  TY  ME
typedef enum {
   CRoot_Reflex_PUBLIC = (1 << 0),            //  X       X   X       X
   CRoot_Reflex_PROTECTED = (1 << 1),         //  X       X   X       X
   CRoot_Reflex_PRIVATE = (1 << 2),           //  X       X   X       X
   CRoot_Reflex_REGISTER = (1 << 3),          //          X   X       X
   CRoot_Reflex_STATIC = (1 << 4),            //          X   X       X
   CRoot_Reflex_CONSTRUCTOR = (1 << 5),       //              X       X
   CRoot_Reflex_DESTRUCTOR = (1 << 6),        //              X       X
   CRoot_Reflex_EXPLICIT = (1 << 7),          //              X       X
   CRoot_Reflex_EXTERN = (1 << 8),            //          X   X       X
   CRoot_Reflex_COPYCONSTRUCTOR = (1 << 9),   //              X       X
   CRoot_Reflex_OPERATOR = (1 << 10),         //              X       X
   CRoot_Reflex_INLINE = (1 << 11),           //              X       X
   CRoot_Reflex_CONVERTER = (1 << 12),        //              X       X
   CRoot_Reflex_AUTO = (1 << 13),             //          X           X
   CRoot_Reflex_MUTABLE = (1 << 14),          //          X           X
   CRoot_Reflex_CONST = (1 << 15),            //          X       X   X
   CRoot_Reflex_VOLATILE = (1 << 16),         //          X       X   X
   CRoot_Reflex_REFERENCE = (1 << 17),        //          X           X
   CRoot_Reflex_ABSTRACT = (1 << 18),         //      X       X   X
   CRoot_Reflex_VIRTUAL = (1 << 19),          //  X   X           X
   CRoot_Reflex_TRANSIENT = (1 << 20),        //          X           X
   CRoot_Reflex_ARTIFICIAL = (1 << 21),       //  X   X   X   X   X   X
   // the bits 31 - 28 are reserved for template default arguments
   CRoot_Reflex_TEMPLATEDEFAULTS1 = (0 << 31) & (0 << 30) & (0 << 29) & (1 << 28),
   CRoot_Reflex_TEMPLATEDEFAULTS2 = (0 << 31) & (0 << 30) & (1 << 29) & (0 << 28),
   CRoot_Reflex_TEMPLATEDEFAULTS3 = (0 << 31) & (0 << 30) & (1 << 29) & (1 << 28),
   CRoot_Reflex_TEMPLATEDEFAULTS4 = (0 << 31) & (1 << 30) & (0 << 29) & (0 << 28),
   CRoot_Reflex_TEMPLATEDEFAULTS5 = (0 << 31) & (1 << 30) & (0 << 29) & (1 << 28),
   CRoot_Reflex_TEMPLATEDEFAULTS6 = (0 << 31) & (1 << 30) & (1 << 29) & (0 << 28),
   CRoot_Reflex_TEMPLATEDEFAULTS7 = (0 << 31) & (1 << 30) & (1 << 29) & (1 << 28),
   CRoot_Reflex_TEMPLATEDEFAULTS8 = (1 << 31) & (0 << 30) & (0 << 29) & (0 << 28),
   CRoot_Reflex_TEMPLATEDEFAULTS9 = (1 << 31) & (0 << 30) & (0 << 29) & (1 << 28),
   CRoot_Reflex_TEMPLATEDEFAULTS10 = (1 << 31) & (0 << 30) & (1 << 29) & (0 << 28),
   CRoot_Reflex_TEMPLATEDEFAULTS11 = (1 << 31) & (0 << 30) & (1 << 29) & (1 << 28),
   CRoot_Reflex_TEMPLATEDEFAULTS12 = (1 << 31) & (1 << 30) & (0 << 29) & (0 << 28),
   CRoot_Reflex_TEMPLATEDEFAULTS13 = (1 << 31) & (1 << 30) & (0 << 29) & (1 << 28),
   CRoot_Reflex_TEMPLATEDEFAULTS14 = (1 << 31) & (1 << 30) & (1 << 29) & (0 << 28),
   CRoot_Reflex_TEMPLATEDEFAULTS15 = (1 << 31) & (1 << 30) & (1 << 29) & (1 << 28)
} CRoot_Reflex_ENTITY_DESCRIPTION;


/** enum for printing names */
typedef enum {
   CRoot_Reflex_FINAL = (1 << 0),
   CRoot_Reflex_QUALIFIED = (1 << 1),
   CRoot_Reflex_SCOPED = (1 << 2),
   CRoot_Reflex_F = (1 << 4),
   CRoot_Reflex_Q = (1 << 5),
   CRoot_Reflex_S = (1 << 6)
} CRoot_Reflex_ENTITY_HANDLING;

/** enum containing all possible types and scopes */
typedef enum {
   CRoot_Reflex_CLASS = 0,
   CRoot_Reflex_STRUCT,
   CRoot_Reflex_ENUM,
   CRoot_Reflex_FUNCTION,
   CRoot_Reflex_ARRAY,
   CRoot_Reflex_FUNDAMENTAL,
   CRoot_Reflex_POINTER,
   CRoot_Reflex_POINTERTOMEMBER,
   CRoot_Reflex_TYPEDEF,
   CRoot_Reflex_UNION,
   CRoot_Reflex_TYPETEMPLATEINSTANCE,
   CRoot_Reflex_MEMBERTEMPLATEINSTANCE,
   CRoot_Reflex_NAMESPACE,
   CRoot_Reflex_DATAMEMBER,
   CRoot_Reflex_FUNCTIONMEMBER,
   CRoot_Reflex_UNRESOLVED
} CRoot_Reflex_TYPE;

/** enum containing all possible 'representation' types */
typedef enum {
   CRoot_Reflex_REPRES_POINTER = 'a' - 'A',                 // To be added to the other value to refer to a pointer to
   CRoot_Reflex_REPRES_CHAR = 'c',
   CRoot_Reflex_REPRES_SIGNED_CHAR = 'c',
   CRoot_Reflex_REPRES_SHORT_INT = 's',
   CRoot_Reflex_REPRES_INT = 'i',
   CRoot_Reflex_REPRES_LONG_INT = 'l',
   CRoot_Reflex_REPRES_UNSIGNED_CHAR = 'b',
   CRoot_Reflex_REPRES_UNSIGNED_SHORT_INT = 'r',
   CRoot_Reflex_REPRES_UNSIGNED_INT = 'h',
   CRoot_Reflex_REPRES_UNSIGNED_LONG_INT = 'k',
   CRoot_Reflex_REPRES_BOOL = 'g',
   CRoot_Reflex_REPRES_FLOAT = 'f',
   CRoot_Reflex_REPRES_DOUBLE = 'd',
   CRoot_Reflex_REPRES_LONG_DOUBLE = 'q',
   CRoot_Reflex_REPRES_VOID = 'y',
   CRoot_Reflex_REPRES_LONGLONG = 'n',
   CRoot_Reflex_REPRES_ULONGLONG = 'm',
   CRoot_Reflex_REPRES_STRUCT = 'u',
   CRoot_Reflex_REPRES_CLASS = 'u',
   CRoot_Reflex_REPRES_ENUM = 'i',                   // Intentionally equal to REPRES_INT
   CRoot_Reflex_REPRES_NOTYPE = '\0'
                   // '1' is also a value used (for legacy implementation of function pointer)
                   // 'E' is also a value used (for legacy implementation of FILE*)
                   // 'a', 'j', 'T', 'o', 'O', 'p', 'P', 'z', 'Z', '\011', '\001', 'w' are also a value used (for support of various interpreter types)
} CRoot_Reflex_REPRESTYPE;

typedef enum {
   CRoot_Reflex_INHERITEDMEMBERS_DEFAULT,    // NO by default, set to ALSO by UpdateMembers()
   CRoot_Reflex_INHERITEDMEMBERS_NO,
   CRoot_Reflex_INHERITEDMEMBERS_ALSO
} CRoot_Reflex_EMEMBERQUERY;

typedef enum {
   CRoot_Reflex_DELAYEDLOAD_OFF,
   CRoot_Reflex_DELAYEDLOAD_ON
} CRoot_Reflex_EDELAYEDLOADSETTING;

CROOT_API
void
CRoot_Reflex_FireClassCallback(CRoot_Reflex_Type self);

CROOT_API
void
CRoot_Reflex_FireFunctionCallback(CRoot_Reflex_Member self);

CROOT_API
CRoot_Reflex_Type
CRoot_Reflex_Type_new(const char* name, unsigned int modifiers);

CROOT_API
void
CRoot_Reflex_Type_delete(CRoot_Reflex_Type self);

CROOT_API
void*
CRoot_Reflex_Type_Id(CRoot_Reflex_Type self);

CROOT_API
size_t
CRoot_Reflex_Type_ArrayLength(CRoot_Reflex_Type self);

CROOT_API
CRoot_Reflex_Type
CRoot_Reflex_Type_ByName(const char *name);

CROOT_API
CRoot_Reflex_Member
CRoot_Reflex_Type_FunctionMemberAt(CRoot_Reflex_Type self,
                                   size_t nth,
                                   CRoot_Reflex_EMEMBERQUERY inh);

CROOT_API
size_t
CRoot_Reflex_Type_FunctionMemberSize(CRoot_Reflex_Type self,
                                     CRoot_Reflex_EMEMBERQUERY inh);

CROOT_API
CRoot_Reflex_Member
CRoot_Reflex_Type_DataMemberAt(CRoot_Reflex_Type self,
                               size_t nth,
                               CRoot_Reflex_EMEMBERQUERY inh);

CROOT_API
size_t
CRoot_Reflex_Type_DataMemberSize(CRoot_Reflex_Type self,
                                 CRoot_Reflex_EMEMBERQUERY inh);

CROOT_API
bool
CRoot_Reflex_Type_IsAbstract(CRoot_Reflex_Type self);

CROOT_API
bool
CRoot_Reflex_Type_IsArray(CRoot_Reflex_Type self);

CROOT_API
bool
CRoot_Reflex_Type_IsClass(CRoot_Reflex_Type self);

CROOT_API
bool
CRoot_Reflex_Type_IsComplete(CRoot_Reflex_Type self);

CROOT_API
bool
CRoot_Reflex_Type_IsEquivalentTo(CRoot_Reflex_Type self,
                                 CRoot_Reflex_Type other,
                                 unsigned int modifiers_mask);

CROOT_API
bool
CRoot_Reflex_Type_IsFunction(CRoot_Reflex_Type self);

CROOT_API
bool
CRoot_Reflex_Type_IsFundamental(CRoot_Reflex_Type self);

CROOT_API
bool
CRoot_Reflex_Type_IsPrivate(CRoot_Reflex_Type self);

CROOT_API
bool
CRoot_Reflex_Type_IsProtected(CRoot_Reflex_Type self);

CROOT_API
bool
CRoot_Reflex_Type_IsPublic(CRoot_Reflex_Type self);

CROOT_API
bool
CRoot_Reflex_Type_IsPointer(CRoot_Reflex_Type self);

CROOT_API
bool
CRoot_Reflex_Type_IsPointerToMember(CRoot_Reflex_Type self);

CROOT_API
bool
CRoot_Reflex_Type_IsReference(CRoot_Reflex_Type self);

CROOT_API
bool
CRoot_Reflex_Type_IsStruct(CRoot_Reflex_Type self);

CROOT_API
bool
CRoot_Reflex_Type_IsVirtual(CRoot_Reflex_Type self);

CROOT_API
CRoot_Reflex_Member
CRoot_Reflex_Type_MemberAt(CRoot_Reflex_Type self,
                           size_t nth,
                           CRoot_Reflex_EMEMBERQUERY inh);

CROOT_API
size_t
CRoot_Reflex_Type_MemberSize(CRoot_Reflex_Type self,
                             CRoot_Reflex_EMEMBERQUERY inh);

CROOT_API
const char*
CRoot_Reflex_Type_Name(CRoot_Reflex_Type self);

CROOT_API
CRoot_Reflex_Type
CRoot_Reflex_Type_RawType(CRoot_Reflex_Type self);

CROOT_API
size_t
CRoot_Reflex_Type_SizeOf(CRoot_Reflex_Type self);

CROOT_API
CRoot_Reflex_Type
CRoot_Reflex_Type_ToType(CRoot_Reflex_Type self);

CROOT_API
CRoot_Reflex_Type
CRoot_Reflex_Type_TypeAt(size_t nth);

CROOT_API
size_t
CRoot_Reflex_Type_TypeSize();

CROOT_API
CRoot_Reflex_TYPE
CRoot_Reflex_Type_TypeType(CRoot_Reflex_Type self);

CROOT_API
void
CRoot_Reflex_Type_Unload(CRoot_Reflex_Type self);

CROOT_API
void
CRoot_Reflex_Type_UpdateMembers(CRoot_Reflex_Type self);

CROOT_API
void
CRoot_Reflex_Type_AddDataMember(CRoot_Reflex_Type self,
                                CRoot_Reflex_Member dm);

CROOT_API
CRoot_Reflex_Member
CRoot_Reflex_Type_AddDataMember2(CRoot_Reflex_Type self,
                                 const char* name,
                                 CRoot_Reflex_Type type,
                                 size_t offset,
                                 unsigned int modifiers,
                                 char *interpreterOffset);

CROOT_API
void
CRoot_Reflex_Type_RemoveDataMember(CRoot_Reflex_Type self,
                                   CRoot_Reflex_Member dm);

CROOT_API
void
CRoot_Reflex_Type_SetSize(CRoot_Reflex_Type self,
                          size_t s);

CROOT_API
CRoot_Reflex_REPRESTYPE
CRoot_Reflex_Type_RepresType(CRoot_Reflex_Type self);

CROOT_API
CRoot_Reflex_Member
CRoot_Reflex_Member_new();

CROOT_API
void
CRoot_Reflex_Member_delete(CRoot_Reflex_Member self);

CROOT_API
bool
CRoot_Reflex_Member_IsDataMember(CRoot_Reflex_Member self);

CROOT_API
bool
CRoot_Reflex_Member_IsPrivate(CRoot_Reflex_Member self);

CROOT_API
bool
CRoot_Reflex_Member_IsProtected(CRoot_Reflex_Member self);

CROOT_API
bool
CRoot_Reflex_Member_IsPublic(CRoot_Reflex_Member self);

CROOT_API
bool
CRoot_Reflex_Member_IsTransient(CRoot_Reflex_Member self);

CROOT_API
bool
CRoot_Reflex_Member_IsVirtual(CRoot_Reflex_Member self);

CROOT_API
CRoot_Reflex_TYPE
CRoot_Reflex_Member_MemberType(CRoot_Reflex_Member self);

CROOT_API
const char*
CRoot_Reflex_Member_Name(CRoot_Reflex_Member self);

CROOT_API
size_t
CRoot_Reflex_Member_Offset(CRoot_Reflex_Member self);

CROOT_API
void
CRoot_Reflex_Member_InterpreterOffset(CRoot_Reflex_Member self,
                                      char *offset);

CROOT_API
CRoot_Reflex_Type
CRoot_Reflex_Member_TypeOf(CRoot_Reflex_Member self);

CROOT_API
void*
CRoot_Reflex_Member_Stubcontext(CRoot_Reflex_Member self);

CROOT_API
CRoot_Reflex_StubFunction
CRoot_Reflex_Member_Stubfunction(CRoot_Reflex_Member self);

/* type builder API */

CROOT_API
CRoot_Reflex_Type
CRoot_Reflex_PointerBuilder_new(CRoot_Reflex_Type t);

CROOT_API
CRoot_Reflex_Type
CRoot_Reflex_ArrayBuilder_new(CRoot_Reflex_Type t,
                              size_t n);

CROOT_API
CRoot_Reflex_Type
CRoot_Reflex_FunctionTypeBuilder_new(CRoot_Reflex_Type r);

CROOT_API
CRoot_Reflex_Type
CRoot_Reflex_FunctionTypeBuilder_new1(CRoot_Reflex_Type r,
                                      CRoot_Reflex_Type t0);

CROOT_API
CRoot_Reflex_Type
CRoot_Reflex_FunctionTypeBuilder_new2(CRoot_Reflex_Type r,
                                      CRoot_Reflex_Type t0,
                                      CRoot_Reflex_Type t1);

CROOT_API
CRoot_Reflex_Type
CRoot_Reflex_FunctionTypeBuilder_new3(CRoot_Reflex_Type r,
                                      CRoot_Reflex_Type t0,
                                      CRoot_Reflex_Type t1,
                                      CRoot_Reflex_Type t2);

CROOT_API
CRoot_Reflex_ClassBuilder
CRoot_Reflex_ClassBuilder_new(const char *name,
                              void* typeinfo,
                              size_t size,
                              unsigned int modifiers,
                              CRoot_Reflex_TYPE type);

CROOT_API
void
CRoot_Reflex_ClassBuilder_delete(CRoot_Reflex_ClassBuilder self);

CROOT_API
void
CRoot_Reflex_ClassBuilder_AddDataMember(CRoot_Reflex_ClassBuilder self,
                                        CRoot_Reflex_Type type,
                                        const char* name,
                                        size_t offset,
                                        unsigned int modifiers);

CROOT_API
void
CRoot_Reflex_ClassBuilder_AddFunctionMember(CRoot_Reflex_ClassBuilder self,
                                            CRoot_Reflex_Type type,
                                            const char *name,
                                            CRoot_Reflex_StubFunction stubFP,
                                            void *stubCtx,
                                            const char *params,
                                            unsigned int modifiers);

CROOT_API
CRoot_Reflex_Type
CRoot_Reflex_ClassBuilder_ToType(CRoot_Reflex_ClassBuilder self);


CROOT_API
CRoot_Reflex_FunctionBuilder
CRoot_Reflex_FunctionBuilder_new(CRoot_Reflex_Type type,
                                 const char* name,
                                 CRoot_Reflex_StubFunction stubFP,
                                 void *stubCtx,
                                 const char *params,
                                 unsigned char modifiers);

CROOT_API
void
CRoot_Reflex_FunctionBuilder_delete(CRoot_Reflex_FunctionBuilder self);

CROOT_API
CRoot_Reflex_Member
CRoot_Reflex_FunctionBuilder_ToMember(CRoot_Reflex_FunctionBuilder self);

CROOT_API
void
CRoot_Cintex_Enable();

CROOT_API
void
CRoot_Cintex_SetDebug(int level);

#ifdef __cplusplus
}
#endif

#endif /* !CROOT_CROOT_H */
