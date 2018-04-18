// -*- c++ -*-

#include "kaleidoscope/hid/Report.h"

#include <Arduino.h>
#include <KeyboardioHID.h>

#include "kaleidoscope/Key.h"
#include "kaleidoscope/cKey.h"


// This version uses KeyboardioHID, not the rewrite

namespace kaleidoscope {
namespace hid {
namespace keyboard {

// These can't be done in the constructor because of the Static Initialization Order
// Fiasco -- one of many reasons I want to rewrite KeyboardioHID
void Report::init() {
  ::Keyboard.begin();
  ::ConsumerControl.begin();
  ::SystemControl.begin();
  clear();
}

void Report::clear() {
  ::Keyboard.releaseAll();
  ::ConsumerControl.releaseAll();
  //nkro_keyboard_ = (BootKeyboard.getProtocol() != HID_BOOT_PROTOCOL);
}

void Report::add(Key key, byte mod_flags_allowed) {
  if (key == cKey::clear)
    return;

  if (KeyboardKey::testType(key)) {
    KeyboardKey keyboard_key{key};

    byte modifiers = keyboard_key.keycodeModifier();
    byte mod_flags = keyboard_key.modifierFlags();

    if (!modifiers) {
      modifiers = mod_flags & mod_flags_allowed;
    } else {
      modifiers |= mod_flags;
    }
    byte mod_keycode = KeyboardKey::mod_keycode_offset;
    // This while loop should be replaced by directly setting the modifiers byte in the
    // report, instead of iterating through it here, but that's probably not possible with
    // KeyboardioHID right now.
    while (modifiers != 0) {
      if (modifiers & 1)
        ::Keyboard.press(mod_keycode);
      ++mod_keycode;
      modifiers >>= 1;
    }
    ::Keyboard.press(keyboard_key.keycode());
    return;
  } else if (ConsumerKey::testType(key)) {
    ::ConsumerControl.press(ConsumerKey(key).keycode());
    return;
  } else if (SystemKey::testType(key)) {
    // System Control is different; press() sends immediately
    ::SystemControl.press(SystemKey(key).keycode());
    return;
  }
}

// This function must be used very carefully; the caller isn't necessarily the only one to
// have added the keycode in question, and removing it could break other plugins'
// assumptions
void Report::remove(Key key) {
  if (key.isEmpty())
    return;

  if (KeyboardKey::testType(key)) {
    // Here we don't want to remove modifier flags, because they could have been added
    // by other keys (or plugins)
    ::Keyboard.release(KeyboardKey(key).keycode());
    return;
  }

  if (ConsumerKey::testType(key)) {
    ::ConsumerControl.release(ConsumerKey(key).keycode());
    return;
  }

  if (SystemKey::testType(key)) {
    // System Control is different; release() sends immediately, and there's only one
    // keycode at a time
    ::SystemControl.release();
    return;
  }
}

void Report::send() {
  ::Keyboard.sendReport();
  ::ConsumerControl.sendReport();
}

//byte Report::activeMods() {}

byte Report::hostLedStates() const {
  return ::Keyboard.getLEDs();
}

} // namespace keyboard {
} // namespace hid {
} // namespace kaleidoscope {
