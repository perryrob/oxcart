/********************************************************************************

Copyright (c) 2017 Bob Perry / asw204k_AT_yahoo.com
All rights reserved.

Please see license in the project root directory fro more details

*/

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <cstdlib>
#include <string>
#include <cassert>
#include <iostream>
#include "named_store.h"
#include "oxapp.h"

using namespace std;

int main(int argc, char *argv[] ) {

  if(argc == 1){ 
    struct shm_remove {
      shm_remove() { bip::shared_memory_object::remove("MySharedMemory"); }
      ~shm_remove(){ bip::shared_memory_object::remove("MySharedMemory"); }
    } remover;

    //Create a shared memory object.
    bip::managed_shared_memory shm(bip::create_only,
                                   "MySharedMemory",
                                   10000*sizeof(std::size_t));
    
    unsigned int dim = 3;
  
    NamedStore<double> *ns_nsm = new NamedStore<double>(dim);
    cerr << "Setting nsm vals ";
    ns_nsm->set_val(X,123.45);
    ns_nsm->set_val(Y,234.56);
    ns_nsm->set_val(Z,345.67);  

    cerr << "OK" << endl << "checking asserts ";

    assert( ns_nsm->get_val(X) == 123.45 );
    assert( ns_nsm->get_val(Y) == 234.56 );
    assert( ns_nsm->get_val(Z) == 345.67 );
    
    delete ns_nsm;
    cerr << "OK delete..." << endl;;
    
    NamedStore<double> *ns_sm= new NamedStore<double>("Accel",&shm,dim);
    
    cerr << "Setting sm vals ";
    ns_sm->set_val(X,123.45);
    ns_sm->set_val(Y,234.56);
    ns_sm->set_val(Z,345.67);  

    cerr << "OK" << endl << "checking asserts ";
  
    assert( ns_sm->get_val(X) == 123.45 );
    assert( ns_sm->get_val(Y) == 234.56 );
    assert( ns_sm->get_val(Z) == 345.67 );

    string s(argv[0]); s += " child ";
    if(0 != system(s.c_str()))
      return 1;
    
    delete ns_sm;
    cerr << "OK delete..." << endl;;
  }
  else {
    cerr << "else" << endl;
    //Open already created shared memory object.
    
    bip::managed_shared_memory shm(bip::open_only,
                                   "MySharedMemory");

    NamedStore<double> ns_sm("Accel",&shm,3);
    ns_sm.set_val(X, 0.0);
    cerr << "Setting X val to 0.0 to kill the other process." << endl;
  }
}
