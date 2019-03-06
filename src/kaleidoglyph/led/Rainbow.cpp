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

#include "kaleidoglyph/led/LedController.h"
#include "kaleidoglyph/Controller.h"
#include "kaleidoglyph/led/Rainbow.h"
#include "kaleidoglyph/led/utils.h"
#include "kaleidoglyph/Color.h"
#include "kaleidoglyph/LedAddr.h"
#include "kaleidoglyph/cLedAddr.h"


namespace kaleidoglyph {

void LedRainbowMode::update(LedController& led_controller) {

  uint16_t current_time = Controller::scanStartTime();
  uint16_t elapsed_time = current_time - last_update_time_;
  if (elapsed_time < update_interval_) {
    return;
  }
  last_update_time_ += update_interval_;
  ++current_hue_;

  Color current_color = hsvToRgb(current_hue_, saturation_, value_);
  led_controller.setKeyColor(current_color);
}


// ---------

void LedRainbowWaveMode::update(LedController& led_controller) {

  uint16_t current_time = Controller::scanStartTime();
  uint16_t elapsed_time = current_time - last_update_time_;
  if (elapsed_time < update_interval_) {
    return;
  }
  last_update_time_ += update_interval_;
  ++current_base_hue_;

  for (LedAddr led{cLedAddr::start}; led < cLedAddr::end; ++led) {
    byte key_hue_offset = 16 * (byte(led) / 4);
    byte key_hue = current_base_hue_ + key_hue_offset;
    Color key_color = hsvToRgb(key_hue, saturation_, value_);
    led_controller.setLedColor(led, key_color);
  }
}

}
