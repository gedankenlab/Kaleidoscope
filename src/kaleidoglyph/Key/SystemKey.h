// -*- c++ -*-

#pragma once

#include "kaleidoglyph/Key.h"
#include <assert.h>


namespace kaleidoglyph {

class SystemKey {

 private:
  byte keycode_ : 8, type_id_ : 8;

 public:
  byte keycode() const { return keycode_; }

  SystemKey() : keycode_ (0),
                type_id_ (Key::system_type_id) {}

  constexpr explicit
  SystemKey(byte keycode) : keycode_ (keycode),
                            type_id_ (Key::system_type_id) {}

  explicit
  SystemKey(Key key) : keycode_ (uint16_t(key)     ),
                       type_id_ (uint16_t(key) >> 8)  {
    assert(type_id_ == Key::system_type_id);
  }

  constexpr
  operator Key() const {
    return Key( keycode_      |
                type_id_ << 8   );
  }

  static bool verify(Key key) {
    return ((uint16_t(key) >> 8) == Key::system_type_id);
  }
};

} // namespace kaleidoglyph {
