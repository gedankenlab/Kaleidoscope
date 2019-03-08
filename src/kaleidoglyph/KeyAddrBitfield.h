// -*- c++ -*-

#pragma once

#include <Arduino.h>

#include "kaleidoglyph/KeyAddr.h"
#include "kaleidoglyph/utils.h"
#include "kaleidoglyph/Bitfield.h"

namespace kaleidoglyph {

typedef Bitfield<total_keys, KeyAddr, byte, byte> KeyAddrBitfield;

}
