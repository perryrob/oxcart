/*
 * Input event codes
 *
 *    *** IMPORTANT ***
 * This file is not only included from C-code but also from devicetree source
 * files. As such this file MUST only contain comments and defines.
 *
 * Copyright (c) 1999-2002 Vojtech Pavlik
 * Copyright (c) 2015 Hans de Goede <hdegoede@redhat.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by
 * the Free Software Foundation.
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
