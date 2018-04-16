// -*- c++ -*-

#pragma once

#include "kaleidoscope/Key.h"
#include "kaleidoscope/cKey/HIDTables.h"
#include <assert.h>


namespace kaleidoscope {

class Key::Keyboard {

 private:
  byte keycode_ : 8, mods_left_ : 4, mod_ralt_ : 1, type_id_ : 3;

  // These mod bits are in the same order as the mod bits in the HID keyboard report for
  // efficiency in passing them on. If they get rearranged, that will mess things up.
  static constexpr byte mod_control { 0b0001 };  // (1 << 0)
  static constexpr byte mod_shift   { 0b0010 };  // (1 << 1)
  static constexpr byte mod_alt     { 0b0100 };  // (1 << 2)
  static constexpr byte mod_gui     { 0b1000 };  // (1 << 3)

  static constexpr byte mod_ralt { mod_alt << 4 };

  // Now I'm really starting to think that it's not worth the trouble to have the
  // mods_right_ member, and it would be simpler to just use the 5 mod flags from
  // Kaleidoscope as-is.

  // These belong in the report, not here? I'm not sure where to put these, but they
  // should be useful for answering questions like "is this key a pure modifier key with
  // shift set?"
  static constexpr byte mod_control_flags { mod_control | mod_control << 4 };
  static constexpr byte mod_shift_flags   { mod_shift   | mod_shift   << 4 };
  static constexpr byte mod_alt_flags     { mod_alt     | mod_alt     << 4 };
  static constexpr byte mod_gui_flags     { mod_gui     | mod_gui     << 4 };

  static constexpr byte mod_keycode_offset { HID_KEYBOARD_LEFT_CONTROL };

 public:
  constexpr
  byte keycode() const { return keycode_; }
  byte modifiers() const;
  byte keycodeModifier() const;
  byte modifierFlags() const;
  bool isModifier() const;
  void addModifier(Key key);
  void setModifiers(byte mods, bool mod_ralt = false);
  void setModifiers(bool control, bool shift, bool alt, bool gui, bool ralt = false);
  void addModifiers(byte mods, bool mod_ralt = false);
  void clearModifiers() {
    setModifiers(0);
  }

  // Run-time constructor; generates and empty Key (equal to cKey::blank)
  Keyboard() : keycode_    (0),
               mods_left_  (0),
               mod_ralt_   (false),
               type_id_    (Key::keyboard_type_id) {}

  // The primary constructor; sets all bit fields in the structure. This is what is used
  // to define Key::Keyboard compile-time constants.
  constexpr explicit
  Keyboard(byte keycode, byte mods_left = 0, bool mod_ralt = false)
      : keycode_(keycode), mods_left_(mods_left), mod_ralt_(mod_ralt),
        type_id_(Key::keyboard_type_id) {}

  // Conversion from Key object. The caller should first verify that it's got the
  // correct type of Key object before calling this constructor.
  explicit
  Keyboard(Key key) : keycode_    (uint16_t(key)               ),
                      mods_left_  (uint16_t(key) >>  8         ),
                      mod_ralt_   (uint16_t(key) >> (8 + 4)    ),
                      type_id_    (uint16_t(key) >> (8 + 4 + 1))  {
    assert(type_id_ == Key::keyboard_type_id);
  }

  // Cast operator to convert Key::Keyboard objects to plain Key objects
  constexpr
  operator Key() const {
    return Key( keycode_                   |
                mods_left_  <<  8          |
                mod_ralt_   << (8 + 4)     |
                type_id_    << (8 + 4 + 1)   );
  }

  static constexpr bool testType(Key key) {
    return ((uint16_t(key) >> (8 + 4 + 1)) == Key::keyboard_type_id);
  }
};

} // namespace kaleidoscope {
