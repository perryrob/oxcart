/********************************************************************************

Copyright (c) 2017 Bob Perry / asw204k_AT_yahoo.com
All rights reserved.

Please see license in the project root directory fro more details

*/

#include "oxmem.h"

OxMem::OxMem( char const * name, unsigned int size ) {

  this->name = name;
  if ( this->shm == 0 ) {
    this->shm = new bip::managed_shared_memory(bip::open_or_create,
                                               this->name.c_str(),
                                               size*sizeof(std::size_t));
  }
}

OxMem::~OxMem(){
   bip::shared_memory_object::remove(this->name.c_str());
   delete this->shm;
}
