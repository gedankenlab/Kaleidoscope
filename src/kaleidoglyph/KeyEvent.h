// -*- c++ -*-

#pragma once

#include "kaleidoglyph/Key.h"
#include "kaleidoglyph/KeyAddr.h"
#include "kaleidoglyph/KeyState.h"
#include "kaleidoglyph/cKey.h"


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
