// -*- c++ -*-

// This file contains function declarations only. The definitions need to be supplied in
// code generated either by preprocessor macros or a pre-build perl script that writes all
// the hook method calls for the sketch based on the plugins that are used.

// I think it will work to put "hooks.cpp" in the sketch module, with the *.ino file.

#pragma once

#include <Arduino.h>

#include KALEIDOGLYPH_HARDWARE_H
#include KALEIDOGLYPH_HARDWARE_KEYBOARD_H
#include "kaleidoglyph/EventHandlerResult.h"
#include "kaleidoglyph/KeyEvent.h"
#include "kaleidoglyph/hid/keyboard.h"


namespace kaleidoglyph {

// forward declaration
class LedController;

namespace hooks {

/// Call pre-keyswitch-scan hooks (run every cycle, before keyswitches are scanned)
void preKeyswitchScan();

void setLedForeground(KeyAddr k);

/// Restore foreground LED colors
bool setForegroundColor(KeyAddr k);

/// Call keyswitch event handler hooks (run when a key press or release is detected)
EventHandlerResult onKeyswitchEvent(KeyEvent& event);

/// Call keyswitch event handler hook for plugin with given id
EventHandlerResult onKeyEvent(byte plugin_id, KeyEvent& event);

/// Call keyboard HID pre-report hooks (run when a keyboard HID report is about to be sent)
bool preKeyboardReport(hid::keyboard::Report& keyboard_report);

/// Call keyboard HID post-report hooks (run after a keyboard HID report is sent)
void postKeyboardReport(KeyEvent event);

} // namespace hooks {
} // namespace kaleidoglyph {
