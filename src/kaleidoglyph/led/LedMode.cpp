// -*- c++ -*-

#include "kaleidoglyph/led/LedMode.h"
#include "kaleidoglyph/led/LedController.h"

namespace kaleidoglyph {

// Temporary initialization of LedController pointer. This gets set when the
// LedController object is created, via `initializeController()`.
LedManager* LedMode::led_manager_p_{nullptr};

LedManager& LedMode::manager() {
  return *led_manager_p_;
}

void LedMode::init(LedManager* led_manager_p) {
  assert(led_manager_p_ == nullptr);
  led_manager_p_ = led_manager_p;
}

bool LedMode::isActive() const {
  assert(led_manager_p_ != nullptr);
  return (this->id_ == led_manager_p_->activeModeIndex());
}

}  // namespace kaleidoglyph
