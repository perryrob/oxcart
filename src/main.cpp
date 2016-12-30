
#include "oxmem.h"


int main(int argc, char * argv[] ){

  unsigned int SHM_SIZE = 16000;

  OxMem shared_mem =  OxMem("OXMEM",SHM_SIZE);

  return 0;
}
