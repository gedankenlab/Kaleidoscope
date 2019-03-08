// -*- c++ -*-

#pragma once

#include <Arduino.h>
#include <assert.h>

#include "kaleidoglyph/Key.h"


namespace kaleidoglyph {

// This is a template class for plugin-specific keys. Each plugin can define a PluginKey
// type with its own unique `_plugin_id`, which should be overridable via a file
// optionally included from the sketch. The default is for each plugin to use an id that
// is seven bits long. With the first bit being reserved to identify the key as a plugin
// key, that leaves eight bits for plugin data, which is likely to be enough for most
// purposes. If all plugins use this system, that allows up to 128 plugins, each with 256
// unique `Key` values -- far more than anyone could possibly need (and much more than
// most keyboard MCU's could support at one time).
template <uint16_t _plugin_id,
          byte     _data_bits = 8,
          typename _DataType  = byte>
class PluginKey {

  // Honorary template parameters:
  static constexpr _DataType _type_id {
    Key::plugin_type_id << (14 - _data_bits) | _plugin_id
  };
  static constexpr byte _type_id_bits = 16 - _data_bits;

  static constexpr _DataType plugin_id_mask = (uint16_t(~0) >> (_data_bits + 1));
  static constexpr _DataType plugin_id = (_plugin_id & plugin_id_mask);
  static_assert(plugin_id == _plugin_id,
                "_plugin_id cannot use more than six bits");
  static_assert(_data_bits < 14,
                "_data_bits cannot have more than 13 bits");
  static_assert(_type_id < (1 << _type_id_bits),
                "_type_id doesn't fit within _type_id_bits");

 private:
  _DataType data_ : _data_bits, type_id_ : _type_id_bits;

 public:
  _DataType data() const { return data_; }

  PluginKey() : data_(0),
                type_id_(_type_id) {}

  constexpr explicit
  PluginKey(byte data) : data_    (data    ),
                         type_id_ (_type_id)  {}

  explicit
  PluginKey(Key key) : data_    (uint16_t(key)              ),
                       type_id_ (uint16_t(key) >> _data_bits)  {
    assert(type_id_ == _type_id);
  }

  constexpr
  operator Key() const {
    return Key( data_                  |
                type_id_ << _data_bits   );
  }

  static constexpr
  bool verifyType(Key key) const {
    return ((uint16_t(key) >> _data_bits) == _type_id);
  }

};

// Examples:
#if 0
typedef PluginKey<0b0001111> SomePluginKey;
typedef PluginKey<0b0001011_110, 5, uint16_t> SmallPluginKey;
typedef PluginKey<0b100, 12, uint16_t> BigPluginKey;
#endif

} // namespace kaleidoglyph {
