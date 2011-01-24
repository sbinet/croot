/* @brief a C-API wrapper for (some of) the C++ classes of ROOT
 */

#ifndef CROOT_CROOT_H
#define CROOT_CROOT_H 1

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int CRoot_Bool;

/* Option_t */
typedef const char CRoot_Option;

/* TObject */
typedef void* CRoot_Object;

const char*
CRoot_Object_ClassName(CRoot_Object self);

CRoot_Object
CRoot_Object_Clone(CRoot_Object self,
                   const char *newname);

CRoot_Object
CRoot_Object_FindObject(CRoot_Object self, 
                        const char *name);

const char*
CRoot_Object_GetName(CRoot_Object self);

const char*
CRoot_Object_GetTitle(CRoot_Object self);

CRoot_Bool
CRoot_Object_InheritsFrom(CRoot_Object self, 
                          const char *classname);

void
CRoot_Object_Print(CRoot_Object self,
                   CRoot_Option *option);


/* TObjArray */
typedef void *CRoot_ObjArray;

/* TBranch */
typedef void *CRoot_Branch;

/* TTree */
typedef void* CRoot_Tree;
CRoot_Tree
CRoot_Tree_New(const char *name, const char *title, int32_t splitlevel);

void
CRoot_Tree_Delete(CRoot_Tree self);

CRoot_Branch
CRoot_Tree_Branch(CRoot_Tree self,
                  const char *name, const char *classname,
                  void *addobj, int32_t bufsize, int32_t splitlevel);

int
CRoot_Tree_Fill(CRoot_Tree self);

CRoot_Branch
CRoot_Tree_GetBranch(CRoot_Tree self,
                     const char *name);

int64_t
CRoot_Tree_GetEntries(CRoot_Tree self);

int32_t
CRoot_Tree_GetEntry(CRoot_Tree self,
                    int64_t entry, int32_t getall);

CRoot_ObjArray
CRoot_Tree_GetListOfBranches(CRoot_Tree self);

CRoot_ObjArray
CRoot_Tree_GetListOfLeaves(CRoot_Tree self);

int64_t
CRoot_Tree_LoadTree(CRoot_Tree self,
                    int64_t entry);

int32_t
CRoot_Tree_MakeClass(CRoot_Tree self,
                     const char *classname, CRoot_Option *option);

CRoot_Bool
CRoot_Tree_Notify(CRoot_Tree self);

void
CRoot_Tree_Print(CRoot_Tree self,
                 CRoot_Option *option);

int64_t
CRoot_Tree_Process(CRoot_Tree self,
                   const char *filename, CRoot_Option *option,
                   int64_t nentries, int64_t firstentry);

int64_t
CRoot_Tree_Project(CRoot_Tree self,
                   const char *hname, const char *varexp,
                   const char *selection, CRoot_Option *option,
                   int64_t nentries, int64_t firstentry);

int32_t
CRoot_Tree_SetBranchAddress(CRoot_Tree self,
                            const char *bname, void *addr, CRoot_Branch *ptr);

void
CRoot_Tree_SetBranchStatus(CRoot_Tree self,
                           const char *bname, CRoot_Bool status, 
                           uint32_t *found);

int32_t
CRoot_Tree_Write(CRoot_Tree self,
                 const char *name, int32_t option, int32_t bufsize);

/* TChain */
typedef void* CRoot_Chain;

CRoot_Chain
CRoot_Chain_New(const char *name, const char *title);

void
CRoot_Chain_Delete(CRoot_Chain self);

int32_t
CRoot_Chain_Add(CRoot_Chain self,
                const char *name, int64_t nentries);

int32_t
CRoot_Chain_AddFile(CRoot_Chain self,
                    const char *name, int64_t nentries, const char *tname);

int64_t
CRoot_Chain_GetEntries(CRoot_Chain self);

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

CRoot_File
CRoot_File_Open(const char *name, 
                CRoot_Option *option,
                const char *ftitle,
                int32_t compress,
                int32_t netopt);

void
CRoot_File_Close(CRoot_File self, CRoot_Option *option);

int
CRoot_File_GetFd(CRoot_File self);

CRoot_Object
CRoot_File_Get(CRoot_File self, const char *namecycle);

CRoot_Bool
CRoot_File_ReadBuffer(CRoot_File self,
                      char *buf, int64_t pos, int32_t len);

CRoot_Bool
CRoot_File_ReadBuffers(CRoot_File self,
                       char *buf, int64_t *pos, int32_t *len, int32_t nbuf);

int32_t
CRoot_File_WriteBuffer(CRoot_File self,
                       const char *buf, int32_t len);

int32_t
CRoot_File_Write(CRoot_File self, 
                 const char *name, int32_t opt, int32_t bufsiz);

#ifdef __cplusplus
}
#endif

#endif /* !CROOT_CROOT_H */
