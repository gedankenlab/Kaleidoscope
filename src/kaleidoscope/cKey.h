// -*- c++ -*-

#pragma once

#include "kaleidoscope/Key.h"
#include "kaleidoscope/cKey/keyboard.h"
#include "kaleidoscope/cKey/consumer.h"


// Keyboard HID mappings
namespace kaleidoscope {

// This namespace is for storing constants of type `Key`. The leading `c` stands for
// `constant` or `const`, so any symbol that begins with `cKey::` can be assumed to be a
// `const Key` object.
namespace cKey {

constexpr Key clear { 0xFFFF };
constexpr Key blank { 0x0000 };

constexpr Key transparent = clear;
constexpr Key no_key      = blank;

} // namespace cKey {

} // namespace kaleidoscope {

#define ___ ::kaleidoscope::cKey::clear
#define XXX ::kaleidoscope::cKey::blank

#define Key_Transparent ::kaleidoscope::cKey::clear
#define Key_NoKey       ::kaleidoscope::cKey::blank

#include "kaleidoscope/cKey/backcompat/key_defs_keyboard.h"
#include "kaleidoscope/cKey/backcompat/key_defs_consumer.h"

#define LAYER_SHIFT_OFFSET 42
#define KEYMAP_PREVIOUS    33
#define KEYMAP_NEXT        34
