// -*- c++ -*-

#include "kaleidoglyph/led/LedController.h"

namespace kaleidoglyph {

// Possibly useful to LED modes
Color LedManager::getKeyColor(KeyAddr k) const {
  return keyboard_.getKeyColor(k);
}

// Set the color of a key. It will get updated on the next LED update.
void LedManager::setKeyColor(KeyAddr k, Color color) {
  keyboard_.setKeyColor(k, color);
}

// Set the color of an LED directly. This will be needed for LEDs not associated
// with individual keys.
void LedManager::setLedColor(LedAddr led, Color color) {
  keyboard_.setLedColor(led, color);
}

// Set the color of all keys
void LedManager::setKeyColor(Color color) {
  for (KeyAddr k : KeyAddr::Iterator{}) {
    setKeyColor(k, color);
  }
}

// When LED modes change, all we do is set this index; the actual mode change
// takes place in sync with the LED update cycle.
void LedManager::setActiveMode(byte index) {
  next_mode_index_ = index;
}

// A plugin can call this function to signal that it will override the
// background LED mode before the next update. It doesn't set the LED at that
// time, because it needs to repeatedly override the background LED mode anyway.
void LedManager::setForeground(KeyAddr k) {
  foreground_mask_.set(k);
}

void LedManager::clearBackgroundColors() {
  setKeyColor(Color{0, 0, 0});
}

void LedManager::activateBackgroundMode() {
  // This function needs to be the place where the active LED mode gets swapped
  // out for a new one from the list in PROGMEM. Note: we don't clear the
  // existing colors here; the new mode is responsible for doing so itself.
  if (isValidMode(curr_mode_index_)) {
    // read loader from progmem
    LedModeLoader loader =
        readFromProgmem(pgm_updater_loaders_[curr_mode_index_]);
    // set current mode pointer. I'm not sure we actually need this for
    // anything.
    curr_mode_p_ = loader.led_mode_p;
    // load current mode's updater. This replaces the previous updater, so now
    // `updater_p_` is a pointer to the new curent mode's updater.
    loader.loadUpdater(curr_mode_p_, updater_p_);
    // activate current led mode
    updater_p_->activate();
  } else {
    clearBackgroundColors();
  }
}

void LedManager::updateBackgroundColors() {
  if (isValidMode(curr_mode_index_)) {
    updater_p_->update();
  }
}

void LedManager::preKeyswitchScan() {
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
      sync_complete    = false;
      return;
    }
    sync_complete = keyboard_.syncLeds();
    return;
  }

  byte current_time = Controller::scanStartTime();
  byte elapsed_time = current_time - last_sync_time;
  if (elapsed_time > led_sync_interval) {
    restoreForegroundColors();
    sync_in_progress = true;
    last_sync_time   = current_time;
  }
}

void LedManager::restoreForegroundColors() {
  for (KeyAddr k : foreground_mask_) {
    bool masked = hooks::setForegroundColor(k);
    // a plugin's `setForegroundColor()` function will call
    // `led_manager->setKeyColor()` and return `true`, or it will return
    // `false`, and the next plugin will get called.
    if (!masked) {
      foreground_mask_.clear(k);
      restoreBackgroundColor(k);
    }
  }
}

// Called when a foreground override comes to an end, and we need to restore the
// color of an LED based on the current mode.
void LedManager::restoreBackgroundColor(KeyAddr k) {
  if (isValidMode(curr_mode_index_)) {
    updater_p_->restore(k);
  } else {
    setKeyColor(k, Color{0, 0, 0});
  }
}

EventHandlerResult LedManager::onKeyEvent(KeyEvent& event) {
  if (event.state.toggledOn()) {
    if (event.key == cLedKey::next_mode) {
      nextMode();
    }
  }
  return EventHandlerResult::proceed;
}

}  // namespace kaleidoglyph
