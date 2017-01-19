#ifndef __named_store_h__
#define __named_store_h__

#include <boost/interprocess/managed_shared_memory.hpp>
#include <string.h>
#include "ns.h"

static const unsigned int X=0;
static const unsigned int Y=1;
static const unsigned int Z=2;
static const unsigned int V=0;
static const unsigned int BMP_ALTITUDE=0;

static const unsigned int CH1=0;
static const unsigned int CH2=1;
static const unsigned int CH3=2;
static const unsigned int CH4=3;
static const unsigned int CH5=4;
static const unsigned int CH6=5;
static const unsigned int CH7=6;
static const unsigned int CH8=7;

static const unsigned int TIME=0;
static const unsigned int MODE=0;

static const unsigned int LONGITUDE=0;
static const unsigned int LATITUDE=1;
static const unsigned int GPS_ALTITUDE=2;
static const unsigned int SPEED=3;
static const unsigned int VERT_SPEED=4;
static const unsigned int TRACK=5;




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
