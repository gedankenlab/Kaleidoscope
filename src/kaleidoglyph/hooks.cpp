// -*- c++ -*-

// This file contains dummy versions of the master hook functions. The real versions
// depend on the specific plugins that are used in the given sketch, and should be defined
// in `<sketch_dir>/src/sketch/hooks.cpp`. The sketch's master header file
// (e.g. `Model01-Firmware.h`, referred to as `KALEIDOGLYPH_SKETCH_H`), should contain a
// reference to that file like so:
//
// #define KALEIDOGLYPH_HOOKS_H <sketch/hooks.h>

#if defined(KALEIDOGLYPH_SKETCH_H)
#include KALEIDOGLYPH_SKETCH_H
#endif

#if defined(KALEIDOGLYPH_HOOKS_H)
#include KALEIDOGLYPH_HOOKS_H
#else
// --------------------------------------------------------------------------------
// Default, in case the sketch hasn't defined a hooks.h file:

#include "kaleidoglyph/hooks.h"

#include <Arduino.h>

#include "kaleidoglyph/EventHandlerResult.h"
#include "kaleidoglyph/KeyEvent.h"
#include "kaleidoglyph/hid/Report.h"

namespace kaleidoglyph {
namespace hooks {

/// Call pre-keyswitch-scan hooks (run every cycle, before keyswitches are scanned)
__attribute__((weak))
void preKeyswitchScan() {}

/// Call onKeyswitchEvent handler hooks (run when a key press or release is detected)
///
/// Returns an `EventHandlerResult`: `proceed` if processing should continue, `abort` if
/// it should stop, and no further action should take place in response to the event.
__attribute__((weak))
EventHandlerResult onKeyswitchEvent(KeyEvent& /*event*/) {
  return EventHandlerResult::proceed;
}

/// Call onKeyEvent handler hooks (run when a key press or release is detected)
///
/// Returns an `EventHandlerResult`: `proceed` if processing should continue, or `abort`
/// if it should stop, and no further action should take place in response to the event.
__attribute__((weak))
EventHandlerResult onKeyEvent(byte /*plugin_id*/, KeyEvent& /*event*/) {
  return EventHandlerResult::proceed;
}

/// Call keyboard HID pre-report hooks (run when a keyboard HID report is about to be sent)
__attribute__((weak))
bool preKeyboardReport(hid::keyboard::Report& /*keyboard_report*/) {
  return true;
}

/// Call keyboard HID post-report hooks (run after a keyboard HID report is sent)
__attribute__((weak))
void postKeyboardReport(KeyEvent /*event*/) {}

} // namespace hooks {
} // namespace kaleidoglyph {

// --------------------------------------------------------------------------------
#endif
