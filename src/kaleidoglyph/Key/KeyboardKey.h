// -*- c++ -*-

#pragma once

#include <Arduino.h>
#include <assert.h>

#include "kaleidoglyph/Key.h"
#include "kaleidoglyph/cKey/HIDTables.h"


namespace kaleidoglyph {

class KeyboardKey {

 private:
  byte keycode_ : 8, mods_left_ : 4, mod_ralt_ : 1, type_id_ : 3;

 public:
  // These mod bits are in the same order as the mod bits in the HID keyboard report for
  // efficiency in passing them on. If they get rearranged, that will mess things up.
  static constexpr byte mod_flag_control { 0b0001 };  // (1 << 0)
  static constexpr byte mod_flag_shift   { 0b0010 };  // (1 << 1)
  static constexpr byte mod_flag_alt     { 0b0100 };  // (1 << 2)
  static constexpr byte mod_flag_gui     { 0b1000 };  // (1 << 3)
  static constexpr byte mod_flag_ralt { mod_flag_alt << 4 };

  static constexpr byte mod_keycode_offset { HID_KEYBOARD_LEFT_CONTROL };

  static constexpr byte mods_mask_control { mod_flag_control | mod_flag_control << 4 };
  static constexpr byte mods_mask_shift   { mod_flag_shift   | mod_flag_shift   << 4 };
  static constexpr byte mods_mask_alt     { mod_flag_alt     | mod_flag_alt     << 4 };
  static constexpr byte mods_mask_gui     { mod_flag_gui     | mod_flag_gui     << 4 };

  constexpr
  byte keycode() const { return keycode_; }
  byte modifiers() const;
  constexpr
  byte keycodeModifier() const;
  byte modifierFlags() const;
  constexpr
  bool isModifier() const {
    byte keycode_mod_num = keycode_ - mod_keycode_offset;
    return { keycode_mod_num < 8 };
  }
  constexpr
  byte modifierIndex() const {
    byte keycode_mod_num = keycode_ - mod_keycode_offset;
    return keycode_mod_num;
  }
  constexpr
  bool isRealShift() const;
  constexpr
  void setModifiers(byte mods, bool mod_ralt = false);
  //void setModifiers(bool control, bool shift, bool alt, bool gui, bool ralt = false);
  constexpr
  void addModifiers(byte mods, bool mod_ralt = false);
  void clearModifiers() {
    setModifiers(0);
  }
  constexpr
  void addLeftControl() {
    addModifiers(mod_flag_control);
  }
  constexpr
  void addLeftShift() {
    addModifiers(mod_flag_shift);
  }
  constexpr
  void addLeftAlt() {
    addModifiers(mod_flag_alt);
  }
  constexpr
  void addLeftGui() {
    addModifiers(mod_flag_gui);
  }
  constexpr
  void addRightAlt() {
    addModifiers(0, true);
  }
  constexpr
  void setKeycode(byte keycode) {
    keycode_ = keycode;
  }

  // Run-time constructor; generates an empty Key (equal to cKey::blank)
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

  static constexpr
  bool verifyType(Key key) {
    return ((uint16_t(key) >> (8 + 4 + 1)) == Key::keyboard_type_id);
  }

}__attribute__((packed));

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
constexpr
byte KeyboardKey::keycodeModifier() const {
  byte modifiers{0};
  byte keycode_mod_bit = keycode_ - mod_keycode_offset;
  if (keycode_mod_bit < 8)
    modifiers |= (1 << keycode_mod_bit);
  return modifiers;
}

// This function is really just here to serve a single plugin, but it is more efficient
// than having it in Unshifter, so I'm ambivalent about it being here.
constexpr
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

constexpr
void KeyboardKey::setModifiers(byte mods, bool ralt) {
  mods_left_ = mods;
  mod_ralt_  = ralt;
}

constexpr
void KeyboardKey::addModifiers(byte mods, bool ralt) {
  mods_left_ |= mods;
  mod_ralt_  |= ralt;
}

constexpr
bool isKeyboardKey(Key key) {
  return KeyboardKey::verifyType(key);
}

constexpr
bool isModifierKey(Key key) {
  return { KeyboardKey::verifyType(key) && KeyboardKey(key).isModifier() };
}

constexpr
KeyboardKey modifierKey(byte n) {
  return KeyboardKey(KeyboardKey::mod_keycode_offset + n);
}

constexpr
KeyboardKey withLeftControl(KeyboardKey key) {
  KeyboardKey result_key = key;
  result_key.addLeftControl();
  return result_key;
}

constexpr
KeyboardKey withLeftShift(KeyboardKey key) {
  KeyboardKey result_key = key;
  result_key.addLeftShift();
  return result_key;
}

constexpr
KeyboardKey withLeftAlt(KeyboardKey key) {
  KeyboardKey result_key = key;
  result_key.addLeftAlt();
  return result_key;
}

constexpr
KeyboardKey withLeftGui(KeyboardKey key) {
  KeyboardKey result_key = key;
  result_key.addLeftGui();
  return result_key;
}

constexpr
KeyboardKey withRightAlt(KeyboardKey key) {
  KeyboardKey result_key = key;
  result_key.addRightAlt();
  return result_key;
}

constexpr KeyboardKey withControl(KeyboardKey key) { return withLeftControl(key); }
constexpr KeyboardKey withShift(KeyboardKey key) { return withLeftShift(key); }
constexpr KeyboardKey withAlt(KeyboardKey key) { return withLeftAlt(key); }
constexpr KeyboardKey withOption(KeyboardKey key) { return withLeftAlt(key); }
constexpr KeyboardKey withGui(KeyboardKey key) { return withLeftGui(key); }
constexpr KeyboardKey withCommand(KeyboardKey key) { return withLeftGui(key); }
constexpr KeyboardKey withCmd(KeyboardKey key) { return withLeftGui(key); }
constexpr KeyboardKey withAltGr(KeyboardKey key) { return withRightAlt(key); }

constexpr KeyboardKey control(KeyboardKey key) { return withLeftControl(key); }
constexpr KeyboardKey ctrl(KeyboardKey key) { return withLeftControl(key); }
constexpr KeyboardKey shift(KeyboardKey key) { return withLeftShift(key); }
constexpr KeyboardKey option(KeyboardKey key) { return withLeftAlt(key); }
constexpr KeyboardKey command(KeyboardKey key) { return withLeftGui(key); }
constexpr KeyboardKey ralt(KeyboardKey key) { return withRightAlt(key); }
constexpr KeyboardKey altgr(KeyboardKey key) { return withRightAlt(key); }

constexpr KeyboardKey ctl(KeyboardKey key) { return withLeftControl(key); }
constexpr KeyboardKey sft(KeyboardKey key) { return withLeftShift(key); }
constexpr KeyboardKey alt(KeyboardKey key) { return withLeftAlt(key); }
constexpr KeyboardKey opt(KeyboardKey key) { return withLeftAlt(key); }
constexpr KeyboardKey gui(KeyboardKey key) { return withLeftGui(key); }
constexpr KeyboardKey cmd(KeyboardKey key) { return withLeftGui(key); }

} // namespace kaleidoglyph {
