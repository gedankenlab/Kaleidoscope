// -*- c++ -*-

#pragma once

#include <Arduino.h>


namespace kaleidoglyph {

class KeyState {

 private:
  byte raw_;

  static constexpr byte curr_bit     {0b001};
  static constexpr byte prev_bit     {0b010};
  static constexpr byte injected_bit {0b100};

 public:

  constexpr
  KeyState() : raw_(0) {}

  // Constructor sets all reserved bits to zero.
  explicit constexpr
  KeyState(byte state)
    : raw_(state & 0b111) {}

  constexpr
  KeyState(bool curr, bool prev, bool injected = false)
    : raw_(curr | (prev << 1) | (injected << 2)) {}

  // These comparisons all assume that the reserved bits are all zero.
  bool isInactive() const {
    return (raw_ & 0b011) == 0; // 0b00 (previous = 0; current = 0;)
  }

  bool toggledOn() const {
    return (raw_ & 0b001) == 1; // 0b01 (previous = 0; current = 1;)
  }

  bool toggledOff() const {
    return (raw_ & 0b011) == 2; // 0b10 (previous = 1; current = 0;)
  }

  bool isHeld() const {
    return (raw_ & 0b011) == 3; // 0b11 (previous = 1; current = 1;)
  }

  bool isInjected() const {
    return raw_ & injected_bit;
  }

  bool isPressed() const {
    return raw_ & curr_bit;
  }

  bool wasPressed() const {
    return raw_ & prev_bit;
  }

};

namespace cKeyState {

constexpr KeyState inactive (0);
constexpr KeyState pressed  (1);
constexpr KeyState released (2);
constexpr KeyState held     (3);

constexpr KeyState idle = inactive;

} // namespace cKeyState {

} // namespace kaleidoglyph {
