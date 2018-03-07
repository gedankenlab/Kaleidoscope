// -*- c++ -*-

#pragma once

#include <Arduino.h>

namespace kaleidoscope {

// I guess this should probably go in the Key.h file, instead of here
enum class KeyFlavor : byte {
  keyboard,
  consumer,
  system,
  mouse,
  layer,
  plugin,
  unknown
};

} // namespace kaleidoscope {
