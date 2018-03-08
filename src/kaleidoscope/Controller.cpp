#include "kaleidoscope/Controller.h"

#include <Arduino.h>

#include KALEIDOSCOPE_HARDWARE_H
#include KALEIDOSCOPE_HARDWARE_KEYBOARD_H
#include "kaleidoscope/hid/Report.h"
#include "kaleidoscope/hooks.h"
#include "kaleidoscope/KeyswitchEvent.h"
#include "kaleidoscope/cKey.h"
#include "kaleidoscope/Key.h"


namespace kaleidoscope {


void Controller::init() {
  //KeyboardHardware.setup();

  // Where is `Keymap keymap` defined? In the sketch?

  // memset() would probably do this faster
  for (Key& key : active_keys_) {
    key = cKey::transparent;
  }
}

void Controller::run() {
  hooks::preScanHooks();
  keyboard_.scanMatrix();

  for (KeyswitchEvent event : keyboard_) {
    if (isMasked(event.addr)) {
      if (event.state.toggledOff())
        active_keys_[event.addr.addr] = cKey::transparent; // unmask(event.addr);
      continue;
    }
    if (event.state.toggledOff()) {
      // key release event
      event.key = active_keys_[event.addr.addr];
      active_keys_[event.addr.addr] = cKey::transparent; // unmask
    } else {
      // non-masked key press event
      event.key = keymap_[event.addr];
      active_keys_[event.addr.addr] = event.key;
    }
    byte caller = 0;
    handleKeyswitchEvent(event, caller); // `0` == Controller is the caller
  }
}

// My big question here is whether to make the first param const and therefore immutable,
// or to let plugins change parts of it (most likely event.key)? The second parameter
// (caller) is there to prevent repeat processing of the same event by any plugin (and
// therefore possible infinite loops)
void Controller::handleKeyswitchEvent(KeyswitchEvent& event, byte caller) {
  if (hooks::keyswitchEventHooks(event, caller)) {
    sendKeyboardReport();
  }
}

// Hooks need to be added here to make it fully-functional
void Controller::sendKeyboardReport() {
  keyboard_report_.clear();
  // Add all active keycodes to the report
  for (Key key : active_keys_) {
    keyboard_report_.add(key);
  }
  keyboard_report_.send();
}

/*
void Controller::sendKeyboardReports() {
  // First, create a (static?) master report adaptor, which contains all the HID
  // reporting. Plugins can interact with that object, but since it's scope is only inside
  // this function, and the master reporter gets passed by reference to the pre-report
  // hooks, plugins can't make the mistake of trying to set values in the report from
  // other hooks. Once the reports are ready, send them all -- maybe this will only apply
  // to the keyboard reports (including consumer & sysctl), not the mouse reports.
  static hid::KeyboardReporter keyboard_report();
  // Clear the report now. It's not accessible to plugins during the event handler hook
  // functions, so anything they need to do to directly interact with the report comes
  // later
  keyboard_report.clear();

  // Loop through all the keys, and add their keycodes to the report
  for (KeyAddr k(0); k < TOTAL_KEYS; ++k) {
    Key mapped_key = active_keys_[k];
    if (mapped_key.isTransparent() || mapped_key.isBlank()) {
      continue;
    }
    keyboard_report.add(mapped_key);
  }

  if (hooks::preKeyboardReportHooks(keyboard_report)) {
    keyboard_report.send();
  }
  hooks::postKeyboardReportHooks();


  // If boot_protocol: send boot keyboard report instead
  hid::keyboard::Report report;
  //hid::keyboard::clearReport();
  for (KeyAddr k; k < TOTAL_KEYS; ++k) {
    Key mapped_key = active_keys_[k];
    // this conditional should probably be in the hid::keyboard::pressKey() code instead
    if (mapped_key != key_transparent && mapped_key != key_none) {
      report.add(mapped_key);
      //hid::keyboard::pressKey(mapped_key);
    }
  }
  if (hooks::preKeyboardReportHooks(report)) {
    hid::keyboard::dispatcher.sendReport(report);
  }
  //hid::keyboard::sendReport();
  hooks::postKeyboardReportHooks();
}
*/

} // namespace kaleidoscope {
