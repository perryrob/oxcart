/********************************************************************************

Copyright (c) 2017 Bob Perry / asw204k_AT_yahoo.com
All rights reserved.

Please see license in the project root directory fro more details

*/

#include "trivial_log.h"

void init_log()
{
    logging::core::get()->set_filter
    (
        logging::trivial::severity >= logging::trivial::debug
    );
}

void init_info_log()
{
    logging::core::get()->set_filter
    (
        logging::trivial::severity >= logging::trivial::info
    );
}


void init_production_log()
{
    logging::core::get()->set_filter
    (
        logging::trivial::severity >= logging::trivial::error
    );
}
