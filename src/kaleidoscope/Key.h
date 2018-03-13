// -*- c++ -*-

#pragma once

#include <Arduino.h>
#include <EEPROM.h>

#include KALEIDOSCOPE_HARDWARE_H
#include KALEIDOSCOPE_KEYADDR_H

#include "KeyFlavor.h" // replace with forward declaration?


namespace kaleidoscope {

// These *_flavor_id constants are used to identify the type of the Key object. Can they
// be defined here, or do they have to go in the *.cpp file?
constexpr byte keyboard_flavor_id { 0b000      };
constexpr byte consumer_flavor_id { 0b001000   };
constexpr byte   system_flavor_id { 0b00100100 };
constexpr byte    mouse_flavor_id { 0b00100101 };
constexpr byte    layer_flavor_id { 0b00101    };
constexpr byte   plugin_flavor_id { 0b01       };

// These mod bits are in the same order as the mod bits in the HID keyboard report for
// efficiency in passing them on. If they get rearranged, that will mess things up.
constexpr byte mod_control { 0b0001 };  // (1 << 0)
constexpr byte mod_shift   { 0b0010 };  // (1 << 1)
constexpr byte mod_alt     { 0b0100 };  // (1 << 2)
constexpr byte mod_gui     { 0b1000 };  // (1 << 3)

union Key {

  // Default key value is cKey::transparent
  uint16_t raw { 0xFFFF };

  // Keyboard key type: 8 bits for keycode, 4 modifier flags, one flag to indicate if the
  // modifiers should apply to the right hand keys instead of the left ones, and three
  // bits for type identification (flavor is all zeros).
  struct {
    uint16_t keycode : 8, mods : 4, mods_right : 1, flavor : 3;
  } keyboard;

  // Consumer Control key type: 10 bits for keycode, 6 for type
  struct {
    uint16_t keycode : 10, flavor : 6;
  } consumer;

  // System Control key type: 8 bits for keycode, 8 for type
  struct {
    uint16_t keycode : 8, flavor : 8;
  } system;

  // Mouse key type: 8 bits for keycode, 8 for type
  struct {
    uint16_t keycode : 8, flavor : 8;
  } mouse;

  // Layer key type: 8 bits for keycode, 8 for type. "keycode" is probably not the best
  // name for the low byte.
  struct {
    uint16_t keycode : 8, meta : 3, flavor : 5;
    // 3 meta bits: 1 for shift/lock, 1 for eeprom/progmem?, 1 for ?
    byte index() { // does this work? If so, does it belong here?
      return byte(keycode);
    }
    byte type() {
      return byte(meta);
    }
  } layer;

  // Plugin key type: only two bits for identifying the type (could be just one), and the
  // rest can be used for identifying plugins, and storing values
  struct {
    uint16_t keycode : 14, flavor : 2;
  } plugin;

  // Constructors
  Key() = default;
  Key(const Key&) = default;

  // The keyword `explicit` here prevents automatic conversion of integers to Key objects
  // in function calls like `foo(27)`, where the function's signature is `foo(Key)`. I
  // think that would be an error, so I'm adding the `explicit` here.
  constexpr explicit Key(uint16_t val)
    : raw{val} {}

  // constexpr Key(int val)
  //   : raw{static_cast<uint16_t>(val)} {}

  // constexpr Key(byte keycode, byte flavor)
  //   : low_byte{keycode}, high_byte{flavor} {}

  // constexpr Key(int keycode, int flavor)
  //   : low_byte{static_cast<byte>(keycode)},
  //     high_byte{static_cast<byte>(flavor)} {}

  void readFromProgmem(const Key& progmem_key) {
    raw = pgm_read_word(&progmem_key);
  }
  void readFromEeprom(uint16_t eeprom_addr) {
    EEPROM.get(eeprom_addr, raw);
  }

  // Actually, I see no point to these being constexpr; that only matters at compile time
  // (I'm pretty sure), and this function is inherently a run-time-only
  // function. Furthermore, they don't need to be here at all; they should be non-member,
  // non-friend functions instead.
  static Key createFromProgmem(const Key& progmem_key) {
    Key new_key;
    new_key.readFromProgmem(progmem_key);
    return new_key;
  }
  static Key createFromEeprom(uint16_t eeprom_addr) {
    Key new_key;
    EEPROM.get(eeprom_addr, new_key);
    return new_key;
  }

  // Very commonly-used test functions. I've decided to use `Blank` instead of `NoKey`
  // because I think it's much clearer, especially in the light of my intention to
  // implement sparse layers. Of course, the hard-coded values must be replaced.
  constexpr bool isTransparent() const {
    return (raw == 0xFFFF);
    //return *this == cKey::transparent;
  }
  constexpr bool isBlank() const {
    return (raw == 0x0000);
    //return *this == cKey::blank;
  }
  constexpr bool isEmpty() const {
    return (this->isTransparent() || this->isBlank());
  }

