// -*- c++ -*-

#pragma once

#include <Arduino.h>
#include <assert.h>

#include KALEIDOGLYPH_HARDWARE_H

#include KALEIDOGLYPH_KEYADDR_H
#include "kaleidoglyph/Key.h"
#include "kaleidoglyph/KeymapEntry.h"
#include "kaleidoglyph/cKeyAddr.h"


namespace kaleidoglyph {

struct KeyArray {
  Key keys[total_keys];

  Key& operator[](KeyAddr k) {
    assert(byte(k) < total_keys);
    return keys[byte(k)];
  }
  const Key& operator[](KeyAddr k) const {
    assert(byte(k) < total_keys);
    return keys[byte(k)];
  }

  // Iterator -- Don't bother returning only non-empty values
 private:
  class Iterator;
  friend class KeyArray::Iterator;

 public:
  Iterator begin() {
    return {*this, cKeyAddr::start};
  }
  Iterator end() {
    return {*this, cKeyAddr::end};
  }

 private:
  class Iterator {
   public:
    Iterator(KeyArray& array, KeyAddr k) : array_(array), k_(k) {}
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
    KeyArray& array_;
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
