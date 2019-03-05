// -*- c++ -*-

#pragma once

#include <Kaleidoglyph.h>

#include <kaleidoglyph/KeyAddr.h>
#include <kaleidoglyph/led/LedController.h>


namespace kaleidoglyph {

class LedForegroundMode : public Plugin {

 public:
  bool setForegroundColor(KeyAddr /*k*/, LedController& /*led_controller*/) {
    return false;
  }

};

} // namespace kaleidoglyph {
