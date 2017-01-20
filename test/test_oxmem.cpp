#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <cstdlib>
#include <string>
#include <cassert>
#include <iostream>
#include "oxmem.h"
#include "named_store.h"

using namespace std;

int main(int argc, char *argv[] ) {

  if(argc == 1){ 

    OxMem *oxm = new OxMem("OX",64000);
    
    unsigned int dim = 3;
    
    NamedStore<double> *ns_sm= new NamedStore<double>("Accel",oxm->get_shm(),
                                                      dim);
    
    cerr << "Setting sm vals ";
    ns_sm->set_val(X,123.45);
    ns_sm->set_val(Y,234.56);
    ns_sm->set_val(Z,345.67);  

    cerr << "OK" << endl << "checking asserts " << endl;
  
    assert( ns_sm->get_val(X) == 123.45 );
    assert( ns_sm->get_val(Y) == 234.56 );
    assert( ns_sm->get_val(Z) == 345.67 );

    cerr << ns_sm->get_val(X) << " " << ns_sm->get_time(X) << endl;
    cerr << ns_sm->get_val(Y) << " " << ns_sm->get_time(Y) << endl;
    cerr << ns_sm->get_val(Z) << " " << ns_sm->get_time(Z) << endl;
    

    string s(argv[0]); s += " child ";
    if(0 != system(s.c_str()))
      return 1;
    
    delete ns_sm;
    cerr << "OK delete..." << endl;;
  }
  else {
    OxMem *oxm = new OxMem("OX",100);
    cerr << "else" << endl;
    NamedStore<double> *ns_sm= new NamedStore<double>("Accel",oxm->get_shm(),
                                                      3);
    ns_sm->set_val(X, 0.0);
    cerr << "Setting X val to 0.0 to kill the other process." << endl;
  }
}
