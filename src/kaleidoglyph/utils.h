// -*- c++ -*-

#pragma once

#include <Arduino.h>

// Is it possible to make this a constexpr function instead of a macro?
#define ELEMENTS(array) (sizeof(array)/sizeof(array[0]))

namespace kaleidoglyph {

/// Calculates the number of bytes needed to store a bitfield of the given size in bits
constexpr byte bitfieldSize(int bits) {
  return ((bits - 1) / 8) + 1;
}

/// I'd really like to know if this works...
template<size_t SIZE, class T>
constexpr size_t arraySize(T (&array)[SIZE]) {
  return SIZE;
}

}
