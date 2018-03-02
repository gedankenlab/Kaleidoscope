#include "Kaleidoscope.h"
#include <stdarg.h>

namespace kaleidoscope {

Kaleidoscope_::eventHandlerHook Kaleidoscope_::eventHandlers[HOOK_MAX];
Kaleidoscope_::loopHook Kaleidoscope_::loopHooks[HOOK_MAX];

Kaleidoscope_::Kaleidoscope_(void) {
}

void
Kaleidoscope_::setup(void) {
  KeyboardHardware.setup();

  kaleidoscope::hid::initializeKeyboard();
  kaleidoscope::hid::initializeConsumerControl();
  kaleidoscope::hid::initializeSystemControl();

  // A workaround, so that the compiler does not optimize handleKeyswitchEvent out...
  // This is a no-op, but tricks the compiler into not being too helpful
  // TODO(anyone): figure out how to hint the compiler in a more reasonable way
  //handleKeyswitchEvent(key, KeyAddr{TOTAL_KEYS}, 0);

  // Update the keymap cache, so we start with a non-empty state.
  Layer.updateActiveLayers();
  for (KeyAddr k{0}; k.addr < TOTAL_KEYS; ++k) {
    Layer.updateLiveCompositeKeymap(k);
  }

  for (Key& key : active_keys) {
    key = Key_Transparent;
  }
}

void
Kaleidoscope_::loop(void) {
  KeyboardHardware.scanMatrix();

  for (KeyAddr k{0}; k.addr < TOTAL_KEYS; ++k) {

    byte key_state = KeyboardHardware.nextKeyswitchEvent(k);

    if (key_state == 0)
      break;

    Key key = Key_NoKey;
    if (handleKeyswitchEvent(k, key, key_state)) {

      for (byte i = 0; loopHooks[i] != NULL && i < HOOK_MAX; i++) {
        loopHook hook = loopHooks[i];
        (*hook)(false);
      }

      sendKeyboardHidReport();

      for (byte i = 0; loopHooks[i] != NULL && i < HOOK_MAX; i++) {
        loopHook hook = loopHooks[i];
        (*hook)(true);
      }
    }
  }
}

bool Kaleidoscope_::handleKeyswitchEvent(KeyAddr k, Key& key, byte keyswitch_state) {

  if (active_keys[k.addr] == Key_NoKey) {
    if (keyToggledOff(keyswitch_state))
      active_keys[k.addr] = Key_Transparent;
    return false;
  }

  // TODO: deal with invalid KeyAddrs & injected keys
  if (keyToggledOff(keyswitch_state)) {
    key = active_keys[k.addr];
    active_keys[k.addr] = Key_Transparent;
  } else if (keyToggledOn(keyswitch_state)){
    Layer.updateLiveCompositeKeymap(k);
    key = Layer.lookup(k);
    active_keys[k.addr] = key;
  } else {
    active_keys[k.addr] = Key_Transparent;
    return false;
  }
  for (byte i{0}; eventHandlers[i] != NULL && i < HOOK_MAX; ++i) {
    eventHandlerHook handler = eventHandlers[i];
    key = (*handler)(key, k, keyswitch_state);
    if (key == Key_NoKey)
      return false;
  }
  key = Layer.eventHandler(key, k, keyswitch_state);
  if (key == Key_NoKey)
    return false;
  return true;
}

void Kaleidoscope_::sendKeyboardHidReport() {
  kaleidoscope::hid::releaseAllKeys();
  for (Key key : active_keys) {
    if (key != Key_Transparent && key != Key_NoKey)
      kaleidoscope::hid::pressKey(key);
  }
  kaleidoscope::hid::sendKeyboardReport();
}

void
Kaleidoscope_::replaceEventHandlerHook(eventHandlerHook oldHook, eventHandlerHook newHook) {
  for (byte i = 0; i < HOOK_MAX; i++) {
    if (eventHandlers[i] == oldHook) {
      eventHandlers[i] = newHook;
      return;
    }
  }
}

void
Kaleidoscope_::appendEventHandlerHook(eventHandlerHook hook) {
  replaceEventHandlerHook((eventHandlerHook)NULL, hook);
}

void
Kaleidoscope_::useEventHandlerHook(eventHandlerHook hook) {
  for (byte i = 0; i < HOOK_MAX; i++) {
    if (eventHandlers[i] == hook)
      return;
  }
  appendEventHandlerHook(hook);
}

void
Kaleidoscope_::replaceLoopHook(loopHook oldHook, loopHook newHook) {
  for (byte i = 0; i < HOOK_MAX; i++) {
    if (loopHooks[i] == oldHook) {
      loopHooks[i] = newHook;
      return;
    }
  }
}

void
Kaleidoscope_::appendLoopHook(loopHook hook) {
  replaceLoopHook((loopHook)NULL, hook);
}

void
Kaleidoscope_::useLoopHook(loopHook hook) {
  for (byte i = 0; i < HOOK_MAX; i++) {
    if (loopHooks[i] == hook)
      return;
  }
  appendLoopHook(hook);
}

bool
Kaleidoscope_::focusHook(const char *command) {
  enum {
    ON,
    OFF,
    GETSTATE,
  } subCommand;

  if (strncmp_P(command, PSTR("layer."), 6) != 0)
    return false;

  if (strcmp_P(command + 6, PSTR("on")) == 0)
    subCommand = ON;
  else if (strcmp_P(command + 6, PSTR("off")) == 0)
    subCommand = OFF;
  else if (strcmp_P(command + 6, PSTR("getState")) == 0)
    subCommand = GETSTATE;
  else
    return false;

  switch (subCommand) {
  case ON: {
    uint8_t layer = Serial.parseInt();
    Layer.on(layer);
    break;
  }

  case OFF: {
    uint8_t layer = Serial.parseInt();
    Layer.off(layer);
    break;
  }

  case GETSTATE:
    Serial.println(Layer.getLayerState(), BIN);
    break;
  }

  return true;
}

} // namespace kaleidoscope {

kaleidoscope::Kaleidoscope_ Kaleidoscope;
