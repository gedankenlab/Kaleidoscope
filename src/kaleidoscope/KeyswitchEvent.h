// -*- c++ -*-

#pragma once

//#include KALEIDOSCOPE_HARDWARE_H
//#include KALEIDOSCOPE_KEYADDR_H

#include "model01/KeyAddr.h"
#include "key_defs.h"
#include "kaleidoscope/KeyswitchState.h"


namespace kaleidoscope {

struct KeyswitchEvent {

  Key             key;
  KeyAddr         addr;
  KeyswitchState  state;

  KeyswitchEvent() = default;
  KeyswitchEvent(Key _key, KeyAddr _addr, KeyswitchState _state)
    : key(_key), addr(_addr), state(_state) {}

};

} // namespace kaleidoscope {
