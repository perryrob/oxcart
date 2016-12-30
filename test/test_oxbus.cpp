#include <boost/chrono.hpp>
#include <cstdlib>
#include <cassert>
#include "oxmem.h"
#include "oxbus.h"
#include "named_store.h"

using namespace std;

class OxBusTest : public OxBus {

public:

  NamedStore<int> *ns;

  unsigned int dim;
 
  OxBusTest() {
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
  
  ~OxBusTest() {
    delete ns;
  }
  
};

int main(int argc, char *argv[] ) {

  if(argc == 1){ 

    OxMem *oxm = new OxMem("OX",100);

    OxBus::set_shared_mem( oxm->get_shm() );

    OxBusTest * ot = new OxBusTest();
    ot->run();
    b::this_thread::sleep_for(b::chrono::milliseconds{1});
    ot->stop();

    assert( ot->get_val() > 0 );
    
    delete ot;
    delete oxm;
  }
}
