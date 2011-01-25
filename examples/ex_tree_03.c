#include <stdio.h>
#include <stdlib.h>

#include "croot.h"

/* example of a Tree where branches are variable length arrays
 * a second tree is created and filled in parallel.
 */

void tree3w()
{
  const int32_t kMaxTrack = 500;
  int32_t ntrack;
  int32_t stat[kMaxTrack];
  int32_t sign[kMaxTrack];
  float px[kMaxTrack];
  float py[kMaxTrack];
  float pz[kMaxTrack];
  float pt[kMaxTrack];
  float zv[kMaxTrack];
  float chi2[kMaxTrack];
  double sumstat;

  CRoot_File f = CRoot_File_Open("tree3.root", "recreate",
                                 "my root file", 1, 0);
  CRoot_Tree t3 = CRoot_Tree_new("t3", "reconstr. ntuple", 32);

  int32_t bufsiz = 32000;
  CRoot_Tree_Branch2(t3, "ntrack", &ntrack, "ntrack/I", bufsiz);
  CRoot_Tree_Branch2(t3, "stat", stat, "stat[ntrack]/I", bufsiz);
  CRoot_Tree_Branch2(t3, "sign", sign, "sign[ntrack]/I", bufsiz);
  CRoot_Tree_Branch2(t3, "px", px, "px[ntrack]/F", bufsiz);
  CRoot_Tree_Branch2(t3, "py", py, "py[ntrack]/F", bufsiz);
  CRoot_Tree_Branch2(t3, "pz", pz, "pz[ntrack]/F", bufsiz);
  CRoot_Tree_Branch2(t3, "zv", zv, "zv[ntrack]/F", bufsiz);
  CRoot_Tree_Branch2(t3, "chi2", chi2, "chi2[ntrack]/F", bufsiz);

  CRoot_File fr = CRoot_File_Open("tree3f.root", "recreate",
                                  "my root file", 1, 0);
  CRoot_Tree t3f = CRoot_Tree_new("t3f", "a friend tree", 32);
  CRoot_Tree_Branch2(t3f, "ntrack", &ntrack, "ntrack/I", bufsiz);
  CRoot_Tree_Branch2(t3f, "sumstat", &sumstat, "sumstat/D", bufsiz);
  CRoot_Tree_Branch2(t3f, "pt", pt, "pt[ntrack]/F", bufsiz);

  for (int32_t i = 0; i < 1000; ++i) {
    int32_t nt = CRoot_Random_Rndm(CRoot_gRandom, 1) * (kMaxTrack-1);
    ntrack = nt;
    sumstat = 0.;
    for (int32_t n = 0; n<nt; ++n) {
      stat[n] = n%3;
      sign[n] = i%2;
      px[n]   = CRoot_Random_Gaus(CRoot_gRandom,  0, 1);
      py[n]   = CRoot_Random_Gaus(CRoot_gRandom,  0, 2);
      pz[n]   = CRoot_Random_Gaus(CRoot_gRandom, 10, 5);
      zv[n]   = CRoot_Random_Gaus(CRoot_gRandom,100, 2);
      chi2[n] = CRoot_Random_Gaus(CRoot_gRandom,  0, .01);
      sumstat += chi2[n];
      pt[n]   = CRoot_Math_Sqrt(px[n]*px[n] + py[n]*py[n]);
    }
    CRoot_Tree_Fill(t3);
    CRoot_Tree_Fill(t3f);
  }
  CRoot_File_cd(f);
  CRoot_Tree_Write(t3, 0, 0, 0);
  CRoot_File_cd(fr);
  CRoot_Tree_Write(t3f, 0, 0, 0);
}

void tree3r()
{
  CRoot_File f = CRoot_File_Open("tree3.root", "read", 
                                 "", 1, 0);
  CRoot_Tree t3 = (CRoot_Tree)CRoot_Object_Get(f, "t3");
  printf(":: entries: %i\n", CRoot_Tree_GetEntries(t3));
}

int main(int argc, char **argv)
{
  tree3w();

  return 0;
}
