// -*- c++ -*-

#pragma once

#include "kaleidoglyph/KeyAddr.h"


namespace kaleidoglyph {
namespace cKeyAddr {

constexpr KeyAddr start   { 0              };
constexpr KeyAddr end     { total_keys     };

constexpr KeyAddr min     { 0              };
constexpr KeyAddr max     { total_keys - 1 };
constexpr KeyAddr total   { total_keys     };
constexpr KeyAddr unknown { total_keys     };
constexpr KeyAddr invalid { 0xFF           };

} // namespace cKeyAddr {
} // namespace kaleidoglyph {
