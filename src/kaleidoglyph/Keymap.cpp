// -*- c++ -*-

#include "kaleidoglyph/Keymap.h"

#include <Arduino.h>
#include <assert.h>

#include "kaleidoglyph/Key.h"
#include "kaleidoglyph/KeyAddr.h"
#include "kaleidoglyph/KeyArray.h"
#include "kaleidoglyph/Layer.h"
#include "kaleidoglyph/cKey.h"
#include "kaleidoglyph/cKeyAddr.h"


namespace kaleidoglyph {

Keymap::Keymap(Layer* const *layers, byte count) : layers_{layers}, layer_count_{count} {
  clearLayerStates_();
}


Key Keymap::lookup(KeyAddr key_addr, byte layer_index) const {
  return (*layers_[layer_index])[key_addr];
}


Key Keymap::operator[](KeyAddr key_addr) const {
  return lookupActiveLayerAndKey(key_addr).key;
}


byte Keymap::lookupActiveLayer(KeyAddr key_addr) const {
  return lookupActiveLayerAndKey(key_addr).layer;
}


// This function should do the caching of lookups to prevent EEPROM lookups from being too
// slow
LayerKeyPair Keymap::lookupActiveLayerAndKey(KeyAddr key_addr) const {
  // First, unconditionally check the top layer
  byte layer_index{top_active_layer_index_};
  Key key = lookup(key_addr, layer_index);
  if (! key.isClear())
    return {layer_index, key};

  // Then search the layer stack, stopping at the default layer
  for (--layer_index; layer_index > default_layer_index_; --layer_index) {
    if (isLayerActive(layer_index)) {
      key = lookup(key_addr, layer_index);
      if (! key.isClear())
        return {layer_index, key};
    }
  }

  // If we still haven't found a non-transparent key, return whatever's in the default
  // layer (even if it's transparent)
  return {default_layer_index_, lookup(key_addr, default_layer_index_)};
}


/// Activate the specified layer
void Keymap::activateLayer(byte layer_index) {
  if (layer_index >= layer_count_)
    return;

  if (getLayerState_(layer_index))
    return;

  setLayerState_(layer_index, true);

  if (layer_index > top_active_layer_index_)
    top_active_layer_index_ = layer_index;
}


/// Deactivate the specified layer
void Keymap::deactivateLayer(byte layer_index) {
  if (layer_index >= layer_count_)
    return;

  if (! getLayerState_(layer_index))
    return;

  setLayerState_(layer_index, false);

  if (layer_index == top_active_layer_index_)
    updateTopActiveLayer_();
}

void Keymap::toggleLayer(byte layer_index) {
  if (getLayerState_(layer_index)) {
    deactivateLayer(layer_index);
  } else {
    activateLayer(layer_index);
  }
}


void Keymap::handleLayerChange(KeyEvent event, KeyArray<total_keys>& active_keys) {
  assert(isLayerKey(event.key));
  LayerKey layer_key{event.key};
  assert(layer_key.index() < layer_count_);

  if (layer_key.isLayerShift()) {
    if (event.state.toggledOn()) {
      top_active_layer_index_ = layer_key.index();
      for (KeyAddr k = cKeyAddr::start; k < cKeyAddr::end; ++k) {
        if (k == event.addr)
          continue;
        Key& key = active_keys[k];
        if (isLayerShiftKey(key))
          key.mask();
      }
    } else {
      updateTopActiveLayer_();
    }
  } else {
    if (event.state.toggledOn())
      toggleLayer(layer_key.index());
  }
  // Maybe we want to use a bit to signal switches between PROGMEM & EEPROM keymaps, but
  // I'm inclined to think that should be a separate function entirely
}


void Keymap::updateTopActiveLayer_() {
  for (byte i(layer_count_ - 1); i > default_layer_index_; --i) {
    if (getLayerState_(i)) {
      top_active_layer_index_ = i;
      return;
    }
  }
  top_active_layer_index_ = default_layer_index_;
}


inline
bool Keymap::getLayerState_(byte layer_index) const {
  return bitRead(layer_states_[layer_index / 8], layer_index % 8);
}


inline
void Keymap::setLayerState_(byte layer_index, bool state) {
  bitWrite(layer_states_[layer_index / 8], layer_index % 8, state);
}


inline
void Keymap::clearLayerStates_() {
  for (byte i(0); i < sizeof(layer_states_); ++i) {
    layer_states_[i] = 0;
  }
  setLayerState_(default_layer_index_, true);
}

} // namespace kaleidoglyph {
