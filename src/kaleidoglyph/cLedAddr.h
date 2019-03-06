// -*- c++ -*-

#pragma once

#include "kaleidoglyph/LedAddr.h"


namespace kaleidoglyph {
namespace cLedAddr {

constexpr LedAddr start   { 0              };
constexpr LedAddr end     { total_leds     };

constexpr LedAddr min     { 0              };
constexpr LedAddr max     { total_leds - 1 };
constexpr LedAddr total   { total_leds     };
constexpr LedAddr unknown { total_leds     };
constexpr LedAddr invalid { 0xFF           };

} // namespace cLedAddr {
} // namespace kaleidoglyph {
