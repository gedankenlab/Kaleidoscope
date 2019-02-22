// -*- c++ -*-

#pragma once

#include <Arduino.h>

#include "kaleidoglyph/Key.h"


namespace kaleidoglyph {

class MouseKey {

 private:
  byte keycode_ : 8, type_id_ : 8;

 public:
  byte keycode() const { return keycode_; }

  MouseKey() : keycode_ (0),
               type_id_ (Key::mouse_type_id) {}

  constexpr explicit
  MouseKey(byte keycode) : keycode_ (keycode),
                           type_id_ (Key::mouse_type_id) {}

  explicit
  MouseKey(Key key) : keycode_ (uint16_t(key)     ),
                      type_id_ (uint16_t(key) << 8)  {
    assert(type_id_ == Key::mouse_type_id);
  }

  constexpr
  operator Key() const {
    return Key( keycode_      |
                type_id_ << 8   );
  }

  static constexpr
  bool verify(Key key) {
    return ((uint16_t(key) >> 8) == Key::mouse_type_id);
  }

};

constexpr
bool isMouseKey(const Key key) {
  return MouseKey::verify(key);
}

} // namespace kaleidoglyph {
