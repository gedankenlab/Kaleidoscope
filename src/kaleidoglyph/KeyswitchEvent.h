// -*- c++ -*-

#pragma once

#include KALEIDOGLYPH_HARDWARE_H
#include KALEIDOGLYPH_KEYADDR_H

#include "kaleidoglyph/Key.h"
#include "kaleidoglyph/cKey.h"
#include "kaleidoglyph/KeyswitchState.h"


namespace kaleidoglyph {

struct KeyswitchEvent {

  Key             key;
  KeyAddr         addr;
  KeyswitchState  state;

  KeyswitchEvent() {}

  KeyswitchEvent(KeyAddr _addr, KeyswitchState _state, Key _key = cKey::clear)
    : key(_key), addr(_addr), state(_state) {}

};

} // namespace kaleidoglyph {
