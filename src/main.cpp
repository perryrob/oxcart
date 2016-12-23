#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <cstring>
#include <cstdlib>
#include <string>
#include <sys/wait.h>
#include <iostream>

using namespace std;
namespace b = boost;
namespace bip = b::interprocess;


class _3d {
public:
  _3d() {x=0;y=0;z=0;}
  double x,y,z;
};

class _thread {

private:
  b::thread* thr;

public:

  bool keep_going;
  
  _thread(){ keep_going = true;}
  
  void wait(int seconds)
  {
    b::this_thread::sleep_for(b::chrono::seconds{seconds});
  }

  void thread()
  {
    for (int i = 0; i < 20; ++i)
      {
        this->wait(1);
        cout << i << '\n';
      }
    keep_going = false;
  }
  void run() {
    thr = new boost::thread(b::bind(&_thread::thread, this));
  }
  ~_thread() { delete thr; } 
};

int main(int argc, char *argv[])
{   

   cerr << "main" << endl;
   if(argc == 1){  //Parent process

     //Remove shared memory on construction and destruction
      struct shm_remove
      {
        shm_remove() { bip::shared_memory_object::remove("MySharedMemory"); }
        ~shm_remove(){ bip::shared_memory_object::remove("MySharedMemory"); }
      } remover;

      cerr << "if" << endl;
      
      //Create a shared memory object.
      bip::managed_shared_memory shm(bip::create_only,
                                     "MySharedMemory",
                                     10000*sizeof(std::size_t));

      _3d *accel = shm.construct<_3d>("Accel")();
      accel->x=1.0;
      accel->y=2.12334;
      accel->z=3.0;

      
      _thread thread;
      thread.run();

      while (thread.keep_going){
        thread.wait(1);
      }
      cerr << "done." << endl;
   }
   else{
     std::cerr << "else" << std::endl;
     //Open already created shared memory object.

     bip::managed_shared_memory shm(bip::open_only,
                                    "MySharedMemory");

     _3d *accel = shm.find_or_construct_it<_3d>("Accel")();

     cerr << accel->x << endl;
     cerr << accel->y << endl;
     cerr << accel->z << endl;     
   }
   return 0;
}
