// -*- c++ -*-

#include "kaleidoscope/Key/Keyboard.h"


namespace kaleidoscope {

byte Key::Keyboard::modifiers() const {
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

// This function is really just here to serve a single plugin, but it is more efficient
// than having it in Unshifter, so I'm ambivalent about it being here.
//inline
bool Key::Keyboard::isRealShift() const {
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

void Key::Keyboard::setModifiers(byte mods, bool ralt) {
  mods_left_ = mods;
  mod_ralt_  = ralt;
}

void Key::Keyboard::addModifiers(byte mods, bool ralt) {
  mods_left_ |= mods;
  mod_ralt_  |= ralt;
}

} // namespace kaleidoscope {
