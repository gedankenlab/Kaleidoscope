// -*- c++ -*-

#pragma once

#include <Kaleidoglyph.h>

#include <kaleidoglyph/KeyAddr.h>


namespace kaleidoglyph {

// Forward declaration; we can't include the header
class LedController;

class LedBackgroundMode : public Plugin {

  friend class LedController;

 public:

 protected:
  bool isActive() const {
    assert(led_controller_p_ != nullptr);
    return (this->id_ == led_controller_p_->activeModeIndex());
  }
  static LedController& controller() const {
    return *led_controller_p_;
  }

 private:
  static LedController* led_controller_p_;
  static void initializeController(LedController* led_controller_p) {
    assert(led_controller_p_ == nullptr);
    led_controller_p_ = led_controller_p;
  }
  byte id_;
  void assignId(byte id) { id_ = id; }
};

} // namespace kaleidoglyph {
