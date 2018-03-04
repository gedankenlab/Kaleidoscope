// -*- c++ -*-

#pragma once

#include <Arduino.h>


namespace kaleidoscope {

union KeyswitchState {

 public:

  byte raw;
  struct {
    byte current : 1, previous : 1, reserved : 6;
  };

  // Constructor sets all reserved bits to zero.
  explicit constexpr
  KeyswitchState(byte state)
    : raw(state & 0x03) {}

  constexpr
  KeyswitchState(byte curr, byte prev)
    : current(curr), previous(prev), reserved(0) {}

  // These comparisons all assume that the reserved bits are all zero.
  bool isInactive() const {
    return raw == 0; // 0b00 (previous = 0; current = 0;)
  }

  bool isPressed() const {
    return raw == 1; // 0b01 (previous = 0; current = 1;)
  }

  bool isReleased() const {
    return raw == 2; // 0b10 (previous = 1; current = 0;)
  }

  bool isHeld() const {
    return raw == 3; // 0b11 (previous = 1; current = 1;)
  }

  bool toggledOn() const {
    return isPressed();
  }

  bool toggledOff() const {
    return isReleased();
  }

  // This operator is probably unnecessary; the above functions should get us everything we need
  bool operator!() const {
    // return (! current && ! previous);
    // return !(raw & B11);
    return (! raw);
  }

};

} // namespace kaleidoscope {
