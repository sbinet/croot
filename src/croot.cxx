#include "croot.h"

#include "TBranch.h"
#include "TTree.h"
#include "TChain.h"
#include "TFile.h"

#include "TObject.h"
#include "TObjArray.h"

#include "TMath.h"
#include "TRandom.h"

/* TObject */
const char*
CRoot_Object_ClassName(CRoot_Object self)
{
  return ((TObject*)self)->ClassName();
}

CRoot_Object
CRoot_Object_Clone(CRoot_Object self,
                   const char *newname)
{
  return (TObject*)(((TObject*)self)->Clone(newname));
}

CRoot_Object
CRoot_Object_FindObject(CRoot_Object self, 
                        const char *name)
{
  return (TObject*)(((TObject*)self)->FindObject(name));
}

const char*
CRoot_Object_GetName(CRoot_Object self)
{
  return ((TObject*)self)->GetName();
}

const char*
CRoot_Object_GetTitle(CRoot_Object self)
{
  return ((TObject*)self)->GetTitle();
}

CRoot_Bool
CRoot_Object_InheritsFrom(CRoot_Object self, 
                          const char *classname)
{
  return (CRoot_Bool)(((TObject*)self)->InheritsFrom(classname));
}

void
CRoot_Object_Print(CRoot_Object self,
                   CRoot_Option *option)
{
  return ((TObject*)self)->Print((Option_t*)option);
}


/* TTree */
CRoot_Tree
CRoot_Tree_new(const char *name, const char *title, int32_t splitlevel)
{
  TTree *self = new TTree(name, title, splitlevel);
  return (CRoot_Tree)self;
}

void
CRoot_Tree_delete(CRoot_Tree self)
{
  TTree *tree = (TTree*)self;
  delete tree;
  self = 0;
}

CRoot_Branch
CRoot_Tree_Branch(CRoot_Tree self,
                  const char *name, const char *classname,
                  void *addobj, int32_t bufsize, int32_t splitlevel)
{
  return (CRoot_Branch)(((TTree*)self)->Branch(name, classname, addobj,
                                               bufsize, splitlevel));
}

CRoot_Branch
CRoot_Tree_Branch2(CRoot_Tree self,
                   const char *name, void *address, const char *leaflist,
                   int32_t bufsize)
{
  return (CRoot_Branch)(((TTree*)self)->Branch(name, address, 
                                               leaflist, bufsize));
}

int
CRoot_Tree_Fill(CRoot_Tree self)
{
  return ((TTree*)self)->Fill();
}

CRoot_Branch
CRoot_Tree_GetBranch(CRoot_Tree self,
                     const char *name)
{
  return (CRoot_Branch)(((TTree*)self)->GetBranch(name));
}

int64_t
CRoot_Tree_GetEntries(CRoot_Tree self)
{
  return ((TTree*)self)->GetEntries();
}

int32_t
CRoot_Tree_GetEntry(CRoot_Tree self,
                    int64_t entry, int32_t getall)
{
  return ((TTree*)self)->GetEntry(entry, getall);
}

CRoot_ObjArray
CRoot_Tree_GetListOfBranches(CRoot_Tree self)
{
  return (CRoot_ObjArray)(((TTree*)self)->GetListOfBranches());
}

CRoot_ObjArray
CRoot_Tree_GetListOfLeaves(CRoot_Tree self)
{
  return (CRoot_ObjArray)(((TTree*)self)->GetListOfLeaves());
}

double*
CRoot_Tree_GetVal(CRoot_Tree self,
                  int32_t i)
{
  return (double*)(((TTree*)self)->GetVal(i));
}

double*
CRoot_Tree_GetV1(CRoot_Tree self)
{
  return (double*)(((TTree*)self)->GetV1());
}

double*
CRoot_Tree_GetV2(CRoot_Tree self)
{
  return (double*)(((TTree*)self)->GetV2());
}

double*
CRoot_Tree_GetV3(CRoot_Tree self)
{
  return (double*)(((TTree*)self)->GetV3());
}

double*
CRoot_Tree_GetV4(CRoot_Tree self)
{
  return (double*)(((TTree*)self)->GetV4());
}

double*
CRoot_Tree_GetW(CRoot_Tree self)
{
  return (double*)(((TTree*)self)->GetW());
}

