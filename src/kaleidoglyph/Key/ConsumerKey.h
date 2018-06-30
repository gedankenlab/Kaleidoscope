// -*- c++ -*-

#pragma once

#include "kaleidoglyph/Key.h"

#include <Arduino.h>
#include <assert.h>


namespace kaleidoglyph {

class ConsumerKey {

 private:
  uint16_t keycode_ : 10, type_id_ : 6;

 public:
  uint16_t keycode() const { return keycode_; }

  ConsumerKey() : keycode_ (0), type_id_ (Key::consumer_type_id) {}

  constexpr explicit
  ConsumerKey(uint16_t keycode) : keycode_ (keycode),
                                  type_id_ (Key::consumer_type_id) {}

  explicit
  ConsumerKey(Key key) : keycode_ (uint16_t(key)      ),
                         type_id_ (uint16_t(key) << 10)  {
    assert(type_id_ == Key::consumer_type_id);
  }

  constexpr
  operator Key() const {
    return Key( keycode_       |
                type_id_ << 10   );
  }

  static bool verify(Key key) {
    return ((uint16_t(key) >> 10) == Key::consumer_type_id);
  }
};

} // namespace kaleidoglyph {
