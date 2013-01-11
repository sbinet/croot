#include <stdio.h>
#include <stdlib.h>

#include "croot/croot.h"

typedef struct {
  double e;
  double t;
} Det;

typedef struct {
  Det a;
  Det b;
} Event;

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
  int32_t nevents = 10000000;
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
