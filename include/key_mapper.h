/********************************************************************************

Copyright (c) 2017 Bob Perry / asw204k_AT_yahoo.com
All rights reserved.

Please see license in the project root directory fro more details

*/

#ifndef __KEY_MAPPER_H__
#define __KEY_MAPPER_H__

#include <linux/input-event-codes.h>
#include <stdint.h>

class KeyMapper {
  
public:

  KeyMapper() {}

  char get_char_from_code( uint8_t );
  uint8_t get_action_from_code( uint8_t );

};
#endif
