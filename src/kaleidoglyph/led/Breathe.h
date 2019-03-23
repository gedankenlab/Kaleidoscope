// -*- c++ -*-

#pragma once

#include <Kaleidoglyph.h>

#include <kaleidoglyph/KeyAddr.h>
#include <kaleidoglyph/Color.h>
#include <kaleidoglyph/led/utils.h>


namespace kaleidoglyph {
//namespace led {

// Forward declaration; we can't include the header
class LedController;

class LedBreatheMode : public LedBackgroundMode {

 public:

  LedBreatheMode(byte hue = 170) : hue_(hue) {}

  void update(LedController& led_controller) override;

  void setHue(byte hue) { hue_ = hue; }

 private:

  byte hue_;

};

inline
void LedBreatheMode::update(LedController& led_controller) {
  Color color = breathCompute(hue_);
  led_controller.setKeyColor(color);
}

//} // namespace led {
} // namespace kaleidoglyph {
