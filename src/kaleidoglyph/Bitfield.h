// -*- c++ -*-

#pragma once

#include <Arduino.h>

#include "kaleidoglyph/KeyAddr.h"
#include "kaleidoglyph/utils.h"


namespace kaleidoglyph {

// ================================================================================
// Generic Bitfield class, useful for defining KeyAddrBitfield, and others.
template <unsigned _size,
          typename _IndexType = KeyAddr,
          typename _UnitType = byte,
          typename _SizeType = byte>
class Bitfield {

  // This makes things easier for the iterator below:
  typedef Bitfield<_size, _IndexType, _UnitType, _SizeType> BitfieldType;

 public:

  static constexpr _SizeType unit_size = 8 * sizeof(_UnitType);
  static constexpr _SizeType total_blocks = bitfieldSize<_UnitType>(_size);
  static constexpr _SizeType size = _size;

  static constexpr _SizeType blockIndex(_IndexType i) {
    return _SizeType(i) / unit_size;
  }
  static constexpr _SizeType bitIndex(_IndexType i) {
    return _SizeType(i) % unit_size;
  }
  static constexpr _IndexType index(_SizeType block_index, _SizeType bit_index) {
    return _IndexType((block_index * unit_size) + bit_index);
  }
  bool read(_IndexType i) const {
    assert(_SizeType(i) < _size);
    return bitRead(data_[blockIndex(i)], bitIndex(i));
  }
  void set(_IndexType i) {
    assert(_SizeType(i) < _size);
    bitSet(data_[blockIndex(i)], bitIndex(i));
  }
  void clear(_IndexType i) {
    assert(_SizeType(i) < _size);
    bitClear(data_[blockIndex(i)], bitIndex(i));
  }
  void write(_IndexType i, bool value) {
    assert(_SizeType(i) < _size);
    bitWrite(data_[blockIndex(i)], bitIndex(i), value);
  }

 private:

  _UnitType data_[total_blocks] = {};


  // ----------------------------------------------------------------------------
  // Iterator!
 public:
  class Iterator;
  friend class Bitfield::Iterator;

  Iterator begin() {
    return Iterator{*this, 0};
  }
  Iterator end() {
    return Iterator{*this, total_blocks};
  }

  class Iterator {
   public:
    Iterator(BitfieldType& bitfield, _SizeType x)
        : bitfield_(bitfield), block_index_(x) {}

    bool operator!=(const Iterator& other) {
      // First, the test for the end condition (return false when all the blocks have been
      // tested):
      while (block_index_ < other.block_index_) {
        // Get the data for the block at `block_index_` from the bitfield, then shift it
        // by the number of bits we've already checked (`bit_index_`):
        block_ = bitfield_.data_[block_index_];
        block_ >>= bit_index_;

        // Now we iterate through that block until we either find a bit that is set, or we
        // find that there are no more bits set. If (as expected most of the time) no bits
        // are set, we do nothing:
        while (block_ != 0) {
          // If the low (remaining) bit is set, generate an `_IndexType` object from the
          // bitfield coordinates and store it for the dereference operator to return:
          if (block_ & 1) {
            index_ = BitfieldType::index(block_index_, bit_index_);
            return true;
          }
          // The low bit wasn't set, so we shift the data block by one and track that
          // shift with the bit coordinate (`bit_index_`):
          block_ >>= 1;
          bit_index_ += 1;
        }

        // When we're done checking a block, move on to the next one:
        block_index_ += 1;
        bit_index_  = 0;
      }
      return false;
    }

    _IndexType operator*() {
      assert(index_ < _size);
      return index_;
    }

    void operator++() {
      ++bit_index_;
    }

   private:
    BitfieldType& bitfield_;
    _SizeType block_index_;    // index of the block
    _SizeType bit_index_{0}; // bit index in the block
    _UnitType block_;
    _IndexType index_;

  }; // class Iterator {

}; // class Bitfield {

} // namespace kaleidoglyph {


// ================================================================================
// How to use the iterator above:
#if 0
typedef Bitfield<total_keys, KeyAddr, byte, byte> KeyAddrBitfield;
// To use the KeyAddrBitfield::Iterator, write a loop like the following:
KeyAddrBitfield bitfield;
for (KeyAddr k : bitfield) {
  // Here, you'll get a `KeyAddr` object for each bit that is set in `bitfield`.
}
#endif
