// -*- c++ -*-

#pragma once

#include <Arduino.h>

#include "kaleidoscope/Key.h"


namespace kaleidoscope {


struct LayerKey {
  byte layer;
  Key  key;
};

} // namespace kaleidoscope {
