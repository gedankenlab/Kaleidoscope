// -*- c++ -*-

#pragma once

#include <Arduino.h>

#include "kaleidoglyph/Color.h"
#include "kaleidoglyph/KeyAddr.h"
#include "kaleidoglyph/KeyAddrBitfield.h"
#include "kaleidoglyph/hardware/Keyboard.h"
#include "kaleidoglyph/hooks.h"
#include "kaleidoglyph/led/LedMode.h"
#include "kaleidoglyph/utils.h"


namespace kaleidoglyph {

#if defined(KALEIDOGLYPH_LED_MANAGER_CONSTANTS_H)
#include KALEIDOGLYPH_LED_MANAGER_CONSTANTS_H
#else
// I should make this a member variable, not a constant (different modes should
// use different update intervals)
constexpr byte led_sync_interval{32};
#endif

class LedManager {

 public:
  // This constructor is a template function so that we can just pass an array
  // to it, instead of needing to have the size of the array as an additional
  // parameter. The first parameter is an array of `LedModeUpdaterLoader`s (in
  // PROGMEM), which contain pointers to ...
  template <byte _modes_count>
  LedManager(LedModeLoader const (&pgm_loaders)[_modes_count],
             void*               updater_buffer,
             hardware::Keyboard& keyboard)
      : keyboard_(keyboard),
        pgm_updater_loaders_(pgm_loaders),
        modes_count_(_modes_count),
        updater_p_(static_cast<LedModeUpdater*>(updater_buffer)) {
    LedMode::init(this);
    for (byte i{0}; i < _modes_count; ++i) {
      LedModeLoader loader = readFromProgmemArray(pgm_loaders, i);
      loader.led_mode_p->assignId(i);
    }
  }

  // Note we don't provied LedAddr versions of these, because that makes the
  // overrides overly complex.
  Color getKeyColor(KeyAddr k) const;
  void  setKeyColor(KeyAddr k, Color color);
  void  setKeyColor(Color color);
  void  setLedColor(LedAddr led, Color color);

  void               preKeyswitchScan();
  EventHandlerResult onKeyEvent(KeyEvent& event);

  void setForeground(KeyAddr k);

  byte activeModeIndex() const { return curr_mode_index_; }

  void nextMode() {
    next_mode_index_ = curr_mode_index_ + 1;
    if (next_mode_index_ > modes_count_) next_mode_index_ = 0;
  }
  void backgroundOff() { next_mode_index_ = 0xFF; }

  LedMode* getCurrentMode() const;
  void     setActiveMode(byte index);

  // byte requestInterval(byte interval);

  // We need a hook somewhere for layer changes (see LED-ActiveLayerColor.cpp)
  // ???


 private:
  static constexpr byte invalid_index_{0xFF};

  hardware::Keyboard& keyboard_;

  LedModeLoader const* pgm_updater_loaders_;
  byte const           modes_count_;

  LedModeUpdater* const updater_p_;
  LedMode*              curr_mode_p_;

  byte curr_mode_index_{invalid_index_};
  byte next_mode_index_{invalid_index_};

  // LedMode* active_mode_{nullptr};

  KeyAddrBitfield foreground_mask_;

  void restoreForegroundColors();
  void restoreBackgroundColor(KeyAddr k);

  void activateBackgroundMode();
  void updateBackgroundColors();
  void clearBackgroundColors();

  bool isValidMode(byte index) { return (index < modes_count_); }
};

// There are a whole lot of functions defined here that would be better to
// define in a non-header file, but I want most of them to be inlined in the
// files where they're called from, and I'm not sure that will happen if the
// linker is involved.


}  // namespace kaleidoglyph
