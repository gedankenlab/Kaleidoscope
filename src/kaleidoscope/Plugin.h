// -*- c++ -*-

#pragma once

#include <Arduino.h>

#include "kaleidoscope/KeyswitchEvent.h"
#include "kaleidoscope/KeyArray.h"
#include "kaleidoscope/hid/Report.h"

namespace kaleidoscope {

class Plugin {

 public:
  // Maybe this should be `getId()`, and take a Controller as the parameter?
  void init(byte id) final {
    if (id_ == 0xFF)
      id_ = id;
  }

  // I might decide to break this up into multiple hooks
  virtual bool keyswitchEventHook(KeyswitchEvent& event,
                                  KeyArray& active_keys,
                                  byte& caller_id) {
    return true;
  }

  virtual bool preReportHook(hid::keyboard::Report& keyboard_report,
                             KeyArray& active_keys) {
    return true;
  }

  virtual void preScanHook(KeyArray& active_keys) {}
  
 protected:
  // Unique ID number for the plugin. This will also be the index number in the
  // Controller's internal plugin array (but that shouldn't matter from here), which will
  // allow the Controller to store values and later call the correct plugin based on those
  // values. The default is all ones, which is an invalid value (if we ever have more than
  // 255 plugins, we'll need a bigger integer type), reserved for the Controller's ID
  // (when calling the keyswitch event hooks).
  byte id_ {0xFF};

};

} // namespace kaleidoscope {
