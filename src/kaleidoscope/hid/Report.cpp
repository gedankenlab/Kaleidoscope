// -*- c++ -*-

#include "kaleidoscope/hid/Report.h"

#include <Arduino.h>
#include <KeyboardioHID.h>

#include "kaleidoscope/KeyFlavor.h"
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

void Report::add(Key key) {
  if (key.isEmpty())
    return;

  switch (key.flavor()) {
    case KeyFlavor::keyboard:
      if (byte modifiers = key.mods()) {
        byte mod_keycode = cKey::first_modifier.keyboard.keycode;
        while (modifiers != 0) {
          if (mod_keycode & 1)
            ::Keyboard.press(mod_keycode);
          mod_keycode <<= 1;
          modifiers   <<= 1;
        }
      }
      ::Keyboard.press(key.keyboard.keycode);
      return;
    case KeyFlavor::consumer:
      // This uses the CONSUMER preprocessor macro
      ::ConsumerControl.press(key.consumer.keycode);
      return;
    case KeyFlavor::system:
      // System Control is different; press() sends immediately
      ::SystemControl.press(key.system.keycode);
      return;
    case KeyFlavor::layer:
      return;
    default:
      return;
  }
}

// This function must be used very carefully; the caller isn't necessarily the only one to
// have added the keycode in question, and removing it could break other plugins'
// assumptions
void Report::remove(Key key) {
  if (key.isEmpty())
    return;

  switch (key.flavor()) {
    case KeyFlavor::keyboard:
      // Here we don't want to remove modifier flags, because they could have been added
      // by other keys (or plugins)
      ::Keyboard.release(key.keyboard.keycode);
      return;
    case KeyFlavor::consumer:
      // This uses the CONSUMER preprocessor macro
      ::ConsumerControl.release(key.consumer.keycode);
      return;
    case KeyFlavor::system:
      // System Control is different; release() sends immediately, and there's only one
      // keycode at a time
      ::SystemControl.release();
      return;
    case KeyFlavor::layer:
      return;
    default:
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
