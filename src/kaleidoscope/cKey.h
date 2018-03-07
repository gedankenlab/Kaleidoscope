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

constexpr Key transparent { 0xFFFF };
constexpr Key blank       { 0x0000 };

} // namespace cKey {

} // namespace kaleidoscope {

#define ___ cKey::transparent
#define XXX cKey::blank

#define Key_Transparent cKey::transparent
#define Key_NoKey       cKey::blank
