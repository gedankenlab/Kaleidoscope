// -*- c++ -*-

#pragma once

#include <Arduino.h>

#include "kaleidoglyph/EventHandlerResult.h"
#include "kaleidoglyph/KeyEvent.h"
#include "kaleidoglyph/hid/Report.h"

namespace kaleidoglyph {

class Plugin {

 public:
  // Note: The following functions would ideally be virtual, but aren't because the
  // compiler stores the vtables in RAM, not just in PROGMEM. This would rapidly use up an
  // unacceptably large amount of precious memory in an AVR chip, so we simply shadow
  // them, rather than doing proper inheritance. I don't like this much, but it's the best
  // solution we have right now. In fact, as it is, the plugins don't even really need to
  // inherit from this class at all, and the functions here are mostly pointless.

  // Run every cycle before the keyswitch scan
  void preKeyswitchScan() {}
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
  bool preKeyboardReport(hid::keyboard::Report& keyboard_report) {
    return true;
  }

  // Runs after a keyboard HID report is sent to the host
  void postKeyboardReport(KeyEvent event) {}

  // TODO: add LED update hook(s), mouse report hook(s), maybe onSetup()
  
};

} // namespace kaleidoglyph {
