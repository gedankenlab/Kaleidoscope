#include "kaleidoscope/Key.h"

#include <Arduino.h>

#include "kaleidoscope/KeyFlavor.h"


namespace kaleidoscope {

// Return the correct type (KeyFlavor) of the Key object. I expect KeyFlavor::plugin to be
// more common than most of the core types, so I moved it up higher. These should be
// sorted in descending order of frequency of use; I'm just guessing here.
KeyFlavor Key::flavor() const {
  if (keyboard.meta == keyboard_flavor_id)
    return KeyFlavor::keyboard;
  if (plugin.meta == plugin_flavor_id)
    return KeyFlavor::plugin;
  if (layer.meta == layer_flavor_id)
    return KeyFlavor::layer;
  if (mouse.meta == mouse_flavor_id)
    return KeyFlavor::mouse;
  if (consumer.meta == consumer_flavor_id)
    return KeyFlavor::consumer;
  if (system.meta == system_flavor_id)
    return KeyFlavor::system;
  return KeyFlavor::unknown;
}


// Get a modifiers byte that can be passed to the keyboard HID report directly
byte Key::mods() const {
  // If it's not a keyboard key, no mods are applied, so bail out. This test is probably
  // inefficient, because we should always be doing it before calling this function, but
  // it's safer this way.
  if (keyboard.meta != keyboard_flavor_id)
    return 0;

  byte modifiers = byte(keyboard.mods);
  // If the fifth bit (mods_right) is set, that means we have to shift the mods four bits
  // to match the right-hand modifier bits in the HID report modifiers byte.
  if (keyboard.mods_right)
    modifiers <<= 4;
  return modifiers;
}

} // namespace kaleidoscope {
