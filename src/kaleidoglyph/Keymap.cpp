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


Key Keymap::lookup(KeyAddr key_addr, byte layer_index) const {
  return (getLayer(layer_index))[key_addr];
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

  // Then search the layer stack, stopping at the default layer
  while ((layer_index > 0) && key.isClear()) {
    --layer_index;
    if (isLayerActive(layer_index)) {
      key = lookup(key_addr, layer_index);
    }
  }
  return {layer_index, key};
}

// This version starts looking at the specified `layer_index` (instead of
// `top_active_layer_index_`), and checks active layers until if finds a
// non-transparent `Key`.
LayerKeyPair Keymap::lookupActiveLayerAndKey(KeyAddr k, int8_t layer_index) const {
  Key key = cKey::clear;
  while(layer_index >= 0 && key.isClear()) {
    if (isLayerActive(layer_index)) {
      key = lookup(k, layer_index);
    }
  }
  return {byte(layer_index), key};
}


/// Activate the specified layer
void Keymap::activateLayer(byte layer_index) {
  if (layer_index >= layer_count_)
    return;

  if (isLayerActive(layer_index))
    return;

  layer_states_.set(layer_index);

  if (layer_index > top_active_layer_index_)
    top_active_layer_index_ = layer_index;
}


/// Deactivate the specified layer
void Keymap::deactivateLayer(byte layer_index) {
  if (layer_index >= layer_count_)
    return;

  if (! isLayerActive(layer_index))
    return;

  layer_states_.clear(layer_index);

  if (layer_index == top_active_layer_index_)
    updateTopActiveLayer_();
}

void Keymap::toggleLayer(byte layer_index) {
  if (isLayerActive(layer_index)) {
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
  for (byte i = layer_count_ - 1; i > default_layer_index_; --i) {
    if (isLayerActive(i)) {
      top_active_layer_index_ = i;
      return;
    }
  }
  top_active_layer_index_ = default_layer_index_;
}

} // namespace kaleidoglyph {
