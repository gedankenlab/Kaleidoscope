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
  static constexpr byte mod_flag_control { 0b0001 };  // (1 << 0)
  static constexpr byte mod_flag_shift   { 0b0010 };  // (1 << 1)
  static constexpr byte mod_flag_alt     { 0b0100 };  // (1 << 2)
  static constexpr byte mod_flag_gui     { 0b1000 };  // (1 << 3)
  static constexpr byte mod_flag_ralt { mod_flag_alt << 4 };

  static constexpr byte mod_keycode_offset { HID_KEYBOARD_LEFT_CONTROL };

 public:

  static constexpr byte mods_mask_control { mod_flag_control | mod_flag_control << 4 };
  static constexpr byte mods_mask_shift   { mod_flag_shift   | mod_flag_shift   << 4 };
  static constexpr byte mods_mask_alt     { mod_flag_alt     | mod_flag_alt     << 4 };
  static constexpr byte mods_mask_gui     { mod_flag_gui     | mod_flag_gui     << 4 };

  constexpr
  byte keycode() const { return keycode_; }
  byte modifiers() const;
  byte keycodeModifier() const;
  byte modifierFlags() const;
  bool isModifier() const;
  bool isRealShift() const;
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
