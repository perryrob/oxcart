#ifndef __TRIVIAL_LOG_H__
#define __TRIVIAL_LOG_H__

#define BOOST_LOG_DYN_LINK 1

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>

namespace logging = boost::log;

void init_log();

#endif
