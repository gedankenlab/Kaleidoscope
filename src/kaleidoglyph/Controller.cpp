// -*- c++ -*-

#include "kaleidoglyph/Controller.h"

#include <Arduino.h>

#include "kaleidoglyph/hardware/Keyboard.h"
#include "kaleidoglyph/EventHandlerResult.h"
#include "kaleidoglyph/Key.h"
#include "kaleidoglyph/KeyAddr.h"
#include "kaleidoglyph/KeyEvent.h"
#include "kaleidoglyph/KeyState.h"
#include "kaleidoglyph/cKey.h"
#include <Kaleidoglyph-HID.h>
#include "kaleidoglyph/hooks.h"
#include "kaleidoglyph/utils.h"
#include "kaleidoglyph/KeyEventHandlerId.h"
#include "kaleidoglyph/Bitfield.h"


namespace kaleidoglyph {

// Initialize the timer variable
uint32_t Controller::scan_start_time_{0};

void Controller::init() {

  keyboard_.setup();
  hid_keyboard_dispatcher_.init();
  hid_consumer_dispatcher_.init();
  hid_system_dispatcher_.init();

  for (KeymapEntry entry : active_keys_) {
    active_keys_[entry.addr] = cKey::clear;
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

// Helper class for masking onKeyEvent() plugin hooks that have changed the Key value for
// a given event:
namespace {
typedef Bitfield<KeyEventHandlerId::count, byte> PluginMask;
}

// I'm starting to think that we should just call the sendReport* functions from here,
// rather than scattering the code around
void Controller::handleKeyEvent(KeyEvent event) {

  const KeyAddr& k = event.addr;
  const KeyState& state = event.state;

  if (active_keys_[k] == cKey::masked) {
    if (state.toggledOff()) {
      active_keys_[k] = cKey::clear;
    }
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
      return; // assert(false)?
    }
  }

  // TODO: more than one hook point here. First early hooks, where plugins might intercept
  // & delay events (and maybe promise to always eventually let them through --
  // e.g. Qukeys), then ones that will stop processing if they handle the event
  // (e.g. Keymap), then maybe ones that need a "final" version of the report ready
  // (though that probably moves to the pre-report hook)
  // if (hooks::onKeyEvent(event) != EventHandlerResult::proceed) {
  //   return;
  // }

  // --------------------------------------------------------------------------------

  EventHandlerResult result;

  if (! event.state.isInjected()) {
    result = hooks::onKeyswitchEvent(event);
    if (result == EventHandlerResult::abort) {
      return;
    }
  }

  if (KeyEventHandlerId::count > 0) {
    // plugin_mask exists so that when a plugin restarts the loop below, it gets skipped
    // in the processing of the event (until the loop ends). It prevents infinite looping
    // from a misbehaving plugin. It's a bitfield where each bit represents one plugin. If
    // that plugin's bit is 1, it is masked and will be skipped.
    //byte plugin_mask[bitfieldByteSize(KeyEventHandlerId::count)] = {};
    PluginMask plugin_mask;

    // A mechanism for knowing if a plugin has changed the value of `event.key` in its
    // `onKeyEvent()` handler function:
    Key prev_key{event.key};

    // This loop makes plugin order mostly irrelevant for the onKeyEvent hooks.
    for (byte id{0}; id < KeyEventHandlerId::count; ++id) {
      // If we have more than eight plugins with `onKeyEvent()` handlers, we need byte and
      // bit indices to identify the plugin. Any plugin with its mask bit set is skipped.
      if (plugin_mask.read(id))
        continue;

      result = hooks::onKeyEvent(id, event);
      assert(result != EventHandlerResult::nxplugin);
      if (result == EventHandlerResult::abort) {
        return;
      }
      if (event.key != prev_key) {
        // If the plugin changed the `event.key` value, it gets masked, and processing
        // starts over, so that the first plugin gets a chance to deal with the event with
        // this new `Key` value. This means that plugins need to be able to deal with
        // multiple events that are actually the same event redefined.
        plugin_mask.set(id);
        prev_key = event.key;
        id = 0;
        continue;
      }
    }
  }

  // --------------------------------------------------------------------------------

  
  // Update active_keys_ based on the key state. Note that this is done *after* plugin
  // event handlers have been called, and had a chance to alter the `Key` value.
  if (state.toggledOff()) {
    // I'm not 100% convinced this is what we want, but it's probably the best choice. It
    // means that if a plugin wants to keep a key active on release, it has to return
    // false in its event handler.
    active_keys_[k] = cKey::clear;
  } else if (state.toggledOn()) {
    // One thing I might want to add here is a check for if we get a key press, and
    // there's already an entry in active_keys_[event.addr]. If so, maybe we should first
    // send a release (recursively calling this function...) before continuing to process
    // the current press. This might stop certain bugs from creeping in before then get
    // started. For example, Unshifter tracks the number of shift keys held; if one of
    // them gets released, but that doesn't get counted because there was no release
    // event, it could get out of sync, and think shift is held all the time.
    if (!(active_keys_[k].isEmpty())) {
      handleKeyEvent({k, cKeyState::injected_release});
    }

    active_keys_[k] = event.key;
  }

  // Handle layer shifts and toggles. Maybe this should happen before updating
  // active_keys_, but if we do that, the keymap will need access to active_keys_ to do
  // the update.
  if (isLayerKey(event.key)) {
    keymap_.handleLayerChange(event, active_keys_);
    return;
  }

  if (event.key.isEmpty()) {
    return;
  }

  // Handle keyboard keys. Maybe this should come before the LayerKey test, because this
  // type is expected to be the most common?
  if (isKeyboardKey(event.key)) {
    KeyboardKey keyboard_key{event.key};
    if (event.state.toggledOn() && !keyboard_key.isModifier()) {
      // If a printable keycode was just pressed, we need to override any modifier
      // flags from held keys that would alter the newly-pressed keycode
      mod_flags_allowed_ = keyboard_key.modifierFlags();
    } else {
      mod_flags_allowed_ = 0xFF;
    }
    sendKeyboardReport(event);
    return;
  }

  // Handle Consumer Control key events
  if (isConsumerKey(event.key)) {
    hid::consumer::Report consumer_report;

    for (KeymapEntry entry : active_keys_) {
      if (entry.key == cKey::clear) continue;
      if (isConsumerKey(entry.key)) {
        ConsumerKey consumer_key{entry.key};
        consumer_report.addKeycode(consumer_key.keycode());
      }
    }
    hid_consumer_dispatcher_.sendReport(consumer_report);
    return;
  }

  // Handle System Control key events. There is no Report class here, because the
  // descriptor only allows a single keycode to be sent at once. We send the keycode from
  // the event when a key toggles on, and a zero byte when it toggles off.
  if (isSystemKey(event.key)) {
    SystemKey system_key{event.key};
    if (event.state.toggledOn()) {
      hid_system_dispatcher_.sendReport(system_key.keycode());
    } else {
      hid_system_dispatcher_.sendReport(0);
    }
  }
}

// I think I need to pass the event as a parameter so that I can correctly deal with
// rollover from one `Key_E` to another `Key_E`, sending an extra report without that
// keycode. In order to do that, I think I'll need to change the iterator for KeyArray to
// return a `Key`/`KeyAddr` pair, instead of just the `Key`. That way, we can compare and
// if hmm... maybe not. If `event.key`'s code is already in the report, and it's a
// keypress event... No, that's no good.
void Controller::sendKeyboardReport(const KeyEvent& event) {
  hid::keyboard::Report keyboard_report;
  //report_.clear();
  //kaleidoglyph::hid::releaseAllKeys();
  byte event_keycode{0};
  if (isKeyboardKey(event.key)) {
    event_keycode = KeyboardKey(event.key).keycode();
  }
  bool send_break_report{false};
  // Add all active keycodes to the report
  for (KeymapEntry entry : active_keys_) {

    // Most keys are going to be a no-op:
    if (entry.key == cKey::clear) continue;

    // Next most common should be KeyboardKeys:
    if (isKeyboardKey(entry.key)) {
      KeyboardKey keyboard_key{entry.key};

      byte modifiers = keyboard_key.keycodeModifier();
      byte mod_flags = keyboard_key.modifierFlags();

      if (modifiers == 0) {
        keyboard_report.addKeycode(keyboard_key.keycode());
        modifiers = mod_flags & mod_flags_allowed_;
      } else {
        modifiers |= mod_flags;
      }
      keyboard_report.addModifiers(modifiers);
    }

    // the event was a keypress
    if (event.state.toggledOn()) {
      // the pressed key has the same keycode as this key (should test something different)
      if (event_keycode != 0 && KeyboardKey(entry.key).keycode() == event_keycode) {
        // this key was held, but has the same keycode as the newly-pressed key
        if (entry.addr != event.addr) {
          // send an extra report without event.key
          send_break_report = true;
        }
      }
    }
  }

  if (send_break_report) {
    hid_keyboard_dispatcher_.sendBreakReport(event_keycode);
  }

  if (hooks::preKeyboardReport(keyboard_report))
    hid_keyboard_dispatcher_.sendReport(keyboard_report);
  //kaleidoglyph::hid::sendKeyboardReport();

  // If we call the post-report hooks here, we can also let plugins check what was sent:
  hooks::postKeyboardReport(event);
  //hooks::postKeyboardReport(event, report_);
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
