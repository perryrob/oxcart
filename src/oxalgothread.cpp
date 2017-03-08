/********************************************************************************

Copyright (c) 2017 Bob Perry / asw204k_AT_yahoo.com
All rights reserved.

Please see license in the project root directory fro more details

*/

#include "oxalgothread.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>

void OxAlgoThread::threaded_task() {
  BOOST_LOG_TRIVIAL(debug) << "threaded_task()";
  while (keep_running) {
    BOOST_LOG_TRIVIAL(debug) <<  "while";
    for( std::deque<OxAlgo*>::iterator itr = algos.begin();
         itr != algos.end(); ++itr ) {
      BOOST_LOG_TRIVIAL(debug) <<  "for";
      BOOST_LOG_TRIVIAL(debug) <<  "rw: " << (*itr)->get_name();
      if ((*itr)->run_it()) {
        (*itr)->run_algo();
        b::this_thread::sleep(b::posix_time::milliseconds(5));
      }
    }
    b::this_thread::yield();
  }
  BOOST_LOG_TRIVIAL(debug) << "threaded_task() COMPLETE";
}


void OxAlgoThread::run() {
  BOOST_LOG_TRIVIAL(debug) <<  "run called";
  keep_running = true;
  thr = new b::thread(b::bind(&OxAlgoThread::threaded_task, this));
  BOOST_LOG_TRIVIAL(debug) <<  "thread new";
}

void OxAlgoThread::stop() {
  keep_running = false;
  thr->join();
  delete thr;
  thr = 0;
}

void OxAlgoThread::add_algo( OxAlgo *algo ) {
  algos.push_back( algo );
  BOOST_LOG_TRIVIAL(debug) <<  "add_algo: " << algo->get_name();
}
  
OxAlgoThread::~OxAlgoThread() {
  keep_running = false;
  delete thr;
  algos.clear();
}
