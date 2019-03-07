// -*- c++ -*-

#pragma once

#include <Arduino.h>

// Is it possible to make this a constexpr function instead of a macro?
#define ELEMENTS(array) (sizeof(array)/sizeof(array[0]))

namespace kaleidoglyph {

// Return the number of `UnitType` units required to store `n` bits. Both `UnitType` &
// `WidthType` should be integer types. `WidthType` is whatever type the parameter `n` is
// stored as, and can be deduced bye the compiler, so it's not necessary to declare it
// when calling this function (e.g. `bitfieldSize<uint16_t>(n)`). The default `UnitType`
// is `byte` (i.e. `uint8_t`, which is almost always what we want, so most of the time we
// can also drop that template parameter (e.g. `bitfieldSize(n)`).
template <typename UnitType = byte, typename WidthType>
constexpr WidthType bitfieldSize(WidthType n) {
  return ((n - 1) / (8 * sizeof(UnitType))) + 1;
}

/// Calculates the number of bytes needed to store a bitfield of the given size in bits
constexpr byte bitfieldByteSize(int bits) {
  return ((bits - 1) / 8) + 1;
}


/// This replaces the `ELEMENTS(array)` macro:
template<size_t SIZE, class T>
constexpr size_t arraySize(T (&/*array*/)[SIZE]) {
  return SIZE;
}

} // namespace kaleidoglyph {
