// -*- c++ -*-

#pragma once

#include "kaleidoscope/Key.h"
#include "kaleidoscope/cKey/HIDTables.h"
#include <assert.h>


namespace kaleidoscope {

class KeyboardKey {

 private:
  byte keycode_ : 8, mods_left_ : 4, mod_ralt_ : 1, type_id_ : 3;

  // These mod bits are in the same order as the mod bits in the HID keyboard report for
  // efficiency in passing them on. If they get rearranged, that will mess things up.
  static constexpr byte mod_flag_control { 0b0001 };  // (1 << 0)
  static constexpr byte mod_flag_shift   { 0b0010 };  // (1 << 1)
  static constexpr byte mod_flag_alt     { 0b0100 };  // (1 << 2)
  static constexpr byte mod_flag_gui     { 0b1000 };  // (1 << 3)
  static constexpr byte mod_flag_ralt { mod_flag_alt << 4 };

 public:

  static constexpr byte mod_keycode_offset { HID_KEYBOARD_LEFT_CONTROL };

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
  //void setModifiers(bool control, bool shift, bool alt, bool gui, bool ralt = false);
  void addModifiers(byte mods, bool mod_ralt = false);
  void clearModifiers() {
    setModifiers(0);
  }

  // Run-time constructor; generates and empty Key (equal to cKey::blank)
  KeyboardKey() : keycode_    (0),
                  mods_left_  (0),
                  mod_ralt_   (false),
                  type_id_    (Key::keyboard_type_id) {}

  // The primary constructor; sets all bit fields in the structure. This is what is used
  // to define KeyboardKey compile-time constants.
  constexpr explicit
  KeyboardKey(byte keycode, byte mods_left = 0, bool mod_ralt = false)
      : keycode_(keycode), mods_left_(mods_left), mod_ralt_(mod_ralt),
        type_id_(Key::keyboard_type_id) {}

  // Conversion from Key object. The caller should first verify that it's got the
  // correct type of Key object before calling this constructor.
  explicit
  KeyboardKey(Key key) : keycode_    (uint16_t(key)               ),
                         mods_left_  (uint16_t(key) >>  8         ),
                         mod_ralt_   (uint16_t(key) >> (8 + 4)    ),
                         type_id_    (uint16_t(key) >> (8 + 4 + 1))  {
    assert(type_id_ == Key::keyboard_type_id);
  }

  // Cast operator to convert KeyboardKey objects to plain Key objects
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

// This method is rendered obsolete by the more useful keycodeModifier() method
inline
bool KeyboardKey::isModifier() const {
  byte keycode_mod_bit = keycode_ - mod_keycode_offset;
  return { keycode_mod_bit < 8 };
}

inline
byte KeyboardKey::modifierFlags() const {
  // Start with the left-modifier flag bits
  byte modifiers = mods_left_;
  // Add the right alt bit, if set
  if (mod_ralt_)
    modifiers |= mod_flag_ralt;
  return modifiers;
}

// Return the modifiers byte for the keycode part of the Key object, if any
inline
byte KeyboardKey::keycodeModifier() const {
  byte modifiers{0};
  byte keycode_mod_bit = keycode_ - mod_keycode_offset;
  if (keycode_mod_bit < 8)
    modifiers |= (1 << keycode_mod_bit);
  return modifiers;
}

// This function is really just here to serve a single plugin, but it is more efficient
// than having it in Unshifter, so I'm ambivalent about it being here.
inline
bool KeyboardKey::isRealShift() const {
  //return { isModifier() && (modifiers() & mod_shift_flags) };

  // We only consider a key to be a "true" `shift` key if it encodes only modifiers,
  // including either the left or right `shift` bits
  if (byte modifiers = keycodeModifier()) {
    modifiers |= mods_left_;
    return bool(modifiers & mods_mask_shift);
  } else {
    return false;
  }

}

inline
byte KeyboardKey::modifiers() const {
  // Start with the left-modifier flag bits
  byte modifiers = mods_left_;
  // Add the right alt bit, if set
  if (mod_ralt_)
    modifiers |= mod_flag_ralt;
  // If the keycode itself is also a modifier, include that as well
  modifiers |= keycodeModifier();
  // byte keycode_mod_bit = keycode_ - mod_keycode_offset;
  // if (keycode_mod_bit < 8)
  //   modifiers |= (1 << keycode_mod_bit);
  return modifiers;
}

inline
void KeyboardKey::setModifiers(byte mods, bool ralt) {
  mods_left_ = mods;
  mod_ralt_  = ralt;
}

inline
void KeyboardKey::addModifiers(byte mods, bool ralt) {
  mods_left_ |= mods;
  mod_ralt_  |= ralt;
}

} // namespace kaleidoscope {
