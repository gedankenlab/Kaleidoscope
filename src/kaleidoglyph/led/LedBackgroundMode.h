// -*- c++ -*-

#pragma once

#include <Kaleidoglyph.h>

#include <kaleidoglyph/KeyAddr.h>


namespace kaleidoglyph {

// Forward declaration; we can't include the header
class LedController;

class LedBackgroundMode : public Plugin {

 public:
  virtual void activate(LedController&) {}
  virtual void update(LedController&) {}
  virtual Color getKeyColor(KeyAddr /*k*/) const {
    return Color{0, 0, 0};
  }

};

} // namespace kaleidoglyph {