  // These would be much cleaner if we could use C++14, where we're not restricted to a
  // single statement for constexpr functions:
  static constexpr Key keyboardKey(byte keycode,
                                   byte mods = 0,
                                   bool mods_right = false) {
    // Key key;
    // key.keyboard.flavor     = keyboard_flavor_id;
    // key.keyboard.keycode    = keycode;
    // key.keyboard.mods       = mods;
    // key.keyboard.mods_right = mods_right;
    // return key;
    return Key((uint16_t(keyboard_flavor_id) << 13) + (mods | (mods_right << 4)) + keycode);
  }
  static constexpr Key consumerKey(uint16_t keycode) {
    // Key key;
    // key.consumer.flavor  = consumer_flavor_id;
    // key.consumer.keycode = keycode;
    // return key;
    return Key((consumer_flavor_id << 10) | (0x03FF & keycode));
  }
  static constexpr Key systemKey(byte keycode) {
    // Key key;
    // key.system.flavor  = system_flaver_id;
    // key.system.keycode = keycode;
    // return key;
    return Key((uint16_t(system_flavor_id) << 8) + keycode);
  }
  static constexpr Key mouseKey(byte keycode) {
    // Key key;
    // key.mouse.flavor  = mouse_flaver_id;
    // key.mouse.keycode = keycode;
    // return key;
    return Key((uint16_t(mouse_flavor_id) << 8) + keycode);
  }
  static constexpr Key layerKey(byte keycode, byte meta) {
    // Key key;
    // key.layer.flavor  = layer_flaver_id;
    // key.layer.meta    = meta;
    // key.layer.keycode = keycode;
    // return key;
    return Key((uint16_t(layer_flavor_id) << 11) + (uint16_t(meta) << 8) + keycode);
  }
  static Key pluginKey(uint16_t keycode) {
    // Key key;
    // key.plugin.flavor  = plugin_flaver_id;
    // key.plugin.keycode = keycode;
    // return key;
    return Key((plugin_flavor_id << 14) | (Key{}.plugin.keycode & keycode));
  }

  // Probably should rename to `variety` or some other synonym
  KeyFlavor flavor() const;

  // get a modifiers byte that can be passed to the keyboard HID report directly
  byte mods() const;


  // Comparison operators (Key objects)
  constexpr bool operator==(Key other) const {
    return this->raw == other.raw;
  }
  constexpr bool operator!=(Key other) const {
    return this->raw != other.raw;
  }
  constexpr bool operator>(Key other) const {
    return this->raw > other.raw;
  }
  constexpr bool operator<(Key other) const {
    return this->raw < other.raw;
  }
  constexpr bool operator>=(Key other) const {
    return this->raw >= other.raw;
  }
  constexpr bool operator<=(Key other) const {
    return this->raw <= other.raw;
  }

  // Comparison operators (integers). I don't think these are really necessary, or even
  // desirable; we should remember to cast integers appropriately, instead. There's
  // probably a small benefit in performance, though.
  constexpr bool operator==(uint16_t val) const {
    return this->raw == val;
  }
  constexpr bool operator>=(uint16_t val) const {
    return this->raw >= val;
  }
  constexpr bool operator<=(uint16_t val) const {
    return this->raw <= val;
  }
  constexpr bool operator>(uint16_t val) const {
    return this->raw > val;
  }
  constexpr bool operator<(uint16_t val) const {
    return this->raw < val;
  }

  // Set key value from integer
  Key& operator=(uint16_t val) {
    this->raw = val;
    return *this;
  }
  // These two operators should be useful for decoding offsets
  Key& operator+=(uint16_t val) {
    this->raw += val;
    return *this;
  }
  Key& operator-=(uint16_t val) {
    this->raw -= val;
    return *this;
  }
  // Key object versions
  Key & operator+=(Key other) {
    this->raw += other.raw;
    return *this;
  }
  Key & operator-=(Key other) {
    this->raw -= other.raw;
    return *this;
  }

  // Other arithmetic operators for use with offsets
  constexpr Key operator+(uint16_t val) const {
    return Key(this->raw + val);
  }
  constexpr Key operator-(uint16_t val) const {
    return Key(this->raw + val);
  }
  // Key object versions
  constexpr Key operator+(Key other) const {
    return Key(this->raw + other.raw);
  }
  constexpr Key operator-(Key other) const {
    return Key(this->raw - other.raw);
  }

};

constexpr Key operator+(Key a, Key b) {
  return Key(a.raw + b.raw);
}
constexpr Key operator-(Key a, Key b) {
  return Key(a.raw - b.raw);
}

constexpr Key operator+(uint16_t x, Key key) {
  return Key(x + key.raw);
}
constexpr Key operator+(Key key, uint16_t x) {
  return Key(key.raw + x);
}
constexpr Key operator-(uint16_t x, Key key) {
  return Key(x - key.raw);
}
constexpr Key operator-(Key key, uint16_t x) {
  return Key(key.raw - x);
}

} // namespace kaleidoscope {
