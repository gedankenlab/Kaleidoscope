// -*- c++ -*-

#pragma once

#include <Arduino.h>

#include "kaleidoglyph/Key.h"
#include <assert.h>


#if defined(LED_CONSTANTS_H)
#include LED_CONSTANTS_H
#else
namespace kaleidoglyph {

constexpr byte type_id_bits {8};
constexpr byte index_bits {8};

constexpr byte led_type_id { Key::led_type_id };

constexpr byte led_background_off_index { 0x00 };
constexpr byte led_next_mode_index      { 0x01 };
constexpr byte led_prev_mode_index      { 0x02 };

}
#endif

namespace kaleidoglyph {

class LedKey {

 private:
  byte index_ : index_bits, type_id_ : type_id_bits;

 public:
  byte index() const { return index_; }

  LedKey() : index_    (0),
             type_id_ (led_type_id) {}

  constexpr explicit
  LedKey(byte index) : index_   (index),
                       type_id_ (led_type_id) {}

  explicit
  LedKey(Key key) : index_   (uint16_t(key)              ),
                    type_id_ (uint16_t(key) >> index_bits)  {
    assert(type_id_ == led_type_id);
  }

  constexpr
  operator Key() const {
    return Key( index_                 |
                type_id_ << index_bits   );
  }

  static bool verifyType(Key key) {
    return ((uint16_t(key) >> index_bits) == led_type_id);
  }
};

namespace cLedKey {

constexpr LedKey background_off{led_background_off_index};
constexpr LedKey next_mode{led_next_mode_index};
constexpr LedKey prev_mode{led_prev_mode_index};

}

} // namespace kaleidoglyph {
