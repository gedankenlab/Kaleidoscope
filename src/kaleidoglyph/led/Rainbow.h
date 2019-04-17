// -*- c++ -*-

/* Kaleidoscope-LEDEffect-Rainbow - Rainbow LED effects for Kaleidoscope.
 * Copyright (C) 2017-2018  Keyboard.io, Inc.
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

// -*- c++ -*-

#pragma once

#include <Kaleidoglyph.h>

#include <kaleidoglyph/KeyAddr.h>
#include <kaleidoglyph/Color.h>
#include <kaleidoglyph/led/utils.h>
#include "kaleidoglyph/led/LedMode.h"


namespace kaleidoglyph {
//namespace led {

// Forward declaration; we can't include the header
class LedController;

class LedRainbowMode : public LedMode {

 public:
  LedRainbowMode() {}

  void setBrightness(byte value) {
    value_ = value;
  }
  void setUpdateInterval(byte interval) {
    update_interval_ = interval;
  }

  class Updater : public LedModeUpdater {
   private:
    LedRainbowMode& mode_;
   public:
    Updater(LedRainbowMode& mode) : mode_(mode) {}
    void update() override;
   private:
    byte current_hue_{0};
    uint16_t last_update_time_{0};
  };
  friend class LedRainbowMode::Updater;

 private:
  byte saturation_{255};
  byte value_{150};
  uint16_t update_interval_{64}; // delay between updates (ms)
};

class LedRainbowWaveMode : public LedMode {

 public:
  LedRainbowWaveMode() {}

  void setBrightness(byte value) {
    value_ = value;
  }
  void setInterval(byte ms) {
    update_interval_ = ms;
  }

  class Updater : public LedModeUpdater {
   private:
    LedRainbowWaveMode& mode_;
   public:
    Updater(LedRainbowWaveMode& mode) : mode_(mode) {}
    void update() override;
   private:
    uint16_t current_base_hue_{0};  //  stores 0 to 614
    uint16_t last_update_time_{0};
  };
  friend class LedRainbowWaveMode::Updater;

 private:
  byte saturation_{255};
  byte value_{150};
  uint16_t update_interval_{64}; // delay between updates (ms)
};

//} // namespace led {
} // namespace kaleidoglyph {
