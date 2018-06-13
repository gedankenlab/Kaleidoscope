// -*- c++ -*-

#pragma once

#include <Arduino.h>


namespace kaleidoglyph {

enum class EventHandlerResult : byte {

  proceed,
  abort,
  nxplugin,

};

} // namespace kaleidoglyph {
