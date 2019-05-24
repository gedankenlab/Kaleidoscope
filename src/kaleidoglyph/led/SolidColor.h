// -*- c++ -*-

#pragma once

#include <Kaleidoglyph.h>

#include <kaleidoglyph/KeyAddr.h>
#include <kaleidoglyph/Color.h>
#include <kaleidoglyph/led/LedMode.h>


namespace kaleidoglyph {

// Forward declaration; we can't include the header
//class LedManager;

class LedSolidColorMode : public LedMode {

 public:
  LedSolidColorMode()
      : background_color_({0, 0, 0}) {}

  LedSolidColorMode(Color background_color)
      : background_color_(background_color) {}

  Color getColor() { return background_color_; }

  class Updater : public LedModeUpdater {
   private:
    // we need a pointer of the LedMode's specific type.
    // LedSolidColorMode& owner() const {
    //   return *(static_cast<LedSolidColorMode*>(&owner_));
    // }
    LedSolidColorMode& mode_;

   public:
    Updater(LedSolidColorMode& mode) : mode_(mode) {}
    void activate() override {
      LedMode::manager().setKeyColor(mode_.getColor());
    }

    // This mode doesn't do any updating, so it needs this to restore a key's
    // color after a foreground override comes to an end.
    void restore(KeyAddr k) const override {
      LedMode::manager().setKeyColor(k, mode_.getColor());
    }
  };

 private:
  Color background_color_;

};

} // namespace kaleidoglyph {
