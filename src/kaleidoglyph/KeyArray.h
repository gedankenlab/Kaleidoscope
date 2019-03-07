// -*- c++ -*-

#pragma once

#include <Arduino.h>
#include <assert.h>

#include "kaleidoglyph/Key.h"
#include "kaleidoglyph/KeyAddr.h"
#include "kaleidoglyph/KeymapEntry.h"
#include "kaleidoglyph/cKeyAddr.h"


namespace kaleidoglyph {

template <byte SIZE = total_keys>
struct KeyArray {
  Key keys[SIZE];

  byte size() {
    return SIZE;
  }
  Key& operator[](KeyAddr k) {
    assert(byte(k) < SIZE);
    return keys[byte(k)];
  }
  const Key& operator[](KeyAddr k) const {
    assert(byte(k) < SIZE);
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
    return {*this, KeyAddr(SIZE)};
  }

 private:
  class Iterator {
   public:
    Iterator(KeyArray<SIZE>& array, KeyAddr k) : array_(array), k_(k) {}
    bool operator!=(const Iterator& other) const {
      return k_ != other.k_;
    }
    Key& operator*() {
      return array_[k_];
    }
    Iterator& operator++() {
      ++k_;
      return *this;
    }
   private:
    KeyArray<SIZE>& array_;
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
