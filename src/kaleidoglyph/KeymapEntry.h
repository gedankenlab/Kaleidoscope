// -*- c++ -*-

#pragma once

#include "kaleidoglyph/Key.h"
#include "kaleidoglyph/KeyAddr.h"

namespace kaleidoglyph {

struct KeymapEntry {

  KeyAddr addr;
  Key     key;

  // This class will need methods for reading from PROGMEM & EEPROM, a la Key
};

} // namespace kaleidoglyph {
