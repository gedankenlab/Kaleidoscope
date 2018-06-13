// -*- c++ -*-

#pragma once

#include <Arduino.h>

#include "kaleidoglyph/KeyEvent.h"
#include "kaleidoglyph/KeyArray.h"
#include "kaleidoglyph/hid/Report.h"

namespace kaleidoglyph {

class Plugin {

 public:

  // Run every cycle before the keyswitch scan
  void beforeKeyswitchScan(uint16_t current_time) {}
  // I should get rid of the current_time arg, and make that available more generally

  // Runs when a (physical) keyswitch event is processed
  EventHandlerResult onKeyswitchEvent(KeyEvent& event) {
    return EventHandlerResult::proceed;
  }

  // Runs when a (physical or injected) key event is processed
  EventHandlerResult onKeyEvent(KeyEvent& event) {
    return EventHandlerResult::proceed;
  }

  // Runs before a keyboard HID report is sent to the host
  bool beforeKeyboardReport(hid::keyboard::Report& keyboard_report) {
    return true;
  }

  // Runs after a keyboard HID report is sent to the host
  void afterKeyboardReport(KeyEvent event) {}

  // TODO: add LED update hook(s), mouse report hook(s), maybe onSetup()
  
};

} // namespace kaleidoglyph {
