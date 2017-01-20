
#include "trivial_log.h"

void init_log()
{
    logging::core::get()->set_filter
    (
        logging::trivial::severity >= logging::trivial::debug
    );
}

void init_production_log()
{
    logging::core::get()->set_filter
    (
        logging::trivial::severity >= logging::trivial::error
    );
}
