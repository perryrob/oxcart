/********************************************************************************

Copyright (c) 2017 Bob Perry / asw204k_AT_yahoo.com
All rights reserved.

Please see license in the project root directory fro more details

*/

#ifndef __named_store_h__
#define __named_store_h__

#include <boost/interprocess/managed_shared_memory.hpp>
#include <string.h>
#include "ns.h"


template <class STORE_T> class NamedStore {

public:
  NamedStore();

  NamedStore( const unsigned int &dimension );


  NamedStore( char const * name,
              bip::managed_shared_memory *shm,
              const unsigned int &dimension );

  NamedStore( char const * name,
              bip::managed_shared_memory *shm,
              const unsigned int &size,
              STORE_T initial_value);


  NamedStore(const NamedStore& rhs);

  ~NamedStore();

  void set_str( const STORE_T * str,unsigned int size);
  STORE_T * get_str();
  
  void set_val( unsigned int index, STORE_T val );
  STORE_T get_val( unsigned int index );
  uint64_t get_time( unsigned int index );
                
private:
  
  STORE_T *vals;
  uint64_t *times; //milliseconds
  unsigned int dimension;
  std::string name;
  bip::managed_shared_memory * shm;
  bool is_shared_mem;

};

#endif
