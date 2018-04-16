// -*- c++ -*-

#include "kaleidoscope/Key/Keyboard.h"


namespace kaleidoscope {

byte Key::Keyboard::modifiers() const {
  // Start with the left-modifier flag bits
  byte modifiers = mods_left_;
  // Add the right alt bit, if set
  if (mod_ralt_)
    modifiers |= mod_ralt;
  // If the keycode itself is also a modifier, include that as well
  modifiers |= keycodeModifier();
  // byte keycode_mod_bit = keycode_ - mod_keycode_offset;
  // if (keycode_mod_bit < 8)
  //   modifiers |= (1 << keycode_mod_bit);
  return modifiers;
}

inline
byte Key::Keyboard::modifierFlags() const {
  // Start with the left-modifier flag bits
  byte modifiers = mods_left_;
  // Add the right alt bit, if set
  if (mod_ralt_)
    modifiers |= mod_ralt;
  return modifiers;
}

#if 0
inline
bool Key::Keyboard::isTrueShift() const {
  //return { isModifier() && (modifiers() & mod_shift_flags) };

  // We only consider a key to be a "true" `shift` key if it encodes only modifiers,
  // including either the left or right `shift` bits
  if (byte modifiers = keycodeModifier()) {
    // In this case, there's no need to shift the mod bits because we don't care if the
    // `shift` modifier is left or right
    modifiers |= mods_left_;
    return { modifiers & mod_shift_flags };
  } else {
    return false;
  }
}
#endif

// This method is rendered obsolete by the more useful keycodeModifier() method
inline
bool Key::Keyboard::isModifier() const {
  return bool(keycodeModifier());
}

// Return the modifiers byte for the keycode part of the Key object, if any
inline
byte Key::Keyboard::keycodeModifier() const {
  byte modifiers{0};
  byte keycode_mod_bit = keycode_ - mod_keycode_offset;
  if (keycode_mod_bit < 8)
    modifiers |= (1 << keycode_mod_bit);
  return modifiers;
}

#if 0
// This function doesn't really seem very useful. It's not helpful at compile time because
// we have better, more efficient ways of setting the mod bits, and I'm struggling to come
// up with any run-time use for it.
void Key::Keyboard::addModifier(Key key) {
  assert(testType(key) && Key::Keyboard(key).isModifier());
  byte mod_bit = Key::Keyboard(key).keycode_ - mod_keycode_offset;
  if (mod_bit > 4) {
    mod_bit -= 4;
    mods_right_ = true;
  }
  mods_ |= (1 << mod_bit);
}
#endif

void Key::Keyboard::setModifiers(byte mods, bool ralt) {
  mods_left_ = mods;
  mod_ralt_  = ralt;
}

void Key::Keyboard::addModifiers(byte mods, bool ralt) {
  mods_left_ |= mods;
  mod_ralt_  |= ralt;
}

} // namespace kaleidoscope {
