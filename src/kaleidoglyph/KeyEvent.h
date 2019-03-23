// -*- c++ -*-

#pragma once

#include "kaleidoglyph/Key.h"
#include "kaleidoglyph/KeyAddr.h"
#include "kaleidoglyph/KeyState.h"
#include "kaleidoglyph/cKey.h"


namespace kaleidoglyph {

// I want to consider adding a serial number to KeyEvent, so that plugins can identify
// events that they record in their `onKeyEvent` handlers, and act on that event showing
// up in the `postKeyboardReport`, event if some of the other properites got changed along
// the way.
struct KeyEvent {

  KeyAddr   addr;
  KeyState  state;
  Key       key;
  byte      caller;

  KeyEvent() {}

  KeyEvent(KeyAddr _addr, KeyState _state, Key _key = cKey::clear, byte _caller = 0)
      : addr(_addr), state(_state), key(_key), caller(_caller) {}

};

} // namespace kaleidoglyph {
