// -*- c++ -*-

// This file contains function declarations only. The definitions need to be supplied in
// code generated either by preprocessor macros or a pre-build perl script that writes all
// the hook method calls for the sketch based on the plugins that are used.

// I think it will work to put "hooks.cpp" in the sketch module, with the *.ino file.

#pragma once

#include "kaleidoscope/KeyswitchEvent.h"
#include "kaleidoscope/KeyArray.h"
#include "kaleidoscope/Plugin.h"
#include "kaleidoscope/hid/Report.h"


namespace kaleidoscope {
namespace hooks {

/// Call pre-keyswitch-scan hooks (run every cycle, before keyswitches are scanned)
void preScanHooks();

/// Call keyswitch event handler hooks (run when a key press or release is detected)
bool keyswitchEventHooks(KeyswitchEvent& event, KeyArray& active_keys, Plugin*& caller);

/// Call keyboard HID pre-report hooks (run when a keyboard HID report is about to be sent)
bool preKeyboardReportHooks(hid::keyboard::Report& keyboard_report);

/// Call keyboard HID post-report hooks (run after a keyboard HID report is sent)
//void postKeyboardReportHooks();

} // namespace hooks {
} // namespace kaleidoscope {
