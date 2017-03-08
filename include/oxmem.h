/********************************************************************************

Copyright (c) 2017 Bob Perry / asw204k_AT_yahoo.com
All rights reserved.

Please see license in the project root directory fro more details

*/

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
