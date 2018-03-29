// -*- c++ -*-

#pragma once

#include <Arduino.h>


namespace kaleidoscope {

class KeyswitchState {

 public:

  constexpr
  KeyswitchState() : raw_(0) {}

  // Constructor sets all reserved bits to zero.
  explicit constexpr
  KeyswitchState(byte state)
    : raw_(state & 0x03) {}

  constexpr
  KeyswitchState(bool curr, bool prev)
    : raw_(curr | (prev << 1)) {}

  // These comparisons all assume that the reserved bits are all zero.
  bool isInactive() const {
    return raw_ == 0; // 0b00 (previous = 0; current = 0;)
  }

  bool isPressed() const {
    return raw_ == 1; // 0b01 (previous = 0; current = 1;)
  }

  bool isReleased() const {
    return raw_ == 2; // 0b10 (previous = 1; current = 0;)
  }

  bool isHeld() const {
    return raw_ == 3; // 0b11 (previous = 1; current = 1;)
  }

  bool toggledOn() const {
    return isPressed();
  }

  bool toggledOff() const {
    return isReleased();
  }

  bool current() const {
    return raw_ & 1;
  }

  bool previous() const {
    return raw_ & 2;
  }

  // This operator is probably unnecessary; the above functions should get us everything we need
  bool operator!() const {
    // return (! current && ! previous);
    // return !(raw_ & B11);
    return (! raw_);
  }

 private:
    byte raw_;

};

namespace cKeyswitchState {

constexpr KeyswitchState inactive (0);
constexpr KeyswitchState pressed  (1);
constexpr KeyswitchState released (2);
constexpr KeyswitchState held     (3);

constexpr KeyswitchState idle = inactive;

} // namespace cKeyswitchState {

} // namespace kaleidoscope {
