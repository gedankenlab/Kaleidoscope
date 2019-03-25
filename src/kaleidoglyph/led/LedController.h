// -*- c++ -*-

#pragma once

#include <Arduino.h>

#include "kaleidoglyph/hardware/Keyboard.h"
#include "kaleidoglyph/KeyAddr.h"
#include "kaleidoglyph/Color.h"
#include "kaleidoglyph/KeyAddrBitfield.h"
#include "kaleidoglyph/led/LedBackgroundMode.h"
#include "kaleidoglyph/utils.h"
#include "kaleidoglyph/hooks.h"


namespace kaleidoglyph {

#if defined(LED_CONTROLLER_CONSTANTS_H)
#include LED_CONTROLLER_CONSTANTS_H
#else
constexpr byte led_sync_interval{32};
#endif

class LedController {

 public:
  template<byte _modes_count>
  LedController(LedBackgroundMode* const (&modes)[_modes_count],
                Controller& controller,
                hardware::Keyboard& keyboard)
      : controller_(controller),
        keyboard_(keyboard),
        modes_(modes),
        modes_count_(_modes_count) {}

  // Note we don't provied LedAddr versions of these, because that makes the overrides
  // overly complex.
  Color getKeyColor(KeyAddr k) const;
  void setKeyColor(KeyAddr k, Color color);
  void setKeyColor(Color color);
  void setLedColor(LedAddr led, Color color);

  void preKeyswitchScan();
  EventHandlerResult onKeyEvent(KeyEvent& event);
  
  void setForeground(KeyAddr k);

  void nextMode() {
    next_mode_index_ = curr_mode_index_ + 1;
    if (next_mode_index_ > modes_count_)
      next_mode_index_ = 0;
  }
  void backgroundOff() {
    next_mode_index_ = 0xFF;
  }

  LedBackgroundMode& getCurrentMode() const;
  void setActiveMode(byte index);

  // We need a hook somewhere for layer changes (see LED-ActiveLayerColor.cpp)


 private:

  static constexpr byte invalid_index_{0xFF};

  Controller& controller_;
  hardware::Keyboard& keyboard_;

  LedBackgroundMode* const *modes_;
  byte               const  modes_count_;

  byte curr_mode_index_{invalid_index_};
  byte next_mode_index_{invalid_index_};

  //LedMode* active_mode_{nullptr};

  KeyAddrBitfield foreground_mask_;

  void restoreForegroundColors();
  void restoreBackgroundColor(KeyAddr k);
  
  void activateBackgroundMode();
  void updateBackgroundColors();
  void clearBackgroundColors();

  bool isValidMode(byte index) {
    return (index < modes_count_);
  }

};

// Possibly useful to LED modes
inline
Color LedController::getKeyColor(KeyAddr k) const {
  return keyboard_.getKeyColor(k);
}

// Set the color of a key. It will get updated on the next LED update.
inline
void LedController::setKeyColor(KeyAddr k, Color color) {
  keyboard_.setKeyColor(k, color);
}

inline
void LedController::setLedColor(LedAddr led, Color color) {
  keyboard_.setLedColor(led, color);
}

inline
void LedController::setKeyColor(Color color) {
  for (KeyAddr k{cKeyAddr::start}; k < cKeyAddr::end; ++k) {
    setKeyColor(k, color);
  }
}

inline
LedBackgroundMode& LedController::getCurrentMode() const {
  return *(readPointerFromProgmemArrayPtr(modes_, curr_mode_index_));
}

// When LED modes change, all we do is set this index; the actual mode change takes place
// in sync with the LED update cycle.
inline
void LedController::setActiveMode(byte index) {
  next_mode_index_ = index;
}

// A plugin can call this function to signal that it will override the background LED mode
// before the next update. It doesn't set the LED at that time, because it needs to
// repeatedly override the background LED mode anyway.
inline
void LedController::setForeground(KeyAddr k) {
  foreground_mask_.set(k);
}

inline
void LedController::restoreBackgroundColor(KeyAddr k) {
  foreground_mask_.clear(k);
  if (isValidMode(curr_mode_index_)) {
    Color color = getCurrentMode().getKeyColor(k);
    setKeyColor(k, color);
  } else {
    setKeyColor(k, Color{0, 0, 0});
  }
}

inline
void LedController::clearBackgroundColors() {
  for (KeyAddr k{cKeyAddr::start}; k < cKeyAddr::end; ++k) {
    setKeyColor(k, Color{0, 0, 0});
  }
}

inline
void LedController::activateBackgroundMode() {
  clearBackgroundColors();
  if (isValidMode(curr_mode_index_)) {
    getCurrentMode().activate(*this);
  }
}

inline
void LedController::updateBackgroundColors() {
  if (isValidMode(curr_mode_index_)) {
    getCurrentMode().update(*this);
  }
}

inline
void LedController::preKeyswitchScan() {
  static byte last_sync_time{0};
  static bool sync_in_progress{false};
  static bool sync_complete{false};

  if (sync_in_progress) {
    if (sync_complete) {
      if (next_mode_index_ != curr_mode_index_) {
        curr_mode_index_ = next_mode_index_;
        activateBackgroundMode();
      } else {
        updateBackgroundColors();
      }
      sync_in_progress = false;
      sync_complete = false;
      return;
    }
    sync_complete = keyboard_.syncLeds();
    return;
  }

  // This is the only thing we need the Controller reference for. It's a run-time only
  // thing, and I'd like to get rid of that initialization order dependency, without
  // resorting to global singletons.
  byte current_time = Controller::scanStartTime();
  byte elapsed_time = current_time - last_sync_time;
  if (elapsed_time > led_sync_interval) {
    restoreForegroundColors();
    sync_in_progress = true;
    last_sync_time = current_time;
  }
}

inline
void LedController::restoreForegroundColors() {
  for (KeyAddr k : foreground_mask_) {
    bool masked = hooks::setForegroundColor(k, *this);
    // a plugin's `setForegroundColor()` function will call
    // `led_controller->setKeyColor()` and return `true`, or return `false`.
    if (! masked)
      restoreBackgroundColor(k);
  }
}

inline
EventHandlerResult LedController::onKeyEvent(KeyEvent& event) {
  if (event.state.toggledOn()) {
    if (event.key == cLedKey::next_mode) {
      nextMode();
    }
  }
  return EventHandlerResult::proceed;
}

} // namespace kaleidoglyph {
