// -*- c++ -*-

#pragma once

#include <Arduino.h>

#include "kaleidoglyph/KeyAddr.h"
#include "kaleidoglyph/utils.h"


namespace kaleidoglyph {

// A bitfield composed of bytes with one bit representing a boolean state for each KeyAddr
// in the keyboard.
class KeyAddrBitfield {

 public:
  KeyAddrBitfield() = default;

  bool bitRead(KeyAddr k) const {
    assert(byte(k) < total_keys);
    byte r = byte(k) / 8;
    byte c = byte(k) % 8;
    return bitRead(data_[r], c);
  }

  void bitSet(KeyAddr k) {
    assert(byte(k) < total_keys);
    byte r = byte(k) / 8;
    byte c = byte(k) % 8;
    bitSet(data_[r], c);
  }

  void bitClear(KeyAddr k) {
    assert(byte(k) < total_keys);
    byte r = byte(k) / 8;
    byte c = byte(k) % 8;
    bitClear(data_[r], c);
  }

  void bitWrite(KeyAddr k, bool v) {
    assert(byte(k) < total_keys);
    byte r = byte(k) / 8;
    byte c = byte(k) % 8;
    bitWrite(data_[r], c, v);
  }

 protected:
  // Here's a possible reason to move this bitfield definition to the hardware module: For
  // 32-bit processors, it may make more sense to use a larger unit size. I'm still a bit
  // skeptical about that actually helping, though, as it increases the chance of needing
  // to check all the bits. The ideal size would be the square root of the number of keys
  // (like the Keyboardio Model01).
  byte data_[bitfieldByteSize(total_keys)];

  // --------------------------------------------------------------------------------
  // Iterator for range-based for loops
 public:
  class Iterator;
  friend class KeyAddrBitfield::Iterator;

  Iterator begin() {
    return Iterator{*this, 0};
  }
  Iterator end() {
    return Iterator{*this, bitfieldByteSize(total_keys)};
  }

  class Iterator {
   public:
    Iterator(KeyAddrBitfield& bitfield, byte x)
        : bitfield_(bitfield), x_(x) {}

    bool operator!=(const Iterator& other);

    KeyAddr operator*();

    void operator++();

   private:
    KeyAddrBitfield& bitfield_;
    byte x_; // byte number in the bitfield
    byte y_{0}; // bit number in the byte
    byte bank_;
    KeyAddr addr_;

  }; // class Iterator {

};

} // namespace kaleidoglyph {


inline
bool Keyboard::Iterator::operator!=(const Iterator& other) {
  // First, the test for the end condition (return false when all the bytes have been
  // tested):
  while (x_ < other.x_) {
    // Get the data for the byte `x_` from the bitfield, then shift it by the number of
    // bits we've already checked (`y_`):
    bank_ = bitfield_.data_[x_];
    bank_ >>= y_;

    // Now we iterate through that byte until we either find a bit that is set, or we find
    // that there are no more bits set. If (as expected most of the time) no bits are set,
    // we do nothing:
    while (bank_ != 0) {
      // If the low (remaining) bit is set, generate a `KeyAddr` object from the bitfield
      // coordinates and store it for the dereference operator to return:
      if (bank_ & 1) {
        addr_ = KeyAddr{(x_ * 8) + y_};
        return true;
      }
      // The low bit wasn't set, so we shift the data by one and track that shift with the
      // bit coordinate (`y_`):
      bank_ >>= 1;
      y_ += 1;
    }

    // When we're done checking a byte, move on to the next one:
    x_ += 1;
    y_  = 0;
  }
  return false;
}

inline
KeyAddr Keyboard::Iterator::operator*() {
  return addr_;
}

inline
void Keyboard::Iterator::operator++() {
  // After the comparison operator returns `true`, we advance the bit coordinate to check
  // the next bit in whichever byte we're looking at. If it's already at 7, that's okay,
  // because `bank_` (see above) will be all zeros when it gets checked at the start of
  // the while loop.
  ++y_;
}


// ================================================================================
// How to use the iterator above:
#if 0
// To use the KeyAddrBitfield::Iterator, write a loop like the following:
KeyAddrBitfield bitfield;
for (KeyAddr k : bitfield) {
  // Here, you'll get a `KeyAddr` object for each bit that is set in `bitfield`.
}
#endif
