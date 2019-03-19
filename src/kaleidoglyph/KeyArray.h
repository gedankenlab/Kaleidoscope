// -*- c++ -*-

#pragma once

#include <Arduino.h>
#include <assert.h>

#include "kaleidoglyph/Key.h"
#include "kaleidoglyph/KeyAddr.h"
#include "kaleidoglyph/KeymapEntry.h"
#include "kaleidoglyph/cKeyAddr.h"


namespace kaleidoglyph {

template <byte _size = total_keys>
struct KeyArray {
  Key keys[_size];

  byte size() {
    return _size;
  }
  Key& operator[](KeyAddr k) {
    assert(byte(k) < _size);
    return keys[byte(k)];
  }
  const Key& operator[](KeyAddr k) const {
    assert(byte(k) < _size);
    return keys[byte(k)];
  }

  // Iterator -- Don't bother returning only non-empty values
 private:
  class Iterator;
  friend class KeyArray::Iterator;

 public:
  Iterator begin() {
    return {*this, KeyAddr(0)};
  }
  Iterator end() {
    return {*this, KeyAddr(_size)};
  }

 private:
  class Iterator {
   public:
    Iterator(KeyArray<_size>& array, KeyAddr k) : array_(array), k_(k) {}
    bool operator!=(const Iterator& other) const {
      return k_ != other.k_;
    }
    KeymapEntry operator*() {
      return {k_, array_[k_]};
    }
    Iterator& operator++() {
      ++k_;
      return *this;
    }
   private:
    KeyArray<_size>& array_;
    KeyAddr k_;
  };
};

} // namespace kaleidoglyph {

#if 0
// Use KeyArray::Iterator as follows:
KeyArray active_keys;
for (Key& key : active_keys) {
  if (key.isEmpty())
    continue;
  key = cKey::clear;
}
// The iterator might not be worth it:
KeyArray active_keys;
for (KeyAddr k{cKeyAddr::start}; k < cKeyAddr::end; ++k) {
  Key& key = active_keys[k];
  if (key.isEmpty())
    continue;
  key = cKey::clear;
}
#endif
