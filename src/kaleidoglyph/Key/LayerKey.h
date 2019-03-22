// -*- c++ -*-

#pragma once

#include <Arduino.h>
#include <assert.h>

#include "kaleidoglyph/Key.h"


namespace kaleidoglyph {

class LayerKey {

 private:
  byte index_ : 6, shift_ : 1, move_ : 1, reserved_ : 2, type_id_ : 6;

 public:
  constexpr
  byte index() const { return index_; }
  constexpr
  bool isLayerShift() const { return shift_; }
  constexpr
  bool isLayerToggle() const { return !shift_; }

  constexpr
  LayerKey() : index_(0), shift_(false), move_(false), reserved_(0),
               type_id_(Key::layer_type_id) {}

  constexpr explicit
  LayerKey(byte index, bool shift = false, bool move = false)
      : index_(index), shift_(shift), move_(move), reserved_(0),
        type_id_(Key::layer_type_id) {}

  constexpr explicit
  LayerKey(Key key) : index_    (uint16_t(key)                   ),
                      shift_    (uint16_t(key) >>  6             ),
                      move_     (uint16_t(key) >> (6 + 1)        ),
                      reserved_ (uint16_t(key) >> (6 + 1 + 1)    ),
                      type_id_  (uint16_t(key) >> (6 + 1 + 1 + 2)) {
    assert(type_id_ == Key::layer_type_id);
  }

  constexpr
  operator Key() const {
    return Key ( index_                      |
                 shift_    <<  6             |
                 move_     << (6 + 1)        |
                 reserved_ << (6 + 1 + 1)    |
                 type_id_  << (6 + 1 + 1 + 2) );
  }

  static constexpr
  bool verifyType(Key key) {
    return ((uint16_t(key) >> (6 + 1 + 1 + 2)) == Key::layer_type_id);
  }

}__attribute__((packed));

constexpr
bool isLayerKey(const Key key) {
  return LayerKey::verifyType(key);
}

constexpr
bool isLayerShiftKey(const Key key) {
  if (LayerKey::verifyType(key)) {
    return LayerKey{key}.isLayerShift();
  }
  return false;
}

constexpr
bool isLayerToggleKey(const Key key) {
  if (LayerKey::verifyType(key)) {
    return LayerKey{key}.isLayerToggle();
  }
  return false;
}

constexpr
LayerKey layerShiftKey(const byte index) {
  return LayerKey(index, true);
}

constexpr
LayerKey layerToggleKey(const byte index) {
  return LayerKey(index, false);
}

} // namespace kaleidoglyph {
