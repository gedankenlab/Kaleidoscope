// -*- c++ -*-

#pragma once

#include <Arduino.h>

namespace kaleidoglyph {

template<typename _Type, byte _size>
class ConstArray {
 public:
  ConstArray(_Type (&)) {}
  byte size() { return _size; }
 private:
  _Type const array_[_size];
};

} //
