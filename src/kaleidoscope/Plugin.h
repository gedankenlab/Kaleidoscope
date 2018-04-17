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
  virtual void init(byte id) final {
    if (id_ == 0xFF)
      id_ = id;
  }

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

  // Maybe I've got this all wrong, and the caller should be a Plugin* (or void*).
  static constexpr byte controller_id_ {0xFF};

  // Unique ID number for the plugin. This will also be the index number in the
  // Controller's internal plugin array (but that shouldn't matter from here), which will
  // allow the Controller to store values and later call the correct plugin based on those
  // values. The default is all ones, which is an invalid value (if we ever have more than
  // 255 plugins, we'll need a bigger integer type), reserved for the Controller's ID
  // (when calling the keyswitch event hooks).
  byte id_ {controller_id_};

  // This function is used to prevent handling the same event twice; use it in event
  // handler hook functions for all plugins -- if it returns true, it means that the
  // plugin should ignore this event.
  virtual bool checkCallerId(byte& caller_id) const final {
    if (caller_id == controller_id_)
      return false;
    if (caller_id == this->id_)
      caller_id = controller_id_;
    return true;
  }

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
