#ifndef __oxmem_h__
#define __oxmem_h__

#include <boost/interprocess/managed_shared_memory.hpp>
#include <string.h>
#include "ns.h"

class OxMem {

public:
  
  OxMem(char const * name, unsigned int size);

  inline bip::managed_shared_memory *get_shm() { return shm; }
  
  ~OxMem();

private:
  
  std::string name;
  bip::managed_shared_memory *shm;
  
};

#endif
