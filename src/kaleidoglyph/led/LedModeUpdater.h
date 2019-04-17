// -*- c++ -*-

#pragma once

#include <Kaleidoglyph.h>
#include "kaleidoglyph/Color.h"
#include "kaleidoglyph/KeyAddr.h"
#include "kaleidoglyph/led/LedMode.h"


namespace kaleidoglyph {

// This is the base class for an LED mode's inner Updater class, which gets
// swapped in and out of memory.
class LedModeUpdater {

 public:
  LedModeUpdater(LedMode& owner) : owner_(owner) {}
  virtual void activate() {}
  virtual void update() {}
  virtual Color getKeyColor(KeyAddr k) const { return Color{0, 0, 0}; }
  // I'm considering this one:
  LedMode& owner() const { return owner_; }

 protected:
  LedMode& owner_;
};

// inner class object size template
template <typename _LedMode>
struct UpdaterSize {
  static constexpr size_t value = sizeof(typename _LedMode::Updater);
};

// variadic template
template <typename _FirstLedMode, typename... _OtherLedModes>
struct MaxUpdaterSize {
  static constexpr size_t first_size = UpdaterSize<_FirstLedMode>::value;
  static constexpr size_t others_max_size =
      MaxUpdaterSize<_OtherLedModes...>::value;
  static constexpr size_t value =
      (first_size > others_max_size) ? first_size : others_max_size;
};

// variadic template terminator
template <typename _LastLedMode>
struct MaxUpdaterSize<_LastLedMode> {
  static constexpr size_t value = UpdaterSize<_LastLedMode>::value;
};

#if 0
// This is how to use the updater size computaton helper template(s). Each
// LedMode object should be passed as a parameter.
constexpr byte max_updater_size =
    MaxUpdaterSize<decltype(foo),
                   decltype(bar),
                   decltype(baz)>::value;
#endif

}  // namespace kaleidoglyph
