// -*- c++ -*-

#pragma once

#include <Arduino.h>
#include "key_defs.h"

#include KALEIDOSCOPE_HARDWARE_H
#include KALEIDOSCOPE_KEYADDR_H
#include KALEIDOSCOPE_HARDWARE_KEYBOARD_H

#include "kaleidoscope/KeyswitchEvent.h"

// Macro for defining the keymap. This should be used in the sketch
// file (*.ino) to define the keymap[] array that holds the user's
// layers. It also computes the number of layers in that keymap.
#define KEYMAPS(layers...)                                              \
  const Key keymaps[][kaleidoscope::hardware::total_keys] PROGMEM = { layers }; \
  uint8_t layer_count = sizeof(keymaps) / sizeof(*keymaps);

namespace kaleidoscope {

class Layer_ {
 public:
  Layer_(void);

  /* There are two lookup functions, because we have two caches, and different
   * parts of the firmware will want to use either this or that (or perhaps
   * both, in rare cases).
   *
   * First of all, we use caches because looking up a key through all the layers
   * is costy, and the cost increases dramatically the more layers we have.
   *
   * Then, we have the `liveCompositeKeymap`, because to have layer behaviours
   * we want, that is, if you hold a key on a layer, release the layer key but
   * continue holding the other, we want for the layered keycode to continue
   * repeating.
   *
   * At the same time, we want other keys to not be affected by the
   * now-turned-off layer. So we update the keycode in the cache on-demand, when
   * the key is pressed. (see the top of `handleKeyswitchEvent`).
   *
   * On the other hand, we also have plugins that scan the whole keymap, and do
   * things based on that information, such as highlighting keys that changed
   * between layers. These need to be able to look at a state of where the
   * keymap *should* be, not necessarily where it is. The `liveCompositeKeymap`
   * is not useful here. So we use `activeLayers` which we update whenever
   * layers change (see `Layer.on` and `Layer.off`), and it updates the cache to
   * show how the keymap should look, without the `liveCompositeKeymap`-induced
   * behaviour.
   *
   * Thus, if we are curious about what a given key will do, use `lookup`. If we
   * are curious what the active layer state describes the key as, use
   * `lookupOnActiveLayer`.
   */
  static Key lookup(KeyAddr k) {
    return liveCompositeKeymap[k.addr];
  }
  static Key lookupOnActiveLayer(KeyAddr k) {
    uint8_t layer = activeLayers[k.addr];
    return (*getKey)(layer, k);
  }
  static uint8_t lookupActiveLayer(KeyAddr k) {
    return activeLayers[k.addr];
  }
  static void on(uint8_t layer);
  static void off(uint8_t layer);
  static void move(uint8_t layer);

  static uint8_t top(void) {
    return highestLayer;
  }
  static void next(void);
  static void previous(void);

  static boolean isOn(uint8_t layer);

  static void defaultLayer(uint8_t layer);
  static uint8_t defaultLayer(void);

  static uint32_t getLayerState(void);

  static Key eventHandler(const KeyswitchEvent& event);

  static Key(*getKey)(uint8_t layer, KeyAddr k);

  static Key getKeyFromPROGMEM(uint8_t layer, KeyAddr k);

  static void updateLiveCompositeKeymap(KeyAddr k);
  static void updateActiveLayers(void);

 private:
  static void updateHighestLayer(void);

  static uint8_t highestLayer;
  static Key liveCompositeKeymap[hardware::total_keys];
  static uint8_t activeLayers[hardware::total_keys];
};

} // namespace kaleidoscope {

extern kaleidoscope::Layer_ Layer;
