#include <boost/chrono/system_clocks.hpp>
#include "named_store.h"
#include "oxapp.h"

template <class STORE_T>
NamedStore<STORE_T>::NamedStore(){
  vals=0;
  times=0;
  name="";
  shm=0;
  is_shared_mem = false;
  dimension = 0;
}

template <class STORE_T>
NamedStore<STORE_T>::NamedStore(const unsigned int &dimension ) {
  this->dimension = dimension;
  vals = new STORE_T[dimension];
  times = new uint64_t[dimension];
  shm=0;
  is_shared_mem = false;
  name ="";
}
template <class STORE_T>
NamedStore<STORE_T>::NamedStore( char const * name,
                        bip::managed_shared_memory *shm,
                        const unsigned int &dimension ) {

  /*
   * First see if the shared memeory object exists. If
   * it does, open it.
   */
  this->name = name;
  this->dimension = dimension;
  
  std::pair<STORE_T*, std::size_t> p = shm->find<STORE_T>(this->name.c_str());
  
  if (p.first == 0 ) {
    this->vals=shm->construct<STORE_T>(this->name.c_str())[this->dimension](0);
  } else {
    this->vals = p.first;
  }

  std::string time_name = this->name + std::string("_time");
  std::pair<uint64_t*, std::size_t> pt = shm->find<uint64_t>(time_name.c_str());

  if (pt.first == 0 ) {
    this->times = shm->construct<uint64_t>(time_name.c_str())[dimension](0);
  } else {
    this->times = pt.first;
  }

  
  
  this->shm = shm;
  this->is_shared_mem = true;
  
}

template <class STORE_T>
void NamedStore<STORE_T>::set_val( unsigned int index, STORE_T val ) {
  vals[index] = val;
  times[index] =  OxApp:: get_time_ms();
}
template <class STORE_T>
STORE_T NamedStore<STORE_T>::get_val( unsigned int index ){
  return vals[index];
}
template <class STORE_T>
uint64_t NamedStore<STORE_T>::get_time( unsigned int index ){
  return times[index];
}

template <class STORE_T>
NamedStore<STORE_T>::NamedStore(const NamedStore& rhs) {
  // This is a bug, if rhs gets deleted then rhs.vals goes away
  // need to caopy here or steal the shm ptr *fixed now*
  if (rhs.is_shared_mem) {
    vals = rhs.vals;
  } else {
    vals = new STORE_T[dimension];
  }
  name = rhs.name;
  shm = rhs.shm;
  is_shared_mem = rhs.is_shared_mem;
    
}

template <class STORE_T>
NamedStore<STORE_T>::~NamedStore() {

  std::string time_name = this->name + std::string("_time");
  
  if (is_shared_mem) {
    shm->destroy<STORE_T>(name.c_str());
    shm->destroy<long>(time_name.c_str());
  } else {
    delete [] vals;
    delete [] times;
  }
}
template class NamedStore<int>;
template class NamedStore<long>;
template class NamedStore<double>;
template class NamedStore<float>;

template class NamedStore<int16_t>;
template class NamedStore<uint64_t>;

