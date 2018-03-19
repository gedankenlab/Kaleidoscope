// -*- c++ -*-

#pragma once

#include <Arduino.h>

#include "kaleidoscope/Key.h"

// I think this class can be the whole interface to the HID module, with the probable
// exception of Mouse & AbsoluteMouse

// This version uses KeyboardioHID, not the rewrite

namespace kaleidoscope {
namespace hid {

namespace keyboard {

class Report {
 public:
  void init();
  void clear();
  void add(Key key, byte mods_allowed = 0xFF);
  void remove(Key key);
  void send();
  //byte activeMods();
  byte hostLedStates() const;
 private:
  //bool nkro_keyboard_;
};

} // namespace keyboard {


namespace mouse {

} // namespace mouse {

} // namespace hid {
} // namespace kaleidoscope {
