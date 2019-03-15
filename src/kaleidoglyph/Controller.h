// -*- c++ -*-

#pragma once

#include <Arduino.h>

// This header file should contain the constants that are needed to correctly size static
// arrays at compile time. Also, (macro) definitions of class & object names (e.g. which
// hardware module to use) should be found here, and possibly other things I haven't
// thought of yet. It should be generated by the same pre-build script that creates the
// keymap file. It probably lives right next to the *.ino file, but maybe in a
// subdirectory (e.g. "libraries/Kaleidoglyph-Constants/"?). It may be necessary to
// include this before others include files; I'm not sure.
//#include <Kaleidoglyph-Constants.inc>
//#include KALEIDOGLYPH_HARDWARE_H  // defined above in Kaleidoglyph-Constants
//#include KALEIDOGLYPH_HID_H

#include "kaleidoglyph/hardware/Keyboard.h"
#include "kaleidoglyph/KeyAddr.h"
#include "kaleidoglyph/Keymap.h"
#include "kaleidoglyph/KeyEvent.h"
#include "kaleidoglyph/Layer.h"
#include "kaleidoglyph/cKey.h"
#include "kaleidoglyph/Plugin.h"
#include "kaleidoglyph/KeyArray.h"
#include "kaleidoglyph/hid/keyboard.h"
#include "kaleidoglyph/hid/consumer.h"


namespace kaleidoglyph {


/// The core Kaleidoglyph program; it controls everything else
class Controller {

 public:

  Controller(Keymap & keymap,
             hardware::Keyboard& keyboard,
             hid::keyboard::Dispatcher& dispatcher)
      : keymap_(keymap),
        keyboard_(keyboard),
        hid_keyboard_dispatcher_(dispatcher) {}
  
  void init(); // setup();
  void run();  // loop();

  void handleKeyEvent(KeyEvent event);
  void pressKeyswitch(KeyAddr k, byte caller = 0); // should use `pluginid::controller`
  void releaseKeyswitch(KeyAddr k, byte caller = 0);
  void sendKeyboardReport(const KeyEvent& event);

  Key lookup(KeyAddr key_addr) const; // probably pointless
  byte getModifierFlags() const; // return mod flags from non-blank, non-modifier keys

  void detachFromHost() {
    keyboard_.detachFromHost();
  }
  void attachToHost() {
    keyboard_.attachToHost();
  }

  static uint32_t scanStartTime() {
    return scan_start_time_;
  }

  // Experimental
  Key& operator[](KeyAddr k) {
    assert(byte(k) < total_keys);
    return active_keys_[k];
  }
  const Key& operator[](KeyAddr k) const {
    assert(byte(k) < total_keys);
    return active_keys_[k];
  }

 private:

  // active_keys_ can't really be a Layer because that would reference PROGMEM
  KeyArray<total_keys> active_keys_;

  Keymap& keymap_;
  hardware::Keyboard& keyboard_;
  // I want to make report_ a full member, not a pointer, but maybe not until I
  // replace KeyboardioHID entirely
  hid::keyboard::Dispatcher& hid_keyboard_dispatcher_;

  // Dispatcher for Consumer Control key events
  hid::consumer::Dispatcher hid_consumer_dispatcher_;

  // cache of modifier flags on non-modifier, non-blank keys
  byte mod_flags_allowed_{0};

  // This one is a class variable; that makes it possible to access without needing a
  // reference (implemented as a pointer) to the `controller` object in every instance
  // that just needs to know the current time.
  static uint32_t scan_start_time_;

};


// inline
// Key Controller::getActiveKey(KeyAddr k) const {
//   return active_keys_[k];
// }

// inline
// void Controller::setActiveKey(KeyAddr k, Key key) const {
//   active_keys_[k] = key;
// }

inline
Key Controller::lookup(KeyAddr k) const {
  return keymap_[k];
}

inline
void Controller::pressKeyswitch(KeyAddr k, byte caller) {
  KeyEvent event{k, cKeyState::press};
  event.caller = caller;
  handleKeyEvent(event);
}

inline
void Controller::releaseKeyswitch(KeyAddr k, byte caller) {
  KeyEvent event{k, cKeyState::release};
  event.caller = caller;
  handleKeyEvent(event);
}

} // namespace kaleidoglyph {
