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

//#include <Kaleidoglyph-Hardware-Model01.h>
#include KALEIDOGLYPH_HARDWARE_H
#include KALEIDOGLYPH_HARDWARE_KEYBOARD_H
#include KALEIDOGLYPH_KEYADDR_H
#include "kaleidoglyph/Keymap.h"
#include "kaleidoglyph/KeyswitchEvent.h"
#include "kaleidoglyph/Layer.h"
#include "kaleidoglyph/cKey.h"
#include "kaleidoglyph/Plugin.h"
#include "kaleidoglyph/hid/Report.h"
#include "kaleidoglyph/KeyArray.h"


namespace kaleidoglyph {

/// The core Kaleidoglyph program; it controls everything else
class Controller {
 public:
  Controller(Keymap & keymap,
             hardware::Keyboard& keyboard,
             hid::keyboard::Report& keyboard_report)
      : keymap_(keymap),
        keyboard_(keyboard),
        report_(keyboard_report),
        plugin_count_(0) {}
  
  void init(); // setup();
  void run();  // loop();

  // this might turn out to be a macro instead; we want this to happen at compile time
  // void initPlugin(Plugin & p) {
  //   p.init(plugin_count_++);
  // }

  static constexpr byte id{0xFF};

  void handleKeyswitchEvent(KeyswitchEvent event, Plugin* caller = nullptr);
  void pressKeyswitch(KeyAddr k, Plugin* caller = nullptr);
  void releaseKeyswitch(KeyAddr k, Plugin* caller = nullptr);
  void sendKeyboardReport();

  Key lookup(KeyAddr key_addr) const; // probably pointless
  // TODO: add operator[] for active_keys_ access
  // TODO: add getModFlags();
  byte getModifierFlags() const; // return mod flags from non-blank, non-modifier keys

 private:

  // active_keys_ can't really be a Layer because that would reference PROGMEM
  //Key active_keys_[total_keys];
  KeyArray active_keys_;

  Keymap& keymap_;
  hardware::Keyboard& keyboard_;
  // I want to make report_ a full member, not a pointer, but maybe not until I
  // replace KeyboardioHID entirely
  hid::keyboard::Report& report_;

  //Plugin* plugins_[MAX_PLUGINS]; // need to define this statically somehow
  byte plugin_count_;

  // cache of modifier flags on non-modifier, non-blank keys
  byte mod_flags_allowed_{0};

};


inline Key Controller::lookup(KeyAddr k) const {
  return keymap_[k];
}

inline
void pressKeyswitch(KeyAddr k, Plugin* caller) {
  KeyswitchEvent event{k, cKeyswitchState::pressed};
  handleKeyswitchEvent(event, caller);
}

inline
void releaseKeyswitch(KeyAddr k, Plugin* caller) {
  KeyswitchEvent event{k, cKeyswitchState::released};
  handleKeyswitchEvent(event, caller);
}

} // namespace kaleidoglyph {
