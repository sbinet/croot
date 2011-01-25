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
  }
}
void tree0(CRoot_File f) 
{
  /* create a tree */
  CRoot_Tree tree = CRoot_Tree_new("tree", "tree", 32);
  Event *e = (Event*)malloc(sizeof(Event));

  int32_t bufsiz = 32000;

  /* create a branch with energy */
  CRoot_Tree_Branch2(tree, "evt_a_e", &e->a.e, "evt_a_e/D", bufsiz);
  CRoot_Tree_Branch2(tree, "evt_a_t", &e->a.t, "evt_a_t/D", bufsiz);
  CRoot_Tree_Branch2(tree, "evt_b_e", &e->b.e, "evt_b_e/D", bufsiz);
  CRoot_Tree_Branch2(tree, "evt_b_t", &e->b.t, "evt_b_t/D", bufsiz);

  /* fill some events with random numbers */
  int32_t nevents = 10000;
  for (int32_t iev=0; iev<nevents; iev++) {
    if (iev%1000 == 0) {
      printf("processing event %i...\n", iev);
    }

    float ea = 0., eb = 0.;
    /* the two energies follow a gauss distribution */
    CRoot_Random_Rannorf(CRoot_gRandom, &ea, &eb);
    e->a.e = ea;
    e->b.e = eb;
    
    e->a.t = CRoot_Random_Rndm(CRoot_gRandom, 1);
    e->b.t = e->a.t * CRoot_Random_Gaus(CRoot_gRandom, 0., 1.);

    if (iev%1000 == 0) {
      printf("evt.a.e= %8.3f\n", e->a.e);
      printf("evt.a.t= %8.3f\n", e->a.t);
      printf("evt.b.e= %8.3f\n", e->b.e);
      printf("evt.b.t= %8.3f\n", e->b.t);
    }
    /* fill the tree with the current event */
    CRoot_Tree_Fill(tree);
  }
  CRoot_File_Write(f, 0, 0, 0);
}

int main(int argc, char **argv)
{
  CRoot_File f = CRoot_File_Open("event.root", "recreate",
                                 "my event file", 1, 0);
  tree0(f);
  CRoot_File_Close(f, "");

  return 0;
}
