// -*- c++ -*-

#pragma once

#include KALEIDOGLYPH_HARDWARE_H
#include KALEIDOGLYPH_KEYADDR_H
#include "kaleidoglyph/Key.h"


namespace kaleidoglyph {

struct KeymapEntry {

  KeyAddr addr;
  Key     key;

  // This class will need methods for reading from PROGMEM & EEPROM, a la Key
};

} // namespace kaleidoglyph {
