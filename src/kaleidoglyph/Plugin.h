// -*- c++ -*-

#pragma once

#include <Arduino.h>

#include "kaleidoglyph/KeyswitchEvent.h"
#include "kaleidoglyph/KeyArray.h"
#include "kaleidoglyph/hid/Report.h"

namespace kaleidoglyph {

class Plugin {

 public:

  // Run every cycle before the keyswitch scan
  virtual void preScanHook(uint16_t current_time) {}

  // I might decide to break this up into multiple hooks
  virtual bool keyswitchEventHook(KeyswitchEvent& event, Plugin*& caller) {
    return true;
  }

  // Should probably be renamed preKeyboardReportHook()
  virtual bool preReportHook(hid::keyboard::Report& keyboard_report) {
    return true;
  }

  // Should probably be renamed postKeyboardReportHook()
  virtual void postReportHook(KeyswitchEvent event) {}
  
 protected:

};

} // namespace kaleidoglyph {
