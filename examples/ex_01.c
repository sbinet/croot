#include <stdio.h>

#include "croot.h"

int main(int argc, char **argv) 
{
  printf("== croot ex-01 ==\n");
  
  CRoot_File f = CRoot_File_Open("event.root", "new", 
                                 "my first root file",
                                 1, 0);

  if (CRoot_File_IsOpen(f)) {
    printf("file opened successfully\n");
  } else {
    printf("** error ** could not open file [event.root]!\n");
    return 1;
  }

  /* closing file...*/
  CRoot_File_Close(f, "");

  return 0;
}
