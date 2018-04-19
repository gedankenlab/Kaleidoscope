// -*- c++ -*-

#pragma once

#include "kaleidoglyph/Key.h"
#include <assert.h>


namespace kaleidoglyph {

class PluginKey {

 private:
  uint16_t data_ : 14, type_id_ : 2;

 public:
  uint16_t data() const { return data_; }

  PluginKey() : data_ (0),
                type_id_ (Key::plugin_type_id) {}

  constexpr explicit
  PluginKey(byte data) : data_    (data),
                         type_id_ (Key::plugin_type_id) {}

  explicit
  PluginKey(Key key) : data_    (uint16_t(key)      ),
                       type_id_ (uint16_t(key) >> 14)  {
    assert(type_id_ == Key::plugin_type_id);
  }

  constexpr
  operator Key() const {
    return Key( data_          |
                type_id_ << 14   );
  }

  static bool verify(Key key) {
    return ((uint16_t(key) >> 14) == Key::plugin_type_id);
  }
};

} // namespace kaleidoglyph {
