// -*- c++ -*-

#pragma once

#include <Arduino.h>

#include "kaleidoscope/KeyswitchEvent.h"
#include "kaleidoscope/KeyArray.h"
#include "kaleidoscope/hid/Report.h"

namespace kaleidoscope {

class Plugin {

 public:

  // I might decide to break this up into multiple hooks
  virtual bool keyswitchEventHook(KeyswitchEvent& event, Plugin*& caller) {
    return true;
  }

  virtual bool preReportHook(hid::keyboard::Report& keyboard_report) {
    return true;
  }

  virtual void postReportHook(KeyswitchEvent event) {}

  virtual void preScanHook(uint16_t current_time) {}
  
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
