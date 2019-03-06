// -*- c++ -*-

#pragma once

#include <Kaleidoglyph.h>

#include <kaleidoglyph/KeyAddr.h>
#include <kaleidoglyph/Color.h>


namespace kaleidoglyph {
//namespace led {

// Forward declaration; we can't include the header
class LedController;

class LedSolidColorMode : public LedBackgroundMode {

 public:

  LedSolidColorMode(Color background_color)
      : background_color_(background_color) {}

  void activate(LedController& led_controller) override {
    led_controller.setKeyColor(background_color_);
  }

  Color getKeyColor(KeyAddr /*k*/) const override {
    return background_color_;
  }


 private:

  Color background_color_;

};

//} // namespace led {
} // namespace kaleidoglyph {
