// -*- c++ -*-

#pragma once

#include <Arduino.h>


namespace kaleidoglyph {

enum class EventHandlerResult : byte {

  ok,
  done,
  nxplugin,

};

} // namespace kaleidoglyph {
