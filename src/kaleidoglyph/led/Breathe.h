// -*- c++ -*-

#pragma once

#include <Kaleidoglyph.h>

#include <kaleidoglyph/KeyAddr.h>
#include <kaleidoglyph/Color.h>
#include <kaleidoglyph/led/utils.h>
#include "kaleidoglyph/led/LedMode.h"


namespace kaleidoglyph {

class LedBreatheMode : public LedMode {

 public:
  LedBreatheMode(byte hue = 170) : hue_(hue) {}

  byte getHue() const { return hue_; }
  void setHue(byte hue) { hue_ = hue; }

  // The itinerant Updater class is what does the actual work
  class Updater : public LedModeUpdater {
   private:
    LedBreatheMode& mode_;

   public:
    Updater(LedBreatheMode& mode) : mode_(mode) {}
    void update() override;
   private:
    byte getHue() const { return mode_.getHue(); }
  };

 private:
  byte hue_;

};

inline
void LedBreatheMode::Updater::update() {
  Color color = breathCompute(mode_.getHue());
  LedMode::manager().setKeyColor(color);
}

//} // namespace led {
} // namespace kaleidoglyph {
