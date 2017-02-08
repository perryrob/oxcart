#include "oxapp.h"
#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include "devices/KOBO.h"
#include <string>

void KOBO::rw_device() {


  std::string GPRMC( OxApp::GPRMC->get_str() );
  std::string GPGGA( OxApp::GPGGA->get_str() );

  bus->write( GPRMC );
  bus->write( GPGGA );

  b::this_thread::sleep(b::posix_time::milliseconds(100));
}
