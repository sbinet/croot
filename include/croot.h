/* @brief a C-API wrapper for (some of) the C++ classes of ROOT
 */

#ifndef CROOT_CROOT_H
#define CROOT_CROOT_H 1

#include <stdint.h>

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

/* TBranch */
typedef void* CRoot_Branch;

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

#ifdef __cplusplus
}
#endif

#endif /* !CROOT_CROOT_H */
