#include <boost/chrono.hpp>
#include <cstdlib>
#include <cassert>
#include "oxmem.h"
#include "oxdev.h"
#include "named_store.h"

using namespace std;

class OxDevTest : public OxDev {

public:

  NamedStore<int> *ns;

  unsigned int dim;
 
  OxDevTest() {
    dim = 1;
    ns = new NamedStore<int>("test",shm,dim);
  }
  
  void threaded_task() {
    int i=0;
    while (is_running) {
      std::cerr << ".";
      ns->set_val(X,i++);
    }
    std::cerr << "done." << std::endl;
  }  

  int get_val() {
    NamedStore<int> junk( "test",shm,dim);
    return junk.get_val(X);
  }
  
  ~OxDevTest() {
    delete ns;
  }
  
};

int main(int argc, char *argv[] ) {

  if(argc == 1){ 

    OxMem *oxm = new OxMem("OX",100);

    OxDev::set_shared_mem( oxm->get_shm() );

    OxDevTest * ot = new OxDevTest();
    ot->run();
    b::this_thread::sleep_for(b::chrono::milliseconds{1});
    ot->stop();

    assert( ot->get_val() > 0 );
    
    delete ot;
    delete oxm;
  }
}
