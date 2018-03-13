// -*- c++ -*-

#pragma once

#include <Arduino.h>

#include KALEIDOSCOPE_HARDWARE_H
#include KALEIDOSCOPE_KEYADDR_H

#include "kaleidoscope/Key.h"
#include "kaleidoscope/KeymapEntry.h"
#include "kaleidoscope/Layer.h"
#include "kaleidoscope/LayerKey.h"
#include "kaleidoscope/cKeyAddr.h"


namespace kaleidoscope {

/// Calculates the number of bytes needed to store a bitfield of the given size in bits
constexpr byte bitfieldSize(int bits) {
  return (bits / 8) + ((bits % 8) ? 1 : 0);
}

// Temporary constant, until I write the pre-build script(s)
constexpr byte MAX_LAYERS = 32;


class Keymap {

 public:
  // Note: `layers` is a pointer to an array of `Layer` pointers. I'm doing this so that
  // new (EEPROM) layers can be added after compile-time
  Keymap(Layer** layers, byte layer_count);

  Key lookup(KeyAddr key_addr, byte layer_index) const;

  LayerKey lookupActiveLayerKey(KeyAddr key_addr) const;
  byte lookupActiveLayer(KeyAddr key_addr) const;
  byte lookupLayer(KeyAddr key_addr) const; // alternative to lookupActiveLayer()
  const Layer& layer(byte layer_index) const;

  bool isLayerActive(byte layer_index) const {
    return getLayerState_(layer_index);
  }

  void activateLayer(byte layer_index);
  void deactivateLayer(byte layer_index);
  void toggleLayer(byte layer_index);
  void shiftToLayer(byte layer_index);
  void moveToLayer(byte layer_index);

  void handleLayerChange(Key key);

  Key operator[](KeyAddr k) const;

 private:
  // An array of pointers to the Layer objects that make up the keymap
  Layer** layers_;
  // The total number of layers; should be equal to MAX_LAYERS if we're just using PROGMEM
  // layers, but could be less if we use EEPROM as well, since it's possible to add layers
  // there at run-time.
  byte layer_count_;

  // Bitfield storing the state of each layer (1 = on, 0 = off). The alternative to this
  // is having each layer store its own state in a boolean (or a bitfield, if it has other
  // state info to store)
  byte layer_states_[bitfieldSize(MAX_LAYERS)];

  // The index of the highest active layer
  byte default_layer_index_ {0};
  byte top_active_layer_index_ {0};
  // Maybe: a cache of the current value for each key. This could be updated entirely
  // whenever a layer change happens, or it could be cleared (set all values to
  // Key_Transparent), and each key gets updated when lookup() is called on that key_addr.
  mutable Key keymap_cache_[total_keys];
  // We could also have a very aggressive cache which stores the layer that each key is
  // mapped from (updated on lookup, cleared when necessary)
  mutable byte active_layers_[total_keys];

  // Also, maybe this is where we store the active_keys_ object (reference?)
  //Layer& active_keys_;

  bool getLayerState_(byte layer_index) const;
  void setLayerState_(byte layer_index, bool state);

  // I think my new caching system makes these obsolete
  void clearLayerStates_();
  void updateTopActiveLayer_();

  // void setLayerActive_(byte layer, bool state);

 private:
  class Iterator;
  friend class Keymap::Iterator;

 public:
  // These iterator functions would be private if I could make them that way; they should
  // not be relied on as part of the public interface except insofar as they make it
  // possible to use a range-based for loop. I think it might be better to do away with
  // that, too, because it doesn't provide the same benefits as it does in the Layer
  // case. However, it does mean that iterating over the Keymap can use the same syntax as
  // iterating over a Layer.
  Iterator begin() const {
    return {*this, top_active_layer_index_};
  }
  Iterator end() const {
    return {*this, default_layer_index_};
  }

 private:
  class Iterator {
   public:
    Iterator(const Keymap& keymap, byte layer_index)
      : keymap_(keymap), layer_index_(layer_index) {}

    bool operator!=(const Iterator& other) const {
      return layer_index_ != other.layer_index_;
    }

    Layer & operator*() const {
      return *(keymap_.layers_[layer_index_]);
    }

    // operator++ used by the iterator doesn't need to return a value in this case. Also
    // it actually decrements, because we're searching from the top down. We can't get
    // away with only returning active layers without extra complications in the code,
    // unfortunately; it's less expensive for the caller to check than to do it here,
    // unless we know for sure that `default_layer_index_` is guaranteed to point to an
    // active layer, which it always should.
    void operator++() {
      --layer_index_;
    }

   private:
    const Keymap& keymap_;
    byte layer_index_;
  };

};


} // namespace kaleidoscope {
