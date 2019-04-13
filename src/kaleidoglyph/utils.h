// -*- c++ -*-

#pragma once

#include <Arduino.h>

namespace kaleidoglyph {

// Return the number of `UnitType` units required to store `n` bits. Both `UnitType` &
// `WidthType` should be integer types. `WidthType` is whatever type the parameter `n` is
// stored as, and can be deduced bye the compiler, so it's not necessary to declare it
// when calling this function (e.g. `bitfieldSize<uint16_t>(n)`). The default `UnitType`
// is `byte` (i.e. `uint8_t`, which is almost always what we want, so most of the time we
// can also drop that template parameter (e.g. `bitfieldSize(n)`).
template <typename _UnitType = byte, typename _WidthType>
constexpr _WidthType bitfieldSize(_WidthType n) {
  return ((n - 1) / (8 * sizeof(_UnitType))) + 1;
}

/// Calculates the number of bytes needed to store a bitfield of the given size in bits
constexpr byte bitfieldByteSize(int bits) {
  return ((bits - 1) / 8) + 1;
}


/// This replaces the `ELEMENTS(array)` macro:
template<size_t _size, typename _Type>
constexpr size_t arraySize(_Type (&/*array*/)[_size]) {
  return _size;
}

template<size_t _length, typename _Type>
constexpr size_t arrayLength(_Type (&/*array*/)[_length]) {
  return _length;
}

// This function is particulary useful for reading from an array of pointers
// stored in PROGMEM, where `_PointerType` would be something like `Layer*`. The
// `reinterpret_cast` is mainly useful for converting a two-byte value to the
// appropriate pointer type.
template<typename _PointerType, byte _array_size>
_PointerType readPointerFromProgmemArray(_PointerType (&pgm_ptr_array)[_array_size],
                                         byte  index) {
  // We don't actually do bounds checking unless we're in debug mode, but this
  // is better than nothing.
  assert(index < _array_size);

  // First, we get the (PROGMEM) pointer to the specific entry in the array by
  // computing its address (`&(pgm_ptr_array[index])`). This must be done in a
  // single step, so that we never access the content of `pgm_ptr_array[index]`,
  // which would read a value from RAM. To make this as clear as possible, we
  // use pointer arithmetic instead of the subscript operator.
  _PointerType* pgm_ptr_p = pgm_ptr_array + index;

  // Now that we've got the address (in PROGMEM) of the pointer data we want, we
  // can read it directly. As long as a pointer is just two bytes, this works
  // just fine. On a system that usese four-byte pointers, we'd have to use
  // `pgm_read_word_far()` instead. Better yet, `memcpy_P()`.
  uint16_t ptr_data = pgm_read_word(pgm_ptr_p);

  // Now we have the value of the pointer, but it's represented as an integer,
  // so we need to use `reinterpret_cast` in order to return it as a pointer of
  // the correct type.
  _PointerType ptr = reinterpret_cast<_PointerType>(ptr_data);

  // Finally, we have a pointer in RAM of the correct type, so we return it.
  return ptr;
}

// This is a less safe version of the above, useful if we don't have an actual
// array, but instead all we have is a pointer to the first element.
template<typename _PointerType>
_PointerType readPointerFromProgmemArrayPtr(_PointerType* pgm_ptr_array,
                                            byte  index) {
  // First, we get the (PROGMEM) pointer to the specific entry in the array by
  // computing its address (`&(pgm_ptr_array[index])`). This must be done in a
  // single step, so that we never access the content of `pgm_ptr_array[index]`,
  // which would read a value from RAM. To make this as clear as possible, we
  // use pointer arithmetic instead of the subscript operator.
  _PointerType* pgm_ptr_p = pgm_ptr_array + index;

  // Now that we've got the address (in PROGMEM) of the pointer data we want, we
  // can read it directly. As long as a pointer is just two bytes, this works
  // just fine. On a system that usese four-byte pointers, we'd have to use
  // `pgm_read_word_far()` instead. Better yet, `memcpy_P()`.
  uint16_t ptr_data = pgm_read_word(pgm_ptr_p);

  // Now we have the value of the pointer, but it's represented as an integer,
  // so we need to use `reinterpret_cast` in order to return it as a pointer of
  // the correct type.
  _PointerType ptr = reinterpret_cast<_PointerType>(ptr_data);

  // Finally, we have a pointer in RAM of the correct type, so we return it.
  return ptr;
}

template<typename _Type>
void loadFromProgmem(_Type& pgm_object, _Type& object) {
  memcpy_P(&object, &pgm_object, sizeof(object));
}

// This should work because we're using a reference parameter; I do not think it
// would work if we pass the parameter by value.
template<typename _Type>
_Type readFromProgmem(_Type const & pgm_object) {
  _Type object;
  memcpy_P(&object, &pgm_object, sizeof(object));
  return object;
}

} // namespace kaleidoglyph {
