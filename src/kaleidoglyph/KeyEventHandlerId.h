// -*- c++ -*-

#pragma once

#include KALEIDOGLYPH_SKETCH_H

#if defined(KALEIDOGLYPH_KEY_EVENT_HANDLER_ID_H)
#include KALEIDOGLYPH_KEY_EVENT_HANDLER_ID_H
#else
// If the header isn't defined by the sketch, we assume that there are no plugins, or at
// least none that use the `onKeyEvent()` handler method, so all we need to define is the
// `count` constant (which should be zero):
namespace kaleidoglyph {

class KeyEventHandlerId {
 public:
  static constexpr byte count{0};
};

}
#endif