int64_t
CRoot_Tree_LoadTree(CRoot_Tree self,
                    int64_t entry)
{
  return ((TTree*)self)->LoadTree(entry);
}

int32_t
CRoot_Tree_MakeClass(CRoot_Tree self,
                     const char *classname, CRoot_Option *option)
{
  return ((TTree*)self)->MakeClass(classname, (Option_t*)option);
}

CRoot_Bool
CRoot_Tree_Notify(CRoot_Tree self)
{
  return (CRoot_Bool)(((TTree*)self)->Notify());
}

void
CRoot_Tree_Print(CRoot_Tree self,
                 CRoot_Option *option)
{
  return ((TTree*)self)->Print((Option_t*)option);
}

int64_t
CRoot_Tree_Process(CRoot_Tree self,
                   const char *filename, CRoot_Option *option,
                   int64_t nentries, int64_t firstentry)
{
  return ((TTree*)self)->Process(filename, (Option_t*)option,
                                 nentries, firstentry);
}

int64_t
CRoot_Tree_Project(CRoot_Tree self,
                   const char *hname, const char *varexp,
                   const char *selection, CRoot_Option *option,
                   int64_t nentries, int64_t firstentry)
{
  return ((TTree*)self)->Project(hname, varexp, selection,
                                 (Option_t*)option, nentries, firstentry);
}

int32_t
CRoot_Tree_SetBranchAddress(CRoot_Tree self,
                            const char *bname, void *addr, CRoot_Branch *ptr)
{
  return ((TTree*)self)->SetBranchAddress(bname, addr, (TBranch**)ptr);
}


void
CRoot_Tree_SetBranchStatus(CRoot_Tree self,
                           const char *bname, CRoot_Bool status, 
                           uint32_t* found)
{
  return ((TTree*)self)->SetBranchStatus(bname, (Bool_t)status, found);
}

int32_t
CRoot_Tree_Write(CRoot_Tree self,
                 const char *name, int32_t option, int32_t bufsize)
{
  return ((TTree*)self)->Write(name, option, bufsize);
}

/* TChain */

CRoot_Chain
CRoot_Chain_new(const char *name, const char *title)
{
  TChain *self = new TChain(name, title);
  return (CRoot_Chain)self;
}

void
CRoot_Chain_delete(CRoot_Chain self)
{
  TChain *tree = (TChain*)self;
  delete tree;
  self = 0;
}

int32_t
CRoot_Chain_Add(CRoot_Chain self,
                const char *name, int64_t nentries)
{
  return ((TChain*)self)->Add(name, nentries);
}

int32_t
CRoot_Chain_AddFile(CRoot_Chain self,
                    const char *name, int64_t nentries, const char *tname)
{
  return ((TChain*)self)->AddFile(name, nentries, tname);
}

int64_t
CRoot_Chain_GetEntries(CRoot_Chain self)
{
  return ((TChain*)self)->GetEntries();
}

int32_t
CRoot_Chain_GetEntry(CRoot_Chain self,
                     int64_t entry, int32_t getall)
{
  return ((TChain*)self)->GetEntry(entry, getall);
}


/* TFile */
CRoot_File
CRoot_File_Open(const char *name, 
                CRoot_Option *option,
                const char *ftitle,
                int32_t compress,
                int32_t netopt)
{
  return (CRoot_File)(TFile::Open(name, (Option_t*)option, 
                                  ftitle, 
                                  compress, netopt));
}

void
CRoot_File_Close(CRoot_File self, CRoot_Option *option)
{
  return ((TFile*)self)->Close((Option_t*)option);
}

int
CRoot_File_GetFd(CRoot_File self)
{
  return ((TFile*)self)->GetFd();
}

CRoot_Object
CRoot_File_Get(CRoot_File self, const char *namecycle)
{
  return (TObject*)((TFile*)self)->Get(namecycle);
}

CRoot_Bool
CRoot_File_IsOpen(CRoot_File self)
{
  return (CRoot_Bool)(((TFile*)self)->IsOpen());
}

CRoot_Bool
CRoot_File_ReadBuffer(CRoot_File self,
                      char *buf, int64_t pos, int32_t len)
{
  return (CRoot_Bool)(((TFile*)self)->ReadBuffer(buf, pos, len));
}

