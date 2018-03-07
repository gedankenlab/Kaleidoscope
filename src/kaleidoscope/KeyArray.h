// -*- c++ -*-

#pragma once

#include <Arduino.h>

#include KALEIDOSCOPE_HARDWARE_H

#include KALEIDOSCOPE_KEYADDR_H
#include "kaleidoscope/Key.h"


namespace kaleidoscope {

struct KeyArray {
  Key keys[total_keys];

  Key& operator[](KeyAddr k) {
    return keys[k.addr];
  }
  const Key& operator[](KeyAddr k) const {
    return keys[k.addr];
  }
};

} // namespace kaleidoscope {
