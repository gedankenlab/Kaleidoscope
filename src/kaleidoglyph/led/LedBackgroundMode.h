// -*- c++ -*-

#pragma once

#include <Kaleidoglyph.h>

namespace kaleidoglyph {
namespace led {

class BackgroundMode : public kaleidoglyph::Plugin {

 public:
  virtual void activate(LedController&) {}
  virtual void update(LedController&) {}
  virtual Color getKeyColor(KeyAddr) const { return Color{0, 0, 0}; }

};

} // namespace led {
} // namespace kaleidoglyph {