CRoot_Bool
CRoot_File_ReadBuffers(CRoot_File self,
                       char *buf, int64_t *pos, int32_t *len, int32_t nbuf)
{
  return (CRoot_Bool)(((TFile*)self)->ReadBuffers(buf, 
                                                  (Long64_t*)pos, 
                                                  (Int_t*)len, 
                                                  nbuf));
}

int32_t
CRoot_File_WriteBuffer(CRoot_File self,
                       const char *buf, int32_t len)
{
  return ((TFile*)self)->WriteBuffer(buf, len);
}

int32_t
CRoot_File_Write(CRoot_File self, 
                 const char *name, int32_t opt, int32_t bufsiz)
{
  return ((TFile*)self)->Write(name, opt, bufsiz);
}

/* TRandom */
CRoot_Random CRoot_gRandom = (CRoot_Random)gRandom;

int32_t
CRoot_Random_Binomial(CRoot_Random self, int32_t ntot, double prob)
{
  return ((TRandom*)self)->Binomial(ntot, prob);
}

double
CRoot_Random_Gaus(CRoot_Random self,
                  double mean, double sigma)
{
  return ((TRandom*)self)->Gaus(mean, sigma);
}

void
CRoot_Random_Rannorf(CRoot_Random self,
                     float *a, float *b)
{
  return ((TRandom*)self)->Rannor(*a, *b);
}

void
CRoot_Random_Rannord(CRoot_Random self,
                     double *a, double *b)
{
  return ((TRandom*)self)->Rannor(*a, *b);
}

double
CRoot_Random_Rndm(CRoot_Random self,
                  int32_t i)
{
  return ((TRandom*)self)->Rndm(i);
}

/* TMath */


double
CRoot_Math_Sin(double x)
{
  return TMath::Sin(x);
}


double
CRoot_Math_Cos(double x)
{
  return TMath::Cos(x);
}

double
CRoot_Math_Tan(double x)
{
  return TMath::Tan(x);
}

double
CRoot_Math_SinH(double x)
{
  return TMath::SinH(x);
}

double
CRoot_Math_CosH(double x)
{
  return TMath::CosH(x);
}

double
CRoot_Math_TanH(double x)
{
  return TMath::TanH(x);
}

double
CRoot_Math_ASin(double x)
{
  return TMath::ASin(x);
}

double
CRoot_Math_ACos(double x)
{
  return TMath::ACos(x);
}

double
CRoot_Math_ATan(double x)
{
  return TMath::ATan(x);
}

double
CRoot_Math_ATan2(double x, double y)
{
  return TMath::ATan2(x,y);
}

double
CRoot_Math_ASinH(double x)
{
  return TMath::ASinH(x);
}

double
CRoot_Math_ACosH(double x)
{
  return TMath::ACosH(x);
}

double
CRoot_Math_ATanH(double x)
{
  return TMath::ATanH(x);
}

double
CRoot_Math_Hypot(double x, double y)
{
  return TMath::Hypot(x, y);
}

double
CRoot_Math_Sqrt(double x)
{
  return TMath::Sqrt(x);
}

double
CRoot_Math_Ceil(double x)
{
  return TMath::Ceil(x);
}

int32_t
CRoot_Math_CeilNint(double x)
{
  return TMath::CeilNint(x);
}

double
CRoot_Math_Floor(double x)
{
  return TMath::Floor(x);
}

int32_t
CRoot_Math_FloorNint(double x)
{
  return TMath::FloorNint(x);
}

double
CRoot_Math_Exp(double x)
{
  return TMath::Exp(x);
}

double
CRoot_Math_Ldexp(double x, int32_t exp)
{
  return TMath::Ldexp(x, exp);
}

double
CRoot_Math_Factorial(int32_t i)
{
  return TMath::Factorial(i);
}


double
CRoot_Math_Power(double x, double y)
{
  return TMath::Power(x, y);
}

double
CRoot_Math_Log(double x)
{
  return TMath::Log(x);
}

double
CRoot_Math_Log2(double x)
{
  return TMath::Log2(x);
}
 
double
CRoot_Math_Log10(double x)
{
  return TMath::Log10(x);
}
