#ifndef __named_store_h__
#define __named_store_h__

#include <boost/interprocess/managed_shared_memory.hpp>
#include <string.h>
#include "ns.h"

static const unsigned int X=0;
static const unsigned int Y=1;
static const unsigned int Z=2;
static const unsigned int V=0;

template <class STORE_T> class NamedStore {

public:
  NamedStore();

  NamedStore( const unsigned int &dimension );


  NamedStore( char const * name,
              bip::managed_shared_memory *shm,
              const unsigned int &dimension );

  NamedStore(const NamedStore& rhs);

  ~NamedStore();

  void set_val( unsigned int index, STORE_T val );
  STORE_T get_val( unsigned int index );

                
private:
  
  STORE_T *vals;
  unsigned int dimension;
  std::string name;
  bip::managed_shared_memory * shm;
  bool is_shared_mem;

};

#endif
