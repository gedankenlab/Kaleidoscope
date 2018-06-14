// -*- c++ -*-

#include "kaleidoglyph/Controller.h"

#include <Arduino.h>

#include KALEIDOGLYPH_HARDWARE_H
#include KALEIDOGLYPH_HARDWARE_KEYBOARD_H
#include "kaleidoglyph/hid/Report.h"
#include "kaleidoglyph/hooks.h"
#include "kaleidoglyph/KeyEvent.h"
#include "kaleidoglyph/cKey.h"
#include "kaleidoglyph/Key.h"


namespace kaleidoglyph {


void Controller::init() {

  keyboard_.setup();
  report_.init();

  for (Key& key : active_keys_) {
    key = cKey::clear;
  }
}

void Controller::run() {

  scan_start_time_ = millis();

  hooks::preKeyswitchScan();

  keyboard_.scanMatrix();

  for (KeyEvent event : keyboard_) {
    handleKeyEvent(event);
  }
}

// I'm starting to think that we should just call the sendReport* functions from here,
// rather than scattering the code around
void Controller::handleKeyEvent(KeyEvent event) {

  const KeyAddr& k = event.addr;
  const KeyState& state = event.state;

  if (active_keys_[k] == cKey::masked) {
    if (state.toggledOff())
      active_keys_[k] = cKey::unmasked;
    return;
  }

  if (event.key.isEmpty()) {
    // TODO: deal with invalid KeyAddrs & injected keys
    if (state.toggledOff()) {
      event.key = active_keys_[k];
    } else if (state.toggledOn()) {
      event.key = keymap_[k];
    } else {
      // TODO: decide what to do if we get a `held` or `idle` state
      //active_keys_[k] = cKey::clear;
      return;
    }
  }

  // TODO: more than one hook point here. First early hooks, where plugins might intercept
  // & delay events (and maybe promise to always eventually let them through --
  // e.g. Qukeys), then ones that will stop processing if they handle the event
  // (e.g. Keymap), then maybe ones that need a "final" version of the report ready
  // (though that probably moves to the pre-report hook)
  if (hooks::onKeyEvent(event) != EventHandlerResult::proceed) {
    return;
  }
  // --------------------------------------------------------------------------------

  EventHandlerResult result;

  if (! event.state.isInjected()) {
    result = hooks::onKeyswitchEvent(event);
    if (result == EventHandlerResult::abort) {
      return;
    }
  }

  PluginMask plugin_mask{};
  Key prev_key{event.key};

  for (byte id{1}; id < plugin_count; ++id) {
    if (plugin_mask.isMasked(id)) continue;

    result = hooks::onKeyEvent(id, event);
    assert(result != EventHandlerResult::nxplugin);
    if (result == EventHandlerResult::abort) {
      return;
    }
    // The following is a more forgiving version, which handles nxplugin results
    // switch (result) {
    //   case EventHandlerResult::nxplugin: // this should never happenxs
    //     plugin_mask.maskPlugin(id);
    //     continue;
    //   case EventHandlerResult::abort:
    //     return;
    //   default:
    //     break;
    // }
    if (event.key != prev_key) {
      plugin_mask.maskPlugin(id);
      prev_key = event.key;
      id = 1;
      continue;
    }
  }

  // --------------------------------------------------------------------------------

  
  // Update active_keys_ based on the key state
  if (state.toggledOff()) {
    // I'm not 100% convinced this is what we want, but it's probably the best choice. It
    // means that if a plugin wants to keep a key active on release, it has to return
    // false in its event handler.
    active_keys_[k] = cKey::clear;
  } else if (state.toggledOn()) {
    active_keys_[k] = event.key;
  }

  // Handle layer shifts and toggles. Maybe this should happen before updating
  // active_keys_, but if we do that, the keymap will need access to active_keys_ to do
  // the update.
  if (LayerKey::verify(event.key)) {
    keymap_.handleLayerChange(event, active_keys_);
    return;
  }

  if (event.key.isEmpty())
    return;

  if (KeyboardKey::verify(event.key)) {
    KeyboardKey keyboard_key{event.key};
    if (event.state.toggledOn() && !keyboard_key.isModifier()) {
      // If a printable keycode was just pressed, we need to override any modifier
      // flags from held keys that would alter the newly-pressed keycode
      mod_flags_allowed_ = keyboard_key.modifierFlags();
    } else {
      mod_flags_allowed_ = 0xFF;
    }
    sendKeyboardReport();
    hooks::postKeyboardReportHooks(event);
    return;
  }
}

// Hooks need to be added here to make it fully-functional
void Controller::sendKeyboardReport() {
  report_.clear();
  //kaleidoglyph::hid::releaseAllKeys();
  // Add all active keycodes to the report
  for (Key key : active_keys_) {
    report_.add(key, mod_flags_allowed_);
    //kaleidoglyph::hid::pressKey(key);
  }
  if (hooks::preKeyboardReportHooks(report_))
    report_.send();
  //kaleidoglyph::hid::sendKeyboardReport();
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
    if (mapped_key != cKey::clear && mapped_key != cKey::blank) {
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

} // namespace kaleidoglyph {
