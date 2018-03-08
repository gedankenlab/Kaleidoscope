// -*- c++ -*-

#pragma once

#include <Arduino.h>

namespace kaleidoscope {

// I guess this should probably go in the Key.h file, instead of here. Also, we need a
// type for LED keys, though that could be a plugin subtype.
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
