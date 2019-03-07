// -*- c++ -*-

#pragma once

#include "kaleidoglyph/Key.h"
#include "kaleidoglyph/cKey/keyboard.h"
#include "kaleidoglyph/cKey/consumer.h"
#include "kaleidoglyph/led/LedKey.h"


// Keyboard HID mappings
namespace kaleidoglyph {

// This namespace is for storing constants of type `Key`. The leading `c` stands for
// `constant` or `const`, so any symbol that begins with `cKey::` can be assumed to be a
// `const Key` object.
namespace cKey {

constexpr Key clear { 0xFFFF };
constexpr Key blank { 0x0000 };

constexpr Key transparent = clear;
constexpr Key no_key      = blank;

constexpr Key masked   = blank;
constexpr Key unmasked = clear;

} // namespace cKey {

} // namespace kaleidoglyph {

#define ___ ::kaleidoglyph::cKey::clear
#define XXX ::kaleidoglyph::cKey::blank

#define Key_Transparent ::kaleidoglyph::cKey::clear
#define Key_NoKey       ::kaleidoglyph::cKey::blank

#include "kaleidoglyph/cKey/backcompat/key_defs_keyboard.h"
#include "kaleidoglyph/cKey/backcompat/key_defs_consumer.h"

#define LAYER_SHIFT_OFFSET 42
#define KEYMAP_PREVIOUS    33
#define KEYMAP_NEXT        34
