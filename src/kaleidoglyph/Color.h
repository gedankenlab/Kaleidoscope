// -*- c++ -*-

#pragma once

// The `Color` type is defined in the hardware module (Kaleidoglyph-Hardware-*). In the
// `boards.txt` file, the master header file for the corresponding hardware module is
// defined as a compiler flag. For example, for the Keyboardio Model01:
//
// '-DKALEIDOGLYPH_HARDWARE_H=<Kaleidoglyph-Hardware-Model01.h>'
//
// That file will contain a definition of a preprocessor macro that refers to the
// hardware-specific implementation of the `Color` type (among others), like so:
//
// #define KALEIDOGLYPH_COLOR_H <model01/Color.h>
//
// This header file exists so that plugin code that uses the `Color` type can treat it
// just like any other type that belongs to Kaleidoglyph, by including it as follows:
//
// #include <kaleidoglyph/Color.h>

#include KALEIDOGLYPH_HARDWARE_H

// Maybe I should use #if defined() here, and provide the reference code below as a
// default definition for hardware that doesn't define `Color`?
#include KALEIDOGLYPH_COLOR_H

// Following is a code describing the interface of the `Color` type, which must be
// provided by any hardware module, and which can be used for quick reference. This is
// just a description of the interface, not the actual definition of the type:
#if 0

namespace kaleidoglyph {

class Color {
 public:
  constexpr
  Color(byte r, byte g, byte b);

  byte red  () const;
  byte green() const;
  byte blue () const;

  void red  (byte r);
  void green(byte g);
  void blue (byte b);

  bool operator==(const Color& other) const;
  bool operator!=(const Color& other) const;

  // copy a Color object from Progmem
  void readFromProgmem(const Color& pgm_color);
};

Color getProgmemColor(const Color& pgm_color);

}

#endif
