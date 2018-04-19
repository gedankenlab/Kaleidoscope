// -*- c++ -*-

#pragma once

#include <Arduino.h>

#include "kaleidoglyph/Key.h"


namespace kaleidoglyph {
namespace hid {

// A facade on top of our HID implementation

extern void initializeKeyboard();

extern void pressKey(Key key);
extern void releaseKey(Key key);
extern void releaseAllKeys();
extern void pressRawKey(Key key);
extern void releaseRawKey(Key key);
/** Flushes any pending regular key switch events and sends them out */
extern void sendKeyboardReport();

extern uint8_t getKeyboardLEDs();

extern void initializeConsumerControl();

extern void pressConsumerControl(Key key);
extern void releaseConsumerControl(Key key);

extern void initializeSystemControl();

extern void pressSystemControl(Key key);
extern void releaseSystemControl(Key key);

extern void initializeMouse();

extern void moveMouse(signed char x, signed char y, signed char vWheel = 0, signed char hWheel = 0);
extern void clickMouseButtons(uint8_t buttons);
extern void pressMouseButtons(uint8_t buttons);
extern void releaseMouseButtons(uint8_t buttons);
extern void releaseAllMouseButtons(void);
extern void sendMouseReport(void);

extern void initializeAbsoluteMouse();

extern void moveAbsoluteMouse(signed char x, signed char y, signed char wheel);
extern void moveAbsoluteMouseTo(uint16_t x, uint16_t y, signed char wheel);
extern void clickAbsoluteMouseButtons(uint8_t buttons);
extern void pressAbsoluteMouseButtons(uint8_t buttons);
extern void releaseAbsoluteMouseButtons(uint8_t buttons);

}
}
