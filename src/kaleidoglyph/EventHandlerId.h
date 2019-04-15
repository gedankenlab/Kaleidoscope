// -*- c++ -*-

#pragma once

#if defined(KALEIDOGLYPH_SKETCH_H)
#include KALEIDOGLYPH_SKETCH_H
#endif

#if defined(KALEIDOGLYPH_EVENT_HANDLER_ID_H)
#include KALEIDOGLYPH_EVENT_HANDLER_ID_H
#else

namespace kaleidoglyph {

enum class EventHandlerId : byte {
  controller,
};

}

#endif
