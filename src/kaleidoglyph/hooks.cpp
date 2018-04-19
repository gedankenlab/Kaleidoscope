// -*- c++ -*-

// This file contains function declarations only. The definitions need to be supplied in
// code generated either by preprocessor macros or a pre-build perl script that writes all
// the hook method calls for the sketch based on the plugins that are used.

// I think it will work to put "hooks.cpp" in the sketch module, with the *.ino file.

#include "kaleidoglyph/hooks.h"
#include "kaleidoglyph/KeyswitchEvent.h"
#include "kaleidoglyph/KeyArray.h"
#include "kaleidoglyph/hid/Report.h"


namespace kaleidoglyph {
namespace hooks {

/// Call pre-keyswitch-scan hooks (run every cycle, before keyswitches are scanned)
__attribute__((weak))
void preScanHooks() {}

/// Call keyswitch event handler hooks (run when a key press or release is detected)
///
/// Return true if processing should continue, false if the event has been completely
/// handled, and no further action should take place in response to the event.
__attribute__((weak))
bool keyswitchEventHooks(KeyswitchEvent& event, KeyArray& active_keys, Plugin*& caller) {
  return true;
}

/// Call keyboard HID pre-report hooks (run when a keyboard HID report is about to be sent)
__attribute__((weak))
bool preKeyboardReportHooks(hid::keyboard::Report& keyboard_report) {
  return true;
}

/// Call keyboard HID post-report hooks (run after a keyboard HID report is sent)
__attribute__((weak))
void postKeyboardReportHooks(KeyswitchEvent event) {}

} // namespace hooks {
} // namespace kaleidoglyph {
