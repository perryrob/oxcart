#ifndef __oxapp_h__
#define __oxapp_h__

#include <boost/interprocess/managed_shared_memory.hpp>

#include <string>

#include "named_store.h"
#include "ns.h"

static const std::string MEM_NAME="OXCART_V1"; 
static const unsigned int MEM_SIZE=64000;

class OxApp  {

public:

  OxApp(){}

  static bip::managed_shared_memory * create();
  static void destroy();
   
  static inline bip::managed_shared_memory * get_shared_mem() {
    return shm;
  }

  ~OxApp(){};
  
private:
  
  static bip::managed_shared_memory * shm;

};

#endif
