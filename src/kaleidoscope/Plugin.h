// -*- c++ -*-

#pragma once

#include <Arduino.h>

#include "kaleidoscope/KeyswitchEvent.h"
#include "kaleidoscope/KeyArray.h"
#include "kaleidoscope/hid/Report.h"

namespace kaleidoscope {

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

} // namespace kaleidoscope {
