// -*- c++ -*-

#pragma once

#include KALEIDOGLYPH_HARDWARE_H
#include KALEIDOGLYPH_KEYADDR_H

#include "kaleidoglyph/Key.h"
#include "kaleidoglyph/cKey.h"
#include "kaleidoglyph/KeyState.h"


namespace kaleidoglyph {

struct KeyEvent {

  Key       key;
  KeyAddr   addr;
  KeyState  state;
  byte      caller;

  KeyEvent() {}

  KeyEvent(KeyAddr _addr, KeyState _state, Key _key = cKey::clear)
    : key(_key), addr(_addr), state(_state) {}

};

} // namespace kaleidoglyph {
