#include "kaleidoscope/Key.h"

#include <Arduino.h>

#include "kaleidoscope/cKey.h"


namespace kaleidoscope {

// This function should probably be removed; it's always more efficient to test just the
// type we're interested in using the specific `Key` variant.
KeyType Key::type() const {
  if (KeyboardKey::verify(*this))
    return KeyType::keyboard;

  if (PluginKey::verify(*this))
    return KeyType::plugin;

  if (LayerKey::verify(*this))
    return KeyType::layer;

  if (MouseKey::verify(*this))
    return KeyType::mouse;

  if (ConsumerKey::verify(*this))
    return KeyType::consumer;

  if (SystemKey::verify(*this))
    return KeyType::system;

  if (raw_ == clear)
    return KeyType::clear;

  return KeyType::unknown;
}

} // namespace kaleidoscope {
