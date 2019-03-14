// -*- c++ -*-

#pragma once

#include <Arduino.h>

// -----------------------------------------------------------------------------------
// Each sketch is specific to the hardware that it will run on, and may override default
// values in plugin code, as well. To accomplish this, we include the sketch's header file
// by adding the following line to its `.kaleidoglyph-builder.conf` file. The example is
// for the default firmware for the Keyboardio Model01.
//
// LOCAL_CFLAGS='-DKALEIDOGLYPH_SKETCH_H=<Model01-Firmware.h>'
//
#if defined(KALEIDOGLYPH_SKETCH_H)
#include KALEIDOGLYPH_SKETCH_H
#endif
// One thing that the sketch's header file should define is `KALEIDOGLYPH_HARDWARE_H` --
// the header file for the hardware module that the firmware should run on. Or maybe it's
// better to stick with that being defined in `boards.txt` in `*.build.extra_flags`, a la
// Kaleidoscope.
// -----------------------------------------------------------------------------------

// The following should include the hardware module's master header file. This will define
// several other preprocessor macros, used throughout Kaleidoglyph to define
// hardware-specific data structures, et cetera. For the Keyboardio Model01, this will be
// defined as `<Kaleidoglyph-Hardward-Model01.h>`.
#include KALEIDOGLYPH_HARDWARE_H

// The hardware module's master header file should define macros to include the headers
// for the following hardware-specific data types:
//
// kaleidoglyph::KeyAddr
#include KALEIDOGLYPH_KEYADDR_H
// kaleidoglyph::LedAddr
#include KALEIDOGLYPH_LEDADDR_H
// kaleidoglyph::Color
#include KALEIDOGLYPH_COLOR_H
// kaleidoglyph::hardware::Keyboard
#include KALEIDOGLYPH_HARDWARE_KEYBOARD_H
// HID module (currently not used, but should be. It's not obvious, but this is hardware specific)
//#include KALEIDOGLYPH_HID_H
#include "Kaleidoglyph-HID.h"

#include "kaleidoglyph/Controller.h"
#include "kaleidoglyph/Key.h"
#include "kaleidoglyph/Keymap.h"
#include "kaleidoglyph/Layer.h"
#include "kaleidoglyph/cKey.h"
