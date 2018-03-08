// -*- c++ -*-

#pragma once

#include KALEIDOSCOPE_HARDWARE_H
#include KALEIDOSCOPE_KEYADDR_H
#include "kaleidoscope/Key.h"


namespace kaleidoscope {

struct KeymapEntry {

  KeyAddr addr;
  Key     key;

  // This class will need methods for reading from PROGMEM & EEPROM, a la Key
};

} // namespace kaleidoscope {
