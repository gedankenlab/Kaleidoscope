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
  virtual void preScanHook(uint16_t current_time) {}

  // I might decide to break this up into multiple hooks
  virtual bool keyswitchEventHook(KeyEvent& event, Plugin*& caller) {
    return true;
  }

  // Should probably be renamed preKeyboardReportHook()
  virtual bool preReportHook(hid::keyboard::Report& keyboard_report) {
    return true;
  }

  // Should probably be renamed postKeyboardReportHook()
  virtual void postReportHook(KeyEvent event) {}
  
 protected:

  // This should maybe use a void* instead of a Plugin*. Also, maybe this should be in
  // keyswitchEventHook instead? (with the return value reversed). No, and NO!
  virtual bool checkCaller(Plugin*& caller) const final {
    if (caller == nullptr)
      return false;
    if (caller == this)
      caller = nullptr;
    return true;
  }

};

} // namespace kaleidoglyph {
